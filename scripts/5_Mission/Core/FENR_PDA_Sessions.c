/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    PDA login sessions (server side).  v8.1

    A PDA is locked until a player logs in on it.  The session is kept on the
    PDA item object (FENR_PDA_Device) and in memory here - never on disk - so:
      - a server restart ends every session;
      - a session ends when its owner logs out on the PDA, when the chosen
        time (SessionMinHours..SessionMaxHours) runs out, when the owner
        logs in on another PDA (one session per player), or when someone
        else logs in on that PDA;
      - disconnecting does NOT end it: a logged-in PDA left on a body or in
        a stash stays readable until it times out.

    Whoever holds a logged-in PDA sees its owner's data:
      - the owner has full access;
      - anyone else gets read-only access (messages, groups, markers, live
        traffic and alerts) and can clone it onto an Encrypted Drive, but
        cannot transmit or change anything.

    "Live" traffic for a player (messages, group lines, S.O.S alerts) goes to
    whoever is currently using that player's logged-in PDA.
*/

// What a request may do with the PDA the player is using.
class FENR_PDA_Access
{
    FENR_PDA_Device PdaDevice;
    string OwnerID;       // Steam64 of the logged-in player (whose data is shown)
    string OwnerName;
    bool IsOwner;         // the requesting player is that player

    string Key()
    {
        return FENR_PDA_AccountStore.KeyFor(OwnerID);
    }
};

class FENR_PDA_Sessions
{
    static const int TICK_MS = 5000;
    static const int HOUR_MS = 3600000;

    protected static ref map<string, FENR_PDA_Device> s_ByOwner;   // Steam64 -> PDA logged in as them
    protected static bool s_Initialized;

