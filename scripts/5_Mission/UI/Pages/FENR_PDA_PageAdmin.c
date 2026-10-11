/*
    Fenrir Industries PDA - Field OS 8.1
    Admin: read-only message archive, online players, network broadcasts and
    custom intel files.

    Edit boxes are single-line and scroll while typing, so the broadcast and
    intel tabs show the whole text wrapped in a large preview above them.

    Uses the existing VPP-gated RPCs (AdminStatus, AdminSearchMessages,
    AdminListPlayers, AdminBroadcast).  The server re-checks authorization on
    every request; hiding the nav item is only cosmetic.
*/
class FENR_PDA_PageAdmin extends FENR_PDA_UI_Page
{
    protected static const int TAB_ARCHIVE = 0;
    protected static const int TAB_PLAYERS = 1;
    protected static const int TAB_BROADCAST = 2;
    protected static const int TAB_INTEL = 3;
    protected static const int INTEL_TITLE_MAX = 48;
    protected static const int INTEL_BODY_MAX = 1000;

    protected Widget m_ArchiveView;
    protected Widget m_PlayersView;
    protected Widget m_BroadcastView;
    protected Widget m_IntelView;
    protected TextWidget m_Subtitle;
    protected int m_Tab = TAB_ARCHIVE;

    protected FENR_PDA_UI_Button m_TabArchive;
    protected FENR_PDA_UI_Button m_TabPlayers;
    protected FENR_PDA_UI_Button m_TabBroadcast;
    protected FENR_PDA_UI_Button m_TabIntel;

    // Archive
    protected FENR_PDA_UI_Input m_Query;
    protected FENR_PDA_UI_Button m_TypeButton;
    protected FENR_PDA_UI_Button m_Search;
    protected FENR_PDA_UI_Button m_Clear;
    protected FENR_PDA_UI_Button m_Prev;
    protected FENR_PDA_UI_Button m_Next;
    protected TextWidget m_PageInfo;
    protected ref FENR_PDA_UI_ChatView m_Results;
    protected ref array<string> m_Types;
    protected int m_TypeIndex;
    protected int m_Page;
    protected int m_TotalPages;
    protected string m_SearchQuery = "";
    protected string m_SearchType = "ALL";
    protected bool m_HasSearched;

    // Players
    protected ref FENR_PDA_UI_RowList m_Players;
    protected TextWidget m_PlayerCount;
    protected TextWidget m_PlayerName;
    protected TextWidget m_PlayerID;
    protected TextWidget m_PlayerState;
    protected FENR_PDA_UI_Button m_PlayerMessage;
    protected FENR_PDA_UI_Button m_PlayerAdd;
    protected FENR_PDA_UI_Button m_PlayerLogs;
    protected FENR_PDA_UI_Button m_PlayersRefresh;
    protected ref array<string> m_PlayerIds;
    protected ref array<string> m_PlayerNames;
    protected ref array<string> m_PlayerStates;
    protected string m_SelectedPlayerID = "";
    protected string m_PendingOpenID = "";
    protected string m_PendingOpenName = "";
    protected float m_PendingOpenTimer;

    // Broadcast
    protected FENR_PDA_UI_Input m_BcInput;
    protected FENR_PDA_UI_Button m_BcSend;
    protected TextWidget m_BcStatus;
    protected TextWidget m_BcCount;
    protected bool m_BcArmed;
    protected float m_BcArmTimer;
    protected bool m_BcSending;
    protected MultilineTextWidget m_BcPreview;
    protected string m_BcShown = "-";

    // Intel
    protected FENR_PDA_UI_Input m_IntelTitle;
    protected FENR_PDA_UI_Input m_IntelBody;
    protected FENR_PDA_UI_Button m_IntelWrite;
    protected TextWidget m_IntelStatus;
    protected TextWidget m_IntelCount;
    protected MultilineTextWidget m_IntelPreview;
    protected string m_IntelShown = "-";
    protected bool m_IntelSending;

