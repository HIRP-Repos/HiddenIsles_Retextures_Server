/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Client-side PDA state.

    v8.1: a PDA is locked until someone logs in on it.  The memory shown
    (contacts, conversations, map markers) belongs to the player the PDA is
    logged in as and lives on the server.  This class is a cache of it:
    filled by DEVICE_SYNC when the PDA is opened (after SESSION_STATE),
    conversations fetched on demand, and every change sent back as a small
    operation.

    Every write carries the account token from the last sync.  Closing the
    PDA invalidates the token.  A read-only (guest) session never writes;
    the server refuses it anyway.

    Legacy local files ($profile:\PDA\contacts_0002.json etc.) are read
    once and copied onto the first blank PDA the player opens.
*/

// A received S.O.S ping (client side, kept until it expires).
class FENR_PDA_SosPing
{
    string Name;
    string SenderID;
    float X;
    float Z;
    int Expires;      // GetGame().GetTime() ms
};

class FENR_PDA_Client extends PluginBase
{
    // Legacy (pre-7.8) local files, used for the one-time migration only.
    static const string SESSION_SUFFIX = "_0002.json";
    static const string CONTACTS_FILE = "contacts";
    static const string NOTES_FILE = "notes";
    static const string MIGRATED_FLAG = "device_migrated_v78.txt";

    static const ref array<ref FENR_PDA_Contact> GLOBAL_CHANNELS = {
        new ref FENR_PDA_Contact(FENR_PDA_ChannelIds.ANNOUNCEMENTS, "Announcements", false),
        new ref FENR_PDA_Contact(FENR_PDA_ChannelIds.GLOBAL, "Global", true),
        new ref FENR_PDA_Contact(FENR_PDA_ChannelIds.BUY_SELL, "Buy/Sell", true)
    };

    ref FENR_PDA_Menu m_Menu;
    ref array<ref FENR_PDA_Contact> m_Contacts;
    ref array<string> m_OnlineContactIds;
    ref map<string, ref array<ref FENR_PDA_ChatMessage>> m_ConversationCache;
    ref array<string> m_PendingConvos;
    ref FENR_PDA_Note m_Notes;
    ref array<ref FENR_PDA_MapMarker> m_Markers;
    string m_MarkerTerrain;
    string m_UserDisplayName;

    protected string m_DeviceToken = "";
    protected bool m_DeviceSyncPending;

    // Login session of the PDA in hands (SESSION_STATE).
    protected int m_SessionState = -1;      // -1 unknown, else FENR_PDA_SessionState
    protected string m_SessionOwner = "";
    protected int m_SessionEnds;            // GetGame().GetTime() ms
    protected int m_Features = 111;         // trade(1) + bounty(10) + sos(100)
    protected int m_MinHours = 1;
    protected int m_MaxHours = 4;
    protected float m_ReadOnlyNoticeTime = -100;

    ref array<ref FENR_PDA_SosPing> m_SosPings;

    // Developer test accounts (re-added after every sync, never saved).
    ref array<string> m_TestIds;
    ref array<string> m_TestNames;

    void FENR_PDA_Client()
    {
        m_Contacts = new array<ref FENR_PDA_Contact>();
        m_OnlineContactIds = new array<string>();
        m_ConversationCache = new map<string, ref array<ref FENR_PDA_ChatMessage>>();
        m_PendingConvos = new array<string>();
        m_Notes = new FENR_PDA_Note();
        m_Markers = new array<ref FENR_PDA_MapMarker>();
        m_TestIds = new array<string>();
        m_TestNames = new array<string>();
        m_SosPings = new array<ref FENR_PDA_SosPing>();
        m_MarkerTerrain = "";

        InsertGlobalChannels();
    }

    override void OnInit()
    {
        super.OnInit();
        FENR_PDA_Storage.InitClient();
        if (GetGame().IsClient())
            FENR_PDA_SettingsStore.Load();
    }

    protected void InsertGlobalChannels()
    {
        foreach (FENR_PDA_Contact channel : GLOBAL_CHANNELS)
        {
            if (channel)
                m_Contacts.Insert(channel);
        }
    }

