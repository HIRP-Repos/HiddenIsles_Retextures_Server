/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Data drives (server side).  Every request is resolved against the drive
    physically attached to the requesting player's PDA.

      INTEL      read: returns the drive's intel file (a blank drive is given
                 a random file from IntelFiles.json, weighted).  Admins can
                 write a custom file (ADMIN > INTEL).  Single use: the file
                 can be decrypted once (10 s, client side); when the reader
                 closes it (CONSUME) the drive is ruined for good.  A drive
                 that was decrypted but never closed (PDA closed, player
                 disconnected) burns out the next time anyone looks at it.

      ENCRYPTED  A write-once data drive with three folders:
                   CONVERSATIONS        whole or partial direct / channel chats
                   GROUP CONVERSATIONS  whole or partial group chats
                   IMPORTANT MARKERS    sets of map markers
                 Whoever holds the drive can browse it (no PIN) or wipe it;
                 nobody can add to it.  Message excerpts are copied from the
                 server's own history (the client only sends message numbers),
                 so a drive cannot carry forged messages.
                 EncryptedDriveDays (7) after the write the data degrades:
                 the next read reports a storage integrity failure.

    v8.1: whoever holds a logged-in PDA can write its owner's conversations,
    groups and markers to an Encrypted Drive (a read-only viewer can clone a
    stolen PDA this way).  Every written drive (encrypted and admin intel)
    is recorded with its full contents in Logs\Drives_<day>.jsonl, kept
    DriveLogsDays.
*/

class FENR_PDA_DriveService
{
    static const int STUB_KEEP_DAYS = 30;   // corrupted stubs are deleted this long after decay
    static const int INTEL_BODY = 1000;     // characters in an admin-written intel file
    static const string CORRUPT_TEXT = "Severe Storage Integrity failure detected.\n\nAttempting to retrieve data........\n\nData Corrupted.";

    // Drive key -> write day ("I:<key>" for intel drives).  Negative = already
    // decayed (stub).
    protected static ref map<string, int> s_Written;

    // Intel Drives decrypted and still open in someone's reader: drive key ->
    // GetGame().GetTime() of the decryption.  Memory only.
    protected static ref map<string, int> s_Reading;
    static const int READ_GRACE_MS = 900000;   // an open reader keeps the drive alive at most 15 min

    // ------------------------------------------------------------------
    // Index of written encrypted drives (for the daily decay pass)
    // ------------------------------------------------------------------
    static void Init()
    {
        EnsureIndex();
    }

    protected static string IndexPath()
    {
        return FENR_PDA_Paths.DRIVE_ROOT + "_index.json";
    }

    protected static void EnsureIndex()
    {
        if (s_Written)
            return;
        s_Written = new map<string, int>();
        ref FENR_PDA_KeyIndex index = new FENR_PDA_KeyIndex();
        if (FileExist(IndexPath()))
            JsonFileLoader<ref FENR_PDA_KeyIndex>.JsonLoadFile(IndexPath(), index);
        if (!index || !index.Keys || !index.Days)
            return;
        for (int i = 0; i < index.Keys.Count() && i < index.Days.Count(); i++)
            s_Written.Set(index.Keys[i], index.Days[i]);
    }

    protected static void SaveIndex()
    {
        ref FENR_PDA_KeyIndex index = new FENR_PDA_KeyIndex();
        for (int i = 0; i < s_Written.Count(); i++)
        {
            index.Keys.Insert(s_Written.GetKey(i));
            index.Days.Insert(s_Written.GetElement(i));
        }
        MakeDirectory(FENR_PDA_Paths.DRIVE_ROOT);
        JsonFileLoader<ref FENR_PDA_KeyIndex>.JsonSaveFile(IndexPath(), index);
    }

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------
    static FENR_PDA_DriveBase FindDrive(PlayerIdentity identity, string kind)
    {
        FENR_PDA_DriveBase drive = FindDriveAny(identity, kind);
        if (drive && drive.IsRuined())
            return null;
        return drive;
    }

    // Also returns a ruined drive (dead Intel Drives still show as inserted).
    static FENR_PDA_DriveBase FindDriveAny(PlayerIdentity identity, string kind)
    {
        if (!identity)
            return null;
        FENR_PDA_Device device = FENR_PDA_Server.FindDevice(FENR_PDA_Server.PlayerOf(identity));
        if (!device)
            return null;
        string slot = FENR_PDA_DriveKind.Slot(kind);
        if (slot == "")
            return null;
        return FENR_PDA_DriveBase.Cast(device.FindAttachmentBySlotName(slot));
    }

