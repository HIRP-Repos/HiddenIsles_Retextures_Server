/*
    Fenrir Industries PDA - Field OS 7.0
    Messages: inbox (global channel + direct contacts) and the card-style
    conversation view from the reference art.
*/
class FENR_PDA_PageMessages extends FENR_PDA_UI_Page
{
    protected Widget m_InboxView;
    protected Widget m_ChatView;
    protected TextWidget m_Identity;
    protected TextWidget m_ChatTitle;
    protected TextWidget m_ChatSub;
    protected TextWidget m_StatusText;
    protected Widget m_StatusDot;

    protected ref FENR_PDA_UI_RowList m_Inbox;
    protected ref FENR_PDA_UI_ChatView m_Chat;
    protected FENR_PDA_UI_Input m_Input;
    protected FENR_PDA_UI_Button m_Send;
    protected FENR_PDA_UI_Button m_Back;

    protected ref array<string> m_RowIds;
    protected string m_ConvId = "";
    protected string m_ConvName = "";
    protected int m_ShownCount = -1;
    protected int m_ShownSeq = -1;     // last message number shown (counts stop growing at 100)

    void FENR_PDA_PageMessages(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_RowIds = new array<string>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_MSG_Root");
        if (!root) return null;

        m_InboxView = root.FindAnyWidget("FI_MSG_InboxView");
        m_ChatView = root.FindAnyWidget("FI_MSG_ChatView");
        m_Identity = Txt("FI_MSG_Subtitle");
        m_ChatTitle = Txt("FI_MSG_ChatTitle");
        m_ChatSub = Txt("FI_MSG_ChatSub");
        m_StatusText = Txt("FI_MSG_Status");
        m_StatusDot = root.FindAnyWidget("FI_MSG_Status_Dot");

        m_Inbox = new FENR_PDA_UI_RowList(m_Menu, root, "FI_MSG_Inbox");
        m_Inbox.SetSelectable(false);
        m_Inbox.SetEmptyText("No conversations yet. Add a contact first.");
        m_Chat = new FENR_PDA_UI_ChatView(m_Menu, root, "FI_MSG");
        m_Input = Field("FI_MSG_Input");
        m_Send = Btn("FI_MSG_Send");
        m_Back = Btn("FI_MSG_Back");

        ShowInbox();
        return root;
    }

    void Invalidate()
    {
        if (m_Chat) m_Chat.Invalidate();
    }

    protected void ShowInbox()
    {
        m_ConvId = "";
        m_ConvName = "";
        m_ShownCount = -1;
        m_ShownSeq = -1;
        if (m_InboxView) m_InboxView.Show(true);
        if (m_ChatView) m_ChatView.Show(false);
    }

    protected void ShowChat(string id, string name)
    {
        m_ConvId = id;
        m_ConvName = name;
        m_ShownCount = -1;
        m_ShownSeq = -1;
        if (m_InboxView) m_InboxView.Show(false);
        if (m_ChatView) m_ChatView.Show(true);
        if (m_Input) m_Input.Clear();
        if (m_Chat) m_Chat.ScrollToBottom();

        FENR_PDA_Client client = PdaClient();
        if (client)
        {
            client.MarkRead(id);
        }
        Refresh();
    }

