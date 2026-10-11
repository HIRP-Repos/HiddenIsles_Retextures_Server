/*
    Fenrir Industries PDA - Field OS 7.0
    Contacts: directory list + contact record.
*/
class FENR_PDA_PageContacts extends FENR_PDA_UI_Page
{
    protected ref FENR_PDA_UI_RowList m_List;
    protected TextWidget m_CountText;
    protected TextWidget m_Name;
    protected TextWidget m_StatusText;
    protected Widget m_StatusDot;
    protected TextWidget m_ID;
    protected TextWidget m_Info;
    protected FENR_PDA_UI_Input m_AddInput;
    protected FENR_PDA_UI_Input m_RenameInput;
    protected FENR_PDA_UI_Button m_Add;
    protected FENR_PDA_UI_Button m_Message;
    protected FENR_PDA_UI_Button m_Block;
    protected FENR_PDA_UI_Button m_Rename;
    protected FENR_PDA_UI_Button m_Remove;
    protected FENR_PDA_UI_Button m_RateUp;
    protected FENR_PDA_UI_Button m_RateDown;
    protected TextWidget m_Relation;
    protected int m_MyVote;
    protected bool m_CanRate;
    protected ref array<int> m_Indices;
    protected string m_SelectedID = "";

    void FENR_PDA_PageContacts(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Indices = new array<int>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_CON_Root");
        if (!root) return null;
        m_List = new FENR_PDA_UI_RowList(m_Menu, root, "FI_CON_List");
        m_List.SetEmptyText("Directory empty. Add a player below.");
        m_CountText = Txt("FI_CON_Count");
        m_Name = Txt("FI_CON_Name");
        m_StatusText = Txt("FI_CON_Status");
        m_StatusDot = root.FindAnyWidget("FI_CON_Status_Dot");
        m_ID = Txt("FI_CON_ID");
        m_Info = Txt("FI_CON_Info");
        m_AddInput = Field("FI_CON_AddInput");
        m_RenameInput = Field("FI_CON_RenameInput");
        m_Add = Btn("FI_CON_Add");
        m_Message = Btn("FI_CON_Message");
        m_Block = Btn("FI_CON_Block");
        m_Rename = Btn("FI_CON_Rename");
        m_Remove = Btn("FI_CON_Remove");
        m_RateUp = Btn("FI_CON_RateUp");
        m_RateDown = Btn("FI_CON_RateDown");
        m_Relation = Txt("FI_CON_Relation");
        SetActions(false);
        return root;
    }

    protected void SetActions(bool state)
    {
        if (m_Message) m_Message.SetEnabled(state);
        if (m_Block) m_Block.SetEnabled(state);
        if (m_Rename) m_Rename.SetEnabled(state);
        if (m_Remove) m_Remove.SetEnabled(state);
        if (m_RenameInput) m_RenameInput.SetEnabled(state);
        UpdateRateButtons(state);
    }

    protected void UpdateRateButtons(bool hasContact)
    {
        bool enabled = hasContact && m_CanRate;
        if (m_RateUp)
        {
            m_RateUp.SetEnabled(enabled);
            m_RateUp.SetActive(enabled && m_MyVote > 0);
        }
        if (m_RateDown)
        {
            m_RateDown.SetEnabled(enabled);
            m_RateDown.SetActive(enabled && m_MyVote < 0);
        }
    }

    void ReceiveRep(string targetID, int score, int count, int myVote, bool canRate)
    {
        if (targetID == "" || targetID != m_SelectedID) return;
        m_MyVote = myVote;
        m_CanRate = canRate;
        if (m_Relation)
        {
            if (count <= 0) m_Relation.SetText("REPUTATION: NO RATINGS YET");
            else
            {
                string sign = "";
                if (score > 0) sign = "+";
                m_Relation.SetText("REPUTATION: " + sign + score.ToString() + " (" + count.ToString() + " RATINGS)");
            }
        }
        UpdateRateButtons(true);
        if (!canRate && m_Info) m_Info.SetText("Trade with this player through a listing to rate them.");
    }

    void ReceiveRateResult(bool success, string info)
    {
        if (!m_Info) return;
        m_Info.SetText(info);
    }

    int SelectedContactIndex()
    {
        if (!m_List) return -1;
        int row = m_List.GetSelected();
        if (row < 0 || row >= m_Indices.Count()) return -1;
        return m_Indices[row];
    }

    protected string StateOf(FENR_PDA_Client client, FENR_PDA_Contact c)
    {
        if (c.m_IsBanned) return "BLOCKED";
        if (client.m_OnlineContactIds.Find(c.m_UID) != -1) return "ONLINE";
        return "OFFLINE";
    }