    // ------------------------------------------------------------------
    // Intel Drives are single use
    // ------------------------------------------------------------------
    // The drive dies: ruined for good, its server data and custom intel go.
    protected static void KillIntel(FENR_PDA_DriveBase drive, string key, FENR_PDA_DriveData data)
    {
        if (data && data.IntelID != "")
        {
            array<string> dead = new array<string>();
            dead.Insert(data.IntelID);
            DropCustomIntel(dead);
        }
        if (drive && !drive.IsRuined())
            drive.SetHealth("", "", 0);
        FENR_PDA_Storage.DeleteDrive(key);
        if (s_Reading)
            s_Reading.Remove(key);
    }

    // true when the drive is dead: already ruined, or decrypted and never
    // closed (it burns out now).
    protected static bool CheckIntel(FENR_PDA_DriveBase drive)
    {
        if (!drive)
            return false;
        if (drive.IsRuined())
            return true;
        string key = drive.FenrGetDriveKey();
        FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(key);
        if (!data || !data.Decoded)
            return false;
        // Still open in the reader of whoever decrypted it.
        if (s_Reading && s_Reading.Contains(key) && GetGame().GetTime() - s_Reading.Get(key) < READ_GRACE_MS)
            return false;
        KillIntel(drive, key, data);
        return true;
    }

