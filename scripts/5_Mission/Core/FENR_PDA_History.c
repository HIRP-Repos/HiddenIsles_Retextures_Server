/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    PDA message history (server side), rebuilt from the message log.

    Every message is written to the log once (FENR_PDA_Storage.RecordMessage).
    At server start the last MessageLogsDays of log are replayed into memory;
    afterwards each new record is added as it is written.

      - Direct messages are filed per player (account key "A<steam64>") and
        conversation, so they follow the player to any PDA they log in on.
      - Public channels (Global, Buy/Sell, Announcements) keep one shared
        rolling history.

    Nothing here is written to disk: the log is the store.
*/

// Conversations of one player.
class FENR_PDA_DeviceHistory
{
    ref map<string, ref array<ref FENR_PDA_ChatMessage>> Convos;

    void FENR_PDA_DeviceHistory()
    {
        Convos = new map<string, ref array<ref FENR_PDA_ChatMessage>>();
    }
};

class FENR_PDA_History
{
    static const int LEGACY_SEQ_BASE = 1000000000;

    protected static ref map<string, ref FENR_PDA_DeviceHistory> s_Direct;
    protected static ref map<string, ref array<ref FENR_PDA_ChatMessage>> s_Channels;
    protected static int s_NextSeq = 1;
    protected static int s_LegacySeq = LEGACY_SEQ_BASE;
    protected static bool s_Built;

    protected static void EnsureMaps()
    {
        if (!s_Direct)
            s_Direct = new map<string, ref FENR_PDA_DeviceHistory>();
        if (!s_Channels)
            s_Channels = new map<string, ref array<ref FENR_PDA_ChatMessage>>();
    }

    // ------------------------------------------------------------------
    // Message numbers
    // ------------------------------------------------------------------
    static int NextSeq()
    {
        int seq = s_NextSeq;
        s_NextSeq++;
        return seq;
    }

    static int PeekNextSeq()
    {
        return s_NextSeq;
    }

    // The saved counter keeps numbers unique even after every log expired.
    static void SetMinNextSeq(int value)
    {
        if (value > s_NextSeq && value < LEGACY_SEQ_BASE)
            s_NextSeq = value;
    }

    // ------------------------------------------------------------------
    // Startup rebuild
    // ------------------------------------------------------------------
    static void Build()
    {
        EnsureMaps();
        if (s_Built)
            return;
        s_Built = true;

        int since = FENR_PDA_Storage.TodaySerial() - FENR_PDA_Storage.MessageHistoryDays() + 1;
        array<string> paths = new array<string>();
        FENR_PDA_Storage.MessageFilesSince(since, paths);

        int count = 0;
        foreach (string path : paths)
        {
            array<ref FENR_PDA_MessageRecord> records = FENR_PDA_Storage.ReadMessageFile(path);
            foreach (FENR_PDA_MessageRecord record : records)
            {
                if (!record)
                    continue;
                Ingest(record, true);
                count++;
            }
        }
        int fileCount = paths.Count();
        FENR_PDA_Storage.LogSystem("PDA history rebuilt from " + fileCount.ToString() + " log files (" + count.ToString() + " records).");
    }

    // ------------------------------------------------------------------
    // Adding records
    // ------------------------------------------------------------------
    static void Ingest(FENR_PDA_MessageRecord record, bool rebuild)
    {
        EnsureMaps();
        if (!record)
            return;
        string type = record.Type;
        if (type != FENR_PDA_MessageType.DIRECT && type != FENR_PDA_MessageType.CHANNEL && type != FENR_PDA_MessageType.BROADCAST)
            return;

        if (record.Seq <= 0)
        {
            // Pre-7.9 records: give them a number for this session only.
            record.Seq = s_LegacySeq;
            s_LegacySeq++;
        }
        else if (record.Seq >= s_NextSeq && record.Seq < LEGACY_SEQ_BASE)
        {
            s_NextSeq = record.Seq + 1;
        }

        ref FENR_PDA_ChatMessage message = new FENR_PDA_ChatMessage();
        message.m_Name = record.SenderName;
        message.m_Message = record.Message;
        message.m_Time = record.GameTime;
        if (message.m_Time == "" && record.Timestamp.Length() >= 16)
            message.m_Time = record.Timestamp.Substring(11, 5);
        message.m_SenderID = record.SenderSteam64;
        message.m_Seq = record.Seq;

        if (type == FENR_PDA_MessageType.CHANNEL)
        {
            AddChannel(record.TargetID, message);
            return;
        }
        if (type == FENR_PDA_MessageType.BROADCAST)
        {
            // Players see broadcasts under a neutral label; the log keeps the admin.
            message.m_Name = "Broadcast";
            AddChannel(FENR_PDA_ChannelIds.ANNOUNCEMENTS, message);
            return;
        }

        // DIRECT: one shared message object, filed under each player involved.
        // Pre-7.9 records carry no filing marks: file them for both sides.
        // Otherwise a side is filed when its mark is set (a blocked
        // recipient's mark is empty).
        bool legacy = record.Seq >= LEGACY_SEQ_BASE;
        string senderKey = "";
        string targetKey = "";
        if (legacy || record.SenderDevice != "")
            senderKey = FENR_PDA_AccountStore.KeyFor(record.SenderSteam64);
        if (legacy || record.TargetDevice != "")
            targetKey = FENR_PDA_AccountStore.KeyFor(record.TargetID);
        if (senderKey != "")
        {
            string senderConv = record.SenderConvID;
            if (senderConv == "")
                senderConv = record.TargetID;
            if (Accept(senderKey, senderConv, record.Seq, rebuild))
                AddDirect(senderKey, senderConv, message);
        }
        if (targetKey != "" && targetKey != senderKey)
        {
            if (Accept(targetKey, record.SenderSteam64, record.Seq, rebuild))
                AddDirect(targetKey, record.SenderSteam64, message);
        }
    }

