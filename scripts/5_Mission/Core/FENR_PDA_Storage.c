/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Single persistence boundary for client state, groups, configuration and
    server audit data. Gameplay systems do not need to know how JSON is stored.
*/

class FENR_PDA_Storage
{
    static const string CONFIG_FILE = "$profile:\\PDA\\Config\\FenrirIndustriesPDA.json";
    static const string LEGACY_LOG_CONFIG_FILE = "$profile:\\PDA\\Config\\Logging.json";
    static const string LEGACY_TEST_CONFIG_FILE = "$profile:\\PDA\\Config\\TestAccounts.json";
    static const string REGISTRY_FILE = "$profile:\\PDA\\Logs\\FENR_FileRegistry.json";
    static const string GROUPS_FILE = "$profile:\\PDA\\Groups\\Groups.json";
    static const string KNOWN_PLAYERS_FILE = "$profile:\\PDA\\KnownPlayers.json";
    static const string TRADE_FILE = "$profile:\\PDA\\Trade\\Listings.json";
    static const string REPUTATION_FILE = "$profile:\\PDA\\Trade\\Reputation.json";
    static const string BOUNTY_FILE = "$profile:\\PDA\\Bounties\\Bounties.json";
    static const string INTEL_FILE = "$profile:\\PDA\\Config\\IntelFiles.json";

    protected static ref FENR_PDA_Config s_Config;
    protected static ref FENR_PDA_LogRegistry s_Registry;
    protected static ref array<ref FENR_PDA_KnownPlayer> s_KnownPlayers;
    protected static ref map<string, FENR_PDA_KnownPlayer> s_KnownBySteam;
    protected static ref map<string, FENR_PDA_KnownPlayer> s_KnownByLegacy;
    protected static bool s_ServerInitialized = false;

    protected static string s_CurrentMessageBucket = "";
    protected static string s_CurrentMessagePath = "";
    protected static ref array<ref FENR_PDA_MessageRecord> s_CurrentMessages;

    // ---------------------------------------------------------------------
    // Initialization / common paths
    // ---------------------------------------------------------------------
    static void InitClient()
    {
        MakeDirectory(FENR_PDA_Paths.PROFILE_ROOT);
        MakeDirectory(FENR_PDA_Paths.CONFIG_ROOT);
    }