    // Daily cleanup: decrypted Intel Drives carried by online players burn out.
    protected static void CheckCarriedIntel()
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player)
                continue;
            array<EntityAI> items = new array<EntityAI>();
            player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
            foreach (EntityAI item : items)
            {
                FENR_PDA_IntelDrive intelDrive = FENR_PDA_IntelDrive.Cast(item);
                if (intelDrive)
                    CheckIntel(intelDrive);
            }
        }
    }

    // The reader closed the decrypted file: the drive burns out.
    protected static bool ConsumeIntel(PlayerIdentity identity, out string info)
    {
        FENR_PDA_DriveBase drive = FindDriveAny(identity, FENR_PDA_DriveKind.INTEL);
        if (!drive)
        {
            info = "The drive was removed.";
            return false;
        }
        if (drive.IsRuined())
        {
            info = "The intel drive burned out.";
            return true;
        }
        string key = drive.FenrGetDriveKey();
        FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(key);
        if (!data || !data.Decoded)
        {
            info = "Nothing was decrypted.";
            return false;
        }
        KillIntel(drive, key, data);
        info = "The intel drive burned out.";
        return true;
    }

    protected static string CleanLine(string text, int maxChars)
    {
        string result = text;
        result.Replace("|", "/");
        result.Replace("\n", " ");
        result = result.Trim();
        if (result.LengthUtf8() > maxChars)
            result = result.SubstringUtf8(0, maxChars);
        return result;
    }

    protected static bool HasContent(FENR_PDA_DriveData data)
    {
        return data && !data.Corrupted && data.Files && data.Files.Count() > 0;
    }

    protected static bool IsExpired(FENR_PDA_DriveData data)
    {
        if (!data || data.WrittenSerial <= 0)
            return false;
        return FENR_PDA_Storage.TodaySerial() - data.WrittenSerial >= FENR_PDA_Storage.EncryptedDriveDays();
    }

    // Data has degraded: keep only a stub so the drive keeps reporting it.
    protected static void Corrupt(string key, FENR_PDA_DriveData data)
    {
        data.Corrupted = true;
        data.Files.Clear();
        FENR_PDA_Storage.SaveDrive(key, data);
        EnsureIndex();
        int day = data.WrittenSerial;
        if (day <= 0)
            day = FENR_PDA_Storage.TodaySerial();
        s_Written.Set(key, -day);
        SaveIndex();
    }

    // Loads an encrypted drive and applies decay.  status: "" ok,
    // "BLANK", or FENR_PDA_DriveLimits.CORRUPT.
    protected static FENR_PDA_DriveData LoadEncrypted(string key, out string status)
    {
        status = "";
        FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(key);
        if (!data || (!data.Corrupted && data.Files.Count() == 0))
        {
            status = "BLANK";
            return data;
        }
        if (!data.Corrupted && IsExpired(data))
            Corrupt(key, data);
        if (data.Corrupted)
            status = FENR_PDA_DriveLimits.CORRUPT;
        return data;
    }

    protected static int FolderCount(FENR_PDA_DriveData data, string folder)
    {
        int count = 0;
        foreach (FENR_PDA_DriveFile file : data.Files)
        {
            if (file && file.Folder == folder) count++;
        }
        return count;
    }

    // ------------------------------------------------------------------
    // Status of both drive slots.  present: "0" none, "1" inserted,
    // "2" inserted and written (encrypted).
    // ------------------------------------------------------------------
    static void BuildStatus(PlayerIdentity identity, array<string> kinds, array<string> present, array<string> summaries)
    {
        kinds.Clear();
        present.Clear();
        summaries.Clear();

        array<string> all = new array<string>();
        all.Insert(FENR_PDA_DriveKind.INTEL);
        all.Insert(FENR_PDA_DriveKind.ENCRYPTED);

        foreach (string kind : all)
        {
            kinds.Insert(kind);
            if (kind == FENR_PDA_DriveKind.INTEL)
            {
                // "3" = inserted but dead.
                FENR_PDA_DriveBase intelDrive = FindDriveAny(identity, kind);
                if (!intelDrive)
                {
                    present.Insert("0");
                    summaries.Insert("NO DRIVE INSERTED");
                }
                else if (CheckIntel(intelDrive))
                {
                    present.Insert("3");
                    summaries.Insert("DRIVE RUINED. The one-time cipher was used: the data is gone.");
                }
                else
                {
                    present.Insert("1");
                    summaries.Insert("ENCRYPTED INTEL. Single use: decrypting it burns out the drive once you close the file.");
                }
                continue;
            }

            FENR_PDA_DriveBase drive = FindDrive(identity, kind);
            if (!drive)
            {
                present.Insert("0");
                summaries.Insert("NO DRIVE INSERTED");
                continue;
            }
            FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(drive.FenrGetDriveKey());

            // "2" = inserted and holding data (write-once: the writer stays closed).
            if (HasContent(data)) present.Insert("2");
            else present.Insert("1");

            if (data && data.Corrupted)
            {
                summaries.Insert("READ ERROR. Data on this drive is unreadable. Wipe it to reuse it.");
            }
            else if (HasContent(data))
            {
                int fileCount = data.Files.Count();
                string writtenDay = data.Written;
                if (writtenDay.Length() > 10)
                    writtenDay = writtenDay.Substring(0, 10);
                summaries.Insert("WRITTEN BY " + data.WrittenBy + "  |  " + fileCount.ToString() + " FILES  |  " + writtenDay + ". Read-only.");
            }
            else
            {
                summaries.Insert("BLANK. Write conversations, group chats or markers to it, then hand it over.");
            }
        }
    }

    // ------------------------------------------------------------------
    // Read
    //   INTEL      payload: title, body
    //   ENCRYPTED  payload: "H|writer|written|files"  then per file
    //              "F|index|folder|name|count|terrain"
    //              info == CORRUPT when the data has degraded.
    // ------------------------------------------------------------------
    static bool Read(PlayerIdentity identity, string kind, out string info, array<string> payload)
    {
        info = "";
        payload.Clear();
        if (kind == FENR_PDA_DriveKind.INTEL)
        {
            FENR_PDA_DriveBase intelDrive = FindDriveAny(identity, kind);
            if (!intelDrive)
            {
                info = "No INTEL drive inserted in your PDA.";
                return false;
            }
            if (CheckIntel(intelDrive))
            {
                // Dead drive (used, or decrypted and never closed): always the same error.
                payload.Insert("STORAGE INTEGRITY FAILURE");
                payload.Insert(CORRUPT_TEXT);
                payload.Insert(FENR_PDA_DriveLimits.CORRUPT);
                info = "Data corrupted. The drive is ruined.";
                return true;
            }
            return ReadIntel(intelDrive.FenrGetDriveKey(), info, payload);
        }

        FENR_PDA_DriveBase drive = FindDrive(identity, kind);
        if (!drive)
        {
            info = "No " + kind + " drive inserted in your PDA.";
            return false;
        }
        string key = drive.FenrGetDriveKey();

        string status;
        FENR_PDA_DriveData data = LoadEncrypted(key, status);
        if (status == "BLANK")
        {
            info = "This drive is blank.";
            return false;
        }
        if (status == FENR_PDA_DriveLimits.CORRUPT)
        {
            info = FENR_PDA_DriveLimits.CORRUPT;
            return false;
        }

        int fileCount = data.Files.Count();
        payload.Insert("H|" + CleanLine(data.WrittenBy, 32) + "|" + CleanLine(data.Written, 32) + "|" + fileCount.ToString());
        for (int i = 0; i < data.Files.Count(); i++)
        {
            FENR_PDA_DriveFile file = data.Files[i];
            if (!file) continue;
            int count = file.Lines.Count();
            if (file.Folder == FENR_PDA_DriveFolder.MARKERS)
                count = file.Markers.Count();
            payload.Insert("F|" + i.ToString() + "|" + file.Folder + "|" + CleanLine(file.Name, 48) + "|" + count.ToString() + "|" + CleanLine(file.Terrain, 48));
        }
        info = "Drive mounted.";
        return true;
    }

    // Decrypts the drive's file (picked from the pool on first use) and
    // marks it decoded: closing it burns the drive out (CONSUME).
    protected static bool ReadIntel(string key, out string info, array<string> payload)
    {
        FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(key);
        array<ref FENR_PDA_IntelFile> pool = FENR_PDA_Storage.LoadIntel();
        if (!data)
        {
            data = new FENR_PDA_DriveData();
            data.Kind = FENR_PDA_DriveKind.INTEL;
        }
        FENR_PDA_IntelFile file = FindIntel(pool, data.IntelID);
        if (!file)
        {
            file = PickIntel(pool);
            if (!file)
            {
                info = "The drive is corrupted. No readable data.";
                return false;
            }
            data.IntelID = file.ID;
            data.Written = FENR_PDA_Storage.Timestamp();
        }
        data.Kind = FENR_PDA_DriveKind.INTEL;
        data.Decoded = true;
        FENR_PDA_Storage.SaveDrive(key, data);
        if (!s_Reading)
            s_Reading = new map<string, int>();
        if (!s_Reading.Contains(key))
            s_Reading.Set(key, GetGame().GetTime());
        payload.Insert(file.Title);
        payload.Insert(file.Body);
        info = "Intel decrypted. The drive burns out when you close the file.";
        return true;
    }

    // One file.  fields: folder, terrain, name, then rows:
    //   conversations / groups  sender, text, time, writer(1/0)  (stride 4)
    //   markers                 name, x, z                      (stride 3)
    static bool ReadDriveFile(PlayerIdentity identity, int index, out string info, array<string> fields)
    {
        info = "";
        fields.Clear();
        FENR_PDA_DriveBase drive = FindDrive(identity, FENR_PDA_DriveKind.ENCRYPTED);
        if (!drive)
        {
            info = "The drive was removed.";
            return false;
        }
        string status;
        FENR_PDA_DriveData data = LoadEncrypted(drive.FenrGetDriveKey(), status);
        if (status == "BLANK")
        {
            info = "This drive is blank.";
            return false;
        }
        if (status != "")
        {
            info = status;
            return false;
        }
        if (index < 0 || index >= data.Files.Count() || !data.Files[index])
        {
            info = "File not found.";
            return false;
        }

        FENR_PDA_DriveFile file = data.Files[index];
        fields.Insert(file.Folder);
        fields.Insert(file.Terrain);
        fields.Insert(file.Name);
        if (file.Folder == FENR_PDA_DriveFolder.MARKERS)
        {
            foreach (FENR_PDA_MapMarker marker : file.Markers)
            {
                if (!marker) continue;
                fields.Insert(marker.Name);
                fields.Insert(marker.X.ToString());
                fields.Insert(marker.Z.ToString());
            }
        }
        else
        {
            foreach (FENR_PDA_DriveLine line : file.Lines)
            {
                if (!line) continue;
                fields.Insert(line.SenderName);
                fields.Insert(line.Message);
                fields.Insert(line.Clock);
                if (line.ByWriter) fields.Insert("1");
                else fields.Insert("0");
            }
        }
        return true;
    }

    // ------------------------------------------------------------------
    // Writer material
    //   GROUPS        fields: id, name                     (stride 2)
    //   GROUP <id>    fields: seq, sender, text, time      (stride 4)
    // ------------------------------------------------------------------
    static void Source(PlayerIdentity identity, string kind, string id, array<string> fields)
    {
        fields.Clear();
        if (!identity)
            return;
        // The groups of the player the open PDA is logged in as.
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (!access)
            return;

        if (kind == "GROUPS")
        {
            array<string> ids = new array<string>();
            array<string> names = new array<string>();
            array<string> owners = new array<string>();
            FENR_PDA_Groups.FillGroupsForMember(access.OwnerID, ids, names, owners);
            for (int i = 0; i < ids.Count() && i < names.Count(); i++)
            {
                fields.Insert(ids[i]);
                fields.Insert(names[i]);
            }
            return;
        }

        if (kind == "GROUP" && FENR_PDA_Groups.IsMemberID(access.OwnerID, id))
        {
            array<ref FENR_PDA_GroupMessage> messages = FENR_PDA_Groups.LoadMessages(id);
            foreach (FENR_PDA_GroupMessage message : messages)
            {
                if (!message) continue;
                fields.Insert(message.Seq.ToString());
                fields.Insert(message.SenderName);
                fields.Insert(message.MessageText);
                fields.Insert(GroupClock(message));
            }
        }
    }

    protected static string GroupClock(FENR_PDA_GroupMessage message)
    {
        if (message.Clock != "")
            return message.Clock;
        if (message.Timestamp.Length() >= 16)
            return message.Timestamp.Substring(11, 5);
        return "";
    }

    // ------------------------------------------------------------------
    // Intel pool
    // ------------------------------------------------------------------
    protected static FENR_PDA_IntelFile FindIntel(array<ref FENR_PDA_IntelFile> pool, string intelID)
    {
        if (intelID == "" || !pool)
            return null;
        foreach (FENR_PDA_IntelFile file : pool)
        {
            if (file && file.ID == intelID)
                return file;
        }
        return null;
    }

    protected static FENR_PDA_IntelFile PickIntel(array<ref FENR_PDA_IntelFile> pool)
    {
        if (!pool || pool.Count() == 0)
            return null;
        int total = 0;
        foreach (FENR_PDA_IntelFile file : pool)
        {
            if (file && file.Weight > 0) total += file.Weight;
        }
        if (total <= 0)
            return pool[Math.RandomInt(0, pool.Count())];
        int roll = Math.RandomInt(0, total);
        foreach (FENR_PDA_IntelFile candidate : pool)
        {
            if (!candidate || candidate.Weight <= 0) continue;
            roll -= candidate.Weight;
            if (roll < 0) return candidate;
        }
        return pool[0];
    }

    // ------------------------------------------------------------------
    // Excerpts (copied from the server's own history)
    // ------------------------------------------------------------------
    protected static int IndexOfChatSeq(array<ref FENR_PDA_ChatMessage> messages, int seq)
    {
        for (int i = 0; i < messages.Count(); i++)
        {
            if (messages[i] && messages[i].m_Seq == seq)
                return i;
        }
        return -1;
    }

    protected static int IndexOfGroupSeq(array<ref FENR_PDA_GroupMessage> messages, int seq)
    {
        for (int i = 0; i < messages.Count(); i++)
        {
            if (messages[i] && messages[i].Seq == seq)
                return i;
        }
        return -1;
    }

    // first/last: message numbers (0, 0 = whole conversation).
    protected static bool CopyChat(array<ref FENR_PDA_ChatMessage> messages, int firstSeq, int lastSeq, string writerID, FENR_PDA_DriveFile file)
    {
        if (!messages || messages.Count() == 0)
            return false;
        int a = 0;
        int b = messages.Count() - 1;
        if (firstSeq != 0 || lastSeq != 0)
        {
            a = IndexOfChatSeq(messages, firstSeq);
            b = IndexOfChatSeq(messages, lastSeq);
            if (a < 0 || b < 0)
                return false;
            if (a > b)
            {
                int swap = a;
                a = b;
                b = swap;
            }
        }
        if (b - a + 1 > FENR_PDA_DriveLimits.LINES)
            a = b - FENR_PDA_DriveLimits.LINES + 1;
        for (int i = a; i <= b; i++)
        {
            FENR_PDA_ChatMessage message = messages[i];
            if (message)
                file.Lines.Insert(new FENR_PDA_DriveLine(message.m_Name, message.m_Message, message.m_Time, message.m_SenderID == writerID));
        }
        return file.Lines.Count() > 0;
    }

    protected static bool CopyGroup(array<ref FENR_PDA_GroupMessage> messages, int firstSeq, int lastSeq, string writerID, FENR_PDA_DriveFile file)
    {
        if (!messages || messages.Count() == 0)
            return false;
        int a = 0;
        int b = messages.Count() - 1;
        if (firstSeq != 0 || lastSeq != 0)
        {
            a = IndexOfGroupSeq(messages, firstSeq);
            b = IndexOfGroupSeq(messages, lastSeq);
            if (a < 0 || b < 0)
                return false;
            if (a > b)
            {
                int swap = a;
                a = b;
                b = swap;
            }
        }
        if (b - a + 1 > FENR_PDA_DriveLimits.LINES)
            a = b - FENR_PDA_DriveLimits.LINES + 1;
        for (int i = a; i <= b; i++)
        {
            FENR_PDA_GroupMessage message = messages[i];
            if (message)
                file.Lines.Insert(new FENR_PDA_DriveLine(message.SenderName, message.MessageText, GroupClock(message), message.SenderID == writerID));
        }
        return file.Lines.Count() > 0;
    }

    // ------------------------------------------------------------------
    // Write / wipe
    //   INTEL (admin)  payload: title, body
    //   ENCRYPTED      payload lines:
    //     "C|conversationID|firstSeq|lastSeq"   conversation excerpt
    //     "G|groupID|firstSeq|lastSeq"          group chat excerpt
    //     "M|terrain"                           starts a marker file ...
    //     "P|name|x|z"                          ... and adds markers to it
    // ------------------------------------------------------------------
    static bool Write(PlayerIdentity identity, string kind, string action, array<string> payload, string extra, out string info)
    {
        info = "";
        if (kind == FENR_PDA_DriveKind.INTEL && action == FENR_PDA_DriveAction.CONSUME)
            return ConsumeIntel(identity, info);
        FENR_PDA_DriveBase drive = FindDrive(identity, kind);
        if (!drive)
        {
            info = "No " + kind + " drive inserted in your PDA.";
            return false;
        }
        string key = drive.FenrGetDriveKey();

        if (action == FENR_PDA_DriveAction.WIPE)
        {
            if (kind == FENR_PDA_DriveKind.INTEL && !FENR_PDA_Admin.IsAuthorized(identity))
            {
                info = "Intel drives are read-only.";
                return false;
            }
            FENR_PDA_Storage.DeleteDrive(key);
            EnsureIndex();
            if (s_Written.Contains(key))
            {
                s_Written.Remove(key);
                SaveIndex();
            }
            info = "Drive wiped.";
            return true;
        }

        if (kind == FENR_PDA_DriveKind.INTEL)
            return WriteIntel(identity, key, payload, info);

        // ENCRYPTED: write once (a degraded drive must be wiped first too).
        string status;
        LoadEncrypted(key, status);
        if (status == "")
        {
            info = "This drive has already been written. Wipe it to reuse it.";
            return false;
        }
        if (status == FENR_PDA_DriveLimits.CORRUPT)
        {
            info = "The data on this drive is corrupted. Wipe it to reuse it.";
            return false;
        }
        if (!payload || payload.Count() == 0)
        {
            info = "Nothing selected to write.";
            return false;
        }

        // Data comes from the player the PDA is logged in as (a read-only
        // viewer clones the owner's data).  "Own" lines are the owner's.
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (!access)
        {
            info = "Log in to your PDA first.";
            return false;
        }
        string accountKey = access.Key();
        string writerID = access.OwnerID;
        ref FENR_PDA_DriveData data = new FENR_PDA_DriveData();
        data.Kind = kind;
        data.WrittenBy = identity.GetName();
        data.WrittenByID = identity.GetPlainId();
        data.Written = FENR_PDA_Storage.Timestamp();
        data.WrittenSerial = FENR_PDA_Storage.TodaySerial();

        FENR_PDA_DriveFile markerFile = null;
        foreach (string line : payload)
        {
            array<string> parts = new array<string>();
            line.Split("|", parts);
            if (parts.Count() < 2)
                continue;
            string tag = parts[0];

            if (tag == "P")
            {
                if (markerFile && parts.Count() >= 4 && markerFile.Markers.Count() < FENR_PDA_DriveLimits.MARKERS)
                    markerFile.Markers.Insert(new FENR_PDA_MapMarker(CleanLine(parts[1], 24), parts[2].ToFloat(), parts[3].ToFloat()));
                continue;
            }

            if (data.Files.Count() >= FENR_PDA_DriveLimits.FILES)
            {
                info = "A drive holds at most " + FENR_PDA_DriveLimits.FILES.ToString() + " files.";
                return false;
            }

            ref FENR_PDA_DriveFile file = new FENR_PDA_DriveFile();
            if (tag == "M")
            {
                file.Folder = FENR_PDA_DriveFolder.MARKERS;
                file.Terrain = CleanLine(parts[1], 48);
                file.Name = "MARKERS";
                markerFile = file;
                data.Files.Insert(file);
                continue;
            }

            markerFile = null;
            if (parts.Count() < 4)
                continue;
            int firstSeq = parts[2].ToInt();
            int lastSeq = parts[3].ToInt();

            if (tag == "C")
            {
                string conversationID = parts[1];
                file.Folder = FENR_PDA_DriveFolder.CONVERSATIONS;
                file.Name = CleanLine(FENR_PDA_AccountStore.ContactName(accountKey, conversationID), 48);
                if (!CopyChat(FENR_PDA_History.Conversation(accountKey, conversationID), firstSeq, lastSeq, writerID, file))
                {
                    info = "Could not copy the conversation with " + file.Name + ". Reopen it and select again.";
                    return false;
                }
                data.Files.Insert(file);
            }
            else if (tag == "G")
            {
                string groupID = parts[1];
                FENR_PDA_Group group = FENR_PDA_Groups.FindGroup(groupID);
                if (!group || !FENR_PDA_Groups.IsMemberID(writerID, groupID))
                {
                    info = "You are not a member of that group.";
                    return false;
                }
                file.Folder = FENR_PDA_DriveFolder.GROUPS;
                file.Name = CleanLine(group.GroupName, 48);
                if (!CopyGroup(FENR_PDA_Groups.LoadMessages(groupID), firstSeq, lastSeq, writerID, file))
                {
                    info = "Could not copy the group chat " + file.Name + ". Reload it and select again.";
                    return false;
                }
                data.Files.Insert(file);
            }
        }

        // Drop marker files that ended up empty.
        for (int f = data.Files.Count() - 1; f >= 0; f--)
        {
            FENR_PDA_DriveFile check = data.Files[f];
            if (check && check.Folder == FENR_PDA_DriveFolder.MARKERS)
            {
                int markerCount = check.Markers.Count();
                if (markerCount == 0)
                    data.Files.RemoveOrdered(f);
                else
                    check.Name = "MARKERS (" + markerCount.ToString() + ")";
            }
        }
        if (data.Files.Count() == 0)
        {
            info = "Nothing selected to write.";
            return false;
        }

        FENR_PDA_Storage.SaveDrive(key, data);
        EnsureIndex();
        s_Written.Set(key, data.WrittenSerial);
        SaveIndex();

        int written = data.Files.Count();
        string cloned = "";
        if (!access.IsOwner)
            cloned = " ClonedFrom=" + access.OwnerID;
        FENR_PDA_Storage.LogSystem("DRIVE_WRITE Encrypted Drive=" + key + " Player=" + identity.GetName() + " Steam64=" + identity.GetPlainId() + cloned + " Files=" + written.ToString());

        // Drive log: who wrote what (full contents).
        ref FENR_PDA_DriveLogRecord logRecord = new FENR_PDA_DriveLogRecord();
        logRecord.Kind = FENR_PDA_DriveKind.ENCRYPTED;
        logRecord.DriveKey = key;
        logRecord.WrittenBy = identity.GetName();
        logRecord.WrittenBySteam64 = identity.GetPlainId();
        if (!access.IsOwner)
            logRecord.ClonedFrom = access.OwnerID;
        logRecord.Data = data;
        FENR_PDA_Storage.LogDrive(logRecord);
        int days = FENR_PDA_Storage.EncryptedDriveDays();
        info = written.ToString() + " files written. The drive is now read-only. Data integrity: " + days.ToString() + " days.";
        return true;
    }

    protected static bool WriteIntel(PlayerIdentity identity, string key, array<string> payload, out string info)
    {
        if (!FENR_PDA_Admin.IsAuthorized(identity))
        {
            info = "Only admins can write intel drives.";
            return false;
        }
        string introTitle = "";
        string introBody = "";
        if (payload && payload.Count() >= 2)
        {
            introTitle = payload[0];
            introBody = payload[1];
            introTitle = introTitle.Trim();
            introBody = introBody.Trim();
        }
        if (introTitle == "" || introBody == "")
        {
            info = "Enter an intel title and body.";
            return false;
        }
        array<ref FENR_PDA_IntelFile> pool = FENR_PDA_Storage.LoadIntel();
        ref FENR_PDA_IntelFile file = new FENR_PDA_IntelFile();
        int now = GetGame().GetTime();
        int salt = Math.RandomInt(1000, 9999);
        file.ID = "intel_" + now.ToString() + "_" + salt.ToString();
        file.Title = CleanLine(introTitle, 48);
        if (introBody.LengthUtf8() > INTEL_BODY) introBody = introBody.SubstringUtf8(0, INTEL_BODY);
        // "|" starts a new line in the admin intel editor.
        introBody.Replace(" | ", "\n");
        introBody.Replace("|", "\n");
        file.Body = introBody;
        file.Weight = 0;   // custom files are never handed out randomly
        pool.Insert(file);
        FENR_PDA_Storage.SaveIntel(pool);

        ref FENR_PDA_DriveData data = new FENR_PDA_DriveData();
        data.Kind = FENR_PDA_DriveKind.INTEL;
        data.WrittenBy = identity.GetName();
        data.WrittenByID = identity.GetPlainId();
        data.Written = FENR_PDA_Storage.Timestamp();
        data.IntelID = file.ID;
        FENR_PDA_Storage.SaveDrive(key, data);
        FENR_PDA_Storage.LogAdmin(identity.GetName(), identity.GetPlainId(), "INTEL_WRITE", file.ID, file.Title);

        ref FENR_PDA_DriveLogRecord logRecord = new FENR_PDA_DriveLogRecord();
        logRecord.Kind = FENR_PDA_DriveKind.INTEL;
        logRecord.DriveKey = key;
        logRecord.WrittenBy = identity.GetName();
        logRecord.WrittenBySteam64 = identity.GetPlainId();
        logRecord.IntelTitle = file.Title;
        logRecord.IntelBody = file.Body;
        FENR_PDA_Storage.LogDrive(logRecord);
        info = "Intel '" + file.Title + "' written to the drive. It can be decrypted once.";
        return true;
    }

    // ------------------------------------------------------------------
    // Daily cleanup: decay old drives, delete long-dead stubs, burn out
    // decrypted Intel Drives that were never closed.
    // ------------------------------------------------------------------
    static void Prune()
    {
        if (!GetGame().IsServer())
            return;
        EnsureIndex();
        CheckCarriedIntel();
        int today = FENR_PDA_Storage.TodaySerial();
        int days = FENR_PDA_Storage.EncryptedDriveDays();
        array<string> decay = new array<string>();
        array<string> expired = new array<string>();
        for (int i = 0; i < s_Written.Count(); i++)
        {
            string entry = s_Written.GetKey(i);
            int day = s_Written.GetElement(i);
            int age = today - Math.AbsInt(day);
            if (day < 0)
            {
                if (age >= days + STUB_KEEP_DAYS)
                    expired.Insert(entry);
            }
            else if (age >= days)
            {
                decay.Insert(entry);
            }
        }

        foreach (string decayKey : decay)
        {
            FENR_PDA_DriveData data = FENR_PDA_Storage.LoadDrive(decayKey);
            if (data)
                Corrupt(decayKey, data);
            else
                s_Written.Remove(decayKey);
        }
        foreach (string expiredKey : expired)
        {
            FENR_PDA_Storage.DeleteDrive(expiredKey);
            s_Written.Remove(expiredKey);
        }
        if (decay.Count() > 0 || expired.Count() > 0)
            SaveIndex();
    }

    // Admin-written intel files (weight 0) are only on one drive each.
    protected static void DropCustomIntel(array<string> intelIDs)
    {
        array<ref FENR_PDA_IntelFile> pool = FENR_PDA_Storage.LoadIntel();
        bool changed = false;
        for (int i = pool.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_IntelFile file = pool[i];
            if (file && file.Weight <= 0 && intelIDs.Find(file.ID) != -1)
            {
                pool.Remove(i);
                changed = true;
            }
        }
        if (changed)
            FENR_PDA_Storage.SaveIntel(pool);
    }
};