    protected bool m_IsAdmin;
    protected bool m_StatusKnown;
    protected string m_Retention = "";

    void FENR_PDA_PageAdmin(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Types = new array<string>();
        m_Types.Insert("ALL");
        m_Types.Insert(FENR_PDA_MessageType.DIRECT);
        m_Types.Insert(FENR_PDA_MessageType.GROUP);
        m_Types.Insert(FENR_PDA_MessageType.CHANNEL);
        m_Types.Insert(FENR_PDA_MessageType.BROADCAST);
        m_PlayerIds = new array<string>();
        m_PlayerNames = new array<string>();
        m_PlayerStates = new array<string>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_ADM_Root");
        if (!root) return null;

        m_ArchiveView = root.FindAnyWidget("FI_ADM_ArchiveView");
        m_PlayersView = root.FindAnyWidget("FI_ADM_PlayersView");
        m_BroadcastView = root.FindAnyWidget("FI_ADM_BroadcastView");
        m_IntelView = root.FindAnyWidget("FI_ADM_IntelView");
        m_Subtitle = Txt("FI_ADM_Subtitle");

        m_TabArchive = Btn("FI_ADM_TabArchive");
        m_TabPlayers = Btn("FI_ADM_TabPlayers");
        m_TabBroadcast = Btn("FI_ADM_TabBroadcast");
        m_TabIntel = Btn("FI_ADM_TabIntel");

        m_Query = Field("FI_ADM_Query");
        m_TypeButton = Btn("FI_ADM_Type");
        m_Search = Btn("FI_ADM_Search");
        m_Clear = Btn("FI_ADM_Clear");
        m_Prev = Btn("FI_ADM_Prev");
        m_Next = Btn("FI_ADM_Next");
        m_PageInfo = Txt("FI_ADM_PageInfo");
        m_Results = new FENR_PDA_UI_ChatView(m_Menu, root, "FI_ADM");
        m_Results.SetTopAnchored(true);
        m_Results.SetReferenceHeight(252.0);   // archive card area is 252 px tall at reference size
        m_Results.SetEmptyText("Run a search to browse the message archive.");

        m_Players = new FENR_PDA_UI_RowList(m_Menu, root, "FI_ADM_Players");
        m_Players.SetEmptyText("No player list loaded.");
        m_PlayerCount = Txt("FI_ADM_PlayerCount");
        m_PlayerName = Txt("FI_ADM_PlayerName");
        m_PlayerID = Txt("FI_ADM_PlayerID");
        m_PlayerState = Txt("FI_ADM_PlayerState");
        m_PlayerMessage = Btn("FI_ADM_PlayerMessage");
        m_PlayerAdd = Btn("FI_ADM_PlayerAdd");
        m_PlayerLogs = Btn("FI_ADM_PlayerLogs");
        m_PlayersRefresh = Btn("FI_ADM_PlayersRefresh");

        m_BcInput = Field("FI_ADM_BcInput");
        m_BcSend = Btn("FI_ADM_BcSend");
        m_BcStatus = Txt("FI_ADM_BcStatus");
        m_BcCount = Txt("FI_ADM_BcCount");
        m_BcPreview = MultilineTextWidget.Cast(root.FindAnyWidget("FI_ADM_BcPreview"));

        m_IntelTitle = Field("FI_ADM_IntelTitle");
        m_IntelBody = Field("FI_ADM_IntelBody");
        m_IntelWrite = Btn("FI_ADM_IntelWrite");
        m_IntelStatus = Txt("FI_ADM_IntelStatus");
        m_IntelCount = Txt("FI_ADM_IntelCount");
        m_IntelPreview = MultilineTextWidget.Cast(root.FindAnyWidget("FI_ADM_IntelPreview"));

        UpdateTypeButton();
        UpdatePager();
        UpdatePlayerDetail();
        SetTab(TAB_ARCHIVE);
        return root;
    }

    void Invalidate()
    {
        if (m_Results) m_Results.Invalidate();
    }