    override void Refresh()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client) return;

        if (m_Identity)
        {
            string n = client.m_UserDisplayName;
            if (n == "") n = "CONNECTING...";
            m_Identity.SetText("IDENTITY: " + n);
        }

        RefreshInbox(client);
        if (m_ConvId != "") RefreshChat(client);
    }

    protected void RefreshInbox(FENR_PDA_Client client)
    {
        if (!m_Inbox) return;
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        m_RowIds.Clear();

        FENR_PDA_Contact globalChannel = client.FindContact(FENR_PDA_ChannelIds.GLOBAL);
        if (globalChannel)
        {
            m_RowIds.Insert(globalChannel.m_UID);
            labels.Insert("GLOBAL / OPEN NET");
            string gmeta = "OPEN CHANNEL";
            if (globalChannel.m_Unreaded > 0 && globalChannel.m_UID != m_ConvId) gmeta = globalChannel.m_Unreaded.ToString() + " NEW  |  OPEN CHANNEL";
            metas.Insert(gmeta);
        }

        foreach (FENR_PDA_Contact c : client.m_Contacts)
        {
            if (!c || FENR_PDA_Client.IsGlobalChannel(c.m_UID)) continue;
            m_RowIds.Insert(c.m_UID);
            labels.Insert(c.m_Name);
            string meta = StateOf(client, c);
            if (c.m_Unreaded > 0 && c.m_UID != m_ConvId) meta = c.m_Unreaded.ToString() + " NEW  |  " + meta;
            metas.Insert(meta);
        }
        m_Inbox.SetItems(labels, metas);
    }

    protected string StateOf(FENR_PDA_Client client, FENR_PDA_Contact c)
    {
        if (c.m_IsBanned) return "BLOCKED";
        if (client.m_OnlineContactIds.Find(c.m_UID) != -1) return "ONLINE";
        return "OFFLINE";
    }

    protected void RefreshChat(FENR_PDA_Client client)
    {
        FENR_PDA_Contact contact = client.FindContact(m_ConvId);
        bool isGlobal = FENR_PDA_Client.IsGlobalChannel(m_ConvId);

        if (m_ChatTitle)
        {
            if (isGlobal) m_ChatTitle.SetText("MESSAGES / OPEN NET");
            else m_ChatTitle.SetText("MESSAGES / DIRECT");
        }
        if (m_ChatSub)
        {
            if (isGlobal) m_ChatSub.SetText("CHANNEL:  " + m_ConvName);
            else m_ChatSub.SetText("CONVERSATION:  " + m_ConvName);
        }

        string state = "OPEN NET";
        int dot = FENR_PDA_UI_Theme.Accent();
        if (!isGlobal && contact)
        {
            state = StateOf(client, contact);
            if (state == "OFFLINE") dot = FENR_PDA_UI_Theme.TextOff();
            if (state == "BLOCKED") dot = FENR_PDA_UI_Theme.Danger();
        }
        if (m_StatusText) m_StatusText.SetText(state);
        if (m_StatusDot) m_StatusDot.SetColor(dot);

        // Reading the open conversation clears its unread counter.
        if (contact && contact.m_Unreaded > 0 && IsShown())
            client.MarkRead(contact.m_UID);

        bool canSend = !contact || !contact.m_IsBanned;
        if (m_Send) m_Send.SetEnabled(canSend);
        if (m_Input) m_Input.SetEnabled(canSend);

        array<ref FENR_PDA_ChatMessage> messages = client.GetConversation(m_ConvId);
        int count = 0;
        if (messages) count = messages.Count();
        bool loading = client.IsConversationLoading(m_ConvId);
        int shownKey = count;
        if (loading) shownKey = -2;
        int lastSeq = 0;
        if (count > 0 && messages[count - 1]) lastSeq = messages[count - 1].m_Seq;
        if (shownKey == m_ShownCount && lastSeq == m_ShownSeq) return;
        m_ShownCount = shownKey;
        m_ShownSeq = lastSeq;

        m_Chat.Clear();
        if (loading) m_Chat.SetEmptyText("Loading conversation from PDA memory...");
        else m_Chat.SetEmptyText("No messages yet. Say something.");
        for (int i = 0; i < count; i++)
        {
            FENR_PDA_ChatMessage msg = messages[i];
            if (!msg) continue;
            int style = FENR_PDA_UI_ChatView.STYLE_REMOTE;
            if (msg.m_Own) style = FENR_PDA_UI_ChatView.STYLE_OWN;
            m_Chat.Add(msg.m_Name, msg.m_Time, msg.m_Message, style);
        }

    }

    void OpenDirectContact(int contactIndex)
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || contactIndex < 0 || contactIndex >= client.m_Contacts.Count()) return;
        FENR_PDA_Contact c = client.m_Contacts[contactIndex];
        if (!c || FENR_PDA_Client.IsGlobalChannel(c.m_UID)) return;
        ShowChat(c.m_UID, c.m_Name);
    }

    protected void OpenRow(int row)
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || row < 0 || row >= m_RowIds.Count()) return;
        string id = m_RowIds[row];
        FENR_PDA_Contact c = client.FindContact(id);
        if (!c) return;
        string name = c.m_Name;
        if (FENR_PDA_Client.IsGlobalChannel(id)) name = "GLOBAL / OPEN NET";
        ShowChat(id, name);
    }

    override bool Submit()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || !m_Input || m_ConvId == "") return false;
        if (m_Send && !m_Send.IsEnabled()) return false;
        string body = m_Input.GetMessage();
        if (body == "") return false;

        FENR_PDA_Contact target = client.FindContact(m_ConvId);
        if (!target) return false;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SEND_MESSAGE, new Param3<string, string, string>(target.m_UID, target.m_Name, body), true);
        m_Input.Clear();
        if (m_Chat) m_Chat.ScrollToBottom();
        if (m_Menu) m_Menu.m_sendMessageStatus = 1;
        return true;
    }

    // Kept for callers of the old API.
    bool SendCurrentMessage() { return Submit(); }

    override void OnShown()
    {
        Refresh();
        if (m_Chat) m_Chat.Invalidate();
    }

    override void OnUpdate(float timeslice)
    {
        if (m_ConvId != "" && m_Chat) m_Chat.Update();
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_ConvId == "")
        {
            if (m_Inbox && m_Inbox.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
            {
                OpenRow(m_Inbox.GetSelected());
                return true;
            }
            return false;
        }

        if (Clicked(m_Back, w)) { ShowInbox(); Refresh(); return true; }
        if (Clicked(m_Send, w)) { Submit(); return true; }
        if (m_Chat && m_Chat.HandleClick(w) != 0) return true;
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_ConvId == "") return m_Inbox && m_Inbox.HandleWheel(x, y, wheel);
        return m_Chat && m_Chat.HandleWheel(x, y, wheel);
    }
}
