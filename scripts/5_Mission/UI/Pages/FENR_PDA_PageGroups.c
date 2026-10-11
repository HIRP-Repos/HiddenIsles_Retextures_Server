/*
    Fenrir Industries PDA - Field OS 7.0
    Groups: channel list -> channel conversation -> channel settings.
    RPC contract and callbacks are unchanged from v6.
*/
class FENR_PDA_PageGroups extends FENR_PDA_UI_Page
{
    protected static const int VIEW_LIST = 0;
    protected static const int VIEW_CHAT = 1;
    protected static const int VIEW_MANAGE = 2;

    protected Widget m_ListView;
    protected Widget m_ChatView;
    protected Widget m_ManageView;
    protected int m_View = VIEW_LIST;

    protected TextWidget m_ListInfo;
    protected TextWidget m_ChatTitle;
    protected TextWidget m_ChatInfo;
    protected TextWidget m_Owner;

    protected ref FENR_PDA_UI_RowList m_List;
    protected ref FENR_PDA_UI_RowList m_Members;
    protected ref FENR_PDA_UI_RowList m_Contacts;
    protected ref FENR_PDA_UI_ChatView m_Chat;

    protected FENR_PDA_UI_Input m_NameInput;
    protected FENR_PDA_UI_Input m_MessageInput;
    protected FENR_PDA_UI_Input m_RenameInput;

    protected FENR_PDA_UI_Button m_Create;
    protected FENR_PDA_UI_Button m_Refresh;
    protected FENR_PDA_UI_Button m_Send;
    protected FENR_PDA_UI_Button m_Back;
    protected FENR_PDA_UI_Button m_Manage;
    protected FENR_PDA_UI_Button m_ManageBack;
    protected FENR_PDA_UI_Button m_Rename;
    protected FENR_PDA_UI_Button m_Leave;
    protected FENR_PDA_UI_Button m_Delete;
    protected FENR_PDA_UI_Button m_AddMember;
    protected FENR_PDA_UI_Button m_RemoveMember;

    protected ref array<string> m_GroupIDs;
    protected ref array<string> m_GroupNames;
    protected ref array<string> m_GroupOwnerIDs;
    protected ref array<string> m_MemberIDs;
    protected ref array<string> m_ContactIDs;
    protected ref array<string> m_ContactNames;

    protected string m_CurrentGroupID = "";
    protected string m_CurrentGroupName = "";
    protected string m_CurrentOwnerID = "";
    protected string m_PendingGroupID = "";

    void FENR_PDA_PageGroups(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_GroupIDs = new array<string>();
        m_GroupNames = new array<string>();
        m_GroupOwnerIDs = new array<string>();
        m_MemberIDs = new array<string>();
        m_ContactIDs = new array<string>();
        m_ContactNames = new array<string>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_GRP_Root");
        if (!root) return null;

        m_ListView = root.FindAnyWidget("FI_GRP_ListView");
        m_ChatView = root.FindAnyWidget("FI_GRP_ChatView");
        m_ManageView = root.FindAnyWidget("FI_GRP_ManageView");

        m_ListInfo = Txt("FI_GRP_Subtitle");
        m_ChatTitle = Txt("FI_GRP_ChatTitle");
        m_ChatInfo = Txt("FI_GRP_ChatSub");
        m_Owner = Txt("FI_GRP_Owner");

        m_List = new FENR_PDA_UI_RowList(m_Menu, root, "FI_GRP_List");
        m_List.SetSelectable(false);
        m_List.SetEmptyText("No private channels. Create one below.");
        m_Members = new FENR_PDA_UI_RowList(m_Menu, root, "FI_GRP_Members");
        m_Members.SetEmptyText("No members loaded.");
        m_Contacts = new FENR_PDA_UI_RowList(m_Menu, root, "FI_GRP_Contacts");
        m_Contacts.SetEmptyText("No directory contacts.");
        m_Chat = new FENR_PDA_UI_ChatView(m_Menu, root, "FI_GRP");
        m_Chat.SetEmptyText("No messages in this private channel.");

        m_NameInput = Field("FI_GRP_NameInput");
        m_MessageInput = Field("FI_GRP_MessageInput");
        m_RenameInput = Field("FI_GRP_RenameInput");

        m_Create = Btn("FI_GRP_Create");
        m_Refresh = Btn("FI_GRP_Refresh");
        m_Send = Btn("FI_GRP_Send");
        m_Back = Btn("FI_GRP_Back");
        m_Manage = Btn("FI_GRP_Manage");
        m_ManageBack = Btn("FI_GRP_ManageBack");
        m_Rename = Btn("FI_GRP_Rename");
        m_Leave = Btn("FI_GRP_Leave");
        m_Delete = Btn("FI_GRP_Delete");
        m_AddMember = Btn("FI_GRP_AddMember");
        m_RemoveMember = Btn("FI_GRP_RemoveMember");

        SetView(VIEW_LIST);
        UpdateButtons();
        return root;
    }

