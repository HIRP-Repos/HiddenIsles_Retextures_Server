/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    One message pipeline for direct messages, public channels and test-account
    mirrors.

    Every message is written to the log once, stamped with the account keys
    of the players it is filed for; FENR_PDA_History files it for them.
    Public channel lines are stored once (shared), not per player.

    v8.1: live delivery goes to whoever is using the recipient's logged-in
    PDA (FENR_PDA_Sessions.LiveHolder); otherwise the message waits in the
    recipient's history until they log in.
*/

class FENR_PDA_Messages
{
    protected static string Clamp(string text, int maxLength)
    {
        if (text.LengthUtf8() > maxLength)
            return text.SubstringUtf8(0, maxLength);
        return text;
    }

    protected static ref FENR_PDA_MessageRecord NewRecord(string type, string senderSteam64, string senderName, string targetID, string targetName)
    {
        ref FENR_PDA_MessageRecord record = new FENR_PDA_MessageRecord();
        record.Type = type;
        record.SenderSteam64 = senderSteam64;
        record.SenderName = senderName;
        record.TargetID = targetID;
        record.TargetName = targetName;
        return record;
    }

    // Writes the audit/history record and files it for the players involved.
    static void Record(FENR_PDA_MessageRecord record)
    {
        if (!record)
            return;
        FENR_PDA_Storage.RecordMessage(record);
        FENR_PDA_History.Ingest(record, false);
    }

    protected static ref FENR_PDA_MessageRecord NewChatRecord(string type, PlayerIdentity sender, string targetID, string targetName, string body)
    {
        ref FENR_PDA_MessageRecord record = NewRecord(type, sender.GetPlainId(), sender.GetName(), targetID, targetName);
        record.Message = body;
        record.Seq = FENR_PDA_History.NextSeq();
        record.GameTime = FENR_PDA_UI_Kit.GameTime();
        return record;
    }