    bool IsAdmin() { return m_IsAdmin; }

    void RequestStatus()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_STATUS, new Param1<bool>(true), true);
    }

    void SetAuthorized(bool isAdmin, string retention)
    {
        m_IsAdmin = isAdmin;
        m_StatusKnown = true;
        m_Retention = retention;
        if (!m_Subtitle) return;
        if (isAdmin)
        {
            string text = "AUTHORIZED";
            if (retention != "") text += "  |  " + retention;
            m_Subtitle.SetText(text);
            m_Subtitle.SetColor(FENR_PDA_UI_Theme.Text());
        }
        else
        {
            m_Subtitle.SetText("ACCESS DENIED  |  VPP ADMIN PERMISSION REQUIRED");
            m_Subtitle.SetColor(FENR_PDA_UI_Theme.Danger());
        }
    }

    override void OnShown()
    {
        if (!m_StatusKnown) RequestStatus();
        if (m_Tab == TAB_ARCHIVE && !m_HasSearched) RunSearch(0);
        if (m_Tab == TAB_PLAYERS) RequestPlayers();
        if (m_Results) m_Results.Invalidate();
    }

    override void OnHidden()
    {
        Disarm();
    }

    protected void SetTab(int tab)
    {
        m_Tab = tab;
        if (m_ArchiveView) m_ArchiveView.Show(tab == TAB_ARCHIVE);
        if (m_PlayersView) m_PlayersView.Show(tab == TAB_PLAYERS);
        if (m_BroadcastView) m_BroadcastView.Show(tab == TAB_BROADCAST);
        if (m_IntelView) m_IntelView.Show(tab == TAB_INTEL);
        if (m_TabArchive) m_TabArchive.SetActive(tab == TAB_ARCHIVE);
        if (m_TabPlayers) m_TabPlayers.SetActive(tab == TAB_PLAYERS);
        if (m_TabBroadcast) m_TabBroadcast.SetActive(tab == TAB_BROADCAST);
        if (m_TabIntel) m_TabIntel.SetActive(tab == TAB_INTEL);
        if (tab != TAB_BROADCAST) Disarm();
        if (tab == TAB_ARCHIVE && m_Results) m_Results.Invalidate();
    }

    // ------------------------------------------------------------------
    // Archive
    // ------------------------------------------------------------------
    protected void UpdateTypeButton()
    {
        if (m_TypeButton) m_TypeButton.SetText("TYPE: " + m_Types[m_TypeIndex]);
    }

    protected void RunSearch(int page)
    {
        if (page < 0) page = 0;
        m_SearchQuery = "";
        if (m_Query) m_SearchQuery = m_Query.GetMessage();
        m_SearchType = m_Types[m_TypeIndex];
        m_HasSearched = true;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_SEARCH, new Param3<string, string, int>(m_SearchQuery, m_SearchType, page), true);
        if (m_PageInfo) m_PageInfo.SetText("SEARCHING...");
    }

    protected void RequestPage(int page)
    {
        if (page < 0) page = 0;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_SEARCH, new Param3<string, string, int>(m_SearchQuery, m_SearchType, page), true);
        int shownPage = page + 1;
        if (m_PageInfo) m_PageInfo.SetText("LOADING PAGE " + shownPage.ToString() + "...");
    }

    protected string TypeTag(string header)
    {
        if (m_SearchType != "ALL") return m_SearchType;
        if (header.Contains("> Broadcast")) return FENR_PDA_MessageType.BROADCAST;
        if (header.Contains("> #")) return "GROUP / CHANNEL";
        return FENR_PDA_MessageType.DIRECT;
    }

    void ReceiveSearch(array<string> headers, array<string> bodies, int total, int page, int pageSize)
    {
        if (pageSize < 1) pageSize = 25;
        m_Page = page;
        m_TotalPages = (total + pageSize - 1) / pageSize;
        if (m_TotalPages < 1) m_TotalPages = 1;

        if (m_Results)
        {
            m_Results.Clear();
            m_Results.SetEmptyText("No messages match this search.");
            if (headers && bodies)
            {
                for (int i = 0; i < headers.Count() && i < bodies.Count(); i++)
                    m_Results.Add(headers[i], TypeTag(headers[i]), bodies[i], FENR_PDA_UI_ChatView.STYLE_REMOTE);
            }
            m_Results.ScrollToBottom();   // top-anchored: back to the first result
        }

        if (m_PageInfo)
        {
            int currentPage = m_Page + 1;
            string info = "PAGE " + currentPage.ToString() + " / " + m_TotalPages.ToString() + "  |  " + total.ToString() + " RESULT";
            if (total != 1) info += "S";
            m_PageInfo.SetText(info);
        }
        UpdatePager();
    }

    protected void UpdatePager()
    {
        if (m_Prev) m_Prev.SetEnabled(m_HasSearched && m_Page > 0);
        if (m_Next) m_Next.SetEnabled(m_HasSearched && m_Page + 1 < m_TotalPages);
    }

    // ------------------------------------------------------------------
    // Players
    // ------------------------------------------------------------------
    protected void RequestPlayers()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_PLAYERS, new Param1<bool>(true), true);
        if (m_PlayerCount) m_PlayerCount.SetText("REFRESHING...");
    }

    void ReceivePlayers(array<string> ids, array<string> rows)
    {
        m_PlayerIds.Clear();
        m_PlayerNames.Clear();
        m_PlayerStates.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        int selectRow = -1;

        int rowCount = 0;
        if (ids && rows) rowCount = Math.Min(ids.Count(), rows.Count());
        for (int i = 0; i < rowCount; i++)
        {
            // Row format from FENR_PDA_Admin: "Name | Steam64 | STATE"
            string row = rows[i];
            array<string> parts = new array<string>();
            row.Split(" | ", parts);
            string name = row;
            string state = "";
            if (parts.Count() >= 1) name = parts[0];
            if (parts.Count() >= 3) state = parts[2];

            m_PlayerIds.Insert(ids[i]);
            m_PlayerNames.Insert(name);
            m_PlayerStates.Insert(state);
            labels.Insert(name);
            metas.Insert(state);
            if (ids[i] == m_SelectedPlayerID) selectRow = i;
        }

        if (m_Players)
        {
            m_Players.SetEmptyText("No players online.");
            m_Players.SetItems(labels, metas);
            m_Players.Select(selectRow);
        }
        if (selectRow < 0) m_SelectedPlayerID = "";
        if (m_PlayerCount)
        {
            string count = labels.Count().ToString() + " PLAYER";
            if (labels.Count() != 1) count += "S";
            m_PlayerCount.SetText(count + " ONLINE");
        }
        UpdatePlayerDetail();
    }

    protected int SelectedPlayer()
    {
        if (!m_Players) return -1;
        int row = m_Players.GetSelected();
        if (row < 0 || row >= m_PlayerIds.Count()) return -1;
        return row;
    }

    protected void UpdatePlayerDetail()
    {
        int row = SelectedPlayer();
        bool has = row >= 0;
        if (has)
        {
            m_SelectedPlayerID = m_PlayerIds[row];
            if (m_PlayerName) m_PlayerName.SetText(m_PlayerNames[row]);
            if (m_PlayerID) m_PlayerID.SetText("STEAM64: " + m_PlayerIds[row]);
            if (m_PlayerState) m_PlayerState.SetText("DEVICE: " + m_PlayerStates[row]);
        }
        else
        {
            if (m_PlayerName) m_PlayerName.SetText("NO PLAYER SELECTED");
            if (m_PlayerID) m_PlayerID.SetText("STEAM64: --");
            if (m_PlayerState) m_PlayerState.SetText("Select a player from the list.");
        }
        if (m_PlayerMessage) m_PlayerMessage.SetEnabled(has);
        if (m_PlayerAdd) m_PlayerAdd.SetEnabled(has);
        if (m_PlayerLogs) m_PlayerLogs.SetEnabled(has);
    }

    protected void MessageSelectedPlayer()
    {
        int row = SelectedPlayer();
        if (row < 0) return;
        FENR_PDA_Client client = PdaClient();
        if (!client) return;

        string id = m_PlayerIds[row];
        FENR_PDA_Contact existing = client.FindContact(id);
        if (existing)
        {
            if (m_Menu) m_Menu.OpenConversation(client.m_Contacts.Find(existing));
            return;
        }
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADD_CONTACT, new Param1<string>(id), true);
        m_PendingOpenID = id;
        m_PendingOpenName = m_PlayerNames[row];
        m_PendingOpenTimer = 5.0;
        if (m_PlayerState) m_PlayerState.SetText("ADDING CONTACT...");
    }

    protected void AddSelectedPlayer()
    {
        int row = SelectedPlayer();
        if (row < 0) return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADD_CONTACT, new Param1<string>(m_PlayerIds[row]), true);
        if (m_PlayerState) m_PlayerState.SetText("CONTACT REQUEST SENT");
    }

    protected void SearchSelectedPlayer()
    {
        int row = SelectedPlayer();
        if (row < 0) return;
        if (m_Query) m_Query.SetText(m_PlayerIds[row]);
        m_TypeIndex = 0;
        UpdateTypeButton();
        SetTab(TAB_ARCHIVE);
        RunSearch(0);
    }

    protected void CheckPendingOpen(float timeslice)
    {
        if (m_PendingOpenID == "") return;
        FENR_PDA_Client client = PdaClient();
        if (!client) return;

        FENR_PDA_Contact contact = client.FindContact(m_PendingOpenID);
        if (!contact)
        {
            foreach (FENR_PDA_Contact c : client.m_Contacts)
            {
                if (c && c.m_Name == m_PendingOpenName && !FENR_PDA_Client.IsGlobalChannel(c.m_UID))
                {
                    contact = c;
                    break;
                }
            }
        }
        if (contact)
        {
            m_PendingOpenID = "";
            if (m_Menu) m_Menu.OpenConversation(client.m_Contacts.Find(contact));
            return;
        }

        m_PendingOpenTimer -= timeslice;
        if (m_PendingOpenTimer <= 0)
        {
            m_PendingOpenID = "";
            if (m_PlayerState) m_PlayerState.SetText("COULD NOT RESOLVE PLAYER");
        }
    }

    // ------------------------------------------------------------------
    // Broadcast (two-step confirm)
    // ------------------------------------------------------------------
    protected void Disarm()
    {
        m_BcArmed = false;
        m_BcArmTimer = 0;
        if (m_BcSend) m_BcSend.SetText("BROADCAST");
    }

    protected void SetBcStatus(string text, int color)
    {
        if (!m_BcStatus) return;
        m_BcStatus.SetText(text);
        m_BcStatus.SetColor(color);
    }

    protected void PressBroadcast()
    {
        if (m_BcSending) return;
        string body = "";
        if (m_BcInput) body = m_BcInput.GetMessage();
        if (body == "")
        {
            SetBcStatus("Type a broadcast message first.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        if (!m_BcArmed)
        {
            m_BcArmed = true;
            m_BcArmTimer = 5.0;
            if (m_BcSend) m_BcSend.SetText("CONFIRM");
            SetBcStatus("Press CONFIRM within 5 seconds to send to ALL PDA users.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        Disarm();
        m_BcSending = true;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.ADMIN_BROADCAST, new Param1<string>(body), true);
        SetBcStatus("Sending broadcast...", FENR_PDA_UI_Theme.Text());
    }

    void ReceiveBroadcastResult(bool success)
    {
        m_BcSending = false;
        if (success)
        {
            if (m_BcInput) m_BcInput.Clear();
            SetBcStatus("Broadcast delivered to all online PDA users.", FENR_PDA_UI_Theme.Accent());
        }
        else
        {
            SetBcStatus("Broadcast rejected: not authorized or empty message.", FENR_PDA_UI_Theme.Danger());
        }
    }

    // ------------------------------------------------------------------
    // Intel (written to the Intel Drive in the admin's own PDA)
    // ------------------------------------------------------------------
    protected void SetIntelStatus(string text, int color)
    {
        if (!m_IntelStatus) return;
        m_IntelStatus.SetText(text);
        m_IntelStatus.SetColor(color);
    }

    protected string IntelTitleText()
    {
        string title = "";
        if (m_IntelTitle) title = m_IntelTitle.GetText();
        title = title.Trim();
        if (title.LengthUtf8() > INTEL_TITLE_MAX) title = title.SubstringUtf8(0, INTEL_TITLE_MAX);
        return title;
    }

    protected string IntelBodyText()
    {
        string body = "";
        if (m_IntelBody) body = m_IntelBody.GetText();
        body = body.Trim();
        if (body.LengthUtf8() > INTEL_BODY_MAX) body = body.SubstringUtf8(0, INTEL_BODY_MAX);
        return body;
    }

    protected void PressIntelWrite()
    {
        if (m_IntelSending) return;
        string title = IntelTitleText();
        string body = IntelBodyText();
        if (title == "" || body == "")
        {
            SetIntelStatus("Enter a title and the intel text first.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        ref array<string> payload = new array<string>();
        payload.Insert(title);
        payload.Insert(body);
        m_IntelSending = true;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_WRITE, new Param4<string, string, ref array<string>, string>(FENR_PDA_DriveKind.INTEL, FENR_PDA_DriveAction.WRITE, payload, ""), true);
        SetIntelStatus("Writing intel...", FENR_PDA_UI_Theme.Text());
    }

    void ReceiveIntelResult(bool success, string info)
    {
        if (!m_IntelSending) return;
        m_IntelSending = false;
        if (success)
        {
            if (m_IntelTitle) m_IntelTitle.Clear();
            if (m_IntelBody) m_IntelBody.Clear();
            SetIntelStatus(info, FENR_PDA_UI_Theme.Accent());
        }
        else
        {
            SetIntelStatus(info, FENR_PDA_UI_Theme.Danger());
        }
    }

    // Live previews (only touched when the text changed).
    protected void UpdatePreviews()
    {
        if (m_Tab == TAB_BROADCAST && m_BcInput && m_BcPreview)
        {
            string bc = m_BcInput.GetText();
            if (bc != m_BcShown)
            {
                m_BcShown = bc;
                if (bc == "") m_BcPreview.SetText("Start typing below. The full message appears here.");
                else m_BcPreview.SetText(bc);
                if (bc == "") m_BcPreview.SetColor(FENR_PDA_UI_Theme.TextDim());
                else m_BcPreview.SetColor(FENR_PDA_UI_Theme.Text());
            }
        }
        if (m_Tab == TAB_INTEL && m_IntelPreview)
        {
            string title = "";
            string body = "";
            if (m_IntelTitle) title = m_IntelTitle.GetText();
            if (m_IntelBody) body = m_IntelBody.GetText();
            string shown = title + "\n" + body;
            if (shown != m_IntelShown)
            {
                m_IntelShown = shown;
                string pretty = body;
                pretty.Replace(" | ", "\n");
                pretty.Replace("|", "\n");
                if (title == "" && body == "")
                {
                    m_IntelPreview.SetText("Type a title and the intel text. Players see it exactly like this when they read the drive.");
                    m_IntelPreview.SetColor(FENR_PDA_UI_Theme.TextDim());
                }
                else
                {
                    m_IntelPreview.SetText(title + "\n\n" + pretty);
                    m_IntelPreview.SetColor(FENR_PDA_UI_Theme.Text());
                }
                if (m_IntelCount)
                {
                    int len = body.LengthUtf8();
                    m_IntelCount.SetText(len.ToString() + " / " + INTEL_BODY_MAX.ToString());
                    if (len > INTEL_BODY_MAX) m_IntelCount.SetColor(FENR_PDA_UI_Theme.Danger());
                    else m_IntelCount.SetColor(FENR_PDA_UI_Theme.TextDim());
                }
            }
        }
    }

    // ------------------------------------------------------------------
    override void OnUpdate(float timeslice)
    {
        if (m_Tab == TAB_ARCHIVE && m_Results) m_Results.Update();
        CheckPendingOpen(timeslice);

        if (m_BcArmed)
        {
            m_BcArmTimer -= timeslice;
            if (m_BcArmTimer <= 0)
            {
                Disarm();
                SetBcStatus("Broadcast cancelled.", FENR_PDA_UI_Theme.TextDim());
            }
        }

        UpdatePreviews();

        if (m_BcCount && m_BcInput)
        {
            int len = m_BcInput.GetText().LengthUtf8();
            m_BcCount.SetText(len.ToString() + " / 256");
            if (len > 256) m_BcCount.SetColor(FENR_PDA_UI_Theme.Danger());
            else m_BcCount.SetColor(FENR_PDA_UI_Theme.TextDim());
        }
    }

    // Enter runs the search on the archive tab.  Broadcasts always need the
    // explicit two-click confirm.
    override bool Submit()
    {
        if (m_Tab == TAB_ARCHIVE)
        {
            RunSearch(0);
            return true;
        }
        return false;
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (Clicked(m_TabArchive, w)) { SetTab(TAB_ARCHIVE); if (!m_HasSearched) RunSearch(0); return true; }
        if (Clicked(m_TabPlayers, w)) { SetTab(TAB_PLAYERS); RequestPlayers(); return true; }
        if (Clicked(m_TabBroadcast, w)) { SetTab(TAB_BROADCAST); return true; }
        if (Clicked(m_TabIntel, w)) { SetTab(TAB_INTEL); return true; }

        if (m_Tab == TAB_ARCHIVE)
        {
            if (Clicked(m_Search, w)) { RunSearch(0); return true; }
            if (Clicked(m_TypeButton, w))
            {
                m_TypeIndex = (m_TypeIndex + 1) % m_Types.Count();
                UpdateTypeButton();
                RunSearch(0);
                return true;
            }
            if (Clicked(m_Clear, w))
            {
                if (m_Query) m_Query.Clear();
                m_TypeIndex = 0;
                UpdateTypeButton();
                RunSearch(0);
                return true;
            }
            if (Clicked(m_Prev, w)) { RequestPage(m_Page - 1); return true; }
            if (Clicked(m_Next, w)) { RequestPage(m_Page + 1); return true; }
            if (m_Results && m_Results.HandleClick(w) != 0) return true;
            return false;
        }

        if (m_Tab == TAB_PLAYERS)
        {
            int result = m_Players.HandleClick(w);
            if (result == FENR_PDA_UI_RowList.RESULT_SELECT) { UpdatePlayerDetail(); return true; }
            if (result != FENR_PDA_UI_RowList.RESULT_NONE) return true;
            if (Clicked(m_PlayersRefresh, w)) { RequestPlayers(); return true; }
            if (Clicked(m_PlayerMessage, w)) { MessageSelectedPlayer(); return true; }
            if (Clicked(m_PlayerAdd, w)) { AddSelectedPlayer(); return true; }
            if (Clicked(m_PlayerLogs, w)) { SearchSelectedPlayer(); return true; }
            return false;
        }

        if (m_Tab == TAB_INTEL)
        {
            if (Clicked(m_IntelWrite, w)) { PressIntelWrite(); return true; }
            return false;
        }

        if (Clicked(m_BcSend, w)) { PressBroadcast(); return true; }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_Tab == TAB_ARCHIVE) return m_Results && m_Results.HandleWheel(x, y, wheel);
        if (m_Tab == TAB_PLAYERS) return m_Players && m_Players.HandleWheel(x, y, wheel);
        return false;
    }
}