    void Invalidate()
    {
        if (m_Chat) m_Chat.Invalidate();
    }

    override void OnShown()
    {
        FillContacts();
        RequestList();
        if (m_View == VIEW_MANAGE) SetView(VIEW_CHAT);
        if (m_Chat) m_Chat.Invalidate();
    }

    override void OnUpdate(float timeslice)
    {
        if (m_View == VIEW_CHAT && m_Chat) m_Chat.Update();
    }

    protected void SetView(int view)
    {
        if (view != VIEW_LIST && m_CurrentGroupID == "") view = VIEW_LIST;
        m_View = view;
        if (m_ListView) m_ListView.Show(view == VIEW_LIST);
        if (m_ChatView) m_ChatView.Show(view == VIEW_CHAT);
        if (m_ManageView) m_ManageView.Show(view == VIEW_MANAGE);
        if (view == VIEW_CHAT && m_Chat) m_Chat.Invalidate();
    }

    protected void SetInfo(string text)
    {
        if (m_ListInfo) m_ListInfo.SetText(text);
        if (m_ChatInfo) m_ChatInfo.SetText(text);
    }

    // ------------------------------------------------------------------
    protected bool IsLocalIdentity(string storedID)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.GetIdentity() || storedID == "") return false;
        PlayerIdentity identity = player.GetIdentity();
        return storedID == identity.GetPlainId() || storedID == identity.GetId();
    }

    protected bool IsOwner()
    {
        return IsLocalIdentity(m_CurrentOwnerID);
    }

    protected string LocalName()
    {
        FENR_PDA_Client client = PdaClient();
        if (client && client.m_UserDisplayName != "") return client.m_UserDisplayName;
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) return player.GetIdentity().GetName();
        return "";
    }

    protected int StyleFor(string senderName)
    {
        if (senderName == "SYSTEM") return FENR_PDA_UI_ChatView.STYLE_SYSTEM;
        string me = LocalName();
        if (me != "" && senderName == me) return FENR_PDA_UI_ChatView.STYLE_OWN;
        return FENR_PDA_UI_ChatView.STYLE_REMOTE;
    }

    protected string DisplaySender(string senderName)
    {
        if (senderName == "SYSTEM") return "SYSTEM EVENT";
        return senderName;
    }

    protected void FillContacts()
    {
        m_ContactIDs.Clear();
        m_ContactNames.Clear();
        FENR_PDA_Client client = PdaClient();
        if (client)
        {
            foreach (FENR_PDA_Contact c : client.m_Contacts)
            {
                if (!c || FENR_PDA_Client.IsGlobalChannel(c.m_UID)) continue;
                m_ContactIDs.Insert(c.m_UID);
                m_ContactNames.Insert(c.m_Name);
            }
        }
        if (m_Contacts)
        {
            m_Contacts.SetItems(m_ContactNames, null);
            m_Contacts.Select(-1);
        }
    }

    void RequestList()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_LIST, new Param1<bool>(true), true);
    }

    protected void SelectGroup(int row, bool openChat)
    {
        if (row < 0 || row >= m_GroupIDs.Count())
        {
            m_CurrentGroupID = "";
            m_CurrentGroupName = "";
            m_CurrentOwnerID = "";
            if (m_Chat) m_Chat.Clear();
            if (m_Members) m_Members.Clear();
            SetView(VIEW_LIST);
            UpdateButtons();
            return;
        }

        bool changed = m_GroupIDs[row] != m_CurrentGroupID;
        m_CurrentGroupID = m_GroupIDs[row];
        m_CurrentGroupName = m_GroupNames[row];
        m_CurrentOwnerID = m_GroupOwnerIDs[row];
        if (m_ChatTitle) m_ChatTitle.SetText("GROUPS / " + m_CurrentGroupName);
        if (m_RenameInput && changed) m_RenameInput.SetText(m_CurrentGroupName);

        if (changed && m_Chat)
        {
            m_Chat.Clear();
            m_Chat.SetEmptyText("Loading secure channel...");
            m_Chat.ScrollToBottom();
        }
        if (changed && m_Members) m_Members.Clear();
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_HISTORY, new Param1<string>(m_CurrentGroupID), true);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_MEMBERS, new Param1<string>(m_CurrentGroupID), true);
        if (openChat) SetView(VIEW_CHAT);
        UpdateButtons();
    }

    protected void UpdateButtons()
    {
        bool hasGroup = m_CurrentGroupID != "";
        bool owner = IsOwner();
        if (m_Manage) m_Manage.SetEnabled(hasGroup);
        if (m_Send) m_Send.SetEnabled(hasGroup);
        if (m_MessageInput) m_MessageInput.SetEnabled(hasGroup);
        if (m_Rename) m_Rename.SetEnabled(hasGroup && owner);
        if (m_RenameInput) m_RenameInput.SetEnabled(hasGroup && owner);
        if (m_Delete) m_Delete.SetEnabled(hasGroup && owner);
        if (m_AddMember) m_AddMember.SetEnabled(hasGroup && owner);
        if (m_RemoveMember) m_RemoveMember.SetEnabled(hasGroup && owner);
        if (m_Leave) m_Leave.SetEnabled(hasGroup && !owner);
        if (m_Owner)
        {
            if (!hasGroup) m_Owner.SetText("OWNER: --");
            else if (owner) m_Owner.SetText("OWNER: YOU  |  " + m_CurrentGroupName);
            else m_Owner.SetText("OWNER: REMOTE MEMBER  |  " + m_CurrentGroupName);
        }
    }

    override bool Submit()
    {
        if (m_View != VIEW_CHAT) return false;
        return SendGroupMessage();
    }

    bool SendGroupMessage()
    {
        if (m_CurrentGroupID == "" || !m_MessageInput) return false;
        string body = m_MessageInput.GetMessage();
        if (body == "") return false;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_SEND, new Param2<string, string>(m_CurrentGroupID, body), true);
        m_MessageInput.Clear();
        if (m_Chat) m_Chat.ScrollToBottom();
        return true;
    }

    // ------------------------------------------------------------------
    // RPC callbacks (via FENR_PDA_Menu)
    // ------------------------------------------------------------------
    void ReceiveList(array<string> ids, array<string> names, array<string> ownerIDs, array<string> unread)
    {
        string wantedID = m_PendingGroupID;
        if (wantedID == "") wantedID = m_CurrentGroupID;
        m_GroupIDs.Clear();
        m_GroupNames.Clear();
        m_GroupOwnerIDs.Clear();

        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        int selectRow = -1;
        for (int i = 0; i < ids.Count(); i++)
        {
            m_GroupIDs.Insert(ids[i]);
            m_GroupNames.Insert(names[i]);
            m_GroupOwnerIDs.Insert(ownerIDs[i]);
            labels.Insert(names[i]);
            string role = "MEMBER";
            if (IsLocalIdentity(ownerIDs[i])) role = "OWNER";
            int newCount = 0;
            if (unread && i < unread.Count()) newCount = unread[i].ToInt();
            if (newCount > 0 && ids[i] != m_CurrentGroupID) metas.Insert(newCount.ToString() + " NEW  |  " + role);
            else metas.Insert(role);
            if (ids[i] == wantedID) selectRow = i;
        }
        if (m_List) m_List.SetItems(labels, metas);
        m_PendingGroupID = "";

        if (selectRow >= 0)
        {
            SelectGroup(selectRow, false);
        }
        else
        {
            SelectGroup(-1, false);
            if (ids.Count() == 0) SetInfo("No private channels. Create one below.");
            else SetInfo(ids.Count().ToString() + " PRIVATE CHANNEL(S)  |  SELECT ONE TO OPEN");
        }
    }

    void ReceiveMembers(string groupID, array<string> ids, array<string> rows, string ownerID)
    {
        if (groupID != m_CurrentGroupID) return;
        m_CurrentOwnerID = ownerID;
        m_MemberIDs.Clear();
        array<string> labels = new array<string>();
        for (int i = 0; i < rows.Count(); i++)
        {
            m_MemberIDs.Insert(ids[i]);
            labels.Insert(rows[i]);
        }
        if (m_Members)
        {
            m_Members.SetItems(labels, null);
            m_Members.Select(-1);
        }
        UpdateButtons();
    }

    void ReceiveHistory(string groupID, array<string> senderNames, array<string> bodies, array<string> times)
    {
        if (groupID != m_CurrentGroupID || !m_Chat) return;
        m_Chat.Clear();
        m_Chat.SetEmptyText("No messages in this private channel.");
        for (int i = 0; i < bodies.Count(); i++)
        {
            string sender = "";
            if (i < senderNames.Count()) sender = senderNames[i];
            string clock = "";
            if (times && i < times.Count()) clock = times[i];
            m_Chat.Add(DisplaySender(sender), clock, bodies[i], StyleFor(sender));
        }
        m_Chat.ScrollToBottom();
        SetInfo("Secure channel loaded. Only listed members can access this history.");
    }

    void ReceiveIncoming(string groupID, string groupName, string senderName, string messageText)
    {
        if (groupID == m_CurrentGroupID && m_Chat)
        {
            m_Chat.SetEmptyText("No messages in this private channel.");
            m_Chat.Add(DisplaySender(senderName), FENR_PDA_UI_Kit.GameTime(), messageText, StyleFor(senderName));
            // Seen live: keep this PDA's read mark current.
            FENR_PDA_Client client = PdaClient();
            if (client && IsShown()) client.MarkGroupRead(groupID);
        }
        else
        {
            SetInfo("New message in " + groupName + " from " + senderName + ".");
        }
    }

    void ReceiveRefresh(string groupID)
    {
        if (groupID != "" && groupID == m_CurrentGroupID) m_PendingGroupID = groupID;
        RequestList();
    }

    void ReceiveActionResult(string action, bool success, string info, string groupID)
    {
        SetInfo(info);
        if (!success) return;
        if (groupID != "") m_PendingGroupID = groupID;
        if (action == "DELETE" || action == "LEAVE")
        {
            m_CurrentGroupID = "";
            m_CurrentOwnerID = "";
            m_PendingGroupID = "";
            SetView(VIEW_LIST);
        }
        if (action == "CREATE" && m_NameInput) m_NameInput.Clear();
        if (action == "SEND") return;
        RequestList();
    }

    // ------------------------------------------------------------------
    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_View == VIEW_LIST)
        {
            if (m_List && m_List.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
            {
                SelectGroup(m_List.GetSelected(), true);
                return true;
            }
            if (Clicked(m_Refresh, w)) { FillContacts(); RequestList(); return true; }
            if (Clicked(m_Create, w))
            {
                string groupName = m_NameInput.GetMessage();
                if (groupName != "")
                    GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_CREATE, new Param1<string>(groupName), true);
                return true;
            }
            return false;
        }

        if (m_View == VIEW_CHAT)
        {
            if (Clicked(m_Back, w)) { SetView(VIEW_LIST); return true; }
            if (Clicked(m_Manage, w)) { FillContacts(); SetView(VIEW_MANAGE); return true; }
            if (Clicked(m_Send, w)) { SendGroupMessage(); return true; }
            if (m_Chat && m_Chat.HandleClick(w) != 0) return true;
            return false;
        }

        // VIEW_MANAGE
        if (Clicked(m_ManageBack, w)) { SetView(VIEW_CHAT); return true; }
        if (m_Members && m_Members.HandleClick(w) != FENR_PDA_UI_RowList.RESULT_NONE) return true;
        if (m_Contacts && m_Contacts.HandleClick(w) != FENR_PDA_UI_RowList.RESULT_NONE) return true;
        if (m_CurrentGroupID == "") return false;

        if (Clicked(m_Rename, w))
        {
            string newName = m_RenameInput.GetMessage();
            if (newName != "")
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_RENAME, new Param2<string, string>(m_CurrentGroupID, newName), true);
            return true;
        }
        if (Clicked(m_Leave, w))
        {
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_LEAVE, new Param1<string>(m_CurrentGroupID), true);
            return true;
        }
        if (Clicked(m_Delete, w))
        {
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_DELETE, new Param1<string>(m_CurrentGroupID), true);
            return true;
        }
        if (Clicked(m_AddMember, w))
        {
            int row = m_Contacts.GetSelected();
            if (row >= 0 && row < m_ContactIDs.Count())
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_ADD_MEMBER, new Param3<string, string, string>(m_CurrentGroupID, m_ContactIDs[row], m_ContactNames[row]), true);
            return true;
        }
        if (Clicked(m_RemoveMember, w))
        {
            int memberRow = m_Members.GetSelected();
            if (memberRow >= 0 && memberRow < m_MemberIDs.Count())
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.GROUP_REMOVE_MEMBER, new Param2<string, string>(m_CurrentGroupID, m_MemberIDs[memberRow]), true);
            return true;
        }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_View == VIEW_LIST) return m_List && m_List.HandleWheel(x, y, wheel);
        if (m_View == VIEW_CHAT) return m_Chat && m_Chat.HandleWheel(x, y, wheel);
        if (m_Members && m_Members.HandleWheel(x, y, wheel)) return true;
        return m_Contacts && m_Contacts.HandleWheel(x, y, wheel);
    }
}
