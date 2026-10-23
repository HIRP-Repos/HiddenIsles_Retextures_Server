/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Bounty board (server side).
      OPEN  --claim(note)-->  CLAIMED  --confirm-->  COMPLETED
                               |--reject--> OPEN
    Posters may cancel their own bounties.  VPP admins may post SERVER
    bounties (any admin can confirm/reject those) and remove any bounty.
    Stored in $profile:\PDA\Bounties\Bounties.json; expires after BountyDays.
*/

class FENR_PDA_BountyBoard
{
    static const int MAX_TOTAL = 300;

    protected static ref array<ref FENR_PDA_Bounty> s_Bounties;
    protected static bool s_Initialized = false;
    protected static int s_Counter = 0;

    static void Init()
    {
        if (s_Initialized || !GetGame().IsServer())
            return;
        s_Bounties = FENR_PDA_Storage.LoadBounties();
        s_Initialized = true;
        CleanupBounties();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CleanupBounties, 3600000, true);
    }

    protected static void EnsureLoaded()
    {
        if (!s_Bounties)
            s_Bounties = FENR_PDA_Storage.LoadBounties();
    }

    protected static void SaveBoard()
    {
        FENR_PDA_Storage.SaveBounties(s_Bounties);
    }

    static void CleanupBounties()
    {
        EnsureLoaded();
        int today = FENR_PDA_Storage.TodaySerial();
        int days = FENR_PDA_Storage.BountyDays();
        bool changed = false;
        for (int i = s_Bounties.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_Bounty bounty = s_Bounties[i];
            if (!bounty || today - bounty.CreatedSerial >= days)
            {
                s_Bounties.RemoveOrdered(i);
                changed = true;
            }
        }
        if (changed)
            SaveBoard();
    }

    protected static string CleanText(string text, int maxChars)
    {
        string result = text;
        result.Replace("\n", " ");
        result.Replace("\r", " ");
        result = result.Trim();
        if (result.LengthUtf8() > maxChars)
            result = result.SubstringUtf8(0, maxChars);
        return result;
    }

    protected static string NewBountyID()
    {
        s_Counter++;
        int now = GetGame().GetTime();
        int salt = Math.RandomInt(1000, 9999);
        return "B" + now.ToString() + "_" + s_Counter.ToString() + "_" + salt.ToString();
    }

    protected static FENR_PDA_Bounty FindBounty(string bountyID)
    {
        EnsureLoaded();
        foreach (FENR_PDA_Bounty bounty : s_Bounties)
        {
            if (bounty && bounty.ID == bountyID)
                return bounty;
        }
        return null;
    }

    protected static int ActiveCountFor(string posterID)
    {
        int count = 0;
        foreach (FENR_PDA_Bounty bounty : s_Bounties)
        {
            if (bounty && !bounty.IsServer && bounty.PosterID == posterID && bounty.Status != FENR_PDA_BountyStatus.COMPLETED)
                count++;
        }
        return count;
    }

    // Sends a HUD popup to whoever is using that player's logged-in PDA.
    static void NotifyPlayer(string playerID, string title, string body)
    {
        if (playerID == "")
            return;
        string steam64 = FENR_PDA_Storage.ResolveSteam64(playerID);
        if (steam64 == "")
            steam64 = playerID;
        PlayerBase player = FENR_PDA_Sessions.LiveHolder(steam64);
        if (!player || !player.GetIdentity())
            return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_NOTIFY, new Param2<string, string>(title, body), true, player.GetIdentity());
    }

    protected static void NotifyEveryone(string title, string body)
    {
        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity() && FENR_PDA_Sessions.ActiveDevice(player))
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_NOTIFY, new Param2<string, string>(title, body), true, player.GetIdentity());
        }
    }

    static bool Post(PlayerIdentity sender, string targetName, string reward, string reason, bool serverBounty, out string info)
    {
        info = "";
        if (!sender)
            return false;
        EnsureLoaded();

        if (!FENR_PDA_Storage.BountyEnabled())
        {
            info = "The bounty board is disabled on this server.";
            return false;
        }

        bool isAdmin = FENR_PDA_Admin.IsAuthorized(sender);
        if (serverBounty && !isAdmin)
        {
            info = "Only admins can post server bounties.";
            return false;
        }

        string target = CleanText(targetName, FENR_PDA_BountyLimits.TARGET);
        string cleanReward = CleanText(reward, FENR_PDA_BountyLimits.REWARD);
        string cleanReason = CleanText(reason, FENR_PDA_BountyLimits.REASON);
        if (target == "")
        {
            info = "Enter the target's name.";
            return false;
        }
        if (cleanReward == "")
        {
            info = "Enter a reward.";
            return false;
        }
        if (target == sender.GetName())
        {
            info = "You cannot place a bounty on yourself.";
            return false;
        }

        string posterID = sender.GetPlainId();
        int maxBounties = FENR_PDA_Storage.BountyMaxPerPlayer();
        if (!serverBounty && ActiveCountFor(posterID) >= maxBounties)
        {
            info = "You already have " + maxBounties.ToString() + " active bounties.";
            return false;
        }
        if (s_Bounties.Count() >= MAX_TOTAL)
        {
            info = "The bounty board is full. Try again later.";
            return false;
        }

        ref FENR_PDA_Bounty bounty = new FENR_PDA_Bounty();
        bounty.ID = NewBountyID();
        bounty.TargetName = target;
        bounty.Reward = cleanReward;
        bounty.Reason = cleanReason;
        bounty.PosterID = posterID;
        bounty.PosterName = sender.GetName();
        bounty.IsServer = serverBounty;
        bounty.Status = FENR_PDA_BountyStatus.OPEN;
        bounty.Created = FENR_PDA_Storage.Timestamp();
        bounty.CreatedSerial = FENR_PDA_Storage.TodaySerial();
        s_Bounties.Insert(bounty);
        SaveBoard();

        FENR_PDA_Storage.LogSystem("BOUNTY POST " + bounty.ID + " by " + bounty.PosterName + " (" + posterID + ") on " + target + " reward " + cleanReward);
        if (serverBounty)
        {
            FENR_PDA_Storage.LogAdmin(sender.GetName(), posterID, "BOUNTY_SERVER_POST", target, cleanReward);
            NotifyEveryone("NEW SERVER BOUNTY", target + "  |  REWARD: " + cleanReward);
        }

        info = "Bounty posted on " + target + ".";
        return true;
    }

    static bool Act(PlayerIdentity sender, string bountyID, string action, string note, out string info)
    {
        info = "";
        if (!sender)
            return false;

        FENR_PDA_Bounty bounty = FindBounty(bountyID);
        if (!bounty)
        {
            info = "That bounty no longer exists.";
            return false;
        }

        string senderID = sender.GetPlainId();
        bool isPoster = bounty.PosterID == senderID;
        bool isAdmin = FENR_PDA_Admin.IsAuthorized(sender);
        // Any admin may manage server bounties.
        bool canManage = isPoster || (bounty.IsServer && isAdmin);

        if (action == FENR_PDA_BountyAction.CLAIM)
        {
            if (isPoster)
            {
                info = "You cannot claim your own bounty.";
                return false;
            }
            if (bounty.Status != FENR_PDA_BountyStatus.OPEN)
            {
                info = "This bounty is not open for claims.";
                return false;
            }
            if (bounty.TargetName == sender.GetName())
            {
                info = "You cannot claim a bounty placed on yourself.";
                return false;
            }
            string cleanNote = CleanText(note, FENR_PDA_BountyLimits.NOTE);
            if (cleanNote == "")
            {
                info = "Add a proof note for the poster (where, when, how).";
                return false;
            }
            bounty.Status = FENR_PDA_BountyStatus.CLAIMED;
            bounty.ClaimerID = senderID;
            bounty.ClaimerName = sender.GetName();
            bounty.ClaimNote = cleanNote;
            SaveBoard();
            NotifyPlayer(bounty.PosterID, "BOUNTY CLAIMED", bounty.ClaimerName + " claims the bounty on " + bounty.TargetName + ".");
            info = "Claim sent. The poster must confirm it.";
            return true;
        }

        if (action == FENR_PDA_BountyAction.CONFIRM || action == FENR_PDA_BountyAction.REJECT)
        {
            if (!canManage)
            {
                info = "Only the poster can review claims.";
                return false;
            }
            if (bounty.Status != FENR_PDA_BountyStatus.CLAIMED)
            {
                info = "There is no pending claim.";
                return false;
            }
            if (action == FENR_PDA_BountyAction.CONFIRM)
            {
                bounty.Status = FENR_PDA_BountyStatus.COMPLETED;
                NotifyPlayer(bounty.ClaimerID, "BOUNTY CONFIRMED", "Your claim on " + bounty.TargetName + " was confirmed. Reward: " + bounty.Reward);
                info = "Claim confirmed. Pay out the reward to " + bounty.ClaimerName + ".";
            }
            else
            {
                NotifyPlayer(bounty.ClaimerID, "BOUNTY CLAIM REJECTED", "Your claim on " + bounty.TargetName + " was rejected.");
                bounty.Status = FENR_PDA_BountyStatus.OPEN;
                bounty.ClaimerID = "";
                bounty.ClaimerName = "";
                bounty.ClaimNote = "";
                info = "Claim rejected. The bounty is open again.";
            }
            SaveBoard();
            return true;
        }

        if (action == FENR_PDA_BountyAction.CANCEL || action == FENR_PDA_BountyAction.REMOVE)
        {
            bool adminRemove = !canManage && isAdmin;
            if (!canManage && !adminRemove)
            {
                info = "Only the poster can cancel this bounty.";
                return false;
            }
            s_Bounties.RemoveItem(bounty);
            SaveBoard();
            if (adminRemove)
                FENR_PDA_Storage.LogAdmin(sender.GetName(), senderID, "BOUNTY_REMOVE", bounty.PosterName + " (" + bounty.PosterID + ")", bounty.TargetName);
            info = "Bounty removed.";
            return true;
        }

        info = "Unknown action.";
        return false;
    }

    // Flat payload (FIELD_STRIDE per bounty): ID, Target, Reward, Reason,
    // PosterID, PosterName, Server("1"/"0"), Status, ClaimerID, ClaimerName,
    // ClaimNote, Posted
    static ref array<string> BuildPage(string board, int page, string viewerID, out int total, out int pageOut)
    {
        EnsureLoaded();
        ref array<string> fields = new array<string>();
        array<FENR_PDA_Bounty> matches = new array<FENR_PDA_Bounty>();

        // Server bounties first, then newest first.
        int pass;
        for (pass = 0; pass < 2; pass++)
        {
            for (int i = s_Bounties.Count() - 1; i >= 0; i--)
            {
                FENR_PDA_Bounty bounty = s_Bounties[i];
                if (!bounty)
                    continue;
                if (pass == 0 && !bounty.IsServer)
                    continue;
                if (pass == 1 && bounty.IsServer)
                    continue;

                if (board == FENR_PDA_BountyLimits.BOARD_MINE)
                {
                    if (bounty.PosterID != viewerID && bounty.ClaimerID != viewerID)
                        continue;
                }
                else if (bounty.Status == FENR_PDA_BountyStatus.COMPLETED)
                {
                    continue;
                }
                matches.Insert(bounty);
            }
        }

        total = matches.Count();
        int pageSize = FENR_PDA_BountyLimits.PAGE_SIZE;
        if (board == FENR_PDA_BountyLimits.BOARD_MINE)
            pageSize = 50;
        int maxPage = 0;
        if (total > 0)
            maxPage = (total - 1) / pageSize;
        if (page > maxPage)
            page = maxPage;
        if (page < 0)
            page = 0;
        pageOut = page;

        int start = page * pageSize;
        int end = start + pageSize;
        if (end > total)
            end = total;

        for (int j = start; j < end; j++)
        {
            FENR_PDA_Bounty item = matches[j];
            string posted = item.Created;
            if (posted.Length() >= 16)
                posted = posted.Substring(5, 11);
            string serverFlag = "0";
            if (item.IsServer)
                serverFlag = "1";
            fields.Insert(item.ID);
            fields.Insert(item.TargetName);
            fields.Insert(item.Reward);
            fields.Insert(item.Reason);
            fields.Insert(item.PosterID);
            fields.Insert(item.PosterName);
            fields.Insert(serverFlag);
            fields.Insert(item.Status);
            fields.Insert(item.ClaimerID);
            fields.Insert(item.ClaimerName);
            fields.Insert(item.ClaimNote);
            fields.Insert(posted);
        }
        return fields;
    }
};
