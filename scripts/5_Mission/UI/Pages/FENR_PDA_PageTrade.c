/*
    Fenrir Industries PDA - Field OS 7.3
    Trade: BUY board, SELL board (4 x 5 listing tiles), CREATE LISTING form
    with the player's own listings, and a floating listing detail popup.

    Server contract: TradeList / TradeCreate / TradeUpdate / TradeResult
    (see FENR_PDA_Trade.c).  Contacting a lister uses the normal direct
    message path; blocking uses the normal contact block.
*/
class FENR_PDA_UI_TradeItem extends Managed
{
    string ID;
    string Type;
    string Title;
    string Price;
    string Description;
    string OwnerID;
    string OwnerName;
    string Status;
    string Posted;
    string Category;
    int RepScore;
    int RepCount;

    void CopyFrom(FENR_PDA_UI_TradeItem other)
    {
        if (!other) return;
        ID = other.ID;
        Type = other.Type;
        Title = other.Title;
        Price = other.Price;
        Description = other.Description;
        OwnerID = other.OwnerID;
        OwnerName = other.OwnerName;
        Status = other.Status;
        Posted = other.Posted;
        Category = other.Category;
        RepScore = other.RepScore;
        RepCount = other.RepCount;
    }

    string RepText()
    {
        return FENR_PDA_PageTrade.FormatRep(RepScore, RepCount);
    }

    bool IsSell() { return Type == FENR_PDA_TradeType.SELL; }
    bool IsClosed() { return Status == FENR_PDA_TradeStatus.CLOSED; }

    string StatusLabel()
    {
        if (Status == FENR_PDA_TradeStatus.CLOSED)
        {
            if (IsSell()) return "SOLD";
            return "FILLED";
        }
        return Status;
    }

    int StatusColor()
    {
        if (Status == FENR_PDA_TradeStatus.OPEN) return FENR_PDA_UI_Theme.Accent();
        if (Status == FENR_PDA_TradeStatus.PENDING) return FENR_PDA_UI_Theme.Warn();
        return FENR_PDA_UI_Theme.TextOff();
    }

    // "SELLER" for sell listings, "BUYER" for buy listings.
    string ListerRole()
    {
        if (IsSell()) return "SELLER";
        return "BUYER";
    }
};

class FENR_PDA_PageTrade extends FENR_PDA_UI_Page
{
    protected static const int VIEW_BUY = 0;
    protected static const int VIEW_SELL = 1;
    protected static const int VIEW_CREATE = 2;
    protected static const int TILE_COUNT = 20;

    protected int m_View = VIEW_SELL;
    protected string m_Board = "SELL";
    protected int m_Page;
    protected int m_TotalPages = 1;
    protected int m_Total;
    protected float m_RefreshTimer;

    protected Widget m_BoardView;
    protected Widget m_CreateView;
    protected TextWidget m_Subtitle;
    protected TextWidget m_PageInfo;
    protected Widget m_Empty;

    protected FENR_PDA_UI_Button m_TabBuy;
    protected FENR_PDA_UI_Button m_TabSell;
    protected FENR_PDA_UI_Button m_TabCreate;
    protected FENR_PDA_UI_Button m_Prev;
    protected FENR_PDA_UI_Button m_Next;
    protected FENR_PDA_UI_Button m_Filter;
    protected ref array<string> m_Categories;
    protected int m_FilterIndex;
    protected ref array<ImageWidget> m_TileIcons;

    protected ref array<FENR_PDA_UI_Button> m_Tiles;
    protected ref array<TextWidget> m_TilePrices;
    protected ref array<TextWidget> m_TileListers;
    protected ref array<TextWidget> m_TileStatuses;
    protected ref array<ref FENR_PDA_UI_TradeItem> m_BoardItems;
    protected ref array<ref FENR_PDA_UI_TradeItem> m_MineItems;

    // Create view
    protected string m_CreateType = "SELL";
    protected string m_CreateCategory = "OTHER";
    protected TextWidget m_FormTitle;
    protected ref array<FENR_PDA_UI_Button> m_CatButtons;
    protected FENR_PDA_UI_Button m_TypeSell;
    protected FENR_PDA_UI_Button m_TypeBuy;
    protected FENR_PDA_UI_Input m_TitleInput;
    protected FENR_PDA_UI_Input m_PriceInput;
    protected FENR_PDA_UI_Input m_DescInput;
    protected FENR_PDA_UI_Button m_Post;
    protected TextWidget m_CreateStatus;
    protected ref FENR_PDA_UI_RowList m_Mine;
    protected bool m_Posting;

