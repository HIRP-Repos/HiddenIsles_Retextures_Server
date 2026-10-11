/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Shared constants for the streamlined codebase.
*/

const string FENR_PDA_RPC_NAMESPACE = "[FENR_PDA] ";

class FENR_PDA_Paths
{
    // Existing player-facing persistence stays under $profile:\PDA for compatibility.
    static const string PROFILE_ROOT = "$profile:\\PDA\\";
    static const string CONFIG_ROOT = "$profile:\\PDA\\Config\\";
    static const string LOG_ROOT = "$profile:\\PDA\\Logs\\";

    // New simplified message schema is isolated from the legacy archive schema.
    static const string MESSAGE_LOG_ROOT = "$profile:\\PDA\\MessageLogs\\";

    static const string GROUP_ROOT = "$profile:\\PDA\\Groups\\";
    static const string GROUP_MESSAGE_ROOT = "$profile:\\PDA\\Groups\\Messages\\";

    static const string TRADE_ROOT = "$profile:\\PDA\\Trade\\";
    static const string MARKER_ROOT = "$profile:\\PDA\\Markers\\";
    static const string BOUNTY_ROOT = "$profile:\\PDA\\Bounties\\";
    static const string DRIVE_ROOT = "$profile:\\PDA\\Drives\\";
    static const string DEVICE_ROOT = "$profile:\\PDA\\Devices\\";     // v7.8-8.0 per-PDA memory (migrated)
    static const string ACCOUNT_ROOT = "$profile:\\PDA\\Accounts\\";   // v8.1 per-player memory
};

class FENR_PDA_Limits
{
    static const int CONTACT_NAME = 32;
    static const int DIRECT_MESSAGE = 256;
    static const int DIRECT_HISTORY = 100;
    static const int GROUP_NAME = 32;
    static const int GROUP_MESSAGE = 256;
    static const int GROUP_HISTORY = 100;
    static const int GROUP_MEMBERS = 25;
    static const int OWNED_GROUPS = 10;
    static const int ADMIN_BROADCAST = 256;
};

class FENR_PDA_ChannelIds
{
    static const string ANNOUNCEMENTS = "StalkerZ_ANNOUNCEMENTS";
    static const string GLOBAL = "StalkerZ_GLOBAL";
    static const string BUY_SELL = "StalkerZ_BUYSELL";

    static bool IsChannel(string id)
    {
        return id == ANNOUNCEMENTS || id == GLOBAL || id == BUY_SELL;
    }

    static string Label(string id)
    {
        if (id == ANNOUNCEMENTS) return "Announcements";
        if (id == GLOBAL) return "Global";
        if (id == BUY_SELL) return "Buy/Sell";
        return id;
    }
};

class FENR_PDA_MessageType
{
    static const string DIRECT = "DIRECT";
    static const string GROUP = "GROUP";
    static const string CHANNEL = "CHANNEL";
    static const string BROADCAST = "BROADCAST";
};

class FENR_PDA_Rpc
{
    // Core / contacts
    static const string USER_ID = "GetVisualUserId";
    static const string ADD_CONTACT = "AddContact";
    static const string CHECK_CONTACTS = "CheckContacts";
    static const string SEND_MESSAGE = "SendMessage";
    static const string SYNC_TEST_ACCOUNTS = "SyncTestAccounts";
    static const string NETWORK_STATUS = "NetworkStatus";
    static const string PDA_USAGE = "PdaUsage";
    static const string PDA_NOTICE = "PdaNotice";

    // Trade board
    static const string TRADE_LIST = "TradeList";
    static const string TRADE_CREATE = "TradeCreate";
    static const string TRADE_UPDATE = "TradeUpdate";
    static const string TRADE_RESULT = "TradeResult";
    static const string TRADE_CONTACT = "TradeContact";
    static const string REP_GET = "RepGet";
    static const string REP_VOTE = "RepVote";

    // Bounty board
    static const string BOUNTY_LIST = "BountyList";
    static const string BOUNTY_POST = "BountyPost";
    static const string BOUNTY_ACTION = "BountyAction";
    static const string BOUNTY_RESULT = "BountyResult";
    static const string BOUNTY_NOTIFY = "BountyNotify";

