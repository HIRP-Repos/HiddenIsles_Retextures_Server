/*
    Fenrir Industries PDA - Field OS 7.6
    Bounty board: ACTIVE BOARD (3 x 4 tiles), MY BOUNTIES, POST BOUNTY and a
    floating bounty detail popup.  Server contract in FENR_PDA_Bounty.c.
*/
class FENR_PDA_UI_BountyItem extends Managed
{
    string ID;
    string Target;
    string Reward;
    string Reason;
    string PosterID;
    string PosterName;
    bool IsServer;
    string Status;
    string ClaimerID;
    string ClaimerName;
    string ClaimNote;
    string Posted;

    void CopyFrom(FENR_PDA_UI_BountyItem other)
    {
        if (!other) return;
        ID = other.ID;
        Target = other.Target;
        Reward = other.Reward;
        Reason = other.Reason;
        PosterID = other.PosterID;
        PosterName = other.PosterName;
        IsServer = other.IsServer;
        Status = other.Status;
        ClaimerID = other.ClaimerID;
        ClaimerName = other.ClaimerName;
        ClaimNote = other.ClaimNote;
        Posted = other.Posted;
    }

    string PosterLabel()
    {
        if (IsServer) return "SERVER";
        return PosterName;
    }

    int StatusColor()
    {
        if (Status == FENR_PDA_BountyStatus.OPEN) return FENR_PDA_UI_Theme.Accent();
        if (Status == FENR_PDA_BountyStatus.CLAIMED) return FENR_PDA_UI_Theme.Warn();
        return FENR_PDA_UI_Theme.TextOff();
    }
};

class FENR_PDA_PageBounty extends FENR_PDA_UI_Page
{
    protected static const int VIEW_BOARD = 0;
    protected static const int VIEW_MINE = 1;
    protected static const int VIEW_POST = 2;

    protected int m_View = VIEW_BOARD;
    protected int m_Page;
    protected int m_TotalPages = 1;
    protected int m_Total;
    protected float m_RefreshTimer;

    protected Widget m_BoardView;
    protected Widget m_MineView;
    protected Widget m_PostView;
    protected TextWidget m_Subtitle;
    protected TextWidget m_PageInfo;
    protected Widget m_Empty;

    protected FENR_PDA_UI_Button m_TabBoard;
    protected FENR_PDA_UI_Button m_TabMine;
    protected FENR_PDA_UI_Button m_TabPost;
    protected FENR_PDA_UI_Button m_Prev;
    protected FENR_PDA_UI_Button m_Next;

    protected ref array<FENR_PDA_UI_Button> m_Tiles;
    protected ref array<TextWidget> m_TileRewards;
    protected ref array<TextWidget> m_TilePosters;
    protected ref array<TextWidget> m_TileStatuses;
    protected ref array<TextWidget> m_TileTags;
    protected ref array<Widget> m_TileBorders;
    protected ref array<ref FENR_PDA_UI_BountyItem> m_BoardItems;
    protected ref array<ref FENR_PDA_UI_BountyItem> m_MineItems;

    protected ref FENR_PDA_UI_RowList m_Mine;

    // Post form
    protected FENR_PDA_UI_Input m_TargetInput;
    protected FENR_PDA_UI_Input m_RewardInput;
    protected FENR_PDA_UI_Input m_ReasonInput;
    protected FENR_PDA_UI_Button m_ServerToggle;
    protected FENR_PDA_UI_Button m_Post;
    protected TextWidget m_PostStatus;
    protected bool m_ServerBounty;
    protected bool m_Posting;