    static void InitServer()
    {
        if (s_ServerInitialized || !GetGame().IsServer())
            return;
        // Set first: logging during startup cleanup calls back into here.
        s_ServerInitialized = true;

        InitClient();
        MakeDirectory(FENR_PDA_Paths.LOG_ROOT);
        MakeDirectory(FENR_PDA_Paths.MESSAGE_LOG_ROOT);
        MakeDirectory(FENR_PDA_Paths.GROUP_ROOT);
        MakeDirectory(FENR_PDA_Paths.GROUP_MESSAGE_ROOT);
        MakeDirectory(FENR_PDA_Paths.TRADE_ROOT);
        MakeDirectory(FENR_PDA_Paths.BOUNTY_ROOT);
        MakeDirectory(FENR_PDA_Paths.DRIVE_ROOT);
        MakeDirectory(FENR_PDA_Paths.DEVICE_ROOT);

        LoadConfig();
        LoadRegistry();
        LoadKnownPlayers();
        EnsureCurrentMessageFile();
        CleanupExpired();

        int cleanupMs = s_Config.CleanupIntervalHours * 60 * 60 * 1000;
        if (cleanupMs < 3600000)
            cleanupMs = 3600000;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CleanupExpired, cleanupMs, true);
        LogSystem("Fenrir Industries PDA storage initialized.");
    }

    static string TwoDigit(int value)
    {
        if (value < 10)
            return "0" + value.ToString();
        return value.ToString();
    }

    static string DayStamp()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return year.ToString() + "-" + TwoDigit(month) + "-" + TwoDigit(day);
    }

    static string Timestamp()
    {
        int year, month, day;
        int hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);
        return year.ToString() + "-" + TwoDigit(month) + "-" + TwoDigit(day) + " " + TwoDigit(hour) + ":" + TwoDigit(minute) + ":" + TwoDigit(second);
    }

    static string HourStamp()
    {
        int year, month, day;
        int hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);
        return year.ToString() + "-" + TwoDigit(month) + "-" + TwoDigit(day) + "_" + TwoDigit(hour);
    }

    static int DateToSerial(int year, int month, int day)
    {
        if (month < 3)
        {
            year = year - 1;
            month = month + 12;
        }

        return (365 * year) + (year / 4) - (year / 100) + (year / 400) + ((153 * (month - 3) + 2) / 5) + day - 1;
    }

    static int TodaySerial()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return DateToSerial(year, month, day);
    }

    // ---------------------------------------------------------------------
    // Legacy client files (pre-7.8), read once for the device migration
    // ---------------------------------------------------------------------
    static ref array<ref FENR_PDA_Contact> LoadContacts(string path)
    {
        ref array<ref FENR_PDA_Contact> data = new array<ref FENR_PDA_Contact>();
        if (FileExist(path))
            JsonFileLoader<ref array<ref FENR_PDA_Contact>>.JsonLoadFile(path, data);
        return data;
    }

    static ref FENR_PDA_Note LoadNotes(string path)
    {
        ref FENR_PDA_Note data = new FENR_PDA_Note();
        if (FileExist(path))
            JsonFileLoader<ref FENR_PDA_Note>.JsonLoadFile(path, data);
        if (!data)
            data = new FENR_PDA_Note();
        return data;
    }

    // ---------------------------------------------------------------------
    // Known PDA identities (Steam64 canonicalization / legacy compatibility)
    // ---------------------------------------------------------------------
    protected static void LoadKnownPlayers()
    {
        s_KnownPlayers = new array<ref FENR_PDA_KnownPlayer>();
        if (FileExist(KNOWN_PLAYERS_FILE))
            JsonFileLoader<ref array<ref FENR_PDA_KnownPlayer>>.JsonLoadFile(KNOWN_PLAYERS_FILE, s_KnownPlayers);
        if (!s_KnownPlayers)
            s_KnownPlayers = new array<ref FENR_PDA_KnownPlayer>();

        // Entries from before 7.9 have no LastSeen: start their clock today.
        int today = TodaySerial();
        foreach (FENR_PDA_KnownPlayer known : s_KnownPlayers)
        {
            if (known && known.LastSeen <= 0)
                known.LastSeen = today;
        }
        RebuildKnownIndex();
    }

    protected static void RebuildKnownIndex()
    {
        s_KnownBySteam = new map<string, FENR_PDA_KnownPlayer>();
        s_KnownByLegacy = new map<string, FENR_PDA_KnownPlayer>();
        foreach (FENR_PDA_KnownPlayer known : s_KnownPlayers)
            IndexKnown(known);
    }

    protected static void IndexKnown(FENR_PDA_KnownPlayer known)
    {
        if (!known)
            return;
        if (known.Steam64 != "")
            s_KnownBySteam.Set(known.Steam64, known);
        if (known.LegacyID != "")
            s_KnownByLegacy.Set(known.LegacyID, known);
    }

    protected static void SaveKnownPlayers()
    {
        if (!s_KnownPlayers)
            s_KnownPlayers = new array<ref FENR_PDA_KnownPlayer>();
        JsonFileLoader<ref array<ref FENR_PDA_KnownPlayer>>.JsonSaveFile(KNOWN_PLAYERS_FILE, s_KnownPlayers);
    }

    protected static FENR_PDA_KnownPlayer FindKnown(string id)
    {
        if (id == "")
            return null;
        if (!s_KnownPlayers)
            LoadKnownPlayers();
        FENR_PDA_KnownPlayer known = s_KnownBySteam.Get(id);
        if (!known)
            known = s_KnownByLegacy.Get(id);
        return known;
    }

    // Called when a player connects / uses the PDA (not on every lookup).
    static void RememberIdentity(PlayerIdentity identity)
    {
        if (!GetGame().IsServer() || !identity)
            return;
        if (!s_KnownPlayers)
            LoadKnownPlayers();

        string steam64 = identity.GetPlainId();
        string legacyID = identity.GetId();
        string name = identity.GetName();
        int today = TodaySerial();

        FENR_PDA_KnownPlayer known = FindKnown(steam64);
        if (!known)
            known = FindKnown(legacyID);
        if (known)
        {
            bool changed = known.Steam64 != steam64 || known.LegacyID != legacyID || known.Name != name || known.LastSeen != today;
            if (!changed)
                return;
            known.Steam64 = steam64;
            known.LegacyID = legacyID;
            known.Name = name;
            known.LastSeen = today;
            IndexKnown(known);
            SaveKnownPlayers();
            return;
        }

        ref FENR_PDA_KnownPlayer created = new FENR_PDA_KnownPlayer(steam64, legacyID, name);
        created.LastSeen = today;
        s_KnownPlayers.Insert(created);
        IndexKnown(created);
        SaveKnownPlayers();
    }

    static void RememberContact(string id, string name)
    {
        if (!GetGame().IsServer() || id == "")
            return;
        if (!s_KnownPlayers)
            LoadKnownPlayers();

        FENR_PDA_KnownPlayer known = FindKnown(id);
        if (known)
        {
            if (name != "" && known.Name != name)
            {
                known.Name = name;
                SaveKnownPlayers();
            }
            return;
        }

        ref FENR_PDA_KnownPlayer created;
        if (id.Length() == 17)
            created = new FENR_PDA_KnownPlayer(id, "", name);
        else
            created = new FENR_PDA_KnownPlayer("", id, name);
        created.LastSeen = TodaySerial();
        s_KnownPlayers.Insert(created);
        IndexKnown(created);
        SaveKnownPlayers();
    }

    // Name matching is only for explicit "find player by name" lookups:
    // names are not unique and anyone can change theirs.
    static string ResolveSteam64(string lookup, bool allowName = false)
    {
        if (lookup == "")
            return "";
        if (lookup.Length() == 17)
            return lookup;

        FENR_PDA_KnownPlayer known = FindKnown(lookup);
        if (known)
            return known.Steam64;
        if (!allowName)
            return "";

        foreach (FENR_PDA_KnownPlayer candidate : s_KnownPlayers)
        {
            if (candidate && candidate.Name == lookup)
                return candidate.Steam64;
        }
        return "";
    }

    static string ResolvePlayerName(string lookup)
    {
        if (lookup == "")
            return "";
        FENR_PDA_KnownPlayer known = FindKnown(lookup);
        if (known)
            return known.Name;
        return "";
    }

    // Forget players not seen for `days` days.
    static void PruneKnownPlayers(int days)
    {
        if (days <= 0)
            return;
        if (!s_KnownPlayers)
            LoadKnownPlayers();
        int today = TodaySerial();
        int removed = 0;
        for (int i = s_KnownPlayers.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_KnownPlayer known = s_KnownPlayers[i];
            if (!known || today - known.LastSeen >= days)
            {
                s_KnownPlayers.RemoveOrdered(i);
                removed++;
            }
        }
        if (removed > 0)
        {
            RebuildKnownIndex();
            SaveKnownPlayers();
            LogSystem("Pruned " + removed.ToString() + " players not seen for " + days.ToString() + " days.");
        }
    }

    // ---------------------------------------------------------------------
    // Group persistence
    // ---------------------------------------------------------------------
    static ref array<ref FENR_PDA_Group> LoadGroups()
    {
        ref array<ref FENR_PDA_Group> groups = new array<ref FENR_PDA_Group>();
        if (FileExist(GROUPS_FILE))
            JsonFileLoader<ref array<ref FENR_PDA_Group>>.JsonLoadFile(GROUPS_FILE, groups);
        return groups;
    }

    static void SaveGroups(array<ref FENR_PDA_Group> groups)
    {
        ref array<ref FENR_PDA_Group> groupsToSave = groups;
        if (!groupsToSave)
            groupsToSave = new array<ref FENR_PDA_Group>();
        JsonFileLoader<ref array<ref FENR_PDA_Group>>.JsonSaveFile(GROUPS_FILE, groupsToSave);
    }

    // ---------------------------------------------------------------------
    // Trade board
    // ---------------------------------------------------------------------
    static ref array<ref FENR_PDA_TradeListing> LoadTradeListings()
    {
        ref array<ref FENR_PDA_TradeListing> listings = new array<ref FENR_PDA_TradeListing>();
        if (FileExist(TRADE_FILE))
            JsonFileLoader<ref array<ref FENR_PDA_TradeListing>>.JsonLoadFile(TRADE_FILE, listings);
        if (!listings)
            listings = new array<ref FENR_PDA_TradeListing>();
        return listings;
    }

    static void SaveTradeListings(array<ref FENR_PDA_TradeListing> listings)
    {
        ref array<ref FENR_PDA_TradeListing> toSave = listings;
        if (!toSave)
            toSave = new array<ref FENR_PDA_TradeListing>();
        JsonFileLoader<ref array<ref FENR_PDA_TradeListing>>.JsonSaveFile(TRADE_FILE, toSave);
    }

    // ---------------------------------------------------------------------
    // Battery drain configuration
    // ---------------------------------------------------------------------
    static bool BatteryDrainEnabled()
    {
        if (!s_Config)
            LoadConfig();
        return s_Config && s_Config.BatteryDrainEnabled;
    }

    static float BatteryDrainOpenPerMinute()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.BatteryDrainOpenPercentPerMinute < 0)
            return 0;
        return s_Config.BatteryDrainOpenPercentPerMinute;
    }

    static float BatteryDrainMapPerMinute()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.BatteryDrainMapPercentPerMinute < 0)
            return 0;
        return s_Config.BatteryDrainMapPercentPerMinute;
    }

    // Legacy client map markers (one file per terrain, pre-7.8)
    static string MarkerPath(string worldName)
    {
        return FENR_PDA_Paths.MARKER_ROOT + worldName + ".json";
    }

    static ref array<ref FENR_PDA_MapMarker> LoadMarkers(string worldName)
    {
        ref array<ref FENR_PDA_MapMarker> markers = new array<ref FENR_PDA_MapMarker>();
        string path = MarkerPath(worldName);
        if (FileExist(path))
            JsonFileLoader<ref array<ref FENR_PDA_MapMarker>>.JsonLoadFile(path, markers);
        if (!markers)
            markers = new array<ref FENR_PDA_MapMarker>();
        return markers;
    }

    static ref FENR_PDA_RepData LoadReputation()
    {
        ref FENR_PDA_RepData data = new FENR_PDA_RepData();
        if (FileExist(REPUTATION_FILE))
            JsonFileLoader<ref FENR_PDA_RepData>.JsonLoadFile(REPUTATION_FILE, data);
        if (!data)
            data = new FENR_PDA_RepData();
        if (!data.Votes)
            data.Votes = new array<ref FENR_PDA_RepVote>();
        if (!data.Pairs)
            data.Pairs = new array<ref FENR_PDA_TradePair>();
        return data;
    }

    static void SaveReputation(FENR_PDA_RepData data)
    {
        if (!data)
            return;
        JsonFileLoader<ref FENR_PDA_RepData>.JsonSaveFile(REPUTATION_FILE, data);
    }

    static ref array<ref FENR_PDA_Bounty> LoadBounties()
    {
        ref array<ref FENR_PDA_Bounty> bounties = new array<ref FENR_PDA_Bounty>();
        if (FileExist(BOUNTY_FILE))
            JsonFileLoader<ref array<ref FENR_PDA_Bounty>>.JsonLoadFile(BOUNTY_FILE, bounties);
        if (!bounties)
            bounties = new array<ref FENR_PDA_Bounty>();
        return bounties;
    }

    static void SaveBounties(array<ref FENR_PDA_Bounty> bounties)
    {
        ref array<ref FENR_PDA_Bounty> toSave = bounties;
        if (!toSave)
            toSave = new array<ref FENR_PDA_Bounty>();
        JsonFileLoader<ref array<ref FENR_PDA_Bounty>>.JsonSaveFile(BOUNTY_FILE, toSave);
    }

    static bool BountyEnabled()
    {
        if (!s_Config)
            LoadConfig();
        return s_Config && s_Config.BountyEnabled;
    }

    static int BountyMaxPerPlayer()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.BountyMaxPerPlayer < 1)
            return 3;
        return s_Config.BountyMaxPerPlayer;
    }

    static int BountyDays()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.BountyDays < 1)
            return 7;
        return s_Config.BountyDays;
    }

    // ---------------------------------------------------------------------
    // Data drives + intel pool
    // ---------------------------------------------------------------------
    static string DrivePath(string driveKey)
    {
        return FENR_PDA_Paths.DRIVE_ROOT + driveKey + ".json";
    }

    static ref FENR_PDA_DriveData LoadDrive(string driveKey)
    {
        string path = DrivePath(driveKey);
        if (!FileExist(path))
            return null;
        ref FENR_PDA_DriveData data = new FENR_PDA_DriveData();
        JsonFileLoader<ref FENR_PDA_DriveData>.JsonLoadFile(path, data);
        if (!data)
            return null;
        if (!data.Files)
            data.Files = new array<ref FENR_PDA_DriveFile>();
        return data;
    }

    static void SaveDrive(string driveKey, FENR_PDA_DriveData data)
    {
        if (!data)
            return;
        MakeDirectory(FENR_PDA_Paths.DRIVE_ROOT);
        JsonFileLoader<ref FENR_PDA_DriveData>.JsonSaveFile(DrivePath(driveKey), data);
    }

    static void DeleteDrive(string driveKey)
    {
        string path = DrivePath(driveKey);
        if (FileExist(path))
            DeleteFile(path);
    }

    static ref array<ref FENR_PDA_IntelFile> LoadIntel()
    {
        ref array<ref FENR_PDA_IntelFile> files = new array<ref FENR_PDA_IntelFile>();
        if (FileExist(INTEL_FILE))
        {
            JsonFileLoader<ref array<ref FENR_PDA_IntelFile>>.JsonLoadFile(INTEL_FILE, files);
            if (!files)
                files = new array<ref FENR_PDA_IntelFile>();
            return files;
        }

        // First run: write a small example pool admins can edit.
        ref FENR_PDA_IntelFile first = new FENR_PDA_IntelFile();
        first.ID = "intel_example_01";
        first.Title = "RECOVERED LOG // CHECKPOINT 7";
        first.Body = "Day 41. The north checkpoint fell last night. Supplies were moved to the old radio tower before the gate went down. Code for the crate is the year the tower was built.";
        first.Weight = 1;
        files.Insert(first);
        ref FENR_PDA_IntelFile second = new FENR_PDA_IntelFile();
        second.ID = "intel_example_02";
        second.Title = "FENRIR INDUSTRIES // FIELD MEMO";
        second.Body = "All field units: secure network relays are to be considered compromised. Use encrypted drives for marker exchange only. Do not trust unsigned broadcasts.";
        second.Weight = 1;
        files.Insert(second);
        SaveIntel(files);
        return files;
    }

    static void SaveIntel(array<ref FENR_PDA_IntelFile> files)
    {
        if (!files)
            return;
        MakeDirectory(FENR_PDA_Paths.CONFIG_ROOT);
        JsonFileLoader<ref array<ref FENR_PDA_IntelFile>>.JsonSaveFile(INTEL_FILE, files);
    }

    static int DeviceInactiveDays()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.DeviceInactiveDays < 0)
            return 0;
        return s_Config.DeviceInactiveDays;
    }

    static int EncryptedDriveDays()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.EncryptedDriveDays < 1)
            return 7;
        return s_Config.EncryptedDriveDays;
    }


    // Login session length players can pick (1-24 hours).
    static int SessionMinHours()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config)
            return 1;
        return Math.Clamp(s_Config.SessionMinHours, 1, 24);
    }

    static int SessionMaxHours()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config)
            return 4;
        int maxHours = Math.Clamp(s_Config.SessionMaxHours, 1, 24);
        if (maxHours < SessionMinHours())
            maxHours = SessionMinHours();
        return maxHours;
    }

    static bool SosEnabled()
    {
        if (!s_Config)
            LoadConfig();
        return s_Config && s_Config.SosEnabled;
    }

    static int SosMaxContacts()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.SosMaxContacts < 1)
            return 5;
        if (s_Config.SosMaxContacts > 20)
            return 20;
        return s_Config.SosMaxContacts;
    }

    static int SosPingMinutes()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.SosPingMinutes < 1)
            return 30;
        return s_Config.SosPingMinutes;
    }

    // How far back PDA message history is rebuilt from the log.
    static int MessageHistoryDays()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config)
            return 30;
        if (s_Config.MessageLogsDays <= 0)
            return 90;   // logs kept forever: rebuild the last 90 days
        return s_Config.MessageLogsDays;
    }

    static bool TradeEnabled()
    {
        if (!s_Config)
            LoadConfig();
        return s_Config && s_Config.TradeEnabled;
    }

    static int TradeMaxListings()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.TradeMaxListingsPerPlayer < 1)
            return 5;
        return s_Config.TradeMaxListingsPerPlayer;
    }

    static int TradeListingDays()
    {
        if (!s_Config)
            LoadConfig();
        if (!s_Config || s_Config.TradeListingDays < 1)
            return 7;
        return s_Config.TradeListingDays;
    }

    static string GroupHistoryPath(string groupID)
    {
        return FENR_PDA_Paths.GROUP_MESSAGE_ROOT + groupID + ".json";
    }

    static ref array<ref FENR_PDA_GroupMessage> LoadGroupHistory(string groupID)
    {
        ref array<ref FENR_PDA_GroupMessage> messages = new array<ref FENR_PDA_GroupMessage>();
        string path = GroupHistoryPath(groupID);
        if (FileExist(path))
            JsonFileLoader<ref array<ref FENR_PDA_GroupMessage>>.JsonLoadFile(path, messages);
        return messages;
    }

    static void SaveGroupHistory(string groupID, array<ref FENR_PDA_GroupMessage> messages)
    {
        if (!messages)
            return;

        while (messages.Count() > FENR_PDA_Limits.GROUP_HISTORY)
            messages.RemoveOrdered(0);

        JsonFileLoader<ref array<ref FENR_PDA_GroupMessage>>.JsonSaveFile(GroupHistoryPath(groupID), messages);
    }

    static void DeleteGroupHistory(string groupID)
    {
        string path = GroupHistoryPath(groupID);
        if (FileExist(path))
            DeleteFile(path);
    }

    // ---------------------------------------------------------------------
    // Unified configuration
    // ---------------------------------------------------------------------
    static const int CONFIG_VERSION = 81;

    // New defaults an update applies once to an existing configuration.
    protected static void UpgradeConfig()
    {
        if (s_Config.ConfigVersion < 81)
        {
            // v8.1: shorter retention to keep server files small.
            s_Config.MessageLogsDays = 14;
            s_Config.EncryptedDriveDays = 7;
        }
        s_Config.ConfigVersion = CONFIG_VERSION;
    }

    protected static void LoadConfig()
    {
        s_Config = new FENR_PDA_Config();
        if (FileExist(CONFIG_FILE))
        {
            JsonFileLoader<ref FENR_PDA_Config>.JsonLoadFile(CONFIG_FILE, s_Config);
            if (!s_Config)
                s_Config = new FENR_PDA_Config();
            // Server only: apply update defaults once, then write back so keys
            // added by updates appear (with defaults).
            if (GetGame().IsServer())
            {
                UpgradeConfig();
                JsonFileLoader<ref FENR_PDA_Config>.JsonSaveFile(CONFIG_FILE, s_Config);
            }
            return;
        }
        s_Config.ConfigVersion = CONFIG_VERSION;

        // One-time migration from the earlier split configuration files.
        if (FileExist(LEGACY_LOG_CONFIG_FILE))
        {
            ref FENR_PDA_LegacyLogConfig legacyLog = new FENR_PDA_LegacyLogConfig();
            JsonFileLoader<ref FENR_PDA_LegacyLogConfig>.JsonLoadFile(LEGACY_LOG_CONFIG_FILE, legacyLog);
            if (legacyLog)
            {
                s_Config.LoggingEnabled = legacyLog.Enabled;
                s_Config.LogSystemEvents = legacyLog.LogSystemEvents;
                s_Config.LogAdminActions = legacyLog.LogAdminActions;
                s_Config.LogErrors = legacyLog.LogErrors;
                s_Config.MessageLogsDays = legacyLog.MessageLogsDays;
                s_Config.SystemLogsDays = legacyLog.SystemLogsDays;
                s_Config.ErrorLogsDays = legacyLog.ErrorLogsDays;
                s_Config.AdminLogsDays = legacyLog.AdminLogsDays;
                s_Config.CleanupIntervalHours = legacyLog.CleanupIntervalHours;
                s_Config.SearchResultsPerPage = legacyLog.SearchResultsPerPage;
            }
        }

        if (FileExist(LEGACY_TEST_CONFIG_FILE))
        {
            ref FENR_PDA_LegacyTestConfig legacyTest = new FENR_PDA_LegacyTestConfig();
            JsonFileLoader<ref FENR_PDA_LegacyTestConfig>.JsonLoadFile(LEGACY_TEST_CONFIG_FILE, legacyTest);
            if (legacyTest)
                s_Config.TestAccountsEnabled = legacyTest.Enabled;
        }

        JsonFileLoader<ref FENR_PDA_Config>.JsonSaveFile(CONFIG_FILE, s_Config);
    }

    static bool TestAccountsEnabled()
    {
        if (!s_Config)
            LoadConfig();
        return s_Config && s_Config.TestAccountsEnabled;
    }

    protected static void LoadRegistry()
    {
        s_Registry = new FENR_PDA_LogRegistry();
        if (FileExist(REGISTRY_FILE))
            JsonFileLoader<ref FENR_PDA_LogRegistry>.JsonLoadFile(REGISTRY_FILE, s_Registry);
        else
            SaveRegistry();

        if (!s_Registry)
            s_Registry = new FENR_PDA_LogRegistry();
    }

    protected static void SaveRegistry()
    {
        if (!s_Registry)
            s_Registry = new FENR_PDA_LogRegistry();
        JsonFileLoader<ref FENR_PDA_LogRegistry>.JsonSaveFile(REGISTRY_FILE, s_Registry);
    }

    protected static void RegisterFile(string path, string category, int daySerial)
    {
        if (!s_Registry)
            s_Registry = new FENR_PDA_LogRegistry();

        foreach (FENR_PDA_LogFileRecord record : s_Registry.Files)
        {
            if (record && record.Path == path)
                return;
        }

        s_Registry.Files.Insert(new FENR_PDA_LogFileRecord(path, category, daySerial));
        SaveRegistry();
    }

    protected static int RetentionFor(string category)
    {
        if (!s_Config)
            LoadConfig();

        if (category == "MESSAGE") return s_Config.MessageLogsDays;
        if (category == "ADMIN") return s_Config.AdminLogsDays;
        if (category == "ERROR") return s_Config.ErrorLogsDays;
        if (category == "DRIVE") return s_Config.DriveLogsDays;
        return s_Config.SystemLogsDays;
    }

    protected static void AppendTextLog(string category, string message)
    {
        if (!GetGame().IsServer())
            return;
        if (!s_ServerInitialized)
            InitServer();
        if (!s_Config || !s_Config.LoggingEnabled)
            return;

        string path = FENR_PDA_Paths.LOG_ROOT + category + "_" + DayStamp() + ".log";
        RegisterFile(path, category, TodaySerial());

        FileHandle handle = OpenFile(path, FileMode.APPEND);
        if (handle != 0)
        {
            FPrintln(handle, "[" + Timestamp() + "][" + category + "] " + message);
            CloseFile(handle);
        }
    }

    static void LogSystem(string message)
    {
        if (s_Config && !s_Config.LogSystemEvents)
            return;
        AppendTextLog("SYSTEM", message);
    }

    static void LogError(string message)
    {
        if (s_Config && !s_Config.LogErrors)
            return;
        AppendTextLog("ERROR", message);
    }

    static void LogAdmin(string adminName, string adminSteam64, string action, string target, string details = "")
    {
        if (s_Config && !s_Config.LogAdminActions)
            return;

        string line = "Admin=" + adminName + " Steam64=" + adminSteam64 + " Action=" + action + " Target=" + target;
        if (details != "")
            line = line + " Details=" + details;
        AppendTextLog("ADMIN", line);
    }

    // Drive write log: one JSON record per written drive, with its contents.
    // Always written (like the message log); kept DriveLogsDays.
    static void LogDrive(FENR_PDA_DriveLogRecord record)
    {
        if (!GetGame().IsServer() || !record)
            return;
        if (!s_ServerInitialized)
            InitServer();
        record.Timestamp = Timestamp();
        string line;
        if (!Json().WriteToString(record, false, line))
            return;
        MakeDirectory(FENR_PDA_Paths.LOG_ROOT);
        string path = FENR_PDA_Paths.LOG_ROOT + "Drives_" + DayStamp() + ".jsonl";
        RegisterFile(path, "DRIVE", TodaySerial());
        FileHandle handle = OpenFile(path, FileMode.APPEND);
        if (handle != 0)
        {
            FPrintln(handle, line);
            CloseFile(handle);
        }
    }

    // ---------------------------------------------------------------------
    // Simplified searchable message log
    // ---------------------------------------------------------------------
    protected static ref JsonSerializer s_Json;

    protected static JsonSerializer Json()
    {
        if (!s_Json)
            s_Json = new JsonSerializer();
        return s_Json;
    }

    protected static void EnsureCurrentMessageFile()
    {
        string bucket = HourStamp();
        if (s_CurrentMessages && s_CurrentMessageBucket == bucket)
            return;

        s_CurrentMessageBucket = bucket;
        s_CurrentMessagePath = FENR_PDA_Paths.MESSAGE_LOG_ROOT + "Messages_" + bucket + ".jsonl";
        s_CurrentMessages = ReadMessageFile(s_CurrentMessagePath);
        RegisterFile(s_CurrentMessagePath, "MESSAGE", TodaySerial());
    }

    // Appends one record to the hourly log (one JSON object per line).
    // Always written: since 7.9 the message log is also the PDA message store.
    static void RecordMessage(FENR_PDA_MessageRecord record)
    {
        if (!GetGame().IsServer() || !record)
            return;
        if (!s_ServerInitialized)
            InitServer();

        EnsureCurrentMessageFile();
        record.Timestamp = Timestamp();
        s_CurrentMessages.Insert(record);

        string line;
        if (!Json().WriteToString(record, false, line))
            return;
        FileHandle handle = OpenFile(s_CurrentMessagePath, FileMode.APPEND);
        if (handle != 0)
        {
            FPrintln(handle, line);
            CloseFile(handle);
        }
    }

    // .jsonl (7.9+): one record per line.  .json (older): one JSON array.
    static ref array<ref FENR_PDA_MessageRecord> ReadMessageFile(string path)
    {
        ref array<ref FENR_PDA_MessageRecord> entries = new array<ref FENR_PDA_MessageRecord>();
        if (!FileExist(path))
            return entries;

        if (path.IndexOf(".jsonl") == -1)
        {
            JsonFileLoader<ref array<ref FENR_PDA_MessageRecord>>.JsonLoadFile(path, entries);
            if (!entries)
                entries = new array<ref FENR_PDA_MessageRecord>();
            return entries;
        }

        FileHandle handle = OpenFile(path, FileMode.READ);
        if (handle == 0)
            return entries;
        string line;
        string error;
        while (FGets(handle, line) >= 0)
        {
            if (line.Length() < 2)
                continue;
            ref FENR_PDA_MessageRecord record = new FENR_PDA_MessageRecord();
            if (Json().ReadFromString(record, line, error))
                entries.Insert(record);
        }
        CloseFile(handle);
        return entries;
    }

    protected static ref array<ref FENR_PDA_MessageRecord> LoadMessageFile(string path)
    {
        EnsureCurrentMessageFile();
        if (path == s_CurrentMessagePath)
            return s_CurrentMessages;
        return ReadMessageFile(path);
    }

    // Message log files written on or after a day, oldest first.
    static void MessageFilesSince(int daySerial, array<string> paths)
    {
        paths.Clear();
        if (!s_Registry)
            LoadRegistry();
        foreach (FENR_PDA_LogFileRecord file : s_Registry.Files)
        {
            if (!file || file.Category != "MESSAGE" || file.DaySerial < daySerial)
                continue;
            if (file.Path.IndexOf(FENR_PDA_Paths.MESSAGE_LOG_ROOT) != 0)
                continue;
            if (FileExist(file.Path))
                paths.Insert(file.Path);
        }
    }

    protected static bool MessageMatches(FENR_PDA_MessageRecord record, FENR_PDA_MessageSearch filter)
    {
        if (!record || !filter)
            return false;

        if (filter.Type != "" && filter.Type != "ALL" && record.Type != filter.Type)
            return false;

        if (filter.Query == "")
            return true;

        if (record.Timestamp.IndexOf(filter.Query) != -1) return true;
        if (record.Type.IndexOf(filter.Query) != -1) return true;
        if (record.SenderSteam64.IndexOf(filter.Query) != -1) return true;
        if (record.SenderName.IndexOf(filter.Query) != -1) return true;
        if (record.TargetID.IndexOf(filter.Query) != -1) return true;
        if (record.TargetName.IndexOf(filter.Query) != -1) return true;
        if (record.Message.IndexOf(filter.Query) != -1) return true;
        return false;
    }

    static ref array<ref FENR_PDA_MessageRecord> SearchMessages(FENR_PDA_MessageSearch filter, int offset, int limit, out int totalMatches)
    {
        ref array<ref FENR_PDA_MessageRecord> results = new array<ref FENR_PDA_MessageRecord>();
        totalMatches = 0;

        if (!GetGame().IsServer())
            return results;
        if (!s_ServerInitialized)
            InitServer();
        ref FENR_PDA_MessageSearch searchFilter = filter;
        if (!searchFilter)
            searchFilter = new FENR_PDA_MessageSearch();

        if (limit <= 0) limit = 25;
        if (limit > 100) limit = 100;
        if (offset < 0) offset = 0;

        // Newest files and newest messages first: the viewer opens on current activity.
        for (int r = s_Registry.Files.Count() - 1; r >= 0; r--)
        {
            FENR_PDA_LogFileRecord file = s_Registry.Files[r];
            if (!file || file.Category != "MESSAGE")
                continue;
            if (file.Path.IndexOf(FENR_PDA_Paths.MESSAGE_LOG_ROOT) != 0)
                continue;
            if (!FileExist(file.Path))
                continue;

            ref array<ref FENR_PDA_MessageRecord> entries = LoadMessageFile(file.Path);
            for (int i = entries.Count() - 1; i >= 0; i--)
            {
                FENR_PDA_MessageRecord entry = entries[i];
                if (!MessageMatches(entry, searchFilter))
                    continue;

                if (totalMatches >= offset && results.Count() < limit)
                    results.Insert(entry);
                totalMatches++;
            }
        }

        return results;
    }

    static int SearchPageSize()
    {
        if (!s_Config)
            LoadConfig();
        int value = s_Config.SearchResultsPerPage;
        if (value < 10) value = 10;
        if (value > 50) value = 50;
        return value;
    }

    static string RetentionSummary()
    {
        if (!s_Config)
            LoadConfig();
        return "Messages: " + s_Config.MessageLogsDays.ToString() + "d | Admin: " + s_Config.AdminLogsDays.ToString() + "d | System: " + s_Config.SystemLogsDays.ToString() + "d";
    }

    static void CleanupExpired()
    {
        if (!GetGame().IsServer())
            return;
        if (!s_Config)
            LoadConfig();
        if (!s_Registry)
            LoadRegistry();

        int today = TodaySerial();
        bool changed = false;

        for (int i = s_Registry.Files.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_LogFileRecord file = s_Registry.Files[i];
            if (!file)
            {
                s_Registry.Files.RemoveOrdered(i);
                changed = true;
                continue;
            }

            int days = RetentionFor(file.Category);
            if (days <= 0)
                continue;

            if ((today - file.DaySerial) >= days)
            {
                if (FileExist(file.Path))
                    DeleteFile(file.Path);
                s_Registry.Files.RemoveOrdered(i);
                changed = true;
            }
        }

        if (changed)
            SaveRegistry();

        // PDA memory, players and encrypted drives that have gone stale.
        int inactiveDays = DeviceInactiveDays();
        FENR_PDA_AccountStore.Prune(inactiveDays);
        PruneKnownPlayers(inactiveDays);
        FENR_PDA_DriveService.Prune();
    }
};
