/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Shared data models.  The message audit model is intentionally small:
    who sent what, to whom/where, and when.
*/

class FENR_PDA_Contact
{
    string m_UID;
    string m_Name;
    int m_Unreaded;
    bool m_IsBanned;
    bool m_IsMuted;
    bool m_CanSend;

    void FENR_PDA_Contact(string uid = "", string name = "", bool canSend = true)
    {
        m_UID = uid;
        m_Name = name;
        m_Unreaded = 0;
        m_IsBanned = false;
        m_IsMuted = false;
        m_CanSend = canSend;
    }
};

class FENR_PDA_ChatMessage
{
    string m_Name;
    string m_Message;
    string m_Time;      // HH:MM (in-game clock) - empty for pre-7.0 history
    string m_SenderID;  // server: who sent it (own/remote is decided per viewer)
    int m_Seq;          // unique message number (drive excerpts select by it)
    bool m_Own;         // client: sent by this player
};

class FENR_PDA_Note
{
    string note;
};

class FENR_PDA_GroupMember
{
    string ID;
    string Name;

    void FENR_PDA_GroupMember(string id = "", string name = "")
    {
        ID = id;
        Name = name;
    }
};

class FENR_PDA_GroupMessage
{
    int Seq;              // per-group message number (assigned on load if missing)
    string Clock;         // HH:MM in-game clock shown on the PDA (7.9+)
    string Timestamp;
    string SenderID;
    string SenderName;
    string MessageText;
};

class FENR_PDA_Group
{
    string GroupID;
    string GroupName;
    string OwnerID;
    string OwnerName;
    ref array<ref FENR_PDA_GroupMember> Members;

    void FENR_PDA_Group()
    {
        Members = new array<ref FENR_PDA_GroupMember>();
    }

    bool HasMember(string memberID)
    {
        if (!Members)
            return false;

        foreach (FENR_PDA_GroupMember member : Members)
        {
            if (member && member.ID == memberID)
                return true;
        }
        return false;
    }

    int FindMemberIndex(string memberID)
    {
        if (!Members)
            return -1;

        for (int i = 0; i < Members.Count(); i++)
        {
            FENR_PDA_GroupMember member = Members.Get(i);
            if (member && member.ID == memberID)
                return i;
        }
        return -1;
    }
};

class FENR_PDA_MapMarker
{
    string Name;
    float X;
    float Z;

    void FENR_PDA_MapMarker(string name = "", float x = 0, float z = 0)
    {
        Name = name;
        X = x;
        Z = z;
    }
};

class FENR_PDA_TradeListing
{
    string ID;
    string Type;          // FENR_PDA_TradeType.BUY / SELL
    string Title;
    string Price;
    string Description;
    string OwnerID;       // Steam64
    string OwnerName;
    string Status;        // FENR_PDA_TradeStatus
    string Created;       // "YYYY-MM-DD HH:MM:SS" (server real time)
    int CreatedSerial;    // day serial used for expiry
    string Category;      // FENR_PDA_TradeCategory (empty on pre-7.5 listings = OTHER)
};

// Reputation: one vote per rater/target pair; only players who have traded
// (one contacted the other through a listing) may rate each other.
class FENR_PDA_RepVote
{
    string RaterID;
    string TargetID;
    int Value;            // +1 / -1
    string Timestamp;
};

class FENR_PDA_TradePair
{
    string ContacterID;   // player who pressed CONTACT
    string OwnerID;       // lister
};

class FENR_PDA_RepData
{
    ref array<ref FENR_PDA_RepVote> Votes;
    ref array<ref FENR_PDA_TradePair> Pairs;

    void FENR_PDA_RepData()
    {
        Votes = new array<ref FENR_PDA_RepVote>();
        Pairs = new array<ref FENR_PDA_TradePair>();
    }
};

class FENR_PDA_Bounty
{
    string ID;
    string TargetName;
    string Reward;
    string Reason;
    string PosterID;
    string PosterName;
    bool IsServer;        // admin-posted server bounty
    string Status;        // FENR_PDA_BountyStatus
    string ClaimerID;
    string ClaimerName;
    string ClaimNote;
    string Created;
    int CreatedSerial;
};

// Per-PDA memory, stored on the server under the PDA's persistent ID.
// Conversations are not stored here: they are rebuilt from the message log.
class FENR_PDA_TerrainMarkers
{
    string TerrainName;
    ref array<ref FENR_PDA_MapMarker> Markers;

    void FENR_PDA_TerrainMarkers()
    {
        Markers = new array<ref FENR_PDA_MapMarker>();
    }
};