    static bool IsGlobalChannel(string contactId)
    {
        return FENR_PDA_ChannelIds.IsChannel(contactId);
    }

    static ref FENR_PDA_Contact FindGlobalChannel(string contactId)
    {
        foreach (FENR_PDA_Contact channel : GLOBAL_CHANNELS)
        {
            if (channel && channel.m_UID == contactId)
                return channel;
        }
        return null;
    }

    static string CurrentTerrain()
    {
        string world;
        GetGame().GetWorldName(world);
        return world;
    }

    bool IsTestContact(string contactId)
    {
        return m_TestIds.Find(contactId) != -1;
    }

    // ------------------------------------------------------------------
    // Device sync
    // ------------------------------------------------------------------
    void RequestSync()
    {
        m_DeviceToken = "";
        m_DeviceSyncPending = true;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_SYNC, new Param1<string>(CurrentTerrain()), true);
    }

    string DeviceToken()
    {
        return m_DeviceToken;
    }

    bool IsDeviceSynced()
    {
        return m_DeviceToken != "";
    }

    bool IsDeviceSyncPending()
    {
        return m_DeviceSyncPending;
    }

    // The PDA was closed: this cache may no longer match the PDA carried.
    void OnMenuClosed()
    {
        m_DeviceToken = "";
        m_DeviceSyncPending = false;
        m_SessionState = -1;
        m_ConversationCache.Clear();
        m_PendingConvos.Clear();
    }

    // ------------------------------------------------------------------
    // Login session
    // ------------------------------------------------------------------
    // state, owner name, seconds left, features, hours range (min*100+max)
    void ReceiveSessionState(int state, string ownerName, int secondsLeft, int features, int range)
    {
        if (!IsOpen())
            return;
        m_SessionState = state;
        m_SessionOwner = ownerName;
        m_SessionEnds = GetGame().GetTime() + secondsLeft * 1000;
        m_Features = features;
        m_MinHours = range / 100;
        m_MaxHours = range % 100;
        if (m_MinHours < 1) m_MinHours = 1;
        if (m_MaxHours < m_MinHours) m_MaxHours = m_MinHours;

        // Locked: forget everything shown so far.
        if (state != FENR_PDA_SessionState.OWNER && state != FENR_PDA_SessionState.GUEST)
            ClearSessionCache();
        if (m_Menu)
            m_Menu.OnSessionState();
    }

    protected void ClearSessionCache()
    {
        m_DeviceToken = "";
        m_Contacts.Clear();
        InsertGlobalChannels();
        foreach (FENR_PDA_Contact channel : GLOBAL_CHANNELS)
        {
            if (channel) channel.m_Unreaded = 0;
        }
        m_ConversationCache.Clear();
        m_PendingConvos.Clear();
        m_Markers.Clear();
        m_Notes = new FENR_PDA_Note();
        if (m_Menu)
            m_Menu.m_dirty = true;
    }

    int SessionState() { return m_SessionState; }
    string SessionOwner() { return m_SessionOwner; }
    int MinHours() { return m_MinHours; }
    int MaxHours() { return m_MaxHours; }

    bool IsGuest() { return m_SessionState == FENR_PDA_SessionState.GUEST; }
    bool IsLoggedIn() { return m_SessionState == FENR_PDA_SessionState.OWNER || m_SessionState == FENR_PDA_SessionState.GUEST; }

    int SessionSecondsLeft()
    {
        if (!IsLoggedIn())
            return 0;
        int left = (m_SessionEnds - GetGame().GetTime()) / 1000;
        if (left < 0)
            left = 0;
        return left;
    }

    bool TradeEnabled() { return m_Features % 10 == 1; }
    bool BountyEnabled() { return (m_Features / 10) % 10 == 1; }
    bool SosEnabled() { return (m_Features / 100) % 10 == 1; }

    // Transmitting / changing anything needs the owner's own session.
    bool CanWrite(bool notify = true)
    {
        if (m_SessionState == FENR_PDA_SessionState.OWNER)
            return true;
        if (notify)
            NotifyReadOnly();
        return false;
    }

    void NotifyReadOnly()
    {
        float now = GetGame().GetTime() / 1000.0;
        if (now - m_ReadOnlyNoticeTime < 2.0)
            return;
        m_ReadOnlyNoticeTime = now;
        string owner = m_SessionOwner;
        if (owner == "")
            owner = "another user";
        FENR_PDA_Toast.Notify("READ-ONLY ACCESS", "LOGGED IN AS " + owner, "You can view this PDA but not transmit from it. Log in as yourself to use it.", "ic_lock", false, true);
    }

    void Login(int hours)
    {
        FENR_PDA_SettingsStore.Get().LoginHours = hours;
        FENR_PDA_SettingsStore.Save();
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SESSION_LOGIN, new Param2<int, string>(hours, CurrentTerrain()), true);
    }

    void Logout()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SESSION_LOGOUT, new Param1<string>(CurrentTerrain()), true);
    }

    // token "" = no PDA.  contactFields stride 5: uid, name, unread, banned, muted
    // markerFields stride 3: name, x, z
    void ReceiveSync(string token, array<string> contactFields, string notes, array<string> markerFields, bool isNew)
    {
        // An answer that arrives after the PDA was closed must not revive the token.
        if (!IsOpen())
        {
            m_DeviceSyncPending = false;
            return;
        }
        m_DeviceSyncPending = false;
        m_DeviceToken = token;

        // Keep the global channel objects (pages may hold them) and rebuild the rest.
        m_Contacts.Clear();
        InsertGlobalChannels();
        foreach (FENR_PDA_Contact channel : GLOBAL_CHANNELS)
        {
            if (channel) channel.m_Unreaded = 0;
        }
        m_ConversationCache.Clear();
        m_PendingConvos.Clear();
        m_Notes = new FENR_PDA_Note();
        m_Markers.Clear();
        m_MarkerTerrain = CurrentTerrain();

        if (token != "")
        {
            if (contactFields)
            {
                for (int i = 0; i + 5 <= contactFields.Count(); i += 5)
                {
                    string uid = contactFields[i];
                    if (uid == "") continue;
                    if (IsGlobalChannel(uid))
                    {
                        // Unread channel lines since this PDA last looked.
                        FENR_PDA_Contact channelEntry = FindGlobalChannel(uid);
                        if (channelEntry) channelEntry.m_Unreaded = contactFields[i + 2].ToInt();
                        continue;
                    }
                    if (FindContact(uid)) continue;
                    ref FENR_PDA_Contact contact = new FENR_PDA_Contact(uid, contactFields[i + 1], true);
                    contact.m_Unreaded = contactFields[i + 2].ToInt();
                    contact.m_IsBanned = contactFields[i + 3] == "1";
                    contact.m_IsMuted = contactFields[i + 4] == "1";
                    m_Contacts.Insert(contact);
                }
            }
            m_Notes.note = notes;
            if (markerFields)
            {
                for (int m = 0; m + 3 <= markerFields.Count(); m += 3)
                    m_Markers.Insert(new FENR_PDA_MapMarker(markerFields[m], markerFields[m + 1].ToFloat(), markerFields[m + 2].ToFloat()));
            }

            if (isNew)
                MigrateLegacy();
        }

        // Developer test accounts are session-only.
        for (int t = 0; t < m_TestIds.Count() && t < m_TestNames.Count(); t++)
        {
            if (!FindContact(m_TestIds[t]))
                m_Contacts.Insert(new FENR_PDA_Contact(m_TestIds[t], m_TestNames[t], true));
        }

        RequestContactStatusRefresh();
        if (m_Menu)
        {
            m_Menu.OnDeviceSynced();
            m_Menu.m_dirty = true;
        }
    }

    // First blank PDA after updating from 7.7 or older: copy the old
    // locally stored contacts, notes and markers onto it, once.
    protected void MigrateLegacy()
    {
        string flagPath = FENR_PDA_Paths.PROFILE_ROOT + MIGRATED_FLAG;
        if (FileExist(flagPath))
            return;

        string contactsPath = FENR_PDA_Paths.PROFILE_ROOT + CONTACTS_FILE + SESSION_SUFFIX;
        if (FileExist(contactsPath))
        {
            array<ref FENR_PDA_Contact> legacyContacts = FENR_PDA_Storage.LoadContacts(contactsPath);
            if (legacyContacts)
            {
                foreach (FENR_PDA_Contact oldContact : legacyContacts)
                {
                    if (!oldContact || oldContact.m_UID == "" || IsGlobalChannel(oldContact.m_UID) || FindContact(oldContact.m_UID)) continue;
                    AddContact(oldContact.m_UID, oldContact.m_Name);
                    if (oldContact.m_IsBanned) SetBlocked(oldContact.m_UID, true);
                    if (oldContact.m_IsMuted) SendContactOp(FENR_PDA_ContactOp.MUTE, oldContact.m_UID, "1");
                }
            }
        }

        string notesPath = FENR_PDA_Paths.PROFILE_ROOT + NOTES_FILE + SESSION_SUFFIX;
        if (FileExist(notesPath))
        {
            FENR_PDA_Note legacyNotes = FENR_PDA_Storage.LoadNotes(notesPath);
            if (legacyNotes && legacyNotes.note != "" && m_Notes.note == "")
            {
                m_Notes.note = legacyNotes.note;
                SaveNotes();
            }
        }

        array<ref FENR_PDA_MapMarker> legacyMarkers = FENR_PDA_Storage.LoadMarkers(m_MarkerTerrain);
        if (legacyMarkers && legacyMarkers.Count() > 0 && m_Markers.Count() == 0)
        {
            foreach (FENR_PDA_MapMarker marker : legacyMarkers)
            {
                if (marker) m_Markers.Insert(new FENR_PDA_MapMarker(marker.Name, marker.X, marker.Z));
            }
            SaveMarkers();
        }

        FileHandle flagFile = OpenFile(flagPath, FileMode.WRITE);
        if (flagFile != 0)
        {
            FPrintln(flagFile, "Legacy PDA data was copied onto a device. Delete this file to copy it again onto the next blank PDA.");
            CloseFile(flagFile);
        }
    }

    // ------------------------------------------------------------------
    // Writes to the PDA (only with a valid device token)
    // ------------------------------------------------------------------
    protected void SendContactOp(string op, string contactId, string value)
    {
        if (m_DeviceToken == "" || IsTestContact(contactId))
            return;
        // Read-only viewers do not move the owner's read marks.
        if (!CanWrite(op != FENR_PDA_ContactOp.READ))
            return;
        // Channels only take read marks.
        if (IsGlobalChannel(contactId) && op != FENR_PDA_ContactOp.READ)
            return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_CONTACT_OP, new Param4<string, string, string, string>(m_DeviceToken, op, contactId, value), true);
    }

    void SaveNotes()
    {
        if (!m_Notes)
            m_Notes = new FENR_PDA_Note();
        if (m_DeviceToken == "" || !CanWrite(false))
            return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_SAVE_NOTES, new Param2<string, string>(m_DeviceToken, m_Notes.note), true);
    }

    void SaveMarkers()
    {
        if (m_DeviceToken == "" || !CanWrite())
            return;

        ref array<string> fields = new array<string>();
        foreach (FENR_PDA_MapMarker marker : m_Markers)
        {
            if (!marker) continue;
            fields.Insert(marker.Name);
            fields.Insert(marker.X.ToString());
            fields.Insert(marker.Z.ToString());
        }
        string terrain = m_MarkerTerrain;
        if (terrain == "")
            terrain = CurrentTerrain();
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_SAVE_MARKERS, new Param3<string, string, ref array<string>>(m_DeviceToken, terrain, fields), true);
    }

    // Adds markers from a drive.  Returns the number added, or -1 when they
    // belong to another terrain.
    int ImportMarkers(string terrain, array<ref FENR_PDA_MapMarker> markers)
    {
        if (!CanWrite())
            return 0;
        string a = terrain;
        string b = CurrentTerrain();
        a.ToLower();
        b.ToLower();
        if (a != "" && a != b)
            return -1;
        int added = 0;
        foreach (FENR_PDA_MapMarker marker : markers)
        {
            if (!marker || m_Markers.Count() >= FENR_PDA_PageMap.MAX_MARKERS) continue;
            m_Markers.Insert(new FENR_PDA_MapMarker(marker.Name, marker.X, marker.Z));
            added++;
        }
        if (added > 0)
        {
            SaveMarkers();
            if (m_Menu)
                m_Menu.OnMarkersChanged();
        }
        return added;
    }

    // ------------------------------------------------------------------
    // Compass HUD markers (PDA closed: fetched read-only from the server)
    // ------------------------------------------------------------------
    void RequestHudMarkers()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_HUD, new Param1<string>(CurrentTerrain()), true);
    }

    // fields stride 3: name, x, z
    void ReceiveHudMarkers(string terrain, array<string> fields)
    {
        FENR_PDA_CompassHud.OnMarkersReceived();
        if (IsOpen())
            return;   // the open PDA's own copy is authoritative
        m_Markers.Clear();
        m_MarkerTerrain = terrain;
        if (!fields)
            return;
        for (int i = 0; i + 3 <= fields.Count(); i += 3)
            m_Markers.Insert(new FENR_PDA_MapMarker(fields[i], fields[i + 1].ToFloat(), fields[i + 2].ToFloat()));
    }

    // ------------------------------------------------------------------
    // S.O.S pings received
    // ------------------------------------------------------------------
    void AddSosPing(string name, float x, float z, int minutes, string senderID)
    {
        FENR_PDA_SosPing ping = null;
        foreach (FENR_PDA_SosPing existing : m_SosPings)
        {
            if (existing && existing.SenderID == senderID)
                ping = existing;
        }
        if (!ping)
        {
            ping = new FENR_PDA_SosPing();
            m_SosPings.Insert(ping);
        }
        ping.Name = name;
        ping.SenderID = senderID;
        ping.X = x;
        ping.Z = z;
        ping.Expires = GetGame().GetTime() + minutes * 60000;

        int gx = Math.Floor(x / 100.0);
        int gz = Math.Floor(z / 100.0);
        if (gx < 0) gx = 0;
        if (gz < 0) gz = 0;
        string where = "GRID " + gx.ToStringLen(3) + " " + gz.ToStringLen(3);
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
            vector me = player.GetPosition();
            float dx = x - me[0];
            float dz = z - me[2];
            float metres = Math.Sqrt(dx * dx + dz * dz);
            where += "  |  " + FENR_PDA_UI_Kit.Distance(metres);
        }
        FENR_PDA_Toast.NotifySos(name, "Emergency beacon at " + where);
        if (m_Menu)
            m_Menu.OnMarkersChanged();
    }

    // Pings still active (expired ones are dropped).
    array<ref FENR_PDA_SosPing> ActiveSosPings()
    {
        int now = GetGame().GetTime();
        for (int i = m_SosPings.Count() - 1; i >= 0; i--)
        {
            if (!m_SosPings[i] || m_SosPings[i].Expires <= now)
                m_SosPings.Remove(i);
        }
        return m_SosPings;
    }

    // ------------------------------------------------------------------
    // Conversations (fetched from the server on demand)
    // ------------------------------------------------------------------
    ref array<ref FENR_PDA_ChatMessage> GetConversation(string contactId)
    {
        if (m_ConversationCache.Contains(contactId))
            return m_ConversationCache[contactId];

        if (IsTestContact(contactId) && m_DeviceToken == "")
            return new array<ref FENR_PDA_ChatMessage>();

        if (m_DeviceToken != "" && m_PendingConvos.Find(contactId) == -1)
        {
            m_PendingConvos.Insert(contactId);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_CONVO, new Param2<string, string>(m_DeviceToken, contactId), true);
        }

        // Not loaded yet: an empty view until the server answers.
        return new array<ref FENR_PDA_ChatMessage>();
    }

    bool IsConversationLoading(string contactId)
    {
        return m_PendingConvos.Find(contactId) != -1;
    }

    // fields stride 5: sender, text, time, own(1/0), seq
    void ReceiveConversation(string contactId, array<string> fields)
    {
        if (m_PendingConvos.Find(contactId) == -1 && m_DeviceToken == "")
            return;   // answer for a PDA that was closed meanwhile
        m_PendingConvos.RemoveItem(contactId);
        ref array<ref FENR_PDA_ChatMessage> messages = new array<ref FENR_PDA_ChatMessage>();
        if (fields)
        {
            for (int i = 0; i + 5 <= fields.Count(); i += 5)
            {
                ref FENR_PDA_ChatMessage message = new FENR_PDA_ChatMessage();
                message.m_Name = fields[i];
                message.m_Message = fields[i + 1];
                message.m_Time = fields[i + 2];
                message.m_Own = fields[i + 3] == "1";
                message.m_Seq = fields[i + 4].ToInt();
                messages.Insert(message);
            }
        }
        m_ConversationCache[contactId] = messages;
        if (m_Menu)
            m_Menu.m_dirty = true;
    }

    void SetOnlineContacts(array<string> onlineIds)
    {
        m_OnlineContactIds.Clear();

        if (onlineIds)
            m_OnlineContactIds.Copy(onlineIds);

        foreach (FENR_PDA_Contact channel : GLOBAL_CHANNELS)
        {
            if (channel && m_OnlineContactIds.Find(channel.m_UID) == -1)
                m_OnlineContactIds.Insert(channel.m_UID);
        }
    }

    // The server already stored the message; only the cache is updated.
    void AppendMessage(string contactId, string senderName, string body, bool own, int seq)
    {
        if (contactId == "")
        {
            RequestContactStatusRefresh();
            return;
        }

        if (m_ConversationCache.Contains(contactId))
        {
            ref FENR_PDA_ChatMessage message = new FENR_PDA_ChatMessage();
            message.m_Name = senderName;
            message.m_Message = body;
            message.m_Time = FENR_PDA_UI_Kit.GameTime();
            message.m_Own = own;
            message.m_Seq = seq;
            array<ref FENR_PDA_ChatMessage> messages = m_ConversationCache[contactId];
            messages.Insert(message);
            while (messages.Count() > FENR_PDA_Limits.DIRECT_HISTORY)
                messages.RemoveOrdered(0);
        }

        FENR_PDA_Contact contact = FindContact(contactId);
        if (contact && !own)
            contact.m_Unreaded++;

        if (IsOpen())
            m_Menu.m_sendMessageStatus = 2;
    }

    protected void RequestContactStatusRefresh()
    {
        if (IsOpen())
            m_Menu.m_sendMessageStatus = 0;

        ref array<string> contactIds = new array<string>();
        foreach (FENR_PDA_Contact contact : m_Contacts)
        {
            if (contact)
                contactIds.Insert(contact.m_UID);
        }

        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.CHECK_CONTACTS, new Param1<ref array<string>>(contactIds), true);
    }

    bool IsOpen()
    {
        return m_Menu && m_Menu.m_active;
    }

    void Open()
    {
        if (IsOpen())
            Close();

        if (GetGame().GetUIManager().GetMenu() != null)
            return;

        m_SessionState = -1;
        m_Menu = new FENR_PDA_Menu();
        m_Menu.Init();
        GetGame().GetUIManager().ShowScriptedMenu(m_Menu, null);

        // Load this PDA's memory, then the developer test accounts.
        RequestSync();
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SYNC_TEST_ACCOUNTS, new Param1<bool>(true), true);
    }

    void Close()
    {
        if (m_Menu)
            m_Menu.ClosePda();
    }

    ref FENR_PDA_Contact FindContact(string contactId)
    {
        foreach (FENR_PDA_Contact contact : m_Contacts)
        {
            if (contact && contact.m_UID == contactId)
                return contact;
        }
        return null;
    }

    // ------------------------------------------------------------------
    // Contact changes made on this PDA
    // ------------------------------------------------------------------
    void AddContact(string contactId, string displayName)
    {
        if (contactId == "" || displayName == "")
            return;

        if (!FindContact(contactId))
        {
            AddContactLocal(contactId, displayName);
            SendContactOp(FENR_PDA_ContactOp.ADD, contactId, displayName);
        }

        if (IsOpen())
            m_Menu.m_addContactStatus = 2;
    }

    // Cache only (the server already knows, e.g. an incoming message).
    void AddContactLocal(string contactId, string displayName)
    {
        if (contactId == "" || FindContact(contactId))
            return;
        string name = displayName;
        if (name == "")
            name = contactId;
        m_Contacts.Insert(new FENR_PDA_Contact(contactId, name, true));
        if (m_OnlineContactIds.Find(contactId) == -1)
            m_OnlineContactIds.Insert(contactId);
    }

    void SetTestContacts(array<string> ids, array<string> names)
    {
        foreach (string oldID : m_TestIds)
        {
            FENR_PDA_Contact oldContact = FindContact(oldID);
            if (oldContact && !IsGlobalChannel(oldID))
                m_Contacts.RemoveItem(oldContact);
            m_OnlineContactIds.RemoveItem(oldID);
        }
        m_TestIds.Clear();
        m_TestNames.Clear();
        if (!ids || !names)
            return;

        int count = ids.Count();
        if (names.Count() < count)
            count = names.Count();
        for (int i = 0; i < count; i++)
        {
            m_TestIds.Insert(ids[i]);
            m_TestNames.Insert(names[i]);
            if (!FindContact(ids[i]))
                m_Contacts.Insert(new FENR_PDA_Contact(ids[i], names[i], true));
            if (m_OnlineContactIds.Find(ids[i]) == -1)
                m_OnlineContactIds.Insert(ids[i]);
        }
    }

    void RemoveContact(string contactId)
    {
        if (IsGlobalChannel(contactId))
            return;

        FENR_PDA_Contact contact = FindContact(contactId);
        if (!contact)
            return;

        m_Contacts.RemoveItem(contact);
        m_OnlineContactIds.RemoveItem(contactId);
        if (m_ConversationCache.Contains(contactId))
            m_ConversationCache.Remove(contactId);
        SendContactOp(FENR_PDA_ContactOp.REMOVE, contactId, "");
    }

    void RenameContact(string contactId, string newName)
    {
        if (newName == "" || IsGlobalChannel(contactId))
            return;

        FENR_PDA_Contact contact = FindContact(contactId);
        if (!contact)
            return;

        contact.m_Name = newName;
        SendContactOp(FENR_PDA_ContactOp.RENAME, contactId, newName);
    }

    void SetBlocked(string contactId, bool blocked)
    {
        FENR_PDA_Contact contact = FindContact(contactId);
        if (!contact || IsGlobalChannel(contactId))
            return;
        contact.m_IsBanned = blocked;
        if (blocked) SendContactOp(FENR_PDA_ContactOp.BLOCK, contactId, "1");
        else SendContactOp(FENR_PDA_ContactOp.BLOCK, contactId, "0");
    }

    void ToggleBlocked(string contactId)
    {
        FENR_PDA_Contact contact = FindContact(contactId);
        if (contact)
            SetBlocked(contactId, !contact.m_IsBanned);
    }

    // A group chat was seen (read mark kept on the PDA).
    void MarkGroupRead(string groupId)
    {
        if (groupId != "")
            SendContactOp(FENR_PDA_ContactOp.READ, "GR:" + groupId, "");
    }

    // Opening a conversation clears its unread counter.
    void MarkRead(string contactId)
    {
        FENR_PDA_Contact contact = FindContact(contactId);
        if (!contact || contact.m_Unreaded <= 0)
            return;
        contact.m_Unreaded = 0;
        SendContactOp(FENR_PDA_ContactOp.READ, contactId, "");
    }
};