    static void Init()
    {
        if (s_Initialized || !GetGame().IsServer())
            return;
        s_Initialized = true;
        EnsureMap();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Tick, TICK_MS, true);
    }

    protected static void EnsureMap()
    {
        if (!s_ByOwner)
            s_ByOwner = new map<string, FENR_PDA_Device>();
    }

    static int MinHours()
    {
        return FENR_PDA_Storage.SessionMinHours();
    }

    static int MaxHours()
    {
        return FENR_PDA_Storage.SessionMaxHours();
    }

    // ------------------------------------------------------------------
    // Devices
    // ------------------------------------------------------------------
    // The player carrying a PDA (null if it lies in the world or a container).
    static PlayerBase HolderOf(FENR_PDA_Device device)
    {
        if (!device)
            return null;
        return PlayerBase.Cast(device.GetHierarchyRootPlayer());
    }

    // Logged-in owner of a PDA ("" = locked).  Ends sessions that ran out.
    static string OwnerOf(FENR_PDA_Device device)
    {
        if (!device)
            return "";
        string owner = device.FenrSessionOwner();
        if (owner == "")
            return "";
        if (device.IsRuined())
        {
            End(device, "");
            return "";
        }
        if (GetGame().GetTime() >= device.FenrSessionEnd())
        {
            End(device, "Session expired. Log in again.");
            return "";
        }
        return owner;
    }

    // Seconds left on a PDA's session (0 = locked).
    static int SecondsLeft(FENR_PDA_Device device)
    {
        if (OwnerOf(device) == "")
            return 0;
        int left = (device.FenrSessionEnd() - GetGame().GetTime()) / 1000;
        if (left < 0)
            left = 0;
        return left;
    }

    // The logged-in, powered PDA a player is using: the one in hands, else
    // the first one carried.  Used for live traffic and the compass HUD.
    static FENR_PDA_Device ActiveDevice(PlayerBase player)
    {
        if (!player)
            return null;
        FENR_PDA_Device hands = FENR_PDA_Device.Cast(player.GetItemInHands());
        if (hands && FENR_PDA_Server.IsWorkingDevice(hands) && OwnerOf(hands) != "")
            return hands;

        array<EntityAI> inventory = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
        foreach (EntityAI entity : inventory)
        {
            FENR_PDA_Device candidate = FENR_PDA_Device.Cast(entity);
            if (candidate && FENR_PDA_Server.IsWorkingDevice(candidate) && OwnerOf(candidate) != "")
                return candidate;
        }
        return null;
    }

    // Who receives a player's live traffic: the player currently using the
    // PDA logged in as them (the owner, or whoever took it).  null = nobody.
    static PlayerBase LiveHolder(string ownerID)
    {
        if (ownerID == "")
            return null;
        EnsureMap();
        FENR_PDA_Device device = s_ByOwner.Get(ownerID);
        if (!device || OwnerOf(device) != ownerID)
            return null;
        PlayerBase holder = HolderOf(device);
        if (!holder || !holder.GetIdentity() || !holder.IsAlive())
            return null;
        if (ActiveDevice(holder) != device)
            return null;
        return holder;
    }

    // ------------------------------------------------------------------
    // Access for requests made through the open PDA (the one in hands)
    // ------------------------------------------------------------------
    static ref FENR_PDA_Access AccessOf(PlayerIdentity identity)
    {
        if (!identity)
            return null;
        PlayerBase player = FENR_PDA_Server.PlayerOf(identity);
        FENR_PDA_Device device = FENR_PDA_Server.FindDevice(player);
        return AccessFor(identity, device);
    }

    // Access through the PDA the player is using with the PDA closed
    // (compass HUD, S.O.S hotkey).
    static ref FENR_PDA_Access ActiveAccessOf(PlayerIdentity identity)
    {
        if (!identity)
            return null;
        PlayerBase player = FENR_PDA_Server.PlayerOf(identity);
        return AccessFor(identity, ActiveDevice(player));
    }

    protected static ref FENR_PDA_Access AccessFor(PlayerIdentity identity, FENR_PDA_Device device)
    {
        if (!device || !FENR_PDA_Server.IsWorkingDevice(device))
            return null;
        string owner = OwnerOf(device);
        if (owner == "")
            return null;
        ref FENR_PDA_Access access = new FENR_PDA_Access();
        access.PdaDevice = device;
        access.OwnerID = owner;
        access.OwnerName = device.FenrSessionName();
        access.IsOwner = owner == identity.GetPlainId();
        return access;
    }

    // ------------------------------------------------------------------
    // Login / logout
    // ------------------------------------------------------------------
    static bool Login(PlayerIdentity identity, int hours, out string info)
    {
        info = "";
        EnsureMap();
        PlayerBase player = FENR_PDA_Server.PlayerOf(identity);
        if (!player || !player.IsAlive())
        {
            info = "Login failed.";
            return false;
        }
        FENR_PDA_Device device = FENR_PDA_Server.FindDevice(player);
        if (!device || !FENR_PDA_Server.IsWorkingDevice(device))
        {
            info = "Your PDA must be powered on.";
            return false;
        }

        int minHours = MinHours();
        int maxHours = MaxHours();
        if (hours < minHours) hours = minHours;
        if (hours > maxHours) hours = maxHours;

        string id = identity.GetPlainId();
        FENR_PDA_AccountStore.NoteLogin(id);

        // One session per player: the PDA they used before locks (quietly
        // when it is the player's own other PDA).
        FENR_PDA_Device previous = s_ByOwner.Get(id);
        if (previous && previous != device && previous.FenrSessionOwner() == id)
        {
            if (HolderOf(previous) == player)
                End(previous, "", false);
            else
                End(previous, "Your account was logged in on another PDA.");
        }

        // Logging in on someone else's PDA ends their session on it.
        string current = device.FenrSessionOwner();
        if (current != "" && current != id)
        {
            if (s_ByOwner.Get(current) == device)
                s_ByOwner.Remove(current);
            FENR_PDA_Storage.LogSystem("PDA_TAKEOVER Player=" + identity.GetName() + " Steam64=" + id + " PreviousOwner=" + current);
        }

        device.FenrStartSession(id, identity.GetName(), GetGame().GetTime() + hours * HOUR_MS);
        s_ByOwner.Set(id, device);
        FENR_PDA_Storage.RememberIdentity(identity);
        FENR_PDA_AccountStore.Touch(id);
        info = "Logged in for " + hours.ToString() + " hour";
        if (hours != 1)
            info += "s";
        info += ".";
        return true;
    }

    // Only the owner can log out (a guest simply puts the PDA away).
    static bool Logout(PlayerIdentity identity, out string info)
    {
        info = "";
        PlayerBase player = FENR_PDA_Server.PlayerOf(identity);
        FENR_PDA_Device device = FENR_PDA_Server.FindDevice(player);
        if (!device || OwnerOf(device) == "")
        {
            info = "This PDA is not logged in.";
            return false;
        }
        if (device.FenrSessionOwner() != identity.GetPlainId())
        {
            info = "Only the logged-in user can log out.";
            return false;
        }
        End(device, "");
        info = "Logged out.";
        return true;
    }

    // Ends a PDA's session.  inform: send the holder the new state, plus
    // `notice` when it is not empty.
    static void End(FENR_PDA_Device device, string notice, bool inform = true)
    {
        if (!device)
            return;
        EnsureMap();
        string owner = device.FenrSessionOwner();
        if (owner != "" && s_ByOwner.Get(owner) == device)
            s_ByOwner.Remove(owner);
        if (owner == "")
            return;
        device.FenrEndSession();

        PlayerBase holder = HolderOf(device);
        if (inform && holder && holder.GetIdentity())
        {
            SendState(holder.GetIdentity());
            if (notice != "")
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.PDA_NOTICE, new Param2<string, string>("PDA LOCKED", notice), true, holder.GetIdentity());
        }
    }

    // Expired sessions lock on their own (also clears the compass HUD).
    static void Tick()
    {
        EnsureMap();
        if (s_ByOwner.Count() == 0)
            return;
        array<string> owners = new array<string>();
        for (int i = 0; i < s_ByOwner.Count(); i++)
            owners.Insert(s_ByOwner.GetKey(i));
        foreach (string owner : owners)
        {
            FENR_PDA_Device device = s_ByOwner.Get(owner);
            if (!device)
            {
                s_ByOwner.Remove(owner);
                continue;
            }
            OwnerOf(device);   // ends it if expired / ruined
        }
    }

    // ------------------------------------------------------------------
    // Client state
    //   state, owner name, seconds left, features, hours range
    //   features: trade(1) + bounty(10) + sos(100)
    //   hours range: min * 100 + max
    // ------------------------------------------------------------------
    static int Features()
    {
        int features = 0;
        if (FENR_PDA_Storage.TradeEnabled()) features += 1;
        if (FENR_PDA_Storage.BountyEnabled()) features += 10;
        if (FENR_PDA_Storage.SosEnabled()) features += 100;
        return features;
    }

    static void SendState(PlayerIdentity identity)
    {
        if (!identity)
            return;
        int state = FENR_PDA_SessionState.NO_POWER;
        string ownerName = "";
        int left = 0;
        PlayerBase player = FENR_PDA_Server.PlayerOf(identity);
        FENR_PDA_Device device = FENR_PDA_Server.FindDevice(player);
        if (device && FENR_PDA_Server.IsWorkingDevice(device))
        {
            string owner = OwnerOf(device);
            if (owner == "")
            {
                state = FENR_PDA_SessionState.LOCKED;
            }
            else
            {
                ownerName = device.FenrSessionName();
                left = SecondsLeft(device);
                if (owner == identity.GetPlainId())
                    state = FENR_PDA_SessionState.OWNER;
                else
                    state = FENR_PDA_SessionState.GUEST;
            }
        }
        int range = MinHours() * 100 + MaxHours();
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SESSION_STATE, new Param5<int, string, int, int, int>(state, ownerName, left, Features(), range), true, identity);
    }
};