    // Data drives
    static const string DRIVE_STATUS = "DriveStatus";
    static const string DRIVE_READ = "DriveRead";
    static const string DRIVE_WRITE = "DriveWrite";
    static const string DRIVE_RESULT = "DriveResult";
    static const string DRIVE_DATA = "DriveData";
    static const string DRIVE_FILE = "DriveFile";
    static const string DRIVE_SOURCE = "DriveSource";

    // Per-PDA memory (server-side device store)
    static const string DEVICE_SYNC = "DeviceSync";
    static const string DEVICE_CONVO = "DeviceConvo";
    static const string DEVICE_CONTACT_OP = "DeviceContactOp";
    static const string DEVICE_SAVE_NOTES = "DeviceSaveNotes";
    static const string DEVICE_SAVE_MARKERS = "DeviceSaveMarkers";
    static const string DEVICE_RESYNC = "DeviceResync";
    static const string DEVICE_HUD = "DeviceHud";

    // Login sessions
    static const string SESSION_STATE = "FenrSessionState";
    static const string SESSION_LOGIN = "FenrSessionLogin";
    static const string SESSION_LOGOUT = "FenrSessionLogout";

    // S.O.S
    static const string SOS_GET = "SosGet";
    static const string SOS_SET = "SosSet";
    static const string SOS_SEND = "SosSend";
    static const string SOS_RESULT = "SosResult";
    static const string SOS_ALERT = "SosAlert";

    // Admin. Delete/mark-deleted intentionally does not exist.
    static const string ADMIN_STATUS = "AdminStatus";
    static const string ADMIN_SEARCH = "AdminSearchMessages";
    static const string ADMIN_PLAYERS = "AdminListPlayers";
    static const string ADMIN_BROADCAST = "AdminBroadcast";

    // Groups
    static const string GROUP_LIST = "GroupList";
    static const string GROUP_CREATE = "GroupCreate";
    static const string GROUP_RENAME = "GroupRename";
    static const string GROUP_DELETE = "GroupDelete";
    static const string GROUP_LEAVE = "GroupLeave";
    static const string GROUP_ADD_MEMBER = "GroupAddMember";
    static const string GROUP_REMOVE_MEMBER = "GroupRemoveMember";
    static const string GROUP_MEMBERS = "GroupMembers";
    static const string GROUP_HISTORY = "GroupHistory";
    static const string GROUP_SEND = "GroupSendMessage";
    static const string GROUP_INCOMING = "GroupIncomingMessage";
    static const string GROUP_REFRESH = "GroupRefresh";
    static const string GROUP_RESULT = "GroupActionResult";
};

class FENR_PDA_TradeType
{
    static const string BUY = "BUY";     // lister wants to buy  -> others contact the BUYER
    static const string SELL = "SELL";   // lister is selling    -> others contact the SELLER
    static const string MINE = "MINE";   // list filter only: the requesting player's own listings
};

class FENR_PDA_TradeStatus
{
    static const string OPEN = "OPEN";
    static const string PENDING = "PENDING";
    static const string CLOSED = "CLOSED";   // shown as SOLD (sell) / FILLED (buy)
};

class FENR_PDA_TradeAction
{
    static const string CREATE = "CREATE";
    static const string MARK_OPEN = "OPEN";
    static const string MARK_PENDING = "PENDING";
    static const string MARK_CLOSED = "CLOSED";
    static const string REMOVE = "REMOVE";
};

class FENR_PDA_TradeLimits
{
    static const int TITLE = 32;
    static const int PRICE = 24;
    static const int DESCRIPTION = 200;
    static const int PAGE_SIZE = 20;      // 4 x 5 board grid
    static const int FIELD_STRIDE = 11;   // strings per listing in TradeList payloads
};