    // Popup
    protected Widget m_Popup;
    protected Widget m_PopupViewer;
    protected Widget m_PopupOwner;
    protected TextWidget m_PopupKind;
    protected TextWidget m_PopupTarget;
    protected TextWidget m_PopupReward;
    protected TextWidget m_PopupPoster;
    protected TextWidget m_PopupStatus;
    protected TextWidget m_PopupPosted;
    protected TextWidget m_PopupClaim;
    protected MultilineTextWidget m_PopupReason;
    protected FENR_PDA_UI_Input m_ClaimNote;
    protected FENR_PDA_UI_Button m_PopupClose;
    protected FENR_PDA_UI_Button m_PopupShade;
    protected FENR_PDA_UI_Button m_PopupClaimBtn;
    protected FENR_PDA_UI_Button m_PopupContact;
    protected FENR_PDA_UI_Button m_PopupAdminRemove;
    protected FENR_PDA_UI_Button m_PopupConfirm;
    protected FENR_PDA_UI_Button m_PopupReject;
    protected FENR_PDA_UI_Button m_PopupContactClaimer;
    protected FENR_PDA_UI_Button m_PopupCancel;
    protected ref FENR_PDA_UI_BountyItem m_PopupItem;
    protected bool m_PopupOpen;

    void FENR_PDA_PageBounty(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Tiles = new array<FENR_PDA_UI_Button>();
        m_TileRewards = new array<TextWidget>();
        m_TilePosters = new array<TextWidget>();
        m_TileStatuses = new array<TextWidget>();
        m_TileTags = new array<TextWidget>();
        m_TileBorders = new array<Widget>();
        m_BoardItems = new array<ref FENR_PDA_UI_BountyItem>();
        m_MineItems = new array<ref FENR_PDA_UI_BountyItem>();
        m_PopupItem = new FENR_PDA_UI_BountyItem();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_BNT_Root");
        if (!root) return null;

        m_BoardView = root.FindAnyWidget("FI_BNT_BoardView");
        m_MineView = root.FindAnyWidget("FI_BNT_MineView");
        m_PostView = root.FindAnyWidget("FI_BNT_PostView");
        m_Subtitle = Txt("FI_BNT_Subtitle");
        m_PageInfo = Txt("FI_BNT_PageInfo");
        m_Empty = root.FindAnyWidget("FI_BNT_Empty");

        m_TabBoard = Btn("FI_BNT_TabBoard");
        m_TabMine = Btn("FI_BNT_TabMine");
        m_TabPost = Btn("FI_BNT_TabPost");
        m_Prev = Btn("FI_BNT_Prev");
        m_Next = Btn("FI_BNT_Next");

        for (int i = 0; i < FENR_PDA_BountyLimits.PAGE_SIZE; i++)
        {
            string tileName = "FI_BNT_T" + i.ToString();
            FENR_PDA_UI_Button tile = Btn(tileName, FENR_PDA_UI_Button.KIND_ROW);
            if (!tile) break;
            m_Tiles.Insert(tile);
            m_TileRewards.Insert(Txt(tileName + "_Reward"));
            m_TilePosters.Insert(Txt(tileName + "_Poster"));
            m_TileStatuses.Insert(Txt(tileName + "_Status"));
            m_TileTags.Insert(Txt(tileName + "_Tag"));
            m_TileBorders.Insert(root.FindAnyWidget(tileName + "_Bd"));
            tile.Show(false);
        }

        m_Mine = new FENR_PDA_UI_RowList(m_Menu, root, "FI_BNT_Mine");
        m_Mine.SetSelectable(false);
        m_Mine.SetEmptyText("You have not posted or claimed any bounties.");

        m_TargetInput = Field("FI_BNT_TargetInput");
        m_RewardInput = Field("FI_BNT_RewardInput");
        m_ReasonInput = Field("FI_BNT_ReasonInput");
        m_ServerToggle = Btn("FI_BNT_ServerToggle");
        m_Post = Btn("FI_BNT_Post");
        m_PostStatus = Txt("FI_BNT_PostStatus");

        m_Popup = root.FindAnyWidget("FI_BNT_Popup");
        m_PopupViewer = root.FindAnyWidget("FI_BNT_PopupViewer");
        m_PopupOwner = root.FindAnyWidget("FI_BNT_PopupOwner");
        m_PopupKind = Txt("FI_BNT_PopupKind");
        m_PopupTarget = Txt("FI_BNT_PopupTarget");
        m_PopupReward = Txt("FI_BNT_PopupReward");
        m_PopupPoster = Txt("FI_BNT_PopupPoster");
        m_PopupStatus = Txt("FI_BNT_PopupStatus");
        m_PopupPosted = Txt("FI_BNT_PopupPosted");
        m_PopupClaim = Txt("FI_BNT_PopupClaim");
        m_PopupReason = MultilineTextWidget.Cast(root.FindAnyWidget("FI_BNT_PopupReason"));
        m_ClaimNote = Field("FI_BNT_ClaimNote");
        m_PopupClose = Btn("FI_BNT_PopupClose");
        m_PopupShade = Btn("FI_BNT_PopupShade");
        m_PopupClaimBtn = Btn("FI_BNT_PopupClaimBtn");
        m_PopupContact = Btn("FI_BNT_PopupContact");
        m_PopupAdminRemove = Btn("FI_BNT_PopupAdminRemove");
        m_PopupConfirm = Btn("FI_BNT_PopupConfirm");
        m_PopupReject = Btn("FI_BNT_PopupReject");
        m_PopupContactClaimer = Btn("FI_BNT_PopupContactClaimer");
        m_PopupCancel = Btn("FI_BNT_PopupCancel");

        SetServerBounty(false);
        ClosePopup();
        SetView(VIEW_BOARD, false);
        return root;
    }