class FENR_PDA_DeviceMeta
{
    ref array<ref FENR_PDA_Contact> Contacts;
    string Notes;
    ref array<ref FENR_PDA_TerrainMarkers> MarkerSets;
    int LastUsed;                       // day serial of the last use
    string LastUser;                    // Steam64 of the last user
    ref array<string> ClearedIDs;       // deleted conversations ...
    ref array<int> ClearedSeq;          // ... hidden up to this message number
    ref array<string> ReadIDs;          // shared histories ("CH:<channel>", "GR:<group>") ...
    ref array<int> ReadSeq;             // ... read up to this message number
    string SosMode;                     // "CONTACTS" or "GROUP"
    ref array<string> SosTargets;       // contact IDs (CONTACTS mode)
    string SosGroup;                    // group ID (GROUP mode)

    void FENR_PDA_DeviceMeta()
    {
        Contacts = new array<ref FENR_PDA_Contact>();
        MarkerSets = new array<ref FENR_PDA_TerrainMarkers>();
        ClearedIDs = new array<string>();
        ClearedSeq = new array<int>();
        ReadIDs = new array<string>();
        ReadSeq = new array<int>();
        SosTargets = new array<string>();
    }
};

// Key -> day serial index (device last use, drive write date).
class FENR_PDA_KeyIndex
{
    ref array<string> Keys;
    ref array<int> Days;
    int NextSeq;                    // account index only: next message number
    int Format;                     // 2 = v8.1 account index (older = per-PDA index, migrated)
    ref array<string> AliasFrom;    // device index only: temporary session keys ...
    ref array<string> AliasTo;      // ... and the persistent key they became
    ref array<string> PlayerIDs;    // device index only: player ...
    ref array<string> PlayerKeys;   // ... and the PDA they last used (offline delivery)

    void FENR_PDA_KeyIndex()
    {
        Keys = new array<string>();
        Days = new array<int>();
        AliasFrom = new array<string>();
        AliasTo = new array<string>();
        PlayerIDs = new array<string>();
        PlayerKeys = new array<string>();
    }
};

// One message line saved on an Encrypted Drive.
class FENR_PDA_DriveLine
{
    string SenderName;
    string Message;
    string Clock;
    bool ByWriter;        // sent by the player who wrote the drive

    void FENR_PDA_DriveLine(string senderName = "", string message = "", string clock = "", bool byWriter = false)
    {
        SenderName = senderName;
        Message = message;
        Clock = clock;
        ByWriter = byWriter;
    }
};

// One file on an Encrypted Drive (FENR_PDA_DriveFolder).
class FENR_PDA_DriveFile
{
    string Folder;
    string Name;
    string Terrain;       // markers only
    ref array<ref FENR_PDA_DriveLine> Lines;
    ref array<ref FENR_PDA_MapMarker> Markers;

    void FENR_PDA_DriveFile()
    {
        Lines = new array<ref FENR_PDA_DriveLine>();
        Markers = new array<ref FENR_PDA_MapMarker>();
    }
};

// Server-side contents of one physical drive.
class FENR_PDA_DriveData
{
    string Kind;
    string WrittenBy;
    string WrittenByID;
    string Written;
    int WrittenSerial;     // day serial of the write (ENCRYPTED decay)
    bool Corrupted;

    // INTEL
    string IntelID;
    bool Decoded;          // decrypted once: the drive burns out when the file is closed

    // ENCRYPTED
    ref array<ref FENR_PDA_DriveFile> Files;

    void FENR_PDA_DriveData()
    {
        Files = new array<ref FENR_PDA_DriveFile>();
    }
};

// One line of the drive write log ($profile:\PDA\Logs\Drives_<day>.jsonl).
class FENR_PDA_DriveLogRecord
{
    string Timestamp;
    string Kind;               // ENCRYPTED or INTEL
    string DriveKey;
    string WrittenBy;
    string WrittenBySteam64;
    string ClonedFrom;         // Steam64 of the PDA owner when a read-only viewer wrote it
    string IntelTitle;
    string IntelBody;
    ref FENR_PDA_DriveData Data;
};

// Intel / lore file pool ($profile:\PDA\Config\IntelFiles.json).
class FENR_PDA_IntelFile
{
    string ID;
    string Title;
    string Body;
    int Weight = 1;
};

class FENR_PDA_Config
{
    bool TestAccountsEnabled = true;

    bool TradeEnabled = true;
    int TradeMaxListingsPerPlayer = 5;
    int TradeListingDays = 7;

    bool BountyEnabled = true;
    int BountyMaxPerPlayer = 3;
    int BountyDays = 7;

    bool BatteryDrainEnabled = true;
    float BatteryDrainOpenPercentPerMinute = 1.0;
    float BatteryDrainMapPercentPerMinute = 1.5;