class FENR_PDA_TradeCategory
{
    static const string ALL = "ALL";            // board filter only
    static const string GUNS = "GUNS";
    static const string AMMO = "AMMO";
    static const string MEDICAL = "MEDICAL";
    static const string TOOLS = "TOOLS";
    static const string CLOTHING = "CLOTHING";
    static const string OTHER = "OTHER";

    // Maps pre-7.8 categories onto the current set.
    static string Normalize(string category)
    {
        if (category == "RIFLE" || category == "PISTOL") return GUNS;
        if (category == "BUILD") return TOOLS;
        if (category == GUNS || category == AMMO || category == MEDICAL || category == TOOLS || category == CLOTHING) return category;
        return OTHER;
    }

    static bool IsValid(string category)
    {
        return category == GUNS || category == AMMO || category == MEDICAL || category == TOOLS || category == CLOTHING || category == OTHER;
    }

    static string Label(string category)
    {
        if (category == ALL) return ALL;
        return Normalize(category);
    }

    static string Icon(string category)
    {
        string c = Normalize(category);
        if (c == GUNS) return "cat_pistol";
        if (c == AMMO) return "cat_ammo";
        if (c == MEDICAL) return "cat_cross";
        if (c == TOOLS) return "cat_hammer";
        if (c == CLOTHING) return "cat_clothing";
        return "cat_other";
    }
};

class FENR_PDA_BountyStatus
{
    static const string OPEN = "OPEN";
    static const string CLAIMED = "CLAIMED";
    static const string COMPLETED = "COMPLETED";
};

class FENR_PDA_BountyAction
{
    static const string POST = "POST";
    static const string CLAIM = "CLAIM";
    static const string CONFIRM = "CONFIRM";
    static const string REJECT = "REJECT";
    static const string CANCEL = "CANCEL";
    static const string REMOVE = "REMOVE";
};

class FENR_PDA_BountyLimits
{
    static const string BOARD_ACTIVE = "ACTIVE";
    static const string BOARD_MINE = "MINE";
    static const int TARGET = 32;
    static const int REWARD = 40;
    static const int REASON = 160;
    static const int NOTE = 120;
    static const int PAGE_SIZE = 12;      // 3 x 4 board grid
    static const int FIELD_STRIDE = 12;
};

class FENR_PDA_DriveKind
{
    static const string INTEL = "INTEL";
    static const string ENCRYPTED = "ENCRYPTED";

    static string Slot(string kind)
    {
        if (kind == INTEL) return "FENR_PDAIntelDrive";
        if (kind == ENCRYPTED) return "FENR_PDAEncryptedDrive";
        return "";
    }
};

class FENR_PDA_DriveAction
{
    static const string WRITE = "WRITE";
    static const string WIPE = "WIPE";
    static const string CONSUME = "CONSUME";   // decrypted intel closed: the drive burns out
};

class FENR_PDA_DriveFolder
{
    static const string CONVERSATIONS = "CONV";
    static const string GROUPS = "GROUP";
    static const string MARKERS = "MARK";

    static string Label(string folder)
    {
        if (folder == CONVERSATIONS) return "CONVERSATIONS";
        if (folder == GROUPS) return "GROUP CONVERSATIONS";
        if (folder == MARKERS) return "IMPORTANT MARKERS";
        return folder;
    }
};

class FENR_PDA_DriveLimits
{
    static const int FILES = 12;          // files per drive
    static const int LINES = 100;         // messages per conversation file
    static const int MARKERS = 40;        // markers per marker file
    static const string CORRUPT = "CORRUPT";
};

// What the PDA in a player's hands is doing (SESSION_STATE).
class FENR_PDA_SessionState
{
    static const int LOCKED = 0;      // nobody logged in: login screen
    static const int OWNER = 1;       // logged in as this player
    static const int GUEST = 2;       // logged in as someone else: read-only
    static const int NO_POWER = 3;    // no powered PDA in hands
};

class FENR_PDA_ContactOp
{
    static const string ADD = "ADD";
    static const string REMOVE = "REMOVE";
    static const string RENAME = "RENAME";
    static const string BLOCK = "BLOCK";
    static const string MUTE = "MUTE";
    static const string READ = "READ";
};
