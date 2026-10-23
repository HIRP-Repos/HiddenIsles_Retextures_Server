/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Per-player PDA memory (server side).  v8.1

    A player's contacts, map markers, read marks and S.O.S settings follow
    the player to any PDA they log in on:

        $profile:\PDA\Accounts\A<steam64>.json     one small file per player
        $profile:\PDA\Accounts\_index.json         last login day of every player

    Conversations are not stored here; FENR_PDA_History rebuilds them from
    the message log.  Files are kept in memory and written in batches (every
    30 s and at shutdown).  A player who has not logged in for
    DeviceInactiveDays is erased by the daily cleanup.

    Every write from a client carries the account token it received at sync.
    A token that no longer matches the PDA in the player's hands is refused
    and the client is told to reload; a read-only (guest) session can never
    write.

    Update from v8.0: the per-PDA files in $profile:\PDA\Devices are moved
    once onto the player who used each PDA last.
*/

class FENR_PDA_AccountStore
{
    static const int FLUSH_MS = 30000;
    static const int MAX_CONTACTS = 200;
    static const int MAX_MARKERS = 40;
    static const int MAX_NOTES = 4000;
    static const int FORMAT = 2;
    static const string READ_ONLY = "Read-only access. Log in as yourself to do that.";

    protected static ref map<string, ref FENR_PDA_DeviceMeta> s_Meta;
    protected static ref array<string> s_Dirty;
    protected static ref map<string, int> s_LastUsed;
    protected static bool s_IndexDirty;
    protected static ref array<string> s_FirstLogins;   // players logging in for the first time
    protected static int s_SavedSeq;
    protected static bool s_Initialized;

    // ------------------------------------------------------------------
    // Keys
    // ------------------------------------------------------------------
    static string KeyFor(string steam64)
    {
        if (steam64 == "")
            return "";
        return "A" + steam64;
    }