    // During a rebuild, skip players that were pruned and conversations the
    // player deleted.
    protected static bool Accept(string deviceKey, string conversationID, int seq, bool rebuild)
    {
        if (!rebuild)
            return true;
        if (!FENR_PDA_AccountStore.IsKnown(deviceKey))
            return false;
        int cleared = FENR_PDA_AccountStore.ClearedSeq(deviceKey, conversationID);
        return seq > cleared;
    }

    protected static void AddDirect(string deviceKey, string conversationID, FENR_PDA_ChatMessage message)
    {
        if (conversationID == "")
            return;
        FENR_PDA_DeviceHistory device = s_Direct.Get(deviceKey);
        if (!device)
        {
            device = new FENR_PDA_DeviceHistory();
            s_Direct.Set(deviceKey, device);
        }
        array<ref FENR_PDA_ChatMessage> messages = device.Convos.Get(conversationID);
        if (!messages)
        {
            messages = new array<ref FENR_PDA_ChatMessage>();
            device.Convos.Set(conversationID, messages);
        }
        messages.Insert(message);
        while (messages.Count() > FENR_PDA_Limits.DIRECT_HISTORY)
            messages.RemoveOrdered(0);
    }

    protected static void AddChannel(string channelID, FENR_PDA_ChatMessage message)
    {
        if (channelID == "")
            return;
        array<ref FENR_PDA_ChatMessage> messages = s_Channels.Get(channelID);
        if (!messages)
        {
            messages = new array<ref FENR_PDA_ChatMessage>();
            s_Channels.Set(channelID, messages);
        }
        messages.Insert(message);
        while (messages.Count() > FENR_PDA_Limits.DIRECT_HISTORY)
            messages.RemoveOrdered(0);
    }

    // ------------------------------------------------------------------
    // Queries
    // ------------------------------------------------------------------
    // Messages a player sees in one conversation (channels are shared).
    static array<ref FENR_PDA_ChatMessage> Conversation(string deviceKey, string conversationID)
    {
        EnsureMaps();
        if (FENR_PDA_ChannelIds.IsChannel(conversationID))
            return s_Channels.Get(conversationID);
        if (deviceKey == "")
            return null;
        FENR_PDA_DeviceHistory device = s_Direct.Get(deviceKey);
        if (!device)
            return null;
        return device.Convos.Get(conversationID);
    }

    static int LastSeq(string channelID)
    {
        EnsureMaps();
        array<ref FENR_PDA_ChatMessage> messages = s_Channels.Get(channelID);
        if (!messages)
            return 0;
        for (int i = messages.Count() - 1; i >= 0; i--)
        {
            if (messages[i] && messages[i].m_Seq < LEGACY_SEQ_BASE)
                return messages[i].m_Seq;
        }
        return 0;
    }

    // Messages after a read mark, not counting the viewer's own.
    static int CountAfter(array<ref FENR_PDA_ChatMessage> messages, int mark, string viewerID)
    {
        if (!messages)
            return 0;
        int count = 0;
        foreach (FENR_PDA_ChatMessage message : messages)
        {
            if (!message || message.m_Seq <= mark || message.m_Seq >= LEGACY_SEQ_BASE)
                continue;
            if (viewerID != "" && message.m_SenderID == viewerID)
                continue;
            count++;
        }
        return count;
    }

    // Flat payload, stride 5: sender, text, time, own (1/0), seq.
    static void Fields(array<ref FENR_PDA_ChatMessage> messages, string viewerID, string viewerName, array<string> output)
    {
        output.Clear();
        if (!messages)
            return;
        foreach (FENR_PDA_ChatMessage message : messages)
        {
            if (!message)
                continue;
            output.Insert(message.m_Name);
            output.Insert(message.m_Message);
            output.Insert(message.m_Time);
            bool own = viewerID != "" && message.m_SenderID == viewerID;
            if (message.m_SenderID == "" && viewerName != "" && message.m_Name == viewerName)
                own = true;
            if (own) output.Insert("1");
            else output.Insert("0");
            output.Insert(message.m_Seq.ToString());
        }
    }

    // ------------------------------------------------------------------
    // Maintenance
    // ------------------------------------------------------------------
    static void ClearConversation(string deviceKey, string conversationID)
    {
        EnsureMaps();
        FENR_PDA_DeviceHistory device = s_Direct.Get(deviceKey);
        if (device)
            device.Convos.Remove(conversationID);
    }

    static void DropDevice(string deviceKey)
    {
        EnsureMaps();
        s_Direct.Remove(deviceKey);
    }

    static void RenameDevice(string fromKey, string toKey)
    {
        EnsureMaps();
        if (fromKey == "" || toKey == "" || fromKey == toKey)
            return;
        FENR_PDA_DeviceHistory device = s_Direct.Get(fromKey);
        if (!device)
            return;
        s_Direct.Set(toKey, device);
        s_Direct.Remove(fromKey);
    }
};