    // Popup
    protected Widget m_Popup;
    protected Widget m_PopupViewer;
    protected Widget m_PopupOwner;
    protected TextWidget m_PopupKind;
    protected TextWidget m_PopupTitle;
    protected TextWidget m_PopupPrice;
    protected TextWidget m_PopupLister;
    protected TextWidget m_PopupStatus;
    protected TextWidget m_PopupPosted;
    protected MultilineTextWidget m_PopupDesc;
    protected FENR_PDA_UI_Button m_PopupClose;
    protected FENR_PDA_UI_Button m_PopupShade;
    protected FENR_PDA_UI_Button m_PopupContact;
    protected FENR_PDA_UI_Button m_PopupBlock;
    protected FENR_PDA_UI_Button m_PopupAdminRemove;
    protected FENR_PDA_UI_Button m_PopupPending;
    protected FENR_PDA_UI_Button m_PopupClosed;
    protected FENR_PDA_UI_Button m_PopupRemove;
    protected FENR_PDA_UI_Button m_PopupRateUp;
    protected FENR_PDA_UI_Button m_PopupRateDown;
    protected ImageWidget m_PopupIcon;
    protected int m_PopupMyVote;
    protected bool m_PopupCanRate;
    protected ref FENR_PDA_UI_TradeItem m_PopupItem;
    protected bool m_PopupOpen;

    void FENR_PDA_PageTrade(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Tiles = new array<FENR_PDA_UI_Button>();
        m_TilePrices = new array<TextWidget>();
        m_TileListers = new array<TextWidget>();
        m_TileStatuses = new array<TextWidget>();
        m_BoardItems = new array<ref FENR_PDA_UI_TradeItem>();
        m_MineItems = new array<ref FENR_PDA_UI_TradeItem>();
        m_PopupItem = new FENR_PDA_UI_TradeItem();
        m_TileIcons = new array<ImageWidget>();
        m_CatButtons = new array<FENR_PDA_UI_Button>();
        m_Categories = new array<string>();
        m_Categories.Insert(FENR_PDA_TradeCategory.ALL);
        m_Categories.Insert(FENR_PDA_TradeCategory.GUNS);
        m_Categories.Insert(FENR_PDA_TradeCategory.AMMO);
        m_Categories.Insert(FENR_PDA_TradeCategory.MEDICAL);
        m_Categories.Insert(FENR_PDA_TradeCategory.TOOLS);
        m_Categories.Insert(FENR_PDA_TradeCategory.CLOTHING);
        m_Categories.Insert(FENR_PDA_TradeCategory.OTHER);
    }

    static string FormatRep(int score, int count)
    {
        if (count <= 0) return "NEW";
        string sign = "";
        if (score > 0) sign = "+";
        return "REP " + sign + score.ToString();
    }