    override void Refresh()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || !m_List) return;

        m_Indices.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        int selectRow = -1;
        int online = 0;
        for (int i = 0; i < client.m_Contacts.Count(); i++)
        {
            FENR_PDA_Contact c = client.m_Contacts[i];
            if (!c || FENR_PDA_Client.IsGlobalChannel(c.m_UID)) continue;
            string state = StateOf(client, c);
            if (state == "ONLINE") online++;
            if (c.m_UID == m_SelectedID) selectRow = labels.Count();
            labels.Insert(c.m_Name);
            metas.Insert(state);
            m_Indices.Insert(i);
        }
        m_List.SetItems(labels, metas);
        m_List.Select(selectRow);
        if (selectRow < 0) m_SelectedID = "";

        if (m_CountText)
            m_CountText.SetText(labels.Count().ToString() + " KNOWN  |  " + online.ToString() + " ONLINE");
        UpdateDetail();
    }

    void UpdateDetail()
    {
        FENR_PDA_Client client = PdaClient();
        int idx = SelectedContactIndex();
        if (!client || idx < 0 || idx >= client.m_Contacts.Count())
        {
            m_SelectedID = "";
            if (m_Name) m_Name.SetText("NO CONTACT SELECTED");
            if (m_StatusText) m_StatusText.SetText("--");
            if (m_StatusDot) m_StatusDot.SetColor(FENR_PDA_UI_Theme.TextOff());
            if (m_ID) m_ID.SetText("PLAYER ID: --");
            if (m_Info) m_Info.SetText("Select a contact from the directory.");
            if (m_RenameInput) m_RenameInput.Clear();
            if (m_Relation) m_Relation.SetText("REPUTATION: --");
            m_CanRate = false;
            SetActions(false);
            return;
        }

        FENR_PDA_Contact c = client.m_Contacts[idx];
        string state = StateOf(client, c);
        int dot = FENR_PDA_UI_Theme.Accent();
        if (state == "OFFLINE") dot = FENR_PDA_UI_Theme.TextOff();
        if (state == "BLOCKED") dot = FENR_PDA_UI_Theme.Danger();

        bool changed = c.m_UID != m_SelectedID;
        m_SelectedID = c.m_UID;
        if (changed)
        {
            m_MyVote = 0;
            m_CanRate = false;
            if (m_Relation) m_Relation.SetText("REPUTATION: CHECKING...");
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_GET, new Param1<string>(c.m_UID), true);
        }
        if (m_Name) m_Name.SetText(c.m_Name);
        if (m_StatusText) m_StatusText.SetText(state);
        if (m_StatusDot) m_StatusDot.SetColor(dot);
        if (m_ID) m_ID.SetText("PLAYER ID: " + c.m_UID);
        if (m_Info)
        {
            if (c.m_Unreaded > 0) m_Info.SetText(c.m_Unreaded.ToString() + " UNREAD MESSAGE(S)");
            else m_Info.SetText("Secure direct channel available.");
        }
        if (m_RenameInput && changed) m_RenameInput.SetText(c.m_Name);
        if (m_Block)
        {
            if (c.m_IsBanned) m_Block.SetText("UNBLOCK");
            else m_Block.SetText("BLOCK");
        }
        SetActions(true);
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        int result = m_List.HandleClick(w);
        if (result == FENR_PDA_UI_RowList.RESULT_SELECT) { UpdateDetail(); return true; }
        if (result != FENR_PDA_UI_RowList.RESULT_NONE) return true;

        if (Clicked(m_Add, w))
        {
            string q = m_AddInput.GetMessage();
            if (q != "")
            {
                GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADD_CONTACT, new Param1<string>(q), true);
                m_AddInput.Clear();
            }
            return true;
        }

        FENR_PDA_Client client = PdaClient();
        if (!client) return false;
        int idx = SelectedContactIndex();
        if (idx < 0 || idx >= client.m_Contacts.Count()) return false;
        FENR_PDA_Contact c = client.m_Contacts[idx];
        if (!c) return false;

        if (Clicked(m_Message, w))
        {
            if (m_Menu) m_Menu.OpenConversation(idx);
            return true;
        }
        if (Clicked(m_Block, w))
        {
            client.ToggleBlocked(c.m_UID);
            Refresh();
            return true;
        }
        if (Clicked(m_Remove, w))
        {
            client.RemoveContact(c.m_UID);
            m_SelectedID = "";
            Refresh();
            return true;
        }
        if (Clicked(m_RateUp, w))
        {
            int upValue = 1;
            if (m_MyVote > 0) upValue = 0;
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_VOTE, new Param2<string, int>(c.m_UID, upValue), true);
            return true;
        }
        if (Clicked(m_RateDown, w))
        {
            int downValue = -1;
            if (m_MyVote < 0) downValue = 0;
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_VOTE, new Param2<string, int>(c.m_UID, downValue), true);
            return true;
        }
        if (Clicked(m_Rename, w))
        {
            string newName = m_RenameInput.GetMessage();
            if (newName != "") client.RenameContact(c.m_UID, newName);
            Refresh();
            return true;
        }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        return m_List && m_List.HandleWheel(x, y, wheel);
    }
}
