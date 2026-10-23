/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Persistent, server-authoritative private channel service.
*/

class FENR_PDA_Groups
{
    protected static ref array<ref FENR_PDA_Group> s_Groups;
    protected static ref map<string, ref array<ref FENR_PDA_GroupMessage>> s_MessageCache;
    static int s_GroupCounter = 0;
    static bool s_Initialized = false;

    static void Init()
    {
        if (!GetGame().IsServer() || s_Initialized)
            return;

        MakeDirectory(FENR_PDA_Paths.PROFILE_ROOT);
        MakeDirectory(FENR_PDA_Paths.GROUP_ROOT);
        MakeDirectory(FENR_PDA_Paths.GROUP_MESSAGE_ROOT);

        s_Groups = FENR_PDA_Storage.LoadGroups();
        s_MessageCache = new map<string, ref array<ref FENR_PDA_GroupMessage>>();
        if (!s_Groups)
            s_Groups = new array<ref FENR_PDA_Group>();
        FENR_PDA_Storage.SaveGroups(s_Groups);

        s_Initialized = true;
        FENR_PDA_Storage.LogSystem("Fenrir Industries PDA group service initialized. Groups=" + s_Groups.Count().ToString());
    }

    static void EnsureInit()
    {
        if (!s_Initialized)
            Init();
    }

    static void SaveGroups()
    {
        if (!s_Groups)
            s_Groups = new array<ref FENR_PDA_Group>();

        FENR_PDA_Storage.SaveGroups(s_Groups);
    }

    protected static string TwoDigit(int value)
    {
        if (value < 10)
            return "0" + value.ToString();
        return value.ToString();
    }