    protected static void SetIcon(ImageWidget icon, string category)
    {
        if (!icon) return;
        icon.LoadImageFile(0, "PDA/gui/os/textures/" + FENR_PDA_TradeCategory.Icon(category) + ".edds");
        icon.SetImage(0);
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_TRD_Root");
        if (!root) return null;

        m_BoardView = root.FindAnyWidget("FI_TRD_BoardView");
        m_CreateView = root.FindAnyWidget("FI_TRD_CreateView");
        m_Subtitle = Txt("FI_TRD_Subtitle");
        m_PageInfo = Txt("FI_TRD_PageInfo");
        m_Empty = root.FindAnyWidget("FI_TRD_Empty");

        m_TabBuy = Btn("FI_TRD_TabBuy");
        m_TabSell = Btn("FI_TRD_TabSell");
        m_TabCreate = Btn("FI_TRD_TabCreate");
        m_Prev = Btn("FI_TRD_Prev");
        m_Next = Btn("FI_TRD_Next");
        m_Filter = Btn("FI_TRD_Filter");

        for (int i = 0; i < TILE_COUNT; i++)
        {
            string tileName = "FI_TRD_T" + i.ToString();
            FENR_PDA_UI_Button tile = Btn(tileName, FENR_PDA_UI_Button.KIND_ROW);
            if (!tile) break;
            m_Tiles.Insert(tile);
            m_TilePrices.Insert(Txt(tileName + "_Price"));
            m_TileListers.Insert(Txt(tileName + "_Lister"));
            m_TileStatuses.Insert(Txt(tileName + "_Status"));
            m_TileIcons.Insert(ImageWidget.Cast(root.FindAnyWidget(tileName + "_Icon")));
            tile.Show(false);
        }

        m_FormTitle = Txt("FI_TRD_FormTitle");
        for (int c = 1; c < m_Categories.Count(); c++)
        {
            FENR_PDA_UI_Button catButton = Btn("FI_TRD_Cat" + m_Categories[c]);
            m_CatButtons.Insert(catButton);
        }
        m_TypeSell = Btn("FI_TRD_TypeSell");
        m_TypeBuy = Btn("FI_TRD_TypeBuy");
        m_TitleInput = Field("FI_TRD_TitleInput");
        m_PriceInput = Field("FI_TRD_PriceInput");
        m_DescInput = Field("FI_TRD_DescInput");
        m_Post = Btn("FI_TRD_Post");
        m_CreateStatus = Txt("FI_TRD_CreateStatus");
        m_Mine = new FENR_PDA_UI_RowList(m_Menu, root, "FI_TRD_Mine");
        m_Mine.SetSelectable(false);
        m_Mine.SetEmptyText("You have no listings.");

        m_Popup = root.FindAnyWidget("FI_TRD_Popup");
        m_PopupViewer = root.FindAnyWidget("FI_TRD_PopupViewer");
        m_PopupOwner = root.FindAnyWidget("FI_TRD_PopupOwner");
        m_PopupKind = Txt("FI_TRD_PopupKind");
        m_PopupTitle = Txt("FI_TRD_PopupTitle");
        m_PopupPrice = Txt("FI_TRD_PopupPrice");
        m_PopupLister = Txt("FI_TRD_PopupLister");
        m_PopupStatus = Txt("FI_TRD_PopupStatus");
        m_PopupPosted = Txt("FI_TRD_PopupPosted");
        m_PopupDesc = MultilineTextWidget.Cast(root.FindAnyWidget("FI_TRD_PopupDesc"));
        m_PopupClose = Btn("FI_TRD_PopupClose");
        m_PopupShade = Btn("FI_TRD_PopupShade");
        m_PopupContact = Btn("FI_TRD_PopupContact");
        m_PopupBlock = Btn("FI_TRD_PopupBlock");
        m_PopupAdminRemove = Btn("FI_TRD_PopupAdminRemove");
        m_PopupPending = Btn("FI_TRD_PopupPending");
        m_PopupClosed = Btn("FI_TRD_PopupClosed");
        m_PopupRemove = Btn("FI_TRD_PopupRemove");
        m_PopupRateUp = Btn("FI_TRD_PopupRateUp");
        m_PopupRateDown = Btn("FI_TRD_PopupRateDown");
        m_PopupIcon = ImageWidget.Cast(root.FindAnyWidget("FI_TRD_PopupIcon"));

        SetCreateType(FENR_PDA_TradeType.SELL);
        SetCreateCategory(FENR_PDA_TradeCategory.OTHER);
        UpdateFilterButton();
        ClosePopup();
        SetView(VIEW_SELL, false);
        return root;
    }

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------
    protected string LocalID()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) return player.GetIdentity().GetPlainId();
        return "";
    }

    protected bool IsBlocked(string ownerID)
    {
        FENR_PDA_Client client = PdaClient();
        if (!client) return false;
        FENR_PDA_Contact contact = client.FindContact(ownerID);
        return contact && contact.m_IsBanned;
    }

    protected void SetSubtitle(string text, int color)
    {
        if (!m_Subtitle) return;
        m_Subtitle.SetText(text);
        m_Subtitle.SetColor(color);
    }

    protected void ParseFields(array<string> fields, array<ref FENR_PDA_UI_TradeItem> output)
    {
        output.Clear();
        if (!fields) return;
        int stride = FENR_PDA_TradeLimits.FIELD_STRIDE;
        for (int i = 0; i + stride <= fields.Count(); i += stride)
        {
            FENR_PDA_UI_TradeItem item = new FENR_PDA_UI_TradeItem();
            item.ID = fields[i];
            item.Type = fields[i + 1];
            item.Title = fields[i + 2];
            item.Price = fields[i + 3];
            item.Description = fields[i + 4];
            item.OwnerID = fields[i + 5];
            item.OwnerName = fields[i + 6];
            item.Status = fields[i + 7];
            item.Posted = fields[i + 8];
            item.Category = fields[i + 9];
            string repField = fields[i + 10];
            array<string> repParts = new array<string>();
            repField.Split(":", repParts);
            if (repParts.Count() == 2)
            {
                item.RepScore = repParts[0].ToInt();
                item.RepCount = repParts[1].ToInt();
            }
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
        bool board = view != VIEW_CREATE;
        if (m_BoardView) m_BoardView.Show(board);
        if (m_CreateView) m_CreateView.Show(!board);
        if (m_TabBuy) m_TabBuy.SetActive(view == VIEW_BUY);
        if (m_TabSell) m_TabSell.SetActive(view == VIEW_SELL);
        if (m_TabCreate) m_TabCreate.SetActive(view == VIEW_CREATE);

        if (board)
        {
            string newBoard = FENR_PDA_TradeType.SELL;
            if (view == VIEW_BUY) newBoard = FENR_PDA_TradeType.BUY;
            if (newBoard != m_Board)
            {
                m_Board = newBoard;
                m_Page = 0;
                m_BoardItems.Clear();
                RedrawBoard(0);
            }
            if (request) RequestBoard();
        }
        else
        {
            SetSubtitle("CREATE A LISTING", FENR_PDA_UI_Theme.Text());
            if (request) RequestMine();
        }
        m_RefreshTimer = 0;
    }

    override void OnShown()
    {
        SetView(m_View, true);
    }

    override void OnHidden()
    {
        ClosePopup();
    }

    protected void RequestBoard()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_LIST, new Param3<string, int, string>(m_Board, m_Page, m_Categories[m_FilterIndex]), true);
        if (m_PageInfo && m_BoardItems.Count() == 0) m_PageInfo.SetText("LOADING...");
    }

    protected void UpdateFilterButton()
    {
        if (!m_Filter) return;
        m_Filter.SetText("FILTER: " + FENR_PDA_TradeCategory.Label(m_Categories[m_FilterIndex]));
        m_Filter.SetActive(m_FilterIndex != 0);
    }

    protected void RequestMine()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_LIST, new Param3<string, int, string>(FENR_PDA_TradeType.MINE, 0, FENR_PDA_TradeCategory.ALL), true);
    }

    // ------------------------------------------------------------------
    // Server responses
    // ------------------------------------------------------------------
    void ReceiveList(array<string> fields, int total, int page, string board)
    {
        if (board == FENR_PDA_TradeType.MINE)
        {
            ParseFields(fields, m_MineItems);
            array<string> labels = new array<string>();
            array<string> metas = new array<string>();
            foreach (FENR_PDA_UI_TradeItem mine : m_MineItems)
            {
                labels.Insert(mine.Title);
                metas.Insert(mine.Type + "  |  " + mine.StatusLabel());
            }
            if (m_Mine) m_Mine.SetItems(labels, metas);
            RefreshPopupFrom(m_MineItems);
            return;
        }

        if (board != m_Board) return;

        array<ref FENR_PDA_UI_TradeItem> parsed = new array<ref FENR_PDA_UI_TradeItem>();
        ParseFields(fields, parsed);

        // Listings from blocked players are hidden for this player.
        m_BoardItems.Clear();
        int hidden = 0;
        foreach (FENR_PDA_UI_TradeItem item : parsed)
        {
            if (IsBlocked(item.OwnerID))
            {
                hidden++;
                continue;
            }
            m_BoardItems.Insert(item);
        }

        m_Total = total;
        m_Page = page;
        m_TotalPages = (total + FENR_PDA_TradeLimits.PAGE_SIZE - 1) / FENR_PDA_TradeLimits.PAGE_SIZE;
        if (m_TotalPages < 1) m_TotalPages = 1;
        RedrawBoard(hidden);
        RefreshPopupFrom(m_BoardItems);
    }

    void ReceiveResult(string action, bool success, string info)
    {
        int color = FENR_PDA_UI_Theme.Accent();
        if (!success) color = FENR_PDA_UI_Theme.Danger();

        if (action == FENR_PDA_TradeAction.CREATE)
        {
            m_Posting = false;
            if (m_Post) m_Post.SetEnabled(true);
            if (m_CreateStatus)
            {
                m_CreateStatus.SetText(info);
                m_CreateStatus.SetColor(color);
            }
            if (success)
            {
                if (m_TitleInput) m_TitleInput.Clear();
                if (m_PriceInput) m_PriceInput.Clear();
                if (m_DescInput) m_DescInput.Clear();
            }
        }
        else
        {
            SetSubtitle(info, color);
            if (success && action == FENR_PDA_TradeAction.REMOVE) ClosePopup();
            if (action == "RATE")
            {
                if (m_View != VIEW_CREATE) RequestBoard();
                return;
            }
        }

        RequestMine();
        if (m_View != VIEW_CREATE) RequestBoard();
    }

    // ------------------------------------------------------------------
    // Board drawing
    // ------------------------------------------------------------------
    protected void RedrawBoard(int hidden)
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
            FENR_PDA_UI_TradeItem item = m_BoardItems[i];
            tile.Show(true);
            tile.SetActive(false);
            tile.SetText(item.Title);
            SetIcon(m_TileIcons[i], item.Category);
            if (m_TilePrices[i]) m_TilePrices[i].SetText(FENR_PDA_UI_Kit.Clip(item.Price, 16));
            if (m_TileListers[i]) m_TileListers[i].SetText(FENR_PDA_UI_Kit.Clip(item.OwnerName, 16) + "  " + item.RepText());
            if (m_TileStatuses[i])
            {
                m_TileStatuses[i].SetText(item.StatusLabel());
                m_TileStatuses[i].SetColor(item.StatusColor());
            }
        }

        if (m_Empty) m_Empty.Show(count == 0);

        string boardName = "SELL BOARD";
        if (m_Board == FENR_PDA_TradeType.BUY) boardName = "BUY BOARD";
        if (m_FilterIndex != 0) boardName += " / " + FENR_PDA_TradeCategory.Label(m_Categories[m_FilterIndex]);
        string summary = boardName + "  |  " + m_Total.ToString() + " LISTING";
        if (m_Total != 1) summary += "S";
        if (hidden > 0) summary += "  |  " + hidden.ToString() + " HIDDEN (BLOCKED)";
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
    protected void OpenPopup(FENR_PDA_UI_TradeItem item)
    {
        if (!item || !m_Popup) return;
        m_PopupItem.CopyFrom(item);
        m_PopupOpen = true;
        m_PopupMyVote = 0;
        m_PopupCanRate = false;
        m_Popup.Show(true);
        FillPopup();
        if (m_PopupItem.OwnerID != LocalID())
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_GET, new Param1<string>(m_PopupItem.OwnerID), true);
    }

    protected void ClosePopup()
    {
        m_PopupOpen = false;
        if (m_Popup) m_Popup.Show(false);
    }

    // Keeps an open popup in sync with fresh server data.
    protected void RefreshPopupFrom(array<ref FENR_PDA_UI_TradeItem> items)
    {
        if (!m_PopupOpen) return;
        foreach (FENR_PDA_UI_TradeItem item : items)
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
        FENR_PDA_UI_TradeItem item = m_PopupItem;
        string role = item.ListerRole();

        SetIcon(m_PopupIcon, item.Category);
        string catLabel = FENR_PDA_TradeCategory.Label(item.Category);
        if (m_PopupKind)
        {
            if (item.IsSell()) m_PopupKind.SetText("FOR SALE  |  " + catLabel);
            else m_PopupKind.SetText("WANTED  |  " + catLabel);
        }
        if (m_PopupTitle) m_PopupTitle.SetText(item.Title);
        if (m_PopupPrice) m_PopupPrice.SetText("PRICE:  " + item.Price);
        if (m_PopupLister)
        {
            string repLine = "NO RATINGS YET";
            if (item.RepCount > 0)
            {
                string sign = "";
                if (item.RepScore > 0) sign = "+";
                repLine = "REP " + sign + item.RepScore.ToString() + " (" + item.RepCount.ToString() + " RATINGS)";
            }
            m_PopupLister.SetText(role + ":  " + item.OwnerName + "   |   " + repLine);
        }
        if (m_PopupStatus)
        {
            m_PopupStatus.SetText("STATUS:  " + item.StatusLabel());
            m_PopupStatus.SetColor(item.StatusColor());
        }
        if (m_PopupPosted) m_PopupPosted.SetText("POSTED:  " + item.Posted);
        if (m_PopupDesc)
        {
            if (item.Description == "") m_PopupDesc.SetText("No details provided.");
            else m_PopupDesc.SetText(item.Description);
        }

        bool own = item.OwnerID != "" && item.OwnerID == LocalID();
        bool admin = m_Menu && m_Menu.IsAdminUser();
        if (m_PopupViewer) m_PopupViewer.Show(!own);
        if (m_PopupOwner) m_PopupOwner.Show(own);

        if (!own)
        {
            if (m_PopupContact)
            {
                m_PopupContact.SetText("CONTACT " + role);
                m_PopupContact.SetEnabled(!item.IsClosed() && !IsBlocked(item.OwnerID));
            }
            if (m_PopupBlock)
            {
                if (IsBlocked(item.OwnerID)) m_PopupBlock.SetText("UNBLOCK " + role);
                else m_PopupBlock.SetText("BLOCK " + role);
            }
            if (m_PopupAdminRemove) m_PopupAdminRemove.Show(admin);
            if (m_PopupRateUp)
            {
                m_PopupRateUp.SetEnabled(m_PopupCanRate);
                m_PopupRateUp.SetActive(m_PopupMyVote > 0);
            }
            if (m_PopupRateDown)
            {
                m_PopupRateDown.SetEnabled(m_PopupCanRate);
                m_PopupRateDown.SetActive(m_PopupMyVote < 0);
            }
        }
        else
        {
            if (m_PopupPending)
            {
                if (item.Status == FENR_PDA_TradeStatus.PENDING) m_PopupPending.SetText("MARK OPEN");
                else m_PopupPending.SetText("MARK PENDING");
                m_PopupPending.SetEnabled(!item.IsClosed());
            }
            if (m_PopupClosed)
            {
                if (item.IsClosed()) m_PopupClosed.SetText("REOPEN LISTING");
                else if (item.IsSell()) m_PopupClosed.SetText("MARK SOLD");
                else m_PopupClosed.SetText("MARK FILLED");
            }
        }
    }

    void ReceiveRep(string targetID, int score, int count, int myVote, bool canRate)
    {
        if (!m_PopupOpen || targetID != m_PopupItem.OwnerID) return;
        m_PopupItem.RepScore = score;
        m_PopupItem.RepCount = count;
        m_PopupMyVote = myVote;
        m_PopupCanRate = canRate;
        FillPopup();
        if (!canRate) SetSubtitle("Contact this " + m_PopupItem.ListerRole() + " through a listing to be able to rate them.", FENR_PDA_UI_Theme.TextDim());
    }

    protected void SendVote(int value)
    {
        if (m_PopupItem.OwnerID == "") return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.REP_VOTE, new Param2<string, int>(m_PopupItem.OwnerID, value), true);
    }

    protected void SendUpdate(string action)
    {
        if (m_PopupItem.ID == "") return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_UPDATE, new Param2<string, string>(m_PopupItem.ID, action), true);
        SetSubtitle("Updating listing...", FENR_PDA_UI_Theme.Text());
    }

    // Adds the lister as a contact if needed and returns that contact.
    protected FENR_PDA_Contact EnsureListerContact()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || m_PopupItem.OwnerID == "") return null;
        FENR_PDA_Contact contact = client.FindContact(m_PopupItem.OwnerID);
        if (!contact)
        {
            client.AddContact(m_PopupItem.OwnerID, m_PopupItem.OwnerName);
            contact = client.FindContact(m_PopupItem.OwnerID);
        }
        return contact;
    }

    protected void ContactLister()
    {
        FENR_PDA_Client client = PdaClient();
        FENR_PDA_Contact contact = EnsureListerContact();
        if (!client || !contact) return;
        if (contact.m_IsBanned)
        {
            SetSubtitle("Unblock this player before contacting them.", FENR_PDA_UI_Theme.Warn());
            return;
        }

        string body;
        if (m_PopupItem.IsSell())
            body = "[TRADE] Hi " + m_PopupItem.OwnerName + ", I want to buy your listing '" + m_PopupItem.Title + "' (" + m_PopupItem.Price + "). Is it still available?";
        else
            body = "[TRADE] Hi " + m_PopupItem.OwnerName + ", I have the item you are looking for: '" + m_PopupItem.Title + "' (" + m_PopupItem.Price + "). Want to trade?";
        if (body.LengthUtf8() > 256) body = body.SubstringUtf8(0, 256);

        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_CONTACT, new Param1<string>(m_PopupItem.ID), true);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SEND_MESSAGE, new Param3<string, string, string>(contact.m_UID, contact.m_Name, body), true);
        if (m_Menu) m_Menu.m_sendMessageStatus = 1;

        int index = client.m_Contacts.Find(contact);
        ClosePopup();
        if (m_Menu && index >= 0) m_Menu.OpenConversation(index);
    }

    protected void ToggleBlockLister()
    {
        FENR_PDA_Client client = PdaClient();
        FENR_PDA_Contact contact = EnsureListerContact();
        if (!client || !contact) return;
        client.ToggleBlocked(contact.m_UID);

        if (contact.m_IsBanned)
        {
            SetSubtitle("Blocked " + contact.m_Name + ". Their messages and listings are hidden.", FENR_PDA_UI_Theme.Warn());
            ClosePopup();
        }
        else
        {
            SetSubtitle("Unblocked " + contact.m_Name + ".", FENR_PDA_UI_Theme.Accent());
            FillPopup();
        }
        if (m_Menu) m_Menu.m_dirty = true;
        if (m_View != VIEW_CREATE) RequestBoard();
    }

    // ------------------------------------------------------------------
    // Create
    // ------------------------------------------------------------------
    protected void SetCreateType(string listingType)
    {
        m_CreateType = listingType;
        if (m_TypeSell) m_TypeSell.SetActive(listingType == FENR_PDA_TradeType.SELL);
        if (m_TypeBuy) m_TypeBuy.SetActive(listingType == FENR_PDA_TradeType.BUY);
        if (m_Post)
        {
            if (listingType == FENR_PDA_TradeType.SELL) m_Post.SetText("POST TO SELL BOARD");
            else m_Post.SetText("POST TO BUY BOARD");
        }
    }

    protected void SetCreateCategory(string category)
    {
        m_CreateCategory = category;
        for (int i = 0; i < m_CatButtons.Count(); i++)
        {
            if (m_CatButtons[i]) m_CatButtons[i].SetActive(m_Categories[i + 1] == category);
        }
        if (m_FormTitle) m_FormTitle.SetText("NEW LISTING  /  " + FENR_PDA_TradeCategory.Label(category));
    }

    protected void SetCreateStatus(string text, int color)
    {
        if (!m_CreateStatus) return;
        m_CreateStatus.SetText(text);
        m_CreateStatus.SetColor(color);
    }

    protected void PostListing()
    {
        if (m_Posting) return;
        string title = "";
        string price = "";
        string desc = "";
        if (m_TitleInput) title = m_TitleInput.GetMessage();
        if (m_PriceInput) price = m_PriceInput.GetMessage();
        if (m_DescInput) desc = m_DescInput.GetMessage();

        if (title == "") { SetCreateStatus("Enter a title for the listing.", FENR_PDA_UI_Theme.Warn()); return; }
        if (price == "") { SetCreateStatus("Enter a price or what you will trade.", FENR_PDA_UI_Theme.Warn()); return; }
        if (title.LengthUtf8() > FENR_PDA_TradeLimits.TITLE) { SetCreateStatus("Title is too long (max 32).", FENR_PDA_UI_Theme.Warn()); return; }
        if (price.LengthUtf8() > FENR_PDA_TradeLimits.PRICE) { SetCreateStatus("Price is too long (max 24).", FENR_PDA_UI_Theme.Warn()); return; }
        if (desc.LengthUtf8() > FENR_PDA_TradeLimits.DESCRIPTION) desc = desc.SubstringUtf8(0, FENR_PDA_TradeLimits.DESCRIPTION);

        m_Posting = true;
        if (m_Post) m_Post.SetEnabled(false);
        SetCreateStatus("Posting listing...", FENR_PDA_UI_Theme.Text());
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.TRADE_CREATE, new Param5<string, string, string, string, string>(m_CreateType, m_CreateCategory, title, price, desc), true);
    }

    // ------------------------------------------------------------------
    // Events
    // ------------------------------------------------------------------
    override void OnUpdate(float timeslice)
    {
        // Keep the visible board fresh while the page is open.
        m_RefreshTimer += timeslice;
        if (m_RefreshTimer >= 20.0)
        {
            m_RefreshTimer = 0;
            if (m_View == VIEW_CREATE) RequestMine();
            else RequestBoard();
        }
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_PopupOpen)
        {
            if (Clicked(m_PopupClose, w) || Clicked(m_PopupShade, w)) { ClosePopup(); return true; }
            if (Clicked(m_PopupContact, w)) { ContactLister(); return true; }
            if (Clicked(m_PopupBlock, w)) { ToggleBlockLister(); return true; }
            if (Clicked(m_PopupAdminRemove, w)) { SendUpdate(FENR_PDA_TradeAction.REMOVE); return true; }
            if (Clicked(m_PopupRemove, w)) { SendUpdate(FENR_PDA_TradeAction.REMOVE); return true; }
            if (Clicked(m_PopupRateUp, w))
            {
                if (m_PopupMyVote > 0) SendVote(0);
                else SendVote(1);
                return true;
            }
            if (Clicked(m_PopupRateDown, w))
            {
                if (m_PopupMyVote < 0) SendVote(0);
                else SendVote(-1);
                return true;
            }
            if (Clicked(m_PopupPending, w))
            {
                if (m_PopupItem.Status == FENR_PDA_TradeStatus.PENDING) SendUpdate(FENR_PDA_TradeAction.MARK_OPEN);
                else SendUpdate(FENR_PDA_TradeAction.MARK_PENDING);
                return true;
            }
            if (Clicked(m_PopupClosed, w))
            {
                if (m_PopupItem.IsClosed()) SendUpdate(FENR_PDA_TradeAction.MARK_OPEN);
                else SendUpdate(FENR_PDA_TradeAction.MARK_CLOSED);
                return true;
            }
            return true;   // swallow clicks behind the popup
        }

        if (Clicked(m_TabBuy, w)) { SetView(VIEW_BUY, true); return true; }
        if (Clicked(m_TabSell, w)) { SetView(VIEW_SELL, true); return true; }
        if (Clicked(m_TabCreate, w)) { SetView(VIEW_CREATE, true); return true; }

        if (m_View != VIEW_CREATE)
        {
            if (Clicked(m_Prev, w)) { m_Page--; RequestBoard(); return true; }
            if (Clicked(m_Next, w)) { m_Page++; RequestBoard(); return true; }
            if (Clicked(m_Filter, w))
            {
                m_FilterIndex = (m_FilterIndex + 1) % m_Categories.Count();
                m_Page = 0;
                UpdateFilterButton();
                RequestBoard();
                return true;
            }
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

        if (Clicked(m_TypeSell, w)) { SetCreateType(FENR_PDA_TradeType.SELL); return true; }
        if (Clicked(m_TypeBuy, w)) { SetCreateType(FENR_PDA_TradeType.BUY); return true; }
        for (int ci = 0; ci < m_CatButtons.Count(); ci++)
        {
            if (Clicked(m_CatButtons[ci], w))
            {
                SetCreateCategory(m_Categories[ci + 1]);
                return true;
            }
        }
        if (Clicked(m_Post, w)) { PostListing(); return true; }
        if (m_Mine)
        {
            int result = m_Mine.HandleClick(w);
            if (result == FENR_PDA_UI_RowList.RESULT_SELECT)
            {
                int row = m_Mine.GetSelected();
                if (row >= 0 && row < m_MineItems.Count()) OpenPopup(m_MineItems[row]);
                return true;
            }
            if (result != FENR_PDA_UI_RowList.RESULT_NONE) return true;
        }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_PopupOpen) return true;
        if (m_View == VIEW_CREATE) return m_Mine && m_Mine.HandleWheel(x, y, wheel);

        if (!FENR_PDA_UI_Kit.IsPointInside(m_BoardView, x, y)) return false;
        if (wheel < 0 && m_Page + 1 < m_TotalPages) { m_Page++; RequestBoard(); }
        else if (wheel > 0 && m_Page > 0) { m_Page--; RequestBoard(); }
        return true;
    }
}
