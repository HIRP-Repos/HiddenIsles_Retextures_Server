/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    S.O.S signal (server side).

    A player sends an S.O.S from a powered PDA logged in as themselves.
    Their stored recipients (up to SosMaxContacts contacts, or one group) get:
      - a direct / group chat message with the sender's grid,
      - live, on whoever is using the recipient's logged-in PDA: a red ping
        on map + compass and an alarm (SOS_ALERT).
    The signal burst then burns out the PDA, its battery and every drive in
    it (all set to ruined).
*/

class FENR_PDA_Sos
{
    protected static string Grid(float x, float z)
    {
        int gx = Math.Floor(x / 100.0);
        int gz = Math.Floor(z / 100.0);
        if (gx < 0) gx = 0;
        if (gz < 0) gz = 0;
        return gx.ToStringLen(3) + " " + gz.ToStringLen(3);
    }

    protected static void Alert(PlayerBase receiver, string senderName, vector pos, int minutes, string senderID)
    {
        if (!receiver || !receiver.GetIdentity())
            return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_ALERT, new Param5<string, float, float, int, string>(senderName, pos[0], pos[2], minutes, senderID), true, receiver.GetIdentity());
    }

    // Steam64 of a stored contact / member ID.
    protected static string Steam64Of(string id)
    {
        string steam64 = FENR_PDA_Storage.ResolveSteam64(id);
        if (steam64 != "")
            return steam64;
        return id;
    }

    // Live ping + alarm for a recipient, unless they blocked the sender.
    // Returns true when someone received it live.
    protected static bool AlertRecipient(string recipientID, string senderName, vector pos, int minutes, string senderID)
    {
        string steam64 = Steam64Of(recipientID);
        if (FENR_PDA_AccountStore.IsBlockedBy(steam64, senderID))
            return false;
        PlayerBase holder = FENR_PDA_Sessions.LiveHolder(steam64);
        if (!holder)
            return false;
        Alert(holder, senderName, pos, minutes, senderID);
        return true;
    }

    // The powered PDA logged in as this player (hands first).
    protected static FENR_PDA_Device OwnDevice(PlayerBase player, string steam64)
    {
        FENR_PDA_Device hands = FENR_PDA_Device.Cast(player.GetItemInHands());
        if (hands && FENR_PDA_Server.IsWorkingDevice(hands) && FENR_PDA_Sessions.OwnerOf(hands) == steam64)
            return hands;
        array<EntityAI> inventory = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
        foreach (EntityAI entity : inventory)
        {
            FENR_PDA_Device candidate = FENR_PDA_Device.Cast(entity);
            if (candidate && FENR_PDA_Server.IsWorkingDevice(candidate) && FENR_PDA_Sessions.OwnerOf(candidate) == steam64)
                return candidate;
        }
        return null;
    }

    // Ruins the PDA and everything attached to it.
    protected static void BurnOut(FENR_PDA_Device device)
    {
        if (!device)
            return;
        FENR_PDA_Sessions.End(device, "");
        array<EntityAI> parts = new array<EntityAI>();
        int count = device.GetInventory().AttachmentCount();
        for (int i = 0; i < count; i++)
        {
            EntityAI attachment = device.GetInventory().GetAttachmentFromIndex(i);
            if (attachment)
                parts.Insert(attachment);
        }
        foreach (EntityAI part : parts)
        {
            if (part)
                part.SetHealth("", "", 0);
        }
        if (device.GetCompEM())
            device.GetCompEM().SwitchOff();
        device.SetHealth("", "", 0);
    }

    static bool Send(PlayerIdentity sender, out string info)
    {
        info = "";
        if (!FENR_PDA_Storage.SosEnabled())
        {
            info = "S.O.S is disabled on this server.";
            return false;
        }
        PlayerBase player = FENR_PDA_Server.PlayerOf(sender);
        if (!player || !player.IsAlive())
        {
            info = "S.O.S failed.";
            return false;
        }
        // The PDA used (and burned) must be powered and logged in as the sender.
        string senderID = sender.GetPlainId();
        FENR_PDA_Device device = OwnDevice(player, senderID);
        if (!device)
        {
            info = "Log in to your PDA to send an S.O.S.";
            return false;
        }
        FENR_PDA_DeviceMeta meta = FENR_PDA_AccountStore.Meta(FENR_PDA_AccountStore.KeyFor(senderID), false);
        if (!meta)
        {
            info = "No S.O.S recipients set on this PDA (SYSTEM > S.O.S).";
            return false;
        }

        vector pos = player.GetPosition();
        string grid = Grid(pos[0], pos[2]);
        string text = "S.O.S  //  EMERGENCY  //  GRID " + grid + "  //  RESPOND";
        int minutes = FENR_PDA_Storage.SosPingMinutes();
        int reached = 0;
        int notified = 0;

        if (meta.SosMode == "GROUP")
        {
            FENR_PDA_Group group = FENR_PDA_Groups.FindGroup(meta.SosGroup);
            if (!group || !FENR_PDA_Groups.IsMember(sender, meta.SosGroup))
            {
                info = "Your S.O.S group no longer exists. Pick another in SYSTEM > S.O.S.";
                return false;
            }
            string result;
            FENR_PDA_Groups.SendMessage(sender, meta.SosGroup, text, result);
            foreach (FENR_PDA_GroupMember member : group.Members)
            {
                if (!member || FENR_PDA_Server.IdentityMatches(sender, member.ID) || FENR_PDA_Server.IsTestAccount(member.ID))
                    continue;
                notified++;
                if (AlertRecipient(member.ID, sender.GetName(), pos, minutes, senderID))
                    reached++;
            }
        }
        else
        {
            if (meta.SosTargets.Count() == 0)
            {
                info = "No S.O.S recipients set on this PDA (SYSTEM > S.O.S).";
                return false;
            }
            int limit = FENR_PDA_Storage.SosMaxContacts();
            foreach (string target : meta.SosTargets)
            {
                if (notified >= limit) break;
                if (target == "" || FENR_PDA_Server.IsTestAccount(target)) continue;
                notified++;
                FENR_PDA_Messages.SendSystemDirect(sender, player, target, text);
                if (AlertRecipient(target, sender.GetName(), pos, minutes, senderID))
                    reached++;
            }
        }

        if (notified == 0)
        {
            info = "No valid S.O.S recipients. Check SYSTEM > S.O.S.";
            return false;
        }

        BurnOut(device);
        FENR_PDA_Storage.LogSystem("SOS Player=" + sender.GetName() + " Steam64=" + senderID + " Grid=" + grid + " Recipients=" + notified.ToString() + " Live=" + reached.ToString());
        info = "S.O.S sent to " + notified.ToString() + " recipient(s), " + reached.ToString() + " received it live. Your PDA burned out.";
        return true;
    }
};