    protected static string NewGroupID()
    {
        int year, month, day;
        int hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);
        s_GroupCounter++;
        return "FENR_PDA_GROUP_" + year.ToString() + TwoDigit(month) + TwoDigit(day) + "_" + TwoDigit(hour) + TwoDigit(minute) + TwoDigit(second) + "_" + Math.RandomInt(1000, 9999).ToString() + "_" + s_GroupCounter.ToString();
    }

    static string StoredMemberID(FENR_PDA_Group group, PlayerIdentity identity)
    {
        if (!group || !identity || !group.Members)
            return "";

        foreach (FENR_PDA_GroupMember member : group.Members)
        {
            if (member && FENR_PDA_Server.IdentityMatches(identity, member.ID))
                return member.ID;
        }
        return "";
    }

    static bool HasMemberIdentity(FENR_PDA_Group group, PlayerIdentity identity)
    {
        return StoredMemberID(group, identity) != "";
    }

    protected static int FindMemberIndexByID(FENR_PDA_Group group, string lookup)
    {
        if (!group || !group.Members || lookup == "")
            return -1;

        string canonicalSteam64 = FENR_PDA_Storage.ResolveSteam64(lookup);
        for (int i = 0; i < group.Members.Count(); i++)
        {
            FENR_PDA_GroupMember member = group.Members.Get(i);
            if (!member)
                continue;
            if (member.ID == lookup)
                return i;

            if (canonicalSteam64 != "")
            {
                string memberSteam64 = FENR_PDA_Storage.ResolveSteam64(member.ID);
                if (memberSteam64 == canonicalSteam64)
                    return i;
            }
        }
        return -1;
    }

    // Membership by stored ID (Steam64 or legacy ID of the same player).
    static bool HasMemberID(FENR_PDA_Group group, string memberID)
    {
        if (memberID == "")
            return false;
        return FindMemberIndexByID(group, memberID) >= 0;
    }

    static bool IsMemberID(string memberID, string groupID)
    {
        FENR_PDA_Group group = FindGroup(groupID);
        return group && HasMemberID(group, memberID);
    }

    // Groups of a player (used for whoever the open PDA is logged in as).
    static void FillGroupsForMember(string memberID, array<string> ids, array<string> names, array<string> ownerIDs)
    {
        EnsureInit();
        if (!ids || !names || !ownerIDs)
            return;
        ids.Clear();
        names.Clear();
        ownerIDs.Clear();
        if (memberID == "")
            return;
        foreach (FENR_PDA_Group group : s_Groups)
        {
            if (!group || !HasMemberID(group, memberID))
                continue;
            ids.Insert(group.GroupID);
            names.Insert(group.GroupName);
            ownerIDs.Insert(group.OwnerID);
        }
    }

    // Steam64 of a stored member ID (legacy IDs resolve through known players).
    protected static string Steam64Of(string memberID)
    {
        string steam64 = FENR_PDA_Storage.ResolveSteam64(memberID);
        if (steam64 != "")
            return steam64;
        return memberID;
    }

    static void FillGroupsForIdentity(PlayerIdentity identity, array<string> ids, array<string> names, array<string> ownerIDs)
    {
        EnsureInit();
        if (!identity || !ids || !names || !ownerIDs)
            return;

        ids.Clear();
        names.Clear();
        ownerIDs.Clear();
        foreach (FENR_PDA_Group group : s_Groups)
        {
            if (!group || !HasMemberIdentity(group, identity))
                continue;
            ids.Insert(group.GroupID);
            names.Insert(group.GroupName);
            ownerIDs.Insert(group.OwnerID);
        }
    }

    static bool IsMember(PlayerIdentity identity, string groupID)
    {
        FENR_PDA_Group group = FindGroup(groupID);
        return group && HasMemberIdentity(group, identity);
    }

    static FENR_PDA_Group FindGroup(string groupID)
    {
        EnsureInit();
        foreach (FENR_PDA_Group group : s_Groups)
        {
            if (group && group.GroupID == groupID)
                return group;
        }
        return null;
    }

    protected static int CountOwnedGroups(PlayerIdentity owner)
    {
        EnsureInit();
        if (!owner)
            return 0;

        int count = 0;
        foreach (FENR_PDA_Group group : s_Groups)
        {
            if (group && FENR_PDA_Server.IdentityMatches(owner, group.OwnerID))
                count++;
        }
        return count;
    }

    protected static string ResolveMemberName(string memberID, string suppliedName)
    {
        if (FENR_PDA_Server.IsTestAccount(memberID))
        {
            string testName = FENR_PDA_Server.TestAccountName(memberID);
            if (testName != "")
                return testName;
        }

        PlayerBase onlinePlayer = FENR_PDA_Server.FindOnlinePlayer(memberID);
        if (onlinePlayer && onlinePlayer.GetIdentity())
            return onlinePlayer.GetIdentity().GetName();

        if (suppliedName != "")
            return suppliedName;

        return memberID;
    }

    static ref array<ref FENR_PDA_GroupMessage> LoadMessages(string groupID)
    {
        EnsureInit();

        if (s_MessageCache.Contains(groupID))
            return s_MessageCache[groupID];

        ref array<ref FENR_PDA_GroupMessage> messages = FENR_PDA_Storage.LoadGroupHistory(groupID);
        if (!messages)
            messages = new array<ref FENR_PDA_GroupMessage>();

        // Histories from before 7.9 have no message numbers: number them once.
        bool missing = false;
        foreach (FENR_PDA_GroupMessage existing : messages)
        {
            if (existing && existing.Seq <= 0)
                missing = true;
        }
        if (missing)
        {
            for (int i = 0; i < messages.Count(); i++)
            {
                if (messages[i])
                    messages[i].Seq = i + 1;
            }
        }

        s_MessageCache.Set(groupID, messages);
        return messages;
    }

    protected static void SaveMessages(string groupID, array<ref FENR_PDA_GroupMessage> messages)
    {
        if (!messages)
            return;

        while (messages.Count() > FENR_PDA_Limits.GROUP_HISTORY)
            messages.RemoveOrdered(0);

        s_MessageCache.Set(groupID, messages);
        FENR_PDA_Storage.SaveGroupHistory(groupID, messages);
    }

    protected static void AppendMessage(string groupID, string senderID, string senderName, string messageText)
    {
        ref array<ref FENR_PDA_GroupMessage> messages = LoadMessages(groupID);
        ref FENR_PDA_GroupMessage message = new FENR_PDA_GroupMessage();
        message.Seq = 1;
        if (messages.Count() > 0 && messages[messages.Count() - 1])
            message.Seq = messages[messages.Count() - 1].Seq + 1;
        message.Timestamp = FENR_PDA_Storage.Timestamp();
        message.Clock = FENR_PDA_UI_Kit.GameTime();
        message.SenderID = senderID;
        message.SenderName = senderName;
        message.MessageText = messageText;
        messages.Insert(message);
        SaveMessages(groupID, messages);
    }

    protected static void AppendSystemMessage(FENR_PDA_Group group, string text)
    {
        if (group)
            AppendMessage(group.GroupID, "SYSTEM", "SYSTEM", text);
    }

    // UI refresh for whoever is using that member's logged-in PDA.
    protected static void SendRefreshToIdentity(string identityID, string groupID)
    {
        if (FENR_PDA_Server.IsTestAccount(identityID))
            return;
        PlayerBase player = FENR_PDA_Sessions.LiveHolder(Steam64Of(identityID));
        if (player && player.GetIdentity())
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_REFRESH, new Param1<string>(groupID), true, player.GetIdentity());
    }

    protected static void BroadcastRefresh(FENR_PDA_Group group, string extraIdentityID = "")
    {
        if (group && group.Members)
        {
            foreach (FENR_PDA_GroupMember member : group.Members)
            {
                if (member)
                    SendRefreshToIdentity(member.ID, group.GroupID);
            }
        }

        if (extraIdentityID != "" && (!group || !group.HasMember(extraIdentityID)))
        {
            string refreshGroupID = "";
            if (group)
                refreshGroupID = group.GroupID;
            SendRefreshToIdentity(extraIdentityID, refreshGroupID);
        }
    }

    protected static void SendIncoming(string memberID, string groupID, string groupName, string senderName, string messageText)
    {
        if (FENR_PDA_Server.IsTestAccount(memberID))
            return;

        // Live to whoever is using that member's logged-in PDA.
        PlayerBase recipient = FENR_PDA_Sessions.LiveHolder(Steam64Of(memberID));
        if (!recipient || !recipient.GetIdentity())
            return;

        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_INCOMING, new Param4<string, string, string, string>(groupID, groupName, senderName, messageText), true, recipient.GetIdentity());
    }

    protected static void BroadcastIncoming(FENR_PDA_Group group, string senderName, string messageText)
    {
        if (!group || !group.Members)
            return;

        foreach (FENR_PDA_GroupMember member : group.Members)
        {
            if (member)
                SendIncoming(member.ID, group.GroupID, group.GroupName, senderName, messageText);
        }
    }

    static bool CreateGroup(PlayerIdentity creator, string groupName, out string groupID, out string resultText)
    {
        EnsureInit();
        groupID = "";
        resultText = "";

        if (!creator)
        {
            resultText = "Invalid PDA identity.";
            return false;
        }

        if (groupName == "" || groupName.LengthUtf8() > FENR_PDA_Limits.GROUP_NAME)
        {
            resultText = "Group name must be 1-32 characters.";
            return false;
        }

        string creatorID = creator.GetPlainId();
        if (CountOwnedGroups(creator) >= FENR_PDA_Limits.OWNED_GROUPS)
        {
            resultText = "You already own the maximum number of groups (10).";
            return false;
        }

        ref FENR_PDA_Group group = new FENR_PDA_Group();
        group.GroupID = NewGroupID();
        group.GroupName = groupName;
        group.OwnerID = creatorID;
        group.OwnerName = creator.GetName();
        group.Members.Insert(new FENR_PDA_GroupMember(creatorID, creator.GetName()));
        s_Groups.Insert(group);
        SaveGroups();

        AppendSystemMessage(group, creator.GetName() + " created the private channel.");
        FENR_PDA_Storage.LogSystem("GROUP_CREATE Group=" + group.GroupID + " Name=" + group.GroupName + " Owner=" + creator.GetName() + " OwnerID=" + creatorID);
        BroadcastRefresh(group);

        groupID = group.GroupID;
        resultText = "Created group: " + group.GroupName;
        return true;
    }

    static bool RenameGroup(PlayerIdentity actor, string groupID, string newName, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !actor)
        {
            resultText = "Group not found.";
            return false;
        }

        if (!FENR_PDA_Server.IdentityMatches(actor, group.OwnerID))
        {
            resultText = "Only the group owner can rename this channel.";
            return false;
        }

        if (newName == "" || newName.LengthUtf8() > FENR_PDA_Limits.GROUP_NAME)
        {
            resultText = "Group name must be 1-32 characters.";
            return false;
        }

        string oldName = group.GroupName;
        group.GroupName = newName;
        SaveGroups();
        AppendSystemMessage(group, actor.GetName() + " renamed the channel from " + oldName + " to " + newName + ".");
        FENR_PDA_Storage.LogSystem("GROUP_RENAME Group=" + groupID + " Old=" + oldName + " New=" + newName + " Actor=" + actor.GetName());
        BroadcastRefresh(group);
        resultText = "Renamed group to: " + newName;
        return true;
    }

    static bool AddMember(PlayerIdentity actor, string groupID, string memberID, string memberName, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !actor)
        {
            resultText = "Group not found.";
            return false;
        }

        if (!FENR_PDA_Server.IdentityMatches(actor, group.OwnerID))
        {
            resultText = "Only the group owner can add members.";
            return false;
        }

        if (memberID == "" || FENR_PDA_ChannelIds.IsChannel(memberID))
        {
            resultText = "Invalid PDA member.";
            return false;
        }

        if (FENR_PDA_Server.IsTestAccount(memberID) && !FENR_PDA_Server.TestAccountsEnabled())
        {
            resultText = "PDA test accounts are disabled.";
            return false;
        }

        if (!FENR_PDA_Server.IsTestAccount(memberID))
        {
            PlayerBase memberPlayer = FENR_PDA_Server.FindOnlinePlayer(memberID);
            if (memberPlayer && memberPlayer.GetIdentity())
            {
                FENR_PDA_Storage.RememberIdentity(memberPlayer.GetIdentity());
                memberID = memberPlayer.GetIdentity().GetPlainId();
                memberName = memberPlayer.GetIdentity().GetName();
            }
            else
            {
                string knownSteam64 = FENR_PDA_Storage.ResolveSteam64(memberID);
                if (knownSteam64 != "")
                    memberID = knownSteam64;
            }
        }

        if (FindMemberIndexByID(group, memberID) >= 0)
        {
            resultText = "That PDA is already in the group.";
            return false;
        }

        if (group.Members.Count() >= FENR_PDA_Limits.GROUP_MEMBERS)
        {
            resultText = "Group is full (25 members).";
            return false;
        }

        string resolvedName = ResolveMemberName(memberID, memberName);
        if (!FENR_PDA_Server.IsTestAccount(memberID))
            FENR_PDA_Storage.RememberContact(memberID, resolvedName);
        group.Members.Insert(new FENR_PDA_GroupMember(memberID, resolvedName));
        SaveGroups();
        AppendSystemMessage(group, actor.GetName() + " added " + resolvedName + ".");
        FENR_PDA_Storage.LogSystem("GROUP_ADD_MEMBER Group=" + groupID + " Actor=" + actor.GetName() + " Member=" + resolvedName + " MemberID=" + memberID);
        BroadcastRefresh(group);
        resultText = "Added " + resolvedName + ".";
        return true;
    }

    static bool RemoveMember(PlayerIdentity actor, string groupID, string memberID, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !actor)
        {
            resultText = "Group not found.";
            return false;
        }

        if (!FENR_PDA_Server.IdentityMatches(actor, group.OwnerID))
        {
            resultText = "Only the group owner can remove members.";
            return false;
        }

        if (memberID == group.OwnerID)
        {
            resultText = "The owner cannot remove themselves. Delete the group instead.";
            return false;
        }

        int memberIndex = FindMemberIndexByID(group, memberID);
        if (memberIndex < 0)
        {
            resultText = "Member not found.";
            return false;
        }

        string removedName = group.Members.Get(memberIndex).Name;
        group.Members.RemoveOrdered(memberIndex);
        SaveGroups();
        AppendSystemMessage(group, actor.GetName() + " removed " + removedName + ".");
        FENR_PDA_Storage.LogSystem("GROUP_REMOVE_MEMBER Group=" + groupID + " Actor=" + actor.GetName() + " Member=" + removedName + " MemberID=" + memberID);
        BroadcastRefresh(group, memberID);
        resultText = "Removed " + removedName + ".";
        return true;
    }

    static bool LeaveGroup(PlayerIdentity actor, string groupID, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !actor)
        {
            resultText = "Group not found.";
            return false;
        }

        string actorID = StoredMemberID(group, actor);
        if (actorID == "")
        {
            resultText = "You are not a member of this group.";
            return false;
        }

        if (group.OwnerID == actorID)
        {
            resultText = "The owner cannot leave. Delete the group instead.";
            return false;
        }

        int memberIndex = group.FindMemberIndex(actorID);
        group.Members.RemoveOrdered(memberIndex);
        SaveGroups();
        AppendSystemMessage(group, actor.GetName() + " left the channel.");
        FENR_PDA_Storage.LogSystem("GROUP_LEAVE Group=" + groupID + " Member=" + actor.GetName() + " MemberID=" + actorID);
        BroadcastRefresh(group, actorID);
        resultText = "Left group: " + group.GroupName;
        return true;
    }

    static bool DeleteGroup(PlayerIdentity actor, string groupID, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !actor)
        {
            resultText = "Group not found.";
            return false;
        }

        if (!FENR_PDA_Server.IdentityMatches(actor, group.OwnerID))
        {
            resultText = "Only the group owner can delete this channel.";
            return false;
        }

        ref array<string> notifyIDs = new array<string>();
        foreach (FENR_PDA_GroupMember member : group.Members)
        {
            if (member)
                notifyIDs.Insert(member.ID);
        }

        string deletedName = group.GroupName;
        s_Groups.RemoveItem(group);
        SaveGroups();

        FENR_PDA_Storage.DeleteGroupHistory(groupID);
        if (s_MessageCache.Contains(groupID))
            s_MessageCache.Remove(groupID);

        FENR_PDA_Storage.LogSystem("GROUP_DELETE Group=" + groupID + " Name=" + deletedName + " Actor=" + actor.GetName());
        foreach (string notifyID : notifyIDs)
            SendRefreshToIdentity(notifyID, groupID);

        resultText = "Deleted group: " + deletedName;
        return true;
    }

    static bool SendMessage(PlayerIdentity sender, string groupID, string messageText, out string resultText)
    {
        EnsureInit();
        resultText = "";
        FENR_PDA_Group group = FindGroup(groupID);
        if (!group || !sender)
        {
            resultText = "Group not found.";
            return false;
        }

        if (!HasMemberIdentity(group, sender))
        {
            resultText = "You are not a member of this group.";
            return false;
        }

        if (messageText == "")
        {
            resultText = "Message is empty.";
            return false;
        }

        if (messageText.LengthUtf8() > FENR_PDA_Limits.GROUP_MESSAGE)
            messageText = messageText.SubstringUtf8(0, FENR_PDA_Limits.GROUP_MESSAGE);

        AppendMessage(groupID, sender.GetPlainId(), sender.GetName(), messageText);

        ref FENR_PDA_MessageRecord groupRecord = new FENR_PDA_MessageRecord();
        groupRecord.Type = FENR_PDA_MessageType.GROUP;
        groupRecord.SenderSteam64 = sender.GetPlainId();
        groupRecord.SenderName = sender.GetName();
        groupRecord.TargetID = groupID;
        groupRecord.TargetName = group.GroupName;
        groupRecord.Message = messageText;
        FENR_PDA_Messages.Record(groupRecord);

        BroadcastIncoming(group, sender.GetName(), messageText);

        if (FENR_PDA_Server.TestAccountsEnabled())
        {
            foreach (FENR_PDA_GroupMember testMember : group.Members)
            {
                if (!testMember || !FENR_PDA_Server.IsTestAccount(testMember.ID))
                    continue;

                string testName = FENR_PDA_Server.TestAccountName(testMember.ID);
                AppendMessage(groupID, testMember.ID, testName, messageText);

                ref FENR_PDA_MessageRecord testGroupRecord = new FENR_PDA_MessageRecord();
                testGroupRecord.Type = FENR_PDA_MessageType.GROUP;
                testGroupRecord.SenderSteam64 = testMember.ID;
                testGroupRecord.SenderName = testName;
                testGroupRecord.TargetID = groupID;
                testGroupRecord.TargetName = group.GroupName;
                testGroupRecord.Message = messageText;
                FENR_PDA_Messages.Record(testGroupRecord);

                BroadcastIncoming(group, testName, messageText);
            }
        }

        resultText = "Message sent.";
        return true;
    }
};