    // ------------------------------------------------------------------
    // Startup / persistence
    // ------------------------------------------------------------------
    static void Init()
    {
        if (s_Initialized || !GetGame().IsServer())
            return;
        EnsureIndex();
        s_Initialized = true;
        FENR_PDA_History.Build();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Flush, FLUSH_MS, true);
    }

    protected static string IndexPath()
    {
        return FENR_PDA_Paths.ACCOUNT_ROOT + "_index.json";
    }

    protected static string MetaPath(string key)
    {
        return FENR_PDA_Paths.ACCOUNT_ROOT + key + ".json";
    }

    protected static void EnsureIndex()
    {
        if (s_LastUsed)
            return;
        s_Meta = new map<string, ref FENR_PDA_DeviceMeta>();
        s_Dirty = new array<string>();
        s_LastUsed = new map<string, int>();
        MakeDirectory(FENR_PDA_Paths.PROFILE_ROOT);
        MakeDirectory(FENR_PDA_Paths.ACCOUNT_ROOT);

        ref FENR_PDA_KeyIndex index = new FENR_PDA_KeyIndex();
        if (FileExist(IndexPath()))
        {
            JsonFileLoader<ref FENR_PDA_KeyIndex>.JsonLoadFile(IndexPath(), index);
            if (index && index.Keys && index.Days)
            {
                for (int i = 0; i < index.Keys.Count() && i < index.Days.Count(); i++)
                    s_LastUsed.Set(index.Keys[i], index.Days[i]);
            }
            if (index)
            {
                FENR_PDA_History.SetMinNextSeq(index.NextSeq);
                s_SavedSeq = index.NextSeq;
            }
            return;
        }

        // First start on v8.1: move the v8.0 per-PDA memory onto players.
        MigrateDevices();
        SaveIndex();
    }

    protected static void SaveIndex()
    {
        ref FENR_PDA_KeyIndex index = new FENR_PDA_KeyIndex();
        for (int i = 0; i < s_LastUsed.Count(); i++)
        {
            index.Keys.Insert(s_LastUsed.GetKey(i));
            index.Days.Insert(s_LastUsed.GetElement(i));
        }
        index.NextSeq = FENR_PDA_History.PeekNextSeq();
        index.Format = FORMAT;
        s_SavedSeq = index.NextSeq;
        MakeDirectory(FENR_PDA_Paths.ACCOUNT_ROOT);
        JsonFileLoader<ref FENR_PDA_KeyIndex>.JsonSaveFile(IndexPath(), index);
        s_IndexDirty = false;
    }

    protected static void MarkDirty(string key)
    {
        if (key != "" && s_Dirty.Find(key) == -1)
            s_Dirty.Insert(key);
    }

    // Writes changed player files (timer, and at mission end).
    static void Flush()
    {
        if (!s_LastUsed)
            return;
        if (s_Dirty.Count() > 0)
        {
            MakeDirectory(FENR_PDA_Paths.ACCOUNT_ROOT);
            foreach (string key : s_Dirty)
            {
                FENR_PDA_DeviceMeta meta = s_Meta.Get(key);
                if (meta)
                    JsonFileLoader<ref FENR_PDA_DeviceMeta>.JsonSaveFile(MetaPath(key), meta);
            }
            s_Dirty.Clear();
        }
        if (FENR_PDA_History.PeekNextSeq() != s_SavedSeq)
            s_IndexDirty = true;
        if (s_IndexDirty)
            SaveIndex();
    }

    // ------------------------------------------------------------------
    // v8.0 -> v8.1 migration (runs once, when no account index exists)
    // ------------------------------------------------------------------
    protected static string OldDevicePath(string deviceKey)
    {
        return FENR_PDA_Paths.DEVICE_ROOT + deviceKey + ".json";
    }

    protected static string OldLegacyPath(string deviceKey)
    {
        return FENR_PDA_Paths.DEVICE_ROOT + deviceKey + "\\meta.json";
    }

    protected static void MigrateDevices()
    {
        string oldIndex = FENR_PDA_Paths.DEVICE_ROOT + "_index.json";
        if (!FileExist(oldIndex))
            return;
        ref FENR_PDA_KeyIndex legacyIndex = new FENR_PDA_KeyIndex();
        JsonFileLoader<ref FENR_PDA_KeyIndex>.JsonLoadFile(oldIndex, legacyIndex);
        if (!legacyIndex || !legacyIndex.Keys || !legacyIndex.Days)
            return;

        FENR_PDA_History.SetMinNextSeq(legacyIndex.NextSeq);

        // Temporary PDA keys that later became persistent keys.
        map<string, string> aliases = new map<string, string>();
        if (legacyIndex.AliasFrom && legacyIndex.AliasTo)
        {
            for (int a = 0; a < legacyIndex.AliasFrom.Count() && a < legacyIndex.AliasTo.Count(); a++)
                aliases.Set(legacyIndex.AliasFrom[a], legacyIndex.AliasTo[a]);
        }

        // The PDA each player used last (v8.0 kept this for offline delivery).
        map<string, string> lastDevice = new map<string, string>();
        if (legacyIndex.PlayerIDs && legacyIndex.PlayerKeys)
        {
            for (int p = 0; p < legacyIndex.PlayerIDs.Count() && p < legacyIndex.PlayerKeys.Count(); p++)
            {
                string usedKey = legacyIndex.PlayerKeys[p];
                if (aliases.Contains(usedKey))
                    usedKey = aliases.Get(usedKey);
                lastDevice.Set(legacyIndex.PlayerIDs[p], usedKey);
            }
        }

        // Pick one PDA per player: the one they used last, else the most
        // recently used PDA they were the last user of.
        map<string, ref FENR_PDA_DeviceMeta> chosen = new map<string, ref FENR_PDA_DeviceMeta>();
        map<string, int> chosenDay = new map<string, int>();
        map<string, bool> chosenExact = new map<string, bool>();
        array<string> oldFiles = new array<string>();
        for (int i = 0; i < legacyIndex.Keys.Count() && i < legacyIndex.Days.Count(); i++)
        {
            string deviceKey = legacyIndex.Keys[i];
            int day = legacyIndex.Days[i];
            string path = OldDevicePath(deviceKey);
            if (!FileExist(path))
                path = OldLegacyPath(deviceKey);
            if (!FileExist(path))
                continue;
            oldFiles.Insert(path);

            ref FENR_PDA_DeviceMeta meta = new FENR_PDA_DeviceMeta();
            JsonFileLoader<ref FENR_PDA_DeviceMeta>.JsonLoadFile(path, meta);
            if (!meta || meta.LastUser == "")
                continue;
            string user = meta.LastUser;
            bool exact = lastDevice.Get(user) == deviceKey;
            if (chosen.Contains(user))
            {
                if (chosenExact.Get(user))
                    continue;
                if (!exact && day <= chosenDay.Get(user))
                    continue;
            }
            chosen.Set(user, meta);
            chosenDay.Set(user, day);
            chosenExact.Set(user, exact);
        }

        int moved = 0;
        for (int c = 0; c < chosen.Count(); c++)
        {
            string steam64 = chosen.GetKey(c);
            FENR_PDA_DeviceMeta source = chosen.GetElement(c);
            string key = KeyFor(steam64);
            Normalize(source);
            source.LastUser = steam64;
            int lastDay = chosenDay.Get(steam64);
            if (lastDay <= 0)
                lastDay = FENR_PDA_Storage.TodaySerial();
            source.LastUsed = lastDay;
            s_Meta.Set(key, source);
            s_LastUsed.Set(key, lastDay);
            MarkDirty(key);
            moved++;
        }
        Flush();

        // The old per-PDA files are no longer used.
        foreach (string oldFile : oldFiles)
        {
            if (FileExist(oldFile))
                DeleteFile(oldFile);
        }
        DeleteFile(oldIndex);
        FENR_PDA_Storage.LogSystem("v8.1 update: moved PDA memory of " + moved.ToString() + " players from Devices to Accounts.");
    }

    protected static void Normalize(FENR_PDA_DeviceMeta meta)
    {
        if (!meta.Contacts) meta.Contacts = new array<ref FENR_PDA_Contact>();
        if (!meta.MarkerSets) meta.MarkerSets = new array<ref FENR_PDA_TerrainMarkers>();
        if (!meta.ClearedIDs) meta.ClearedIDs = new array<string>();
        if (!meta.ClearedSeq) meta.ClearedSeq = new array<int>();
        if (!meta.ReadIDs) meta.ReadIDs = new array<string>();
        if (!meta.ReadSeq) meta.ReadSeq = new array<int>();
        if (!meta.SosTargets) meta.SosTargets = new array<string>();
    }

    // ------------------------------------------------------------------
    // Meta
    // ------------------------------------------------------------------
    static bool IsKnown(string key)
    {
        if (key == "")
            return false;
        EnsureIndex();
        if (s_LastUsed.Contains(key) || s_Meta.Contains(key))
            return true;
        return FileExist(MetaPath(key));
    }

    static FENR_PDA_DeviceMeta Meta(string key, bool create)
    {
        if (key == "")
            return null;
        EnsureIndex();
        FENR_PDA_DeviceMeta cached = s_Meta.Get(key);
        if (cached)
            return cached;
        if (!create && !IsKnown(key))
            return null;

        ref FENR_PDA_DeviceMeta meta = new FENR_PDA_DeviceMeta();
        string path = MetaPath(key);
        if (FileExist(path))
            JsonFileLoader<ref FENR_PDA_DeviceMeta>.JsonLoadFile(path, meta);
        if (!meta)
            meta = new FENR_PDA_DeviceMeta();
        Normalize(meta);
        s_Meta.Set(key, meta);

        if (!s_LastUsed.Contains(key))
        {
            int day = meta.LastUsed;
            if (day <= 0)
                day = FENR_PDA_Storage.TodaySerial();
            s_LastUsed.Set(key, day);
            s_IndexDirty = true;
            MarkDirty(key);
        }
        return meta;
    }

    // Called before Touch() on login: remembers players who have no memory
    // yet (their pre-7.8 local files are copied once, see BuildSync).
    static void NoteLogin(string steam64)
    {
        if (!s_FirstLogins)
            s_FirstLogins = new array<string>();
        if (steam64 != "" && !IsKnown(KeyFor(steam64)) && s_FirstLogins.Find(steam64) == -1)
            s_FirstLogins.Insert(steam64);
    }

    protected static bool TakeFirstLogin(string steam64)
    {
        if (!s_FirstLogins || s_FirstLogins.Find(steam64) == -1)
            return false;
        s_FirstLogins.RemoveItem(steam64);
        return true;
    }

    // A player logged in or used their PDA today.
    static void Touch(string steam64)
    {
        string key = KeyFor(steam64);
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        if (!meta)
            return;
        int today = FENR_PDA_Storage.TodaySerial();
        if (meta.LastUsed != today || meta.LastUser != steam64)
        {
            meta.LastUsed = today;
            meta.LastUser = steam64;
            MarkDirty(key);
        }
        if (s_LastUsed.Get(key) != today)
        {
            s_LastUsed.Set(key, today);
            s_IndexDirty = true;
        }
    }

    // ------------------------------------------------------------------
    // Request checks
    // ------------------------------------------------------------------
    // Checks the client's account token against the PDA in the player's
    // hands.  On mismatch the client is told to reload and "" is returned.
    // write: the request changes something (refused for read-only access;
    // `quiet` skips the notice, e.g. for read marks).
    static string Authorize(PlayerIdentity identity, string token, bool write, bool quiet = false)
    {
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (!access || token == "" || token != access.Key())
        {
            if (identity)
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_RESYNC, new Param1<bool>(true), true, identity);
            return "";
        }
        if (write && !access.IsOwner)
        {
            if (!quiet)
                FENR_PDA_Server.Deny(identity, READ_ONLY);
            return "";
        }
        return access.Key();
    }

    // ------------------------------------------------------------------
    // Read marks for shared histories (channels and group chats)
    // ------------------------------------------------------------------
    static string ChannelReadID(string channelID)
    {
        return "CH:" + channelID;
    }

    static string GroupReadID(string groupID)
    {
        return "GR:" + groupID;
    }

    protected static int ReadMark(FENR_PDA_DeviceMeta meta, string readID)
    {
        int index = meta.ReadIDs.Find(readID);
        if (index < 0 || index >= meta.ReadSeq.Count())
            return -1;
        return meta.ReadSeq[index];
    }

    protected static void SetReadMark(string key, FENR_PDA_DeviceMeta meta, string readID, int seq)
    {
        int index = meta.ReadIDs.Find(readID);
        if (index >= 0 && index < meta.ReadSeq.Count())
        {
            if (meta.ReadSeq[index] == seq)
                return;
            meta.ReadSeq.Set(index, seq);
        }
        else
        {
            meta.ReadIDs.Insert(readID);
            meta.ReadSeq.Insert(seq);
        }
        MarkDirty(key);
    }

    protected static int GroupLastSeq(string groupID)
    {
        array<ref FENR_PDA_GroupMessage> messages = FENR_PDA_Groups.LoadMessages(groupID);
        if (!messages || messages.Count() == 0 || !messages[messages.Count() - 1])
            return 0;
        return messages[messages.Count() - 1].Seq;
    }

    // Unread channel lines since the player last looked.  The first time a
    // player sees a channel, it starts as read (only the owner sets marks).
    static int ChannelUnread(string key, string channelID, string viewerID, bool canMark)
    {
        FENR_PDA_DeviceMeta meta = Meta(key, false);
        if (!meta)
            return 0;
        string readID = ChannelReadID(channelID);
        int mark = ReadMark(meta, readID);
        if (mark < 0)
        {
            if (canMark)
                SetReadMark(key, meta, readID, FENR_PDA_History.LastSeq(channelID));
            return 0;
        }
        return FENR_PDA_History.CountAfter(FENR_PDA_History.Conversation(key, channelID), mark, viewerID);
    }

    static int GroupUnread(string key, string groupID, string viewerID, bool canMark)
    {
        FENR_PDA_DeviceMeta meta = Meta(key, false);
        if (!meta)
            return 0;
        string readID = GroupReadID(groupID);
        int mark = ReadMark(meta, readID);
        if (mark < 0)
        {
            if (canMark)
                SetReadMark(key, meta, readID, GroupLastSeq(groupID));
            return 0;
        }
        int count = 0;
        array<ref FENR_PDA_GroupMessage> messages = FENR_PDA_Groups.LoadMessages(groupID);
        foreach (FENR_PDA_GroupMessage message : messages)
        {
            if (message && message.Seq > mark && message.SenderID != viewerID && message.SenderID != "SYSTEM")
                count++;
        }
        return count;
    }

    static void MarkChannelRead(string key, string channelID)
    {
        FENR_PDA_DeviceMeta meta = Meta(key, false);
        if (meta)
            SetReadMark(key, meta, ChannelReadID(channelID), FENR_PDA_History.LastSeq(channelID));
    }

    static void MarkGroupRead(string key, string groupID)
    {
        FENR_PDA_DeviceMeta meta = Meta(key, false);
        if (meta)
            SetReadMark(key, meta, GroupReadID(groupID), GroupLastSeq(groupID));
    }

    // ------------------------------------------------------------------
    // Contacts
    // ------------------------------------------------------------------
    protected static FENR_PDA_Contact FindContactIn(FENR_PDA_DeviceMeta meta, string contactID)
    {
        if (!meta)
            return null;
        foreach (FENR_PDA_Contact contact : meta.Contacts)
        {
            if (contact && contact.m_UID == contactID)
                return contact;
        }
        return null;
    }

    static bool HasContact(string key, string contactID)
    {
        return FindContactIn(Meta(key, false), contactID) != null;
    }

    protected static string CleanName(string name)
    {
        string result = name.Trim();
        if (result.LengthUtf8() > FENR_PDA_Limits.CONTACT_NAME)
            result = result.SubstringUtf8(0, FENR_PDA_Limits.CONTACT_NAME);
        return result;
    }

    static string ContactName(string key, string contactID)
    {
        if (FENR_PDA_ChannelIds.IsChannel(contactID))
            return FENR_PDA_ChannelIds.Label(contactID);
        FENR_PDA_Contact contact = FindContactIn(Meta(key, false), contactID);
        if (contact && contact.m_Name != "")
            return contact.m_Name;
        string known = FENR_PDA_Storage.ResolvePlayerName(contactID);
        if (known != "")
            return known;
        return contactID;
    }

    // `steam64` has `contactID` blocked.
    static bool IsBlockedBy(string steam64, string contactID)
    {
        FENR_PDA_Contact contact = FindContactIn(Meta(KeyFor(steam64), false), contactID);
        return contact && contact.m_IsBanned;
    }

    static int ClearedSeq(string key, string conversationID)
    {
        FENR_PDA_DeviceMeta meta = Meta(key, false);
        if (!meta)
            return 0;
        int index = meta.ClearedIDs.Find(conversationID);
        if (index < 0 || index >= meta.ClearedSeq.Count())
            return 0;
        return meta.ClearedSeq[index];
    }

    protected static FENR_PDA_TerrainMarkers MarkerSetFor(FENR_PDA_DeviceMeta meta, string terrain, bool create)
    {
        string wanted = terrain;
        wanted.ToLower();
        foreach (FENR_PDA_TerrainMarkers markerSet : meta.MarkerSets)
        {
            if (!markerSet) continue;
            string name = markerSet.TerrainName;
            name.ToLower();
            if (name == wanted)
                return markerSet;
        }
        if (!create)
            return null;
        ref FENR_PDA_TerrainMarkers created = new FENR_PDA_TerrainMarkers();
        created.TerrainName = terrain;
        meta.MarkerSets.Insert(created);
        return created;
    }

    // ------------------------------------------------------------------
    // Message delivery (called by FENR_PDA_Messages)
    // ------------------------------------------------------------------
    // ownerID's copy of a direct message: makes sure the other side is in
    // their contacts and counts it as unread when incoming.
    static void OnDirectMessage(string ownerID, string conversationID, string contactName, bool incoming)
    {
        if (ownerID == "" || conversationID == "")
            return;
        if (FENR_PDA_ChannelIds.IsChannel(conversationID) || FENR_PDA_Server.IsTestAccount(conversationID))
            return;

        string key = KeyFor(ownerID);
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        FENR_PDA_Contact contact = FindContactIn(meta, conversationID);
        if (!contact)
        {
            if (meta.Contacts.Count() >= MAX_CONTACTS)
                return;
            string name = CleanName(contactName);
            if (name == "")
                name = conversationID;
            contact = new FENR_PDA_Contact(conversationID, name, true);
            meta.Contacts.Insert(contact);
        }
        if (incoming)
            contact.m_Unreaded = contact.m_Unreaded + 1;
        MarkDirty(key);
    }

    // ------------------------------------------------------------------
    // Client sync for the PDA in the player's hands
    //   contacts: uid, name, unread, banned(1/0), muted(1/0)  (stride 5)
    //   markers:  name, x, z                                   (stride 3)
    // Returns the account token ("" = locked / no PDA).
    // ------------------------------------------------------------------
    static string BuildSync(PlayerIdentity identity, string terrain, array<string> contactFields, out string notes, array<string> markerFields, out bool isNew)
    {
        contactFields.Clear();
        markerFields.Clear();
        notes = "";
        isNew = false;

        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (!access)
            return "";
        string key = access.Key();

        FENR_PDA_DeviceMeta meta = Meta(key, true);
        // Never copy a guest's legacy files onto someone else.
        if (access.IsOwner)
        {
            isNew = TakeFirstLogin(access.OwnerID);
            Touch(access.OwnerID);
        }

        foreach (FENR_PDA_Contact contact : meta.Contacts)
        {
            if (!contact) continue;
            contactFields.Insert(contact.m_UID);
            contactFields.Insert(contact.m_Name);
            contactFields.Insert(contact.m_Unreaded.ToString());
            if (contact.m_IsBanned) contactFields.Insert("1");
            else contactFields.Insert("0");
            if (contact.m_IsMuted) contactFields.Insert("1");
            else contactFields.Insert("0");
        }
        // Public channels: unread lines since the player last looked.
        array<string> channels = new array<string>();
        channels.Insert(FENR_PDA_ChannelIds.ANNOUNCEMENTS);
        channels.Insert(FENR_PDA_ChannelIds.GLOBAL);
        channels.Insert(FENR_PDA_ChannelIds.BUY_SELL);
        foreach (string channelID : channels)
        {
            int channelUnread = ChannelUnread(key, channelID, access.OwnerID, access.IsOwner);
            contactFields.Insert(channelID);
            contactFields.Insert(FENR_PDA_ChannelIds.Label(channelID));
            contactFields.Insert(channelUnread.ToString());
            contactFields.Insert("0");
            contactFields.Insert("0");
        }
        notes = meta.Notes;
        MarkerFields(meta, terrain, markerFields);
        return key;
    }

    protected static void MarkerFields(FENR_PDA_DeviceMeta meta, string terrain, array<string> fields)
    {
        FENR_PDA_TerrainMarkers markerSet = MarkerSetFor(meta, terrain, false);
        if (!markerSet)
            return;
        foreach (FENR_PDA_MapMarker marker : markerSet.Markers)
        {
            if (!marker) continue;
            fields.Insert(marker.Name);
            fields.Insert(marker.X.ToString());
            fields.Insert(marker.Z.ToString());
        }
    }

    static void ConvoFields(PlayerIdentity identity, string token, string conversationID, array<string> output)
    {
        output.Clear();
        string key = Authorize(identity, token, false);
        if (key == "")
            return;
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        FENR_PDA_History.Fields(FENR_PDA_History.Conversation(key, conversationID), access.OwnerID, access.OwnerName, output);
    }

    static void ContactOp(PlayerIdentity identity, string token, string op, string contactID, string value)
    {
        // Read marks from a read-only viewer are dropped quietly: the owner
        // still sees them as unread.
        bool readMark = op == FENR_PDA_ContactOp.READ;
        string key = Authorize(identity, token, true, readMark);
        if (key == "" || contactID == "")
            return;

        if (readMark && FENR_PDA_ChannelIds.IsChannel(contactID))
        {
            MarkChannelRead(key, contactID);
            return;
        }
        if (readMark && contactID.IndexOf("GR:") == 0)
        {
            string groupID = contactID.Substring(3, contactID.Length() - 3);
            if (FENR_PDA_Groups.IsMember(identity, groupID))
                MarkGroupRead(key, groupID);
            return;
        }
        if (FENR_PDA_ChannelIds.IsChannel(contactID))
            return;

        FENR_PDA_DeviceMeta meta = Meta(key, true);
        FENR_PDA_Contact contact = FindContactIn(meta, contactID);

        if (op == FENR_PDA_ContactOp.ADD)
        {
            if (contact || meta.Contacts.Count() >= MAX_CONTACTS || FENR_PDA_Server.IsTestAccount(contactID))
                return;
            string name = CleanName(value);
            if (name == "")
                name = contactID;
            meta.Contacts.Insert(new FENR_PDA_Contact(contactID, name, true));
        }
        else if (op == FENR_PDA_ContactOp.REMOVE)
        {
            if (contact)
                meta.Contacts.RemoveItem(contact);
            meta.SosTargets.RemoveItem(contactID);
            // Hide everything up to now, even after a restart rebuild.
            int cleared = FENR_PDA_History.PeekNextSeq() - 1;
            int index = meta.ClearedIDs.Find(contactID);
            if (index >= 0 && index < meta.ClearedSeq.Count())
            {
                meta.ClearedSeq.Set(index, cleared);
            }
            else
            {
                meta.ClearedIDs.Insert(contactID);
                meta.ClearedSeq.Insert(cleared);
            }
            FENR_PDA_History.ClearConversation(key, contactID);
        }
        else
        {
            if (!contact)
                return;
            if (op == FENR_PDA_ContactOp.RENAME)
            {
                string renamed = CleanName(value);
                if (renamed == "")
                    return;
                contact.m_Name = renamed;
            }
            else if (op == FENR_PDA_ContactOp.BLOCK)
                contact.m_IsBanned = value == "1";
            else if (op == FENR_PDA_ContactOp.MUTE)
                contact.m_IsMuted = value == "1";
            else if (op == FENR_PDA_ContactOp.READ)
                contact.m_Unreaded = 0;
            else
                return;
        }
        MarkDirty(key);
    }

    static void SaveNotes(PlayerIdentity identity, string token, string notes)
    {
        string key = Authorize(identity, token, true);
        if (key == "")
            return;
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        string clean = notes;
        if (clean.LengthUtf8() > MAX_NOTES)
            clean = clean.SubstringUtf8(0, MAX_NOTES);
        if (meta.Notes == clean)
            return;
        meta.Notes = clean;
        MarkDirty(key);
    }

    static void SaveMarkers(PlayerIdentity identity, string token, string terrain, array<string> fields)
    {
        string key = Authorize(identity, token, true);
        if (key == "" || terrain == "" || !fields)
            return;
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        FENR_PDA_TerrainMarkers markerSet = MarkerSetFor(meta, terrain, true);
        markerSet.Markers.Clear();
        for (int i = 0; i + 3 <= fields.Count(); i += 3)
        {
            if (markerSet.Markers.Count() >= MAX_MARKERS) break;
            string name = fields[i];
            if (name.LengthUtf8() > 24) name = name.SubstringUtf8(0, 24);
            markerSet.Markers.Insert(new FENR_PDA_MapMarker(name, fields[i + 1].ToFloat(), fields[i + 2].ToFloat()));
        }
        MarkDirty(key);
    }

    // ------------------------------------------------------------------
    // S.O.S recipients (stored with the player)
    // ------------------------------------------------------------------
    static bool GetSos(PlayerIdentity identity, string token, out string mode, array<string> targets, out string groupID)
    {
        mode = "CONTACTS";
        groupID = "";
        targets.Clear();
        string key = Authorize(identity, token, false);
        if (key == "")
            return false;
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        if (meta.SosMode == "GROUP")
            mode = "GROUP";
        groupID = meta.SosGroup;
        foreach (string target : meta.SosTargets)
        {
            if (FindContactIn(meta, target))
                targets.Insert(target);
        }
        return true;
    }

    static void SetSos(PlayerIdentity identity, string token, string mode, array<string> targets, string groupID)
    {
        string key = Authorize(identity, token, true);
        if (key == "")
            return;
        FENR_PDA_DeviceMeta meta = Meta(key, true);
        if (mode == "GROUP") meta.SosMode = "GROUP";
        else meta.SosMode = "CONTACTS";

        meta.SosTargets.Clear();
        int limit = FENR_PDA_Storage.SosMaxContacts();
        if (targets)
        {
            foreach (string target : targets)
            {
                if (meta.SosTargets.Count() >= limit) break;
                if (target == "" || meta.SosTargets.Find(target) != -1) continue;
                if (!FindContactIn(meta, target) || FENR_PDA_Server.IsTestAccount(target)) continue;
                meta.SosTargets.Insert(target);
            }
        }

        meta.SosGroup = "";
        if (groupID != "" && FENR_PDA_Groups.IsMember(identity, groupID))
            meta.SosGroup = groupID;
        MarkDirty(key);
    }

    // Markers shown on the compass HUD of the PDA a player is using
    // (read-only; a guest sees the owner's markers).
    static void HudMarkers(PlayerIdentity identity, string terrain, array<string> fields)
    {
        fields.Clear();
        FENR_PDA_Access access = FENR_PDA_Sessions.ActiveAccessOf(identity);
        if (!access)
            return;
        FENR_PDA_DeviceMeta meta = Meta(access.Key(), false);
        if (meta)
            MarkerFields(meta, terrain, fields);
    }

    // ------------------------------------------------------------------
    // Daily cleanup: erase players who have not logged in for `days` days.
    // ------------------------------------------------------------------
    static void Prune(int days)
    {
        if (days <= 0 || !GetGame().IsServer())
            return;
        EnsureIndex();
        int today = FENR_PDA_Storage.TodaySerial();
        array<string> stale = new array<string>();
        for (int i = 0; i < s_LastUsed.Count(); i++)
        {
            if (today - s_LastUsed.GetElement(i) >= days)
                stale.Insert(s_LastUsed.GetKey(i));
        }
        if (stale.Count() == 0)
            return;

        foreach (string key : stale)
        {
            s_LastUsed.Remove(key);
            s_Meta.Remove(key);
            s_Dirty.RemoveItem(key);
            if (FileExist(MetaPath(key)))
                DeleteFile(MetaPath(key));
            FENR_PDA_History.DropDevice(key);
        }

        SaveIndex();
        int count = stale.Count();
        FENR_PDA_Storage.LogSystem("Erased the PDA memory of " + count.ToString() + " players inactive for " + days.ToString() + " days.");
    }
};