    // ------------------------------------------------------------------
    protected string LocalID()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) return player.GetIdentity().GetPlainId();
        return "";
    }

    protected void SetSubtitle(string text, int color)
    {
        if (!m_Subtitle) return;
        m_Subtitle.SetText(text);
        m_Subtitle.SetColor(color);
    }

    protected void ParseFields(array<string> fields, array<ref FENR_PDA_UI_BountyItem> output)
    {
        output.Clear();
        if (!fields) return;
        int stride = FENR_PDA_BountyLimits.FIELD_STRIDE;
        for (int i = 0; i + stride <= fields.Count(); i += stride)
        {
            FENR_PDA_UI_BountyItem item = new FENR_PDA_UI_BountyItem();
            item.ID = fields[i];
            item.Target = fields[i + 1];
            item.Reward = fields[i + 2];
            item.Reason = fields[i + 3];
            item.PosterID = fields[i + 4];
            item.PosterName = fields[i + 5];
            item.IsServer = fields[i + 6] == "1";
            item.Status = fields[i + 7];
            item.ClaimerID = fields[i + 8];
            item.ClaimerName = fields[i + 9];
            item.ClaimNote = fields[i + 10];
            item.Posted = fields[i + 11];
            output.Insert(item);
        }
    }

    // ------------------------------------------------------------------
    // Views
    // ------------------------------------------------------------------
    protected void SetView(int view, bool request)
    {
        m_View = view;
        ClosePopup();
        if (m_BoardView) m_BoardView.Show(view == VIEW_BOARD);
        if (m_MineView) m_MineView.Show(view == VIEW_MINE);
        if (m_PostView) m_PostView.Show(view == VIEW_POST);
        if (m_TabBoard) m_TabBoard.SetActive(view == VIEW_BOARD);
        if (m_TabMine) m_TabMine.SetActive(view == VIEW_MINE);
        if (m_TabPost) m_TabPost.SetActive(view == VIEW_POST);

        bool admin = m_Menu && m_Menu.IsAdminUser();
        if (m_ServerToggle) m_ServerToggle.Show(admin);
        if (!admin) SetServerBounty(false);

        if (view == VIEW_POST) SetSubtitle("POST A BOUNTY", FENR_PDA_UI_Theme.Text());
        if (view == VIEW_MINE) SetSubtitle("YOUR BOUNTIES AND CLAIMS", FENR_PDA_UI_Theme.Text());
        if (request) RequestCurrent();
        m_RefreshTimer = 0;
    }

    protected void RequestCurrent()
    {
        if (m_View == VIEW_BOARD) RequestBoard();
        else if (m_View == VIEW_MINE) RequestMine();
    }

    protected void RequestBoard()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_LIST, new Param2<string, int>(FENR_PDA_BountyLimits.BOARD_ACTIVE, m_Page), true);
    }

    protected void RequestMine()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_LIST, new Param2<string, int>(FENR_PDA_BountyLimits.BOARD_MINE, 0), true);
    }

    // Called when a bounty popup notification arrives.
    void RefreshFromServer()
    {
        if (IsShown()) RequestCurrent();
    }

    override void OnShown()
    {
        SetView(m_View, true);
    }

    override void OnHidden()
    {
        ClosePopup();
    }

    // ------------------------------------------------------------------
    // Server responses
    // ------------------------------------------------------------------
    void ReceiveList(array<string> fields, int total, int page, string board)
    {
        if (board == FENR_PDA_BountyLimits.BOARD_MINE)
        {
            ParseFields(fields, m_MineItems);
            string me = LocalID();
            array<string> labels = new array<string>();
            array<string> metas = new array<string>();
            foreach (FENR_PDA_UI_BountyItem mine : m_MineItems)
            {
                labels.Insert(mine.Target + "  |  " + FENR_PDA_UI_Kit.Clip(mine.Reward, 24));
                string role = "POSTED";
                if (mine.ClaimerID == me && mine.PosterID != me) role = "YOUR CLAIM";
                string meta = role + "  |  " + mine.Status;
                if (mine.PosterID == me && mine.Status == FENR_PDA_BountyStatus.CLAIMED) meta = "REVIEW CLAIM  |  CLAIMED";
                metas.Insert(meta);
            }
            if (m_Mine) m_Mine.SetItems(labels, metas);
            RefreshPopupFrom(m_MineItems);
            return;
        }

        ParseFields(fields, m_BoardItems);
        m_Total = total;
        m_Page = page;
        m_TotalPages = (total + FENR_PDA_BountyLimits.PAGE_SIZE - 1) / FENR_PDA_BountyLimits.PAGE_SIZE;
        if (m_TotalPages < 1) m_TotalPages = 1;
        RedrawBoard();
        RefreshPopupFrom(m_BoardItems);
    }

    void ReceiveResult(string action, bool success, string info)
    {
        int color = FENR_PDA_UI_Theme.Accent();
        if (!success) color = FENR_PDA_UI_Theme.Danger();

        if (action == FENR_PDA_BountyAction.POST)
        {
            m_Posting = false;
            if (m_Post) m_Post.SetEnabled(true);
            if (m_PostStatus)
            {
                m_PostStatus.SetText(info);
                m_PostStatus.SetColor(color);
            }
            if (success)
            {
                if (m_TargetInput) m_TargetInput.Clear();
                if (m_RewardInput) m_RewardInput.Clear();
                if (m_ReasonInput) m_ReasonInput.Clear();
            }
            return;
        }

        SetSubtitle(info, color);
        if (success && (action == FENR_PDA_BountyAction.CANCEL || action == FENR_PDA_BountyAction.REMOVE)) ClosePopup();
        if (success && action == FENR_PDA_BountyAction.CLAIM && m_ClaimNote) m_ClaimNote.Clear();
        RequestCurrent();
    }

    // ------------------------------------------------------------------
    protected void RedrawBoard()
    {
        int count = m_BoardItems.Count();
        for (int i = 0; i < m_Tiles.Count(); i++)
        {
            FENR_PDA_UI_Button tile = m_Tiles[i];
            if (i >= count)
            {
                tile.Show(false);
                continue;
            }
            FENR_PDA_UI_BountyItem item = m_BoardItems[i];
            tile.Show(true);
            tile.SetActive(false);
            tile.SetText(FENR_PDA_UI_Kit.Clip(item.Target, 20));
            if (m_TileRewards[i]) m_TileRewards[i].SetText("REWARD: " + FENR_PDA_UI_Kit.Clip(item.Reward, 26));
            if (m_TilePosters[i]) m_TilePosters[i].SetText("BY " + FENR_PDA_UI_Kit.Clip(item.PosterLabel(), 18));
            if (m_TileStatuses[i])
            {
                m_TileStatuses[i].SetText(item.Status);
                m_TileStatuses[i].SetColor(item.StatusColor());
            }
            if (m_TileTags[i])
            {
                if (item.IsServer) m_TileTags[i].SetText("SERVER");
                else m_TileTags[i].SetText("");
            }
            // Server bounties get an amber frame (re-applied after hover changes).
            if (item.IsServer) FENR_PDA_UI_Kit.ColorBorder(m_TileBorders[i], FENR_PDA_UI_Theme.Warn());
        }

        if (m_Empty) m_Empty.Show(count == 0);
        string summary = "ACTIVE BOUNTIES  |  " + m_Total.ToString() + " POSTED";
        SetSubtitle(summary, FENR_PDA_UI_Theme.Text());
        if (m_PageInfo)
        {
            int shownPage = m_Page + 1;
            m_PageInfo.SetText("PAGE " + shownPage.ToString() + " / " + m_TotalPages.ToString());
        }
        if (m_Prev) m_Prev.SetEnabled(m_Page > 0);
        if (m_Next) m_Next.SetEnabled(m_Page + 1 < m_TotalPages);
    }

    // ------------------------------------------------------------------
    // Popup
    // ------------------------------------------------------------------
    protected void OpenPopup(FENR_PDA_UI_BountyItem item)
    {
        if (!item || !m_Popup) return;
        m_PopupItem.CopyFrom(item);
        m_PopupOpen = true;
        if (m_ClaimNote) m_ClaimNote.Clear();
        m_Popup.Show(true);
        FillPopup();
    }

    protected void ClosePopup()
    {
        m_PopupOpen = false;
        if (m_Popup) m_Popup.Show(false);
    }

    protected void RefreshPopupFrom(array<ref FENR_PDA_UI_BountyItem> items)
    {
        if (!m_PopupOpen) return;
        foreach (FENR_PDA_UI_BountyItem item : items)
        {
            if (item.ID == m_PopupItem.ID)
            {
                m_PopupItem.CopyFrom(item);
                FillPopup();
                return;
            }
        }
    }

    protected void FillPopup()
    {
        FENR_PDA_UI_BountyItem item = m_PopupItem;
        string me = LocalID();
        bool admin = m_Menu && m_Menu.IsAdminUser();
        bool isPoster = item.PosterID == me;
        bool manages = isPoster || (item.IsServer && admin);

        if (m_PopupKind)
        {
            string kind = "PLAYER BOUNTY";
            if (item.IsServer) kind = "SERVER BOUNTY";
            m_PopupKind.SetText(kind + "  |  " + item.Status);
            if (item.IsServer) m_PopupKind.SetColor(FENR_PDA_UI_Theme.Warn());
            else m_PopupKind.SetColor(FENR_PDA_UI_Theme.Accent());
        }
        if (m_PopupTarget) m_PopupTarget.SetText(item.Target);
        if (m_PopupReward) m_PopupReward.SetText("REWARD:  " + item.Reward);
        if (m_PopupPoster) m_PopupPoster.SetText("POSTED BY:  " + item.PosterLabel());
        if (m_PopupStatus)
        {
            m_PopupStatus.SetText("STATUS:  " + item.Status);
            m_PopupStatus.SetColor(item.StatusColor());
        }
        if (m_PopupPosted) m_PopupPosted.SetText("POSTED:  " + item.Posted);
        if (m_PopupReason)
        {
            if (item.Reason == "") m_PopupReason.SetText("No reason given.");
            else m_PopupReason.SetText(item.Reason);
        }
        if (m_PopupClaim)
        {
            if (item.ClaimerName != "") m_PopupClaim.SetText("CLAIM BY " + item.ClaimerName + ": " + FENR_PDA_UI_Kit.Clip(item.ClaimNote, 70));
            else m_PopupClaim.SetText("");
        }

        if (m_PopupViewer) m_PopupViewer.Show(!manages);
        if (m_PopupOwner) m_PopupOwner.Show(manages);

        if (!manages)
        {
            bool isOpen = item.Status == FENR_PDA_BountyStatus.OPEN;
            if (m_PopupClaimBtn) m_PopupClaimBtn.SetEnabled(isOpen);
            if (m_ClaimNote) m_ClaimNote.SetEnabled(isOpen);
            if (m_PopupContact)
            {
                m_PopupContact.SetEnabled(!item.IsServer);
                if (item.IsServer) m_PopupContact.SetText("SERVER BOUNTY");
                else m_PopupContact.SetText("CONTACT POSTER");
            }
            if (m_PopupAdminRemove) m_PopupAdminRemove.Show(admin);
        }
        else
        {
            bool claimed = item.Status == FENR_PDA_BountyStatus.CLAIMED;
            if (m_PopupConfirm) m_PopupConfirm.SetEnabled(claimed);
            if (m_PopupReject) m_PopupReject.SetEnabled(claimed);
            if (m_PopupContactClaimer) m_PopupContactClaimer.SetEnabled(item.ClaimerID != "" && item.ClaimerID != me);
            if (m_PopupCancel)
            {
                if (item.Status == FENR_PDA_BountyStatus.COMPLETED) m_PopupCancel.SetText("REMOVE BOUNTY");
                else m_PopupCancel.SetText("CANCEL BOUNTY");
            }
        }
    }

    protected void SendAction(string action, string note)
    {
        if (m_PopupItem.ID == "") return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_ACTION, new Param3<string, string, string>(m_PopupItem.ID, action, note), true);
        SetSubtitle("Updating bounty...", FENR_PDA_UI_Theme.Text());
    }

    // Adds the player as a contact (if needed), sends an opening message and
    // jumps to the conversation.
    protected void ContactPlayer(string playerID, string playerName, string body)
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || playerID == "") return;
        FENR_PDA_Contact contact = client.FindContact(playerID);
        if (!contact)
        {
            client.AddContact(playerID, playerName);
            contact = client.FindContact(playerID);
        }
        if (!contact) return;
        if (contact.m_IsBanned)
        {
            SetSubtitle("You have blocked this player.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        if (body.LengthUtf8() > 256) body = body.SubstringUtf8(0, 256);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SEND_MESSAGE, new Param3<string, string, string>(contact.m_UID, contact.m_Name, body), true);
        if (m_Menu) m_Menu.m_sendMessageStatus = 1;
        int index = client.m_Contacts.Find(contact);
        ClosePopup();
        if (m_Menu && index >= 0) m_Menu.OpenConversation(index);
    }

    // ------------------------------------------------------------------
    // Post
    // ------------------------------------------------------------------
    protected void SetServerBounty(bool state)
    {
        m_ServerBounty = state;
        if (!m_ServerToggle) return;
        m_ServerToggle.SetActive(state);
        if (state) m_ServerToggle.SetText("SERVER BOUNTY: ON (ANNOUNCED TO ALL)");
        else m_ServerToggle.SetText("SERVER BOUNTY: OFF");
    }

    protected void SetPostStatus(string text, int color)
    {
        if (!m_PostStatus) return;
        m_PostStatus.SetText(text);
        m_PostStatus.SetColor(color);
    }

    protected void PostBounty()
    {
        if (m_Posting) return;
        string target = "";
        string reward = "";
        string reason = "";
        if (m_TargetInput) target = m_TargetInput.GetMessage();
        if (m_RewardInput) reward = m_RewardInput.GetMessage();
        if (m_ReasonInput) reason = m_ReasonInput.GetMessage();

        if (target == "") { SetPostStatus("Enter the target's name.", FENR_PDA_UI_Theme.Warn()); return; }
        if (reward == "") { SetPostStatus("Enter a reward.", FENR_PDA_UI_Theme.Warn()); return; }
        if (target.LengthUtf8() > FENR_PDA_BountyLimits.TARGET) { SetPostStatus("Target name is too long.", FENR_PDA_UI_Theme.Warn()); return; }
        if (reward.LengthUtf8() > FENR_PDA_BountyLimits.REWARD) { SetPostStatus("Reward is too long (max 40).", FENR_PDA_UI_Theme.Warn()); return; }

        m_Posting = true;
        if (m_Post) m_Post.SetEnabled(false);
        SetPostStatus("Posting bounty...", FENR_PDA_UI_Theme.Text());
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.BOUNTY_POST, new Param4<string, string, string, bool>(target, reward, reason, m_ServerBounty), true);
    }

    // ------------------------------------------------------------------
    // Events
    // ------------------------------------------------------------------
    override void OnUpdate(float timeslice)
    {
        m_RefreshTimer += timeslice;
        if (m_RefreshTimer >= 20.0)
        {
            m_RefreshTimer = 0;
            RequestCurrent();
        }
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_PopupOpen)
        {
            if (Clicked(m_PopupClose, w) || Clicked(m_PopupShade, w)) { ClosePopup(); return true; }
            if (Clicked(m_PopupClaimBtn, w))
            {
                string note = "";
                if (m_ClaimNote) note = m_ClaimNote.GetMessage();
                if (note == "")
                {
                    SetSubtitle("Add a proof note before claiming.", FENR_PDA_UI_Theme.Warn());
                    return true;
                }
                SendAction(FENR_PDA_BountyAction.CLAIM, note);
                return true;
            }
            if (Clicked(m_PopupContact, w))
            {
                ContactPlayer(m_PopupItem.PosterID, m_PopupItem.PosterName, "[BOUNTY] Hi " + m_PopupItem.PosterName + ", about your bounty on " + m_PopupItem.Target + " (" + m_PopupItem.Reward + ").");
                return true;
            }
            if (Clicked(m_PopupContactClaimer, w))
            {
                ContactPlayer(m_PopupItem.ClaimerID, m_PopupItem.ClaimerName, "[BOUNTY] Hi " + m_PopupItem.ClaimerName + ", about your claim on " + m_PopupItem.Target + ".");
                return true;
            }
            if (Clicked(m_PopupAdminRemove, w)) { SendAction(FENR_PDA_BountyAction.REMOVE, ""); return true; }
            if (Clicked(m_PopupConfirm, w)) { SendAction(FENR_PDA_BountyAction.CONFIRM, ""); return true; }
            if (Clicked(m_PopupReject, w)) { SendAction(FENR_PDA_BountyAction.REJECT, ""); return true; }
            if (Clicked(m_PopupCancel, w)) { SendAction(FENR_PDA_BountyAction.CANCEL, ""); return true; }
            return true;
        }

        if (Clicked(m_TabBoard, w)) { SetView(VIEW_BOARD, true); return true; }
        if (Clicked(m_TabMine, w)) { SetView(VIEW_MINE, true); return true; }
        if (Clicked(m_TabPost, w)) { SetView(VIEW_POST, true); return true; }

        if (m_View == VIEW_BOARD)
        {
            if (Clicked(m_Prev, w)) { m_Page--; RequestBoard(); return true; }
            if (Clicked(m_Next, w)) { m_Page++; RequestBoard(); return true; }
            for (int i = 0; i < m_Tiles.Count() && i < m_BoardItems.Count(); i++)
            {
                if (w == m_Tiles[i].m_Button)
                {
                    OpenPopup(m_BoardItems[i]);
                    return true;
                }
            }
            return false;
        }

        if (m_View == VIEW_MINE)
        {
            int result = m_Mine.HandleClick(w);
            if (result == FENR_PDA_UI_RowList.RESULT_SELECT)
            {
                int row = m_Mine.GetSelected();
                if (row >= 0 && row < m_MineItems.Count()) OpenPopup(m_MineItems[row]);
                return true;
            }
            return result != FENR_PDA_UI_RowList.RESULT_NONE;
        }

        if (Clicked(m_ServerToggle, w)) { SetServerBounty(!m_ServerBounty); return true; }
        if (Clicked(m_Post, w)) { PostBounty(); return true; }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_PopupOpen) return true;
        if (m_View == VIEW_MINE) return m_Mine && m_Mine.HandleWheel(x, y, wheel);
        if (m_View != VIEW_BOARD || !FENR_PDA_UI_Kit.IsPointInside(m_BoardView, x, y)) return false;
        if (wheel < 0 && m_Page + 1 < m_TotalPages) { m_Page++; RequestBoard(); }
        else if (wheel > 0 && m_Page > 0) { m_Page--; RequestBoard(); }
        return true;
    }
}