    // Server -> one client.  own = the receiving player wrote it.
    protected static void Deliver(PlayerBase player, string conversationID, string senderName, string body, bool own, int seq)
    {
        if (!player || !player.GetIdentity())
            return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SEND_MESSAGE, new Param5<string, string, string, bool, int>(conversationID, senderName, body, own, seq), true, player.GetIdentity());
    }

    static void Submit(PlayerIdentity sender, string targetID, string targetName, string body)
    {
        if (!GetGame().IsServer() || !sender || targetID == "" || body == "")
            return;

        PlayerBase senderPlayer = FENR_PDA_Server.PlayerOf(sender);
        if (!FENR_PDA_Server.RequireDevice(sender, senderPlayer))
            return;
        if (!FENR_PDA_Server.Throttle(sender, "MSG", 5, 1.0))
        {
            FENR_PDA_Server.Deny(sender, "Transmitting too fast. Wait a moment.");
            return;
        }

        FENR_PDA_Storage.RememberIdentity(sender);
        body = Clamp(body, FENR_PDA_Limits.DIRECT_MESSAGE);

        if (FENR_PDA_Server.TestAccountsEnabled() && FENR_PDA_Server.IsTestAccount(targetID))
        {
            SubmitTestMirror(sender, senderPlayer, targetID, body);
            return;
        }

        if (FENR_PDA_ChannelIds.IsChannel(targetID))
        {
            // Announcements are admin-only (FENR_PDA_Admin.Broadcast).
            if (targetID == FENR_PDA_ChannelIds.ANNOUNCEMENTS)
                return;
            SubmitChannel(sender, targetID, body);
            return;
        }

        SubmitDirect(sender, senderPlayer, targetID, targetName, body);
    }

    // Server-generated direct message (S.O.S): no throttle, same pipeline.
    static void SendSystemDirect(PlayerIdentity sender, PlayerBase senderPlayer, string targetID, string body)
    {
        if (!sender || !senderPlayer || targetID == "" || body == "")
            return;
        SubmitDirect(sender, senderPlayer, targetID, FENR_PDA_Storage.ResolvePlayerName(targetID), Clamp(body, FENR_PDA_Limits.DIRECT_MESSAGE));
    }

    protected static void SubmitDirect(PlayerIdentity sender, PlayerBase senderPlayer, string targetID, string targetName, string body)
    {
        PlayerBase online = FENR_PDA_Server.FindOnlinePlayer(targetID);

        string targetSteam64 = FENR_PDA_Storage.ResolveSteam64(targetID);
        string resolvedName = FENR_PDA_Storage.ResolvePlayerName(targetID);
        if (online && online.GetIdentity())
        {
            targetSteam64 = online.GetIdentity().GetPlainId();
            resolvedName = online.GetIdentity().GetName();
        }
        if (resolvedName == "")
            resolvedName = targetName;
        if (resolvedName == "")
            resolvedName = targetID;

        string senderID = sender.GetPlainId();

        // Filed for the recipient unless they are unknown or blocked the sender.
        // The message waits in their history until they log in on a PDA.
        bool filed = targetSteam64 != "" && !FENR_PDA_AccountStore.IsBlockedBy(targetSteam64, senderID);

        ref FENR_PDA_MessageRecord record = NewChatRecord(FENR_PDA_MessageType.DIRECT, sender, targetSteam64, resolvedName, body);
        if (record.TargetID == "")
            record.TargetID = targetID;
        record.SenderDevice = FENR_PDA_AccountStore.KeyFor(senderID);
        record.SenderConvID = targetID;
        if (filed)
            record.TargetDevice = FENR_PDA_AccountStore.KeyFor(targetSteam64);
        Record(record);

        // Accepted sends always appear in the sender's conversation.
        FENR_PDA_AccountStore.OnDirectMessage(senderID, targetID, resolvedName, false);
        Deliver(senderPlayer, targetID, sender.GetName(), body, true, record.Seq);

        if (!filed)
            return;
        FENR_PDA_AccountStore.OnDirectMessage(targetSteam64, senderID, sender.GetName(), true);
        PlayerBase holder = FENR_PDA_Sessions.LiveHolder(targetSteam64);
        if (holder)
            Deliver(holder, senderID, sender.GetName(), body, false, record.Seq);
    }

    protected static void SubmitTestMirror(PlayerIdentity sender, PlayerBase senderPlayer, string testID, string body)
    {
        string testName = FENR_PDA_Server.TestAccountName(testID);
        string senderKey = FENR_PDA_AccountStore.KeyFor(sender.GetPlainId());

        ref FENR_PDA_MessageRecord outbound = NewChatRecord(FENR_PDA_MessageType.DIRECT, sender, testID, testName, body);
        outbound.SenderDevice = senderKey;
        outbound.SenderConvID = testID;
        Record(outbound);
        Deliver(senderPlayer, testID, sender.GetName(), body, true, outbound.Seq);

        ref FENR_PDA_MessageRecord reply = NewRecord(FENR_PDA_MessageType.DIRECT, testID, testName, sender.GetPlainId(), sender.GetName());
        reply.Message = body;
        reply.Seq = FENR_PDA_History.NextSeq();
        reply.GameTime = FENR_PDA_UI_Kit.GameTime();
        reply.TargetDevice = senderKey;
        Record(reply);
        Deliver(senderPlayer, testID, testName, body, false, reply.Seq);
    }

    protected static void SubmitChannel(PlayerIdentity sender, string channelID, string body)
    {
        ref FENR_PDA_MessageRecord record = NewChatRecord(FENR_PDA_MessageType.CHANNEL, sender, channelID, FENR_PDA_ChannelIds.Label(channelID), body);
        Record(record);
        Broadcast(channelID, sender.GetName(), body, sender.GetPlainId(), record.Seq);
    }

    // Sends a stored channel line to every logged-in PDA in use.  "own" is
    // relative to the player the PDA is logged in as.
    static void Broadcast(string channelID, string senderName, string body, string senderID, int seq)
    {
        if (!GetGame().IsServer())
            return;

        ref array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.GetIdentity())
                continue;
            FENR_PDA_Device device = FENR_PDA_Sessions.ActiveDevice(player);
            if (!device)
                continue;
            bool own = senderID != "" && device.FenrSessionOwner() == senderID;
            Deliver(player, channelID, senderName, body, own, seq);
        }
    }

    // Admin broadcast: the caller has already logged the record with this seq.
    static void BroadcastAnnouncement(string senderName, string body, int seq)
    {
        Broadcast(FENR_PDA_ChannelIds.ANNOUNCEMENTS, senderName, body, "", seq);
    }

    static void BuildOnlineContactIds(array<string> requestedIDs, array<string> output)
    {
        if (!output)
            return;

        output.Clear();
        if (!requestedIDs)
            return;

        // One pass over the players instead of one per contact.
        map<string, PlayerBase> online = new map<string, PlayerBase>();
        FENR_PDA_Server.FillOnlinePlayers(online);

        foreach (string requestedID : requestedIDs)
        {
            if (FENR_PDA_Server.TestAccountsEnabled() && FENR_PDA_Server.IsTestAccount(requestedID))
            {
                output.Insert(requestedID);
                continue;
            }

            // Online = someone is using a PDA logged in as that player.
            string steam64 = requestedID;
            PlayerBase player = online.Get(requestedID);
            if (player && player.GetIdentity())
                steam64 = player.GetIdentity().GetPlainId();
            else
            {
                string resolved = FENR_PDA_Storage.ResolveSteam64(requestedID);
                if (resolved != "")
                    steam64 = resolved;
            }
            // Keep the client's stored key so legacy GetId() contacts and
            // Steam64 contacts both highlight correctly.
            if (FENR_PDA_Sessions.LiveHolder(steam64))
                output.Insert(requestedID);
        }
    }

    static bool ResolveContact(string lookup, out string contactID, out string displayName)
    {
        contactID = "";
        displayName = "";

        if (FENR_PDA_Server.ResolveTestAccount(lookup, contactID, displayName))
            return true;

        // Explicit "add by name or ID": the only lookup allowed to match names.
        PlayerBase player = FENR_PDA_Server.FindOnlinePlayer(lookup, true);
        if (!player || !player.GetIdentity())
            return false;

        contactID = player.GetIdentity().GetPlainId();
        displayName = player.GetIdentity().GetName();
        return true;
    }
};
