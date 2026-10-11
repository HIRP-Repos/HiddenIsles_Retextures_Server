/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Server boundary: RPC dispatch, online-player lookup, PDA validation and the
    lightweight test-account harness. Domain logic is delegated to Messages,
    Groups, Storage and Admin.
*/

class FENR_PDA_Server extends PluginBase
{
    EffectSound m_MessageSound;

    static const string TEST_ID_1 = "PDA_TEST_001";
    static const string TEST_ID_2 = "PDA_TEST_002";
    static const string TEST_ID_3 = "PDA_TEST_003";
    static const string TEST_NAME_1 = "Test User 1";
    static const string TEST_NAME_2 = "Test User 2";
    static const string TEST_NAME_3 = "Test User 3";

    override void OnInit()
    {
        super.OnInit();

        RegisterRpc(FENR_PDA_Rpc.USER_ID);
        RegisterRpc(FENR_PDA_Rpc.ADD_CONTACT);
        RegisterRpc(FENR_PDA_Rpc.CHECK_CONTACTS);
        RegisterRpc(FENR_PDA_Rpc.SEND_MESSAGE);
        RegisterRpc(FENR_PDA_Rpc.SYNC_TEST_ACCOUNTS);
        RegisterRpc(FENR_PDA_Rpc.NETWORK_STATUS);
        RegisterRpc(FENR_PDA_Rpc.PDA_USAGE);
        RegisterRpc(FENR_PDA_Rpc.PDA_NOTICE);

        RegisterRpc(FENR_PDA_Rpc.TRADE_LIST);
        RegisterRpc(FENR_PDA_Rpc.TRADE_CREATE);
        RegisterRpc(FENR_PDA_Rpc.TRADE_UPDATE);
        RegisterRpc(FENR_PDA_Rpc.TRADE_RESULT);
        RegisterRpc(FENR_PDA_Rpc.TRADE_CONTACT);
        RegisterRpc(FENR_PDA_Rpc.REP_GET);
        RegisterRpc(FENR_PDA_Rpc.REP_VOTE);

        RegisterRpc(FENR_PDA_Rpc.BOUNTY_LIST);
        RegisterRpc(FENR_PDA_Rpc.BOUNTY_POST);
        RegisterRpc(FENR_PDA_Rpc.BOUNTY_ACTION);
        RegisterRpc(FENR_PDA_Rpc.BOUNTY_RESULT);
        RegisterRpc(FENR_PDA_Rpc.BOUNTY_NOTIFY);

        RegisterRpc(FENR_PDA_Rpc.DRIVE_STATUS);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_READ);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_WRITE);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_RESULT);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_DATA);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_FILE);
        RegisterRpc(FENR_PDA_Rpc.DRIVE_SOURCE);

        RegisterRpc(FENR_PDA_Rpc.DEVICE_SYNC);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_CONVO);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_CONTACT_OP);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_SAVE_NOTES);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_SAVE_MARKERS);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_RESYNC);
        RegisterRpc(FENR_PDA_Rpc.DEVICE_HUD);

        RegisterRpc(FENR_PDA_Rpc.SESSION_STATE);
        RegisterRpc(FENR_PDA_Rpc.SESSION_LOGIN);
        RegisterRpc(FENR_PDA_Rpc.SESSION_LOGOUT);

        RegisterRpc(FENR_PDA_Rpc.SOS_GET);
        RegisterRpc(FENR_PDA_Rpc.SOS_SET);
        RegisterRpc(FENR_PDA_Rpc.SOS_SEND);
        RegisterRpc(FENR_PDA_Rpc.SOS_RESULT);
        RegisterRpc(FENR_PDA_Rpc.SOS_ALERT);

        RegisterRpc(FENR_PDA_Rpc.ADMIN_STATUS);
        RegisterRpc(FENR_PDA_Rpc.ADMIN_SEARCH);
        RegisterRpc(FENR_PDA_Rpc.ADMIN_PLAYERS);
        RegisterRpc(FENR_PDA_Rpc.ADMIN_BROADCAST);

        RegisterRpc(FENR_PDA_Rpc.GROUP_LIST);
        RegisterRpc(FENR_PDA_Rpc.GROUP_CREATE);
        RegisterRpc(FENR_PDA_Rpc.GROUP_RENAME);
        RegisterRpc(FENR_PDA_Rpc.GROUP_DELETE);
        RegisterRpc(FENR_PDA_Rpc.GROUP_LEAVE);
        RegisterRpc(FENR_PDA_Rpc.GROUP_ADD_MEMBER);
        RegisterRpc(FENR_PDA_Rpc.GROUP_REMOVE_MEMBER);
        RegisterRpc(FENR_PDA_Rpc.GROUP_MEMBERS);
        RegisterRpc(FENR_PDA_Rpc.GROUP_HISTORY);
        RegisterRpc(FENR_PDA_Rpc.GROUP_SEND);
        RegisterRpc(FENR_PDA_Rpc.GROUP_INCOMING);
        RegisterRpc(FENR_PDA_Rpc.GROUP_REFRESH);
        RegisterRpc(FENR_PDA_Rpc.GROUP_RESULT);

        if (GetGame().IsServer())
        {
            FENR_PDA_Storage.InitServer();
            FENR_PDA_AccountStore.Init();
            FENR_PDA_Sessions.Init();
            FENR_PDA_DriveService.Init();
            FENR_PDA_Groups.Init();
            FENR_PDA_Trade.Init();
            FENR_PDA_Power.Init();
            FENR_PDA_BountyBoard.Init();
        }

        if (GetGame().IsClient())
        {
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.USER_ID, new Param1<string>(""), true);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SYNC_TEST_ACCOUNTS, new Param1<bool>(true), true);
        }
    }

    protected void RegisterRpc(string rpcName)
    {
        GetRPCManager().AddRPC(FENR_PDA_RPC_NAMESPACE, rpcName, this, SingleplayerExecutionType.Both);
    }

    protected FENR_PDA_Client ClientState()
    {
        FENR_PDA_Client client;
        Class.CastTo(client, GetPlugin(FENR_PDA_Client));
        return client;
    }

    // ---------------------------------------------------------------------
    // Shared player/PDA helpers
    // ---------------------------------------------------------------------
    static bool IdentityMatches(PlayerIdentity identity, string storedID)
    {
        if (!identity || storedID == "")
            return false;
        return identity.GetPlainId() == storedID || identity.GetId() == storedID;
    }

    // Finds an online player by Steam64 or legacy ID.  Display names only
    // match when allowName is set (explicit "find by name" lookups): names
    // are not unique and anyone can change theirs.
    static PlayerBase FindOnlinePlayer(string lookup, bool allowName = false)
    {
        if (lookup == "")
            return null;

        string canonicalSteam64 = FENR_PDA_Storage.ResolveSteam64(lookup, allowName);
        PlayerBase byName = null;
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;

            PlayerIdentity identity = player.GetIdentity();
            string plainID = identity.GetPlainId();
            if (plainID == lookup || identity.GetId() == lookup || (canonicalSteam64 != "" && plainID == canonicalSteam64))
                return player;
            if (allowName && !byName && identity.GetName() == lookup)
                byName = player;
        }
        return byName;
    }

    static PlayerBase PlayerOf(PlayerIdentity identity)
    {
        if (!identity)
            return null;
        return FindOnlinePlayer(identity.GetPlainId());
    }

    // Steam64 and legacy ID -> player, built in one pass.
    static void FillOnlinePlayers(map<string, PlayerBase> output)
    {
        output.Clear();
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;
            output.Set(player.GetIdentity().GetPlainId(), player);
            output.Set(player.GetIdentity().GetId(), player);
        }
    }

    static bool IsWorkingDevice(EntityAI entity)
    {
        FENR_PDA_Device device;
        if (!FENR_PDA_Device.CastTo(device, entity))
            return false;
        if (device.IsRuined() || !device.HasEnergyManager() || !device.GetCompEM())
            return false;
        return device.GetCompEM().CanWork();
    }

    // The PDA a player opens / logs in on: the one in hands, else the first
    // powered one carried, else the first intact one.  Requests made through
    // the open PDA and battery drain use this choice; live traffic and the
    // compass use FENR_PDA_Sessions.ActiveDevice (logged-in PDAs only).
    static FENR_PDA_Device FindDevice(PlayerBase player)
    {
        if (!player)
            return null;

        FENR_PDA_Device device = FENR_PDA_Device.Cast(player.GetItemInHands());
        if (device && !device.IsRuined())
            return device;

        FENR_PDA_Device fallback = null;
        ref array<EntityAI> inventory = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
        foreach (EntityAI entity : inventory)
        {
            FENR_PDA_Device candidate = FENR_PDA_Device.Cast(entity);
            if (!candidate || candidate.IsRuined())
                continue;
            if (IsWorkingDevice(candidate))
                return candidate;
            if (!fallback)
                fallback = candidate;
        }
        return fallback;
    }

    // ------------------------------------------------------------------
    // Request guards
    // ------------------------------------------------------------------
    protected static ref map<string, float> s_Tokens;
    protected static ref map<string, int> s_TokenTime;

    // Token bucket per player and action: `capacity` requests at once,
    // refilled at `perSecond`.
    static bool Throttle(PlayerIdentity identity, string bucket, float capacity, float perSecond)
    {
        if (!identity)
            return false;
        if (!s_Tokens) s_Tokens = new map<string, float>();
        if (!s_TokenTime) s_TokenTime = new map<string, int>();

        string key = identity.GetPlainId() + "|" + bucket;
        int now = GetGame().GetTime();
        float tokens = capacity;
        if (s_Tokens.Contains(key))
        {
            int elapsed = now - s_TokenTime.Get(key);
            tokens = s_Tokens.Get(key) + elapsed / 1000.0 * perSecond;
            if (tokens > capacity)
                tokens = capacity;
        }
        s_TokenTime.Set(key, now);
        if (tokens < 1.0)
        {
            s_Tokens.Set(key, tokens);
            return false;
        }
        s_Tokens.Set(key, tokens - 1.0);
        return true;
    }

    // Short HUD notice for a refused request.
    static void Deny(PlayerIdentity identity, string text)
    {
        if (identity)
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.PDA_NOTICE, new Param2<string, string>("PDA NETWORK", text), true, identity);
    }

    // Network actions need a powered PDA logged in as the sender (a
    // read-only guest session can never transmit or change anything).
    static bool RequireDevice(PlayerIdentity identity, PlayerBase player = null)
    {
        if (!identity)
            return false;
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (access && access.IsOwner)
            return true;
        if (access)
            Deny(identity, FENR_PDA_AccountStore.READ_ONLY);
        else
            Deny(identity, "Log in to your PDA first.");
        return false;
    }

    // Steam64 whose data the open PDA shows ("" = locked).
    static string ViewerID(PlayerIdentity identity)
    {
        FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(identity);
        if (!access)
            return "";
        return access.OwnerID;
    }

    // The 9V cell powering the player's PDA, if any.
    static EntityAI FindDeviceBattery(PlayerBase player)
    {
        FENR_PDA_Device device = FindDevice(player);
        if (!device)
            return null;

        EntityAI battery = device.FindAttachmentBySlotName("BatteryD");
        if (!battery && device.GetCompEM())
            battery = device.GetCompEM().GetEnergySource();
        return battery;
    }

    static bool HasWorkingDevice(PlayerBase player)
    {
        if (!player)
            return false;

        if (IsWorkingDevice(EntityAI.Cast(player.GetItemInHands())))
            return true;

        ref array<EntityAI> inventory = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
        foreach (EntityAI entity : inventory)
        {
            if (IsWorkingDevice(entity))
                return true;
        }
        return false;
    }

    // ---------------------------------------------------------------------
    // Test accounts
    // ---------------------------------------------------------------------
    static bool TestAccountsEnabled()
    {
        return FENR_PDA_Storage.TestAccountsEnabled();
    }

    static bool IsTestAccount(string id)
    {
        return id == TEST_ID_1 || id == TEST_ID_2 || id == TEST_ID_3;
    }

    static string TestAccountName(string id)
    {
        if (id == TEST_ID_1) return TEST_NAME_1;
        if (id == TEST_ID_2) return TEST_NAME_2;
        if (id == TEST_ID_3) return TEST_NAME_3;
        return "";
    }

    static bool ResolveTestAccount(string lookup, out string id, out string name)
    {
        id = "";
        name = "";
        if (!TestAccountsEnabled())
            return false;

        if (lookup == TEST_ID_1 || lookup == TEST_NAME_1) { id = TEST_ID_1; name = TEST_NAME_1; return true; }
        if (lookup == TEST_ID_2 || lookup == TEST_NAME_2) { id = TEST_ID_2; name = TEST_NAME_2; return true; }
        if (lookup == TEST_ID_3 || lookup == TEST_NAME_3) { id = TEST_ID_3; name = TEST_NAME_3; return true; }
        return false;
    }

    static void FillTestAccounts(array<string> ids, array<string> names)
    {
        if (!ids || !names)
            return;
        ids.Clear();
        names.Clear();
        if (!TestAccountsEnabled())
            return;

        ids.Insert(TEST_ID_1); names.Insert(TEST_NAME_1);
        ids.Insert(TEST_ID_2); names.Insert(TEST_NAME_2);
        ids.Insert(TEST_ID_3); names.Insert(TEST_NAME_3);
    }

    // ---------------------------------------------------------------------
    // Core / contacts / direct messages
    // ---------------------------------------------------------------------
    void SyncTestAccounts(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            ref array<string> ids = new array<string>();
            ref array<string> names = new array<string>();
            FillTestAccounts(ids, names);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SYNC_TEST_ACCOUNTS, new Param2<ref array<string>, ref array<string>>(ids, names), true, sender);
            return;
        }

        Param2<ref array<string>, ref array<string>> data;
        if (!ctx.Read(data))
            return;

        FENR_PDA_Client client = ClientState();
        if (!client)
            return;

        client.SetTestContacts(data.param1, data.param2);

        if (client.IsOpen() && client.m_Menu)
            client.m_Menu.m_dirty = true;
    }

    void SendMessage(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param3<string, string, string> request;
            if (ctx.Read(request))
                FENR_PDA_Messages.Submit(sender, request.param1, request.param2, request.param3);
            return;
        }

        // conversation, sender name, body, own (this player wrote it), message number
        Param5<string, string, string, bool, int> response;
        if (!ctx.Read(response))
            return;

        FENR_PDA_Client client = ClientState();
        if (!client)
            return;

        string conversationID = response.param1;
        bool own = response.param4;
        ref FENR_PDA_Contact contact = client.FindContact(conversationID);
        if (!contact && !own)
        {
            // The server already added the sender to this PDA's memory.
            client.AddContactLocal(conversationID, response.param2);
            contact = client.FindContact(conversationID);
        }

        client.AppendMessage(conversationID, response.param2, response.param3, own, response.param5);
        if (!contact || contact.m_IsBanned)
            return;

        // Popup + sound for incoming traffic (never for your own echoed sends).
        if (!own && !contact.m_IsMuted)
        {
            if (conversationID == FENR_PDA_ChannelIds.ANNOUNCEMENTS)
                FENR_PDA_Toast.Notify("NETWORK BULLETIN", "FENRIR SECURE NETWORK", response.param3, "ic_announcements");
            else if (!FENR_PDA_ChannelIds.IsChannel(conversationID))
                FENR_PDA_Toast.Notify("NEW PDA MESSAGE", response.param2, response.param3, "ic_messages");
            else
                FENR_PDA_Toast.PlayChime();
        }
    }

    // Server -> client: short notice (refused request etc.).
    void PdaNotice(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param2<string, string> response;
        if (ctx.Read(response))
            FENR_PDA_Toast.Notify(response.param1, "FENRIR SECURE NETWORK", response.param2, "ic_system", false, true);
    }

    void CheckContacts(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param1<array<string>> request;
            if (!ctx.Read(request))
                return;

            ref array<string> result = new array<string>();
            FENR_PDA_Messages.BuildOnlineContactIds(request.param1, result);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.CHECK_CONTACTS, new Param1<ref array<string>>(result), true, sender);
            return;
        }

        Param1<array<string>> response;
        if (!ctx.Read(response))
            return;

        FENR_PDA_Client client = ClientState();
        if (client)
        {
            client.SetOnlineContacts(response.param1);
            if (client.IsOpen() && client.m_Menu)
                client.m_Menu.m_dirty = true;
        }
    }

    void GetVisualUserId(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (sender)
            {
                FENR_PDA_Storage.RememberIdentity(sender);
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.USER_ID, new Param1<string>(sender.GetName()), true, sender);
            }
            return;
        }

        Param1<string> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.m_UserDisplayName = response.param1;
    }

    void AddContact(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param1<string> request;
            if (!ctx.Read(request))
                return;

            string id;
            string name;
            if (FENR_PDA_Messages.ResolveContact(request.param1, id, name))
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADD_CONTACT, new Param2<string, string>(id, name), true, sender);
            return;
        }

        Param2<string, string> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client && client.IsOpen())
            client.AddContact(response.param1, response.param2);
    }

    // ---------------------------------------------------------------------
    // Network status (player-facing): how many PDA users are online.
    // Returns counts only - no names or IDs.
    // ---------------------------------------------------------------------
    void NetworkStatus(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;

            int pdaUsers = 0;
            int playerCount = 0;
            ref array<Man> players = new array<Man>();
            GetGame().GetPlayers(players);
            foreach (Man man : players)
            {
                PlayerBase player = PlayerBase.Cast(man);
                if (!player || !player.GetIdentity())
                    continue;
                playerCount++;
                if (FENR_PDA_Sessions.ActiveDevice(player))
                    pdaUsers++;
            }
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.NETWORK_STATUS, new Param2<int, int>(pdaUsers, playerCount), true, sender);
            return;
        }

        Param2<int, int> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().NetworkReceiveStatus(response.param1, response.param2);
    }

    // ---------------------------------------------------------------------
    // Bounty board
    // ---------------------------------------------------------------------
    void BountyList(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param2<string, int> request;
            if (!ctx.Read(request))
                return;
            int total = 0;
            int pageOut = 0;
            ref array<string> fields = new array<string>();
            string bountyViewer = ViewerID(sender);
            if (bountyViewer != "" && FENR_PDA_Storage.BountyEnabled())
                fields = FENR_PDA_BountyBoard.BuildPage(request.param1, request.param2, bountyViewer, total, pageOut);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_LIST, new Param4<ref array<string>, int, int, string>(fields, total, pageOut, request.param1), true, sender);
            return;
        }

        Param4<ref array<string>, int, int, string> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().BountyReceiveList(response.param1, response.param2, response.param3, response.param4);
    }

    void BountyPost(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param4<string, string, string, bool> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;
        string info;
        bool success = false;
        if (!Throttle(sender, "BOUNTY", 3, 0.2))
            info = "Posting too fast. Wait a moment.";
        else
            success = FENR_PDA_BountyBoard.Post(sender, request.param1, request.param2, request.param3, request.param4, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_RESULT, new Param3<string, bool, string>(FENR_PDA_BountyAction.POST, success, info), true, sender);
    }

    void BountyAction(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param3<string, string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;
        string info;
        bool success = false;
        if (!Throttle(sender, "BOUNTY_ACT", 5, 0.5))
            info = "Too fast. Wait a moment.";
        else
            success = FENR_PDA_BountyBoard.Act(sender, request.param1, request.param2, request.param3, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_RESULT, new Param3<string, bool, string>(request.param2, success, info), true, sender);
    }

    void BountyResult(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param3<string, bool, string> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().BountyReceiveResult(response.param1, response.param2, response.param3);
    }

    void BountyNotify(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param2<string, string> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Toast.Notify(response.param1, "BOUNTY BOARD", response.param2, "ic_bounty");
        if (FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().BountyRefresh();
    }

    // ---------------------------------------------------------------------
    // Data drives
    // ---------------------------------------------------------------------
    protected void SendDriveStatus(PlayerIdentity recipient)
    {
        if (!recipient)
            return;
        ref array<string> kinds = new array<string>();
        ref array<string> present = new array<string>();
        ref array<string> summaries = new array<string>();
        FENR_PDA_DriveService.BuildStatus(recipient, kinds, present, summaries);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_STATUS, new Param3<ref array<string>, ref array<string>, ref array<string>>(kinds, present, summaries), true, recipient);
    }

    void DriveStatus(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (sender && FENR_PDA_Sessions.AccessOf(sender))
                SendDriveStatus(sender);
            return;
        }

        Param3<ref array<string>, ref array<string>, ref array<string>> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().DriveReceiveStatus(response.param1, response.param2, response.param3);
    }

    void DriveRead(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> request;
        if (!ctx.Read(request))
            return;
        string info = "Log in to your PDA first.";
        ref array<string> payload = new array<string>();
        bool success = false;
        if (FENR_PDA_Sessions.AccessOf(sender))
            success = FENR_PDA_DriveService.Read(sender, request.param1, info, payload);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_DATA, new Param4<string, bool, string, ref array<string>>(request.param1, success, info, payload), true, sender);
        SendDriveStatus(sender);
    }

    void DriveData(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param4<string, bool, string, ref array<string>> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().DriveReceiveData(response.param1, response.param2, response.param3, response.param4);
    }

    // One file from the inserted Encrypted Drive.
    void DriveFile(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param1<int> request;
            if (!ctx.Read(request))
                return;
            string info = "Log in to your PDA first.";
            ref array<string> fields = new array<string>();
            bool success = false;
            if (FENR_PDA_Sessions.AccessOf(sender))
                success = FENR_PDA_DriveService.ReadDriveFile(sender, request.param1, info, fields);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_FILE, new Param4<int, bool, string, ref array<string>>(request.param1, success, info, fields), true, sender);
            return;
        }

        Param4<int, bool, string, ref array<string>> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().DriveReceiveFile(response.param1, response.param2, response.param3, response.param4);
    }

    // Material for the drive writer (group list / one group's history).
    void DriveSource(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param2<string, string> request;
            if (!ctx.Read(request))
                return;
            ref array<string> fields = new array<string>();
            FENR_PDA_DriveService.Source(sender, request.param1, request.param2, fields);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_SOURCE, new Param3<string, string, ref array<string>>(request.param1, request.param2, fields), true, sender);
            return;
        }

        Param3<string, string, ref array<string>> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().DriveReceiveSource(response.param1, response.param2, response.param3);
    }

    void DriveWrite(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param4<string, string, ref array<string>, string> request;
        if (!ctx.Read(request))
            return;
        string info;
        bool success = false;
        if (!FENR_PDA_Sessions.AccessOf(sender))
            info = "Log in to your PDA first.";
        else if (!Throttle(sender, "DRIVE", 3, 0.5))
            info = "Drive busy. Try again in a moment.";
        else
            success = FENR_PDA_DriveService.Write(sender, request.param1, request.param2, request.param3, request.param4, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_RESULT, new Param3<string, bool, string>(request.param1, success, info), true, sender);
        SendDriveStatus(sender);
    }

    void DriveResult(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param3<string, bool, string> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().DriveReceiveResult(response.param1, response.param2, response.param3);
    }

    // ---------------------------------------------------------------------
    // Player memory (FENR_PDA_AccountStore) through the PDA in hands.  Every
    // write carries the account token from the last sync; a stale token is
    // refused with DeviceResync.
    // ---------------------------------------------------------------------
    // Sends the session state, then the memory of the logged-in player.
    protected void SendDeviceSync(PlayerIdentity identity, string terrain)
    {
        if (!identity)
            return;
        FENR_PDA_Storage.RememberIdentity(identity);
        FENR_PDA_Sessions.SendState(identity);
        if (!FENR_PDA_Sessions.AccessOf(identity))
            return;
        ref array<string> contactFields = new array<string>();
        ref array<string> markerFields = new array<string>();
        string notes;
        bool isNew;
        string token = FENR_PDA_AccountStore.BuildSync(identity, terrain, contactFields, notes, markerFields, isNew);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_SYNC, new Param5<string, ref array<string>, string, ref array<string>, bool>(token, contactFields, notes, markerFields, isNew), true, identity);
    }

    void DeviceSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param1<string> request;
            if (!ctx.Read(request))
                return;
            SendDeviceSync(sender, request.param1);
            return;
        }

        Param5<string, ref array<string>, string, ref array<string>, bool> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.ReceiveSync(response.param1, response.param2, response.param3, response.param4, response.param5);
    }

    // ---------------------------------------------------------------------
    // Login sessions (FENR_PDA_Sessions)
    // ---------------------------------------------------------------------
    // Server -> client: state of the PDA in hands.
    void FenrSessionState(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param5<int, string, int, int, int> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.ReceiveSessionState(response.param1, response.param2, response.param3, response.param4, response.param5);
    }

    // Client -> server: hours, terrain.
    void FenrSessionLogin(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param2<int, string> request;
        if (!ctx.Read(request))
            return;
        string info;
        if (!Throttle(sender, "LOGIN", 3, 0.2))
            info = "Too many attempts. Wait a moment.";
        else if (FENR_PDA_Sessions.Login(sender, request.param1, info))
            info = "";
        if (info != "")
            Deny(sender, info);
        SendDeviceSync(sender, request.param2);
    }

    // Client -> server: terrain.
    void FenrSessionLogout(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> request;
        if (!ctx.Read(request))
            return;
        string info;
        if (!FENR_PDA_Sessions.Logout(sender, info))
            Deny(sender, info);
        FENR_PDA_Sessions.SendState(sender);
    }

    void DeviceConvo(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param2<string, string> request;
            if (!ctx.Read(request))
                return;
            ref array<string> fields = new array<string>();
            FENR_PDA_AccountStore.ConvoFields(sender, request.param1, request.param2, fields);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_CONVO, new Param2<string, ref array<string>>(request.param2, fields), true, sender);
            return;
        }

        Param2<string, ref array<string>> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.ReceiveConversation(response.param1, response.param2);
    }

    void DeviceContactOp(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param4<string, string, string, string> request;
        if (ctx.Read(request))
            FENR_PDA_AccountStore.ContactOp(sender, request.param1, request.param2, request.param3, request.param4);
    }

    void DeviceSaveNotes(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param2<string, string> request;
        if (ctx.Read(request))
            FENR_PDA_AccountStore.SaveNotes(sender, request.param1, request.param2);
    }

    void DeviceSaveMarkers(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param3<string, string, ref array<string>> request;
        if (ctx.Read(request))
            FENR_PDA_AccountStore.SaveMarkers(sender, request.param1, request.param2, request.param3);
    }

    // Server -> client: the PDA in hands changed (or locked); reload.
    void DeviceResync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        FENR_PDA_Client client = ClientState();
        if (client && client.IsOpen())
            client.RequestSync();
    }

    // Compass HUD: markers of the logged-in PDA the player uses (read-only).
    void DeviceHud(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param1<string> request;
            if (!ctx.Read(request))
                return;
            if (!Throttle(sender, "HUD", 3, 0.2))
                return;
            ref array<string> fields = new array<string>();
            FENR_PDA_AccountStore.HudMarkers(sender, request.param1, fields);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DEVICE_HUD, new Param2<string, ref array<string>>(request.param1, fields), true, sender);
            return;
        }

        Param2<string, ref array<string>> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.ReceiveHudMarkers(response.param1, response.param2);
    }

    // ---------------------------------------------------------------------
    // S.O.S
    // ---------------------------------------------------------------------
    void SosGet(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param1<string> request;
            if (!ctx.Read(request))
                return;
            string mode;
            string groupID;
            ref array<string> targets = new array<string>();
            if (!FENR_PDA_AccountStore.GetSos(sender, request.param1, mode, targets, groupID))
                return;
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_GET, new Param4<string, ref array<string>, string, int>(mode, targets, groupID, FENR_PDA_Storage.SosMaxContacts()), true, sender);
            return;
        }

        Param4<string, ref array<string>, string, int> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().SosReceiveConfig(response.param1, response.param2, response.param3, response.param4);
    }

    void SosSet(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param4<string, string, ref array<string>, string> request;
        if (ctx.Read(request))
            FENR_PDA_AccountStore.SetSos(sender, request.param1, request.param2, request.param3, request.param4);
    }

    void SosSend(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<bool> request;
        if (!ctx.Read(request))
            return;
        string info;
        bool success = false;
        if (!Throttle(sender, "SOS", 1, 0.1))
            info = "S.O.S transmitter recharging. Try again in a moment.";
        else
            success = FENR_PDA_Sos.Send(sender, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_RESULT, new Param2<bool, string>(success, info), true, sender);
    }

    void SosResult(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param2<bool, string> response;
        if (!ctx.Read(response))
            return;
        if (FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().SosReceiveResult(response.param1, response.param2);
        FENR_PDA_Client client = ClientState();
        if (response.param1)
        {
            // The PDA burned out.
            if (client && client.IsOpen()) client.Close();
            FENR_PDA_Toast.Notify("S.O.S TRANSMITTED", "PDA BURNED OUT", response.param2, "ic_warning", false, true);
        }
        else
        {
            FENR_PDA_Toast.Notify("S.O.S FAILED", "FENRIR SECURE NETWORK", response.param2, "ic_warning", false, true);
        }
    }

    void SosAlert(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param5<string, float, float, int, string> response;
        if (!ctx.Read(response))
            return;
        FENR_PDA_Client client = ClientState();
        if (client)
            client.AddSosPing(response.param1, response.param2, response.param3, response.param4, response.param5);
    }

    // ---------------------------------------------------------------------
    // Battery usage reports (client -> server)
    // ---------------------------------------------------------------------
    void PdaUsage(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<int> request;
        if (ctx.Read(request))
            FENR_PDA_Power.SetUsage(sender, request.param1);
    }

    // ---------------------------------------------------------------------
    // Trade board
    // ---------------------------------------------------------------------
    void TradeList(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param3<string, int, string> request;
            if (!ctx.Read(request))
                return;

            int total = 0;
            int pageOut = 0;
            ref array<string> fields = new array<string>();
            string tradeViewer = ViewerID(sender);
            if (tradeViewer != "" && FENR_PDA_Storage.TradeEnabled())
                fields = FENR_PDA_Trade.BuildPage(request.param1, request.param2, tradeViewer, request.param3, total, pageOut);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_LIST, new Param4<ref array<string>, int, int, string>(fields, total, pageOut, request.param1), true, sender);
            return;
        }

        Param4<ref array<string>, int, int, string> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().TradeReceiveList(response.param1, response.param2, response.param3, response.param4);
    }

    void TradeCreate(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param5<string, string, string, string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;

        string info;
        bool success = false;
        if (!Throttle(sender, "TRADE", 3, 0.2))
            info = "Posting too fast. Wait a moment.";
        else
            success = FENR_PDA_Trade.Create(sender, request.param1, request.param2, request.param3, request.param4, request.param5, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_RESULT, new Param3<string, bool, string>(FENR_PDA_TradeAction.CREATE, success, info), true, sender);
    }

    void TradeUpdate(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param2<string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;

        string info;
        bool success = false;
        if (!Throttle(sender, "TRADE_UPD", 5, 0.5))
            info = "Too fast. Wait a moment.";
        else
            success = FENR_PDA_Trade.Update(sender, request.param1, request.param2, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_RESULT, new Param3<string, bool, string>(request.param2, success, info), true, sender);
    }

    // Client pressed CONTACT on a listing: remember the trade pair for reputation.
    void TradeContact(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param1<string> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;
        string ownerID = FENR_PDA_Trade.OwnerOf(request.param1);
        if (ownerID != "")
            FENR_PDA_Reputation.RecordContact(sender.GetPlainId(), ownerID);
    }

    protected void SendRep(PlayerIdentity recipient, string targetID)
    {
        if (!recipient)
            return;
        string raterID = recipient.GetPlainId();
        int score = FENR_PDA_Reputation.ScoreOf(targetID);
        int count = FENR_PDA_Reputation.CountOf(targetID);
        int myVote = FENR_PDA_Reputation.VoteOf(raterID, targetID);
        bool canRate = FENR_PDA_Reputation.CanRate(raterID, targetID);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_GET, new Param5<string, int, int, int, bool>(targetID, score, count, myVote, canRate), true, recipient);
    }

    void RepGet(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender)
                return;
            Param1<string> request;
            if (ctx.Read(request))
                SendRep(sender, request.param1);
            return;
        }

        Param5<string, int, int, int, bool> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().RepReceive(response.param1, response.param2, response.param3, response.param4, response.param5);
    }

    void RepVote(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server || !sender)
            return;
        Param2<string, int> request;
        if (!ctx.Read(request) || !RequireDevice(sender))
            return;

        string info;
        bool success = FENR_PDA_Reputation.Vote(sender.GetPlainId(), request.param1, request.param2, info);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_RESULT, new Param3<string, bool, string>("RATE", success, info), true, sender);
        SendRep(sender, request.param1);
    }

    void TradeResult(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
            return;
        Param3<string, bool, string> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().TradeReceiveResult(response.param1, response.param2, response.param3);
    }

    // ---------------------------------------------------------------------
    // Admin
    // ---------------------------------------------------------------------
    void AdminStatus(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            // The admin panel only opens on the admin's own logged-in PDA.
            FENR_PDA_Access adminAccess = FENR_PDA_Sessions.AccessOf(sender);
            bool isAdmin = adminAccess && adminAccess.IsOwner && FENR_PDA_Admin.IsAuthorized(sender);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_STATUS, new Param2<bool, string>(isAdmin, FENR_PDA_Storage.RetentionSummary()), true, sender);
            return;
        }

        Param2<bool, string> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().AdminReceiveStatus(data.param1, data.param2);
    }

    void AdminSearchMessages(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!FENR_PDA_Admin.IsAuthorized(sender))
                return;

            Param3<string, string, int> request;
            if (!ctx.Read(request))
                return;

            int page = request.param3;
            if (page < 0) page = 0;

            ref FENR_PDA_AdminSearchResult searchResult = FENR_PDA_Admin.BuildSearch(request.param1, request.param2, page);

            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_SEARCH, new Param5<ref array<string>, ref array<string>, int, int, int>(searchResult.Headers, searchResult.Bodies, searchResult.Total, page, FENR_PDA_Storage.SearchPageSize()), true, sender);
            FENR_PDA_Storage.LogAdmin(sender.GetName(), sender.GetPlainId(), "SEARCH_MESSAGES", request.param1, "Type=" + request.param2 + " Page=" + page.ToString());
            return;
        }

        Param5<ref array<string>, ref array<string>, int, int, int> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().AdminReceiveSearch(response.param1, response.param2, response.param3, response.param4, response.param5);
    }

    void AdminListPlayers(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!FENR_PDA_Admin.IsAuthorized(sender))
                return;
            ref array<string> ids = new array<string>();
            ref array<string> rows = new array<string>();
            FENR_PDA_Admin.BuildOnlinePlayerRows(ids, rows);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_PLAYERS, new Param2<ref array<string>, ref array<string>>(ids, rows), true, sender);
            return;
        }

        Param2<ref array<string>, ref array<string>> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().AdminReceivePlayers(response.param1, response.param2);
    }

    void AdminBroadcast(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param1<string> request;
            if (!ctx.Read(request) || !RequireDevice(sender))
                return;
            bool success = FENR_PDA_Admin.Broadcast(sender, request.param1);
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_BROADCAST, new Param1<bool>(success), true, sender);
            return;
        }

        Param1<bool> response;
        if (ctx.Read(response) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().AdminReceiveBroadcastResult(response.param1);
    }

    // ---------------------------------------------------------------------
    // Groups
    // ---------------------------------------------------------------------
    protected void SendGroupActionResult(PlayerIdentity recipient, string action, bool success, string info, string groupID = "")
    {
        if (recipient)
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_RESULT, new Param4<string, bool, string, string>(action, success, info, groupID), true, recipient);
    }

    void GroupActionResult(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Client)
            return;
        Param4<string, bool, string, string> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveActionResult(data.param1, data.param2, data.param3, data.param4);
    }

    void GroupList(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            if (!sender) return;
            ref array<string> ids = new array<string>();
            ref array<string> names = new array<string>();
            ref array<string> ownerIDs = new array<string>();
            ref array<string> unread = new array<string>();
            // The groups of the player the open PDA is logged in as.
            FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(sender);
            if (access)
            {
                FENR_PDA_Groups.FillGroupsForMember(access.OwnerID, ids, names, ownerIDs);
                // Unread lines per group since that player last opened it.
                string accountKey = access.Key();
                foreach (string groupID : ids)
                {
                    int count = FENR_PDA_AccountStore.GroupUnread(accountKey, groupID, access.OwnerID, access.IsOwner);
                    unread.Insert(count.ToString());
                }
            }
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_LIST, new Param4<ref array<string>, ref array<string>, ref array<string>, ref array<string>>(ids, names, ownerIDs, unread), true, sender);
            return;
        }

        Param4<ref array<string>, ref array<string>, ref array<string>, ref array<string>> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveList(data.param1, data.param2, data.param3, data.param4);
    }

    void GroupCreate(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param1<string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string groupID, info;
        bool success = FENR_PDA_Groups.CreateGroup(sender, request.param1, groupID, info);
        SendGroupActionResult(sender, "CREATE", success, info, groupID);
    }

    void GroupRename(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param2<string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = FENR_PDA_Groups.RenameGroup(sender, request.param1, request.param2, info);
        SendGroupActionResult(sender, "RENAME", success, info, request.param1);
    }

    void GroupDelete(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param1<string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = FENR_PDA_Groups.DeleteGroup(sender, request.param1, info);
        SendGroupActionResult(sender, "DELETE", success, info, "");
    }

    void GroupLeave(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param1<string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = FENR_PDA_Groups.LeaveGroup(sender, request.param1, info);
        SendGroupActionResult(sender, "LEAVE", success, info, "");
    }

    void GroupAddMember(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param3<string, string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = FENR_PDA_Groups.AddMember(sender, request.param1, request.param2, request.param3, info);
        SendGroupActionResult(sender, "ADD_MEMBER", success, info, request.param1);
    }

    void GroupRemoveMember(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param2<string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = FENR_PDA_Groups.RemoveMember(sender, request.param1, request.param2, info);
        SendGroupActionResult(sender, "REMOVE_MEMBER", success, info, request.param1);
    }

    void GroupMembers(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param1<string> request;
            if (!ctx.Read(request) || !sender) return;
            FENR_PDA_Group group = FENR_PDA_Groups.FindGroup(request.param1);
            string memberViewer = ViewerID(sender);
            if (!group || !FENR_PDA_Groups.HasMemberID(group, memberViewer)) return;

            ref array<string> ids = new array<string>();
            ref array<string> rows = new array<string>();
            foreach (FENR_PDA_GroupMember member : group.Members)
            {
                if (!member) continue;
                ids.Insert(member.ID);
                if (member.ID == group.OwnerID) rows.Insert("[OWNER] " + member.Name);
                else rows.Insert(member.Name);
            }
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_MEMBERS, new Param4<string, ref array<string>, ref array<string>, string>(group.GroupID, ids, rows, group.OwnerID), true, sender);
            return;
        }

        Param4<string, ref array<string>, ref array<string>, string> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveMembers(data.param1, data.param2, data.param3, data.param4);
    }

    void GroupHistory(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            Param1<string> request;
            if (!ctx.Read(request) || !sender) return;
            FENR_PDA_Group group = FENR_PDA_Groups.FindGroup(request.param1);
            FENR_PDA_Access access = FENR_PDA_Sessions.AccessOf(sender);
            if (!group || !access || !FENR_PDA_Groups.HasMemberID(group, access.OwnerID)) return;

            ref array<ref FENR_PDA_GroupMessage> messages = FENR_PDA_Groups.LoadMessages(group.GroupID);
            ref array<string> senderNames = new array<string>();
            ref array<string> bodies = new array<string>();
            ref array<string> times = new array<string>();
            foreach (FENR_PDA_GroupMessage message : messages)
            {
                if (!message) continue;
                senderNames.Insert(message.SenderName);
                bodies.Insert(message.MessageText);
                string clock = message.Clock;
                if (clock == "" && message.Timestamp.Length() >= 16)
                    clock = message.Timestamp.Substring(11, 5);
                times.Insert(clock);
            }
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_HISTORY, new Param4<string, ref array<string>, ref array<string>, ref array<string>>(group.GroupID, senderNames, bodies, times), true, sender);

            // Opening a group chat marks it read (not for read-only viewers).
            if (access.IsOwner)
                FENR_PDA_AccountStore.MarkGroupRead(access.Key(), group.GroupID);
            return;
        }

        Param4<string, ref array<string>, ref array<string>, ref array<string>> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveHistory(data.param1, data.param2, data.param3, data.param4);
    }

    void GroupSendMessage(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Server) return;
        Param2<string, string> request;
        if (!ctx.Read(request) || !RequireDevice(sender)) return;
        string info;
        bool success = false;
        if (!Throttle(sender, "GROUP", 5, 1.0))
            info = "Transmitting too fast. Wait a moment.";
        else
            success = FENR_PDA_Groups.SendMessage(sender, request.param1, request.param2, info);
        if (!success)
            SendGroupActionResult(sender, "SEND", false, info, request.param1);
    }

    void GroupIncomingMessage(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Client) return;
        Param4<string, string, string, string> data;
        if (!ctx.Read(data))
            return;
        if (FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveIncoming(data.param1, data.param2, data.param3, data.param4);

        FENR_PDA_Client client = ClientState();
        bool ownMessage = client && client.m_UserDisplayName != "" && data.param3 == client.m_UserDisplayName;
        if (!ownMessage && data.param3 != "SYSTEM")
            FENR_PDA_Toast.Notify("GROUP / " + data.param2, data.param3, data.param4, "ic_groups");
    }

    void GroupRefresh(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type != CallType.Client) return;
        Param1<string> data;
        if (ctx.Read(data) && FENR_PDA_Menu.GetInstance())
            FENR_PDA_Menu.GetInstance().GroupReceiveRefresh(data.param1);
    }
};
