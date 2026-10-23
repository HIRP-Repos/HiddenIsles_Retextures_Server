/*
    Fenrir Industries PDA - Field OS 7.0
    Announcements: bulletin list + reader.
*/
class FENR_PDA_PageAnnouncements extends FENR_PDA_UI_Page
{
    protected ref FENR_PDA_UI_RowList m_List;
    protected TextWidget m_Count;
    protected TextWidget m_Source;
    protected TextWidget m_Meta;
    protected MultilineTextWidget m_Body;
    protected ref array<ref FENR_PDA_ChatMessage> m_Messages;
    protected int m_LastCount = -1;
    protected int m_LastSeq = -1;

    void FENR_PDA_PageAnnouncements(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Messages = new array<ref FENR_PDA_ChatMessage>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_ANN_Root");
        if (!root) return null;
        m_List = new FENR_PDA_UI_RowList(m_Menu, root, "FI_ANN_List");
        m_List.SetEmptyText("No bulletins received.");
        m_Count = Txt("FI_ANN_Count");
        m_Source = Txt("FI_ANN_Source");
        m_Meta = Txt("FI_ANN_Meta");
        m_Body = MultilineTextWidget.Cast(root.FindAnyWidget("FI_ANN_Body"));
        return root;
    }

    protected string SourceOf(FENR_PDA_ChatMessage msg)
    {
        string source = msg.m_Name;
        if (source == "Broadcast" || source == "") source = "NETWORK";
        return source;
    }

    override void Refresh()
    {
        if (!m_List) return;
        FENR_PDA_Client client = PdaClient();
        if (!client) return;

        array<ref FENR_PDA_ChatMessage> msgs = client.GetConversation(FENR_PDA_ChannelIds.ANNOUNCEMENTS);
        // Bulletins on screen count as read on this PDA.
        if (IsShown()) client.MarkRead(FENR_PDA_ChannelIds.ANNOUNCEMENTS);
        int previousSelection = m_List.GetSelected();
        int newestSeq = 0;
        if (msgs && msgs.Count() > 0 && msgs[msgs.Count() - 1]) newestSeq = msgs[msgs.Count() - 1].m_Seq;
        bool grew = msgs && (msgs.Count() != m_LastCount || newestSeq != m_LastSeq);
        m_LastSeq = newestSeq;

        // Newest first.
        m_Messages.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        if (msgs)
        {
            for (int i = msgs.Count() - 1; i >= 0; i--)
            {
                FENR_PDA_ChatMessage msg = msgs[i];
                if (!msg) continue;
                m_Messages.Insert(msg);
                labels.Insert(FENR_PDA_UI_Kit.Clip(msg.m_Message, 18));
                metas.Insert(msg.m_Time);
            }
            m_LastCount = msgs.Count();
        }
        m_List.SetItems(labels, metas);

        if (m_Count)
        {
            if (m_Messages.Count() == 1) m_Count.SetText("1 BULLETIN RECEIVED");
            else m_Count.SetText(m_Messages.Count().ToString() + " BULLETINS RECEIVED");
        }

        if (m_Messages.Count() == 0)
        {
            if (m_Source) m_Source.SetText("NO BULLETINS RECEIVED");
            if (m_Meta) m_Meta.SetText("NETWORK ARCHIVE EMPTY");
            if (m_Body) m_Body.SetText("This terminal has not received any official network bulletins.");
            return;
        }

        if (grew || previousSelection < 0) m_List.Select(0);
        else m_List.Select(previousSelection);
        UpdateDetail();
    }

    void UpdateDetail()
    {
        int row = m_List.GetSelected();
        if (row < 0 || row >= m_Messages.Count()) return;
        FENR_PDA_ChatMessage msg = m_Messages[row];
        if (!msg) return;
        if (m_Source) m_Source.SetText("SOURCE / " + SourceOf(msg));
        string meta = "OFFICIAL SECURE FIELD NETWORK BULLETIN";
        if (msg.m_Time != "") meta = "RECEIVED " + msg.m_Time + "  |  " + meta;
        if (m_Meta) m_Meta.SetText(meta);
        if (m_Body) m_Body.SetText(msg.m_Message);
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        int result = m_List.HandleClick(w);
        if (result == FENR_PDA_UI_RowList.RESULT_SELECT) { UpdateDetail(); return true; }
        return result != FENR_PDA_UI_RowList.RESULT_NONE;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        return m_List && m_List.HandleWheel(x, y, wheel);
    }
}