    bool LoggingEnabled = true;
    bool LogSystemEvents = true;
    bool LogAdminActions = true;
    bool LogErrors = true;

    int MessageLogsDays = 14;
    int SystemLogsDays = 30;
    int ErrorLogsDays = 30;
    int AdminLogsDays = 90;
    int CleanupIntervalHours = 24;
    int SearchResultsPerPage = 25;

    int DeviceInactiveDays = 30;     // a player's PDA memory is erased after this many days without logging in (0 = never)
    int EncryptedDriveDays = 7;      // Encrypted Drive data corrupts this long after writing
    int DriveLogsDays = 7;           // how long the drive write log (Logs\Drives_<day>.jsonl) is kept

    int SessionMinHours = 1;         // PDA login session length players can choose
    int SessionMaxHours = 4;

    bool SosEnabled = true;
    int SosMaxContacts = 5;          // contacts one PDA can send its S.O.S to
    int SosPingMinutes = 30;         // how long the red ping stays on receivers' map / compass

    int ConfigVersion = 0;           // set by the mod; used to apply new defaults once on update
};

// Client-side display settings ($profile:\PDA\Settings.json on the player's machine).
class FENR_PDA_Settings
{
    string Preset = "FENRIR GREEN";
    int Hue = 150;              // 0-359
    int Saturation = 100;       // percent
    int Brightness = 100;       // text / lines, percent
    int Backlight = 100;        // panels / backgrounds, percent

    bool CompassEnabled = true;
    int CompassPosition = 0;    // 0 top, 1 bottom
    int CompassSize = 1;        // 0 small, 1 medium, 2 large
    int CompassOpacity = 85;    // percent
    bool CompassMatchTheme = true;
    int CompassHue = 150;
    bool CompassMarkers = true;
    bool CompassDistances = true;
    bool CompassBearing = true;

    int LoginHours = 2;         // last session length chosen on the login screen
};

// Read-only migration shapes for pre-streamline configuration files.
class FENR_PDA_LegacyLogConfig
{
    bool Enabled = true;
    bool LogMessageContents = true;
    bool LogSystemEvents = true;
    bool LogAdminActions = true;
    bool LogErrors = true;
    bool LogConnections = true;
    int MessageLogsDays = 30;
    int SystemLogsDays = 30;
    int ErrorLogsDays = 30;
    int ConnectionLogsDays = 30;
    int AdminLogsDays = 90;
    int CleanupIntervalHours = 24;
    int SearchResultsPerPage = 25;
};

class FENR_PDA_LegacyTestConfig
{
    bool Enabled = true;
};

class FENR_PDA_LogFileRecord
{
    string Path;
    string Category;
    int DaySerial;

    void FENR_PDA_LogFileRecord(string path = "", string category = "", int daySerial = 0)
    {
        Path = path;
        Category = category;
        DaySerial = daySerial;
    }
};

class FENR_PDA_LogRegistry
{
    ref array<ref FENR_PDA_LogFileRecord> Files;

    void FENR_PDA_LogRegistry()
    {
        Files = new array<ref FENR_PDA_LogFileRecord>();
    }
};

class FENR_PDA_KnownPlayer
{
    string Steam64;
    string LegacyID;
    string Name;
    int LastSeen;         // day serial

    void FENR_PDA_KnownPlayer(string steam64 = "", string legacyID = "", string name = "")
    {
        Steam64 = steam64;
        LegacyID = legacyID;
        Name = name;
    }
};

class FENR_PDA_MessageRecord
{
    string Timestamp;
    string Type;

    // For real players these fields use Steam64 (PlayerIdentity.GetPlainId()).
    // Test accounts keep their explicit FENR test IDs.
    string SenderSteam64;
    string SenderName;

    // DIRECT: recipient Steam64
    // GROUP: group ID
    // CHANNEL: channel ID
    // BROADCAST: "BROADCAST"
    string TargetID;
    string TargetName;

    string Message;

    // v7.9: the log is also the PDA message store.
    int Seq;
    string GameTime;       // HH:MM in-game clock shown on the PDA
    string SenderDevice;   // v8.1: account key the copy was filed under ("" = none); before: device key
    string SenderConvID;   // conversation ID on the sender's PDA
    string TargetDevice;   // v8.1: recipient account key ("" = not delivered, e.g. blocked)
};

class FENR_PDA_MessageSearch
{
    string Query;
    string Type;
    void FENR_PDA_MessageSearch()
    {
        Query = "";
        Type = "";
    }
};


class FENR_PDA_AdminSearchResult
{
    ref array<string> Headers;
    ref array<string> Bodies;
    int Total;

    void FENR_PDA_AdminSearchResult()
    {
        Headers = new array<string>();
        Bodies = new array<string>();
        Total = 0;
    }
};
