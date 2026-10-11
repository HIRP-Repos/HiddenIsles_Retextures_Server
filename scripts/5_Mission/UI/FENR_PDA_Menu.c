/*
    Fenrir Industries PDA - Field OS 8.1
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Shell controller.
      - Loads FI_OS_Shell.layout once (guarded against a second Init call).
      - Sizes FI_Device to the largest 16:9 box that fits the screen so the
        UI always sits exactly inside the frame glass, on any aspect ratio.
      - Owns navigation, the header/status strip, the button + input registry
        (hover/focus visuals) and routes events to the active page.
      - Keeps every backend callback the rest of the mod calls.
      - v8.1: shows the login screen until the PDA is logged in, hides the
        Trade / Bounty boards when the server disables them, and blocks
        every transmitting control in read-only (guest) sessions.
*/
class FENR_PDA_Menu extends UIScriptedMenu
{
    static FENR_PDA_Menu s_Instance;

    // Read/written by FENR_PDA_Client / FENR_PDA_Server.
    bool m_active = false;
    bool m_dirty = true;
    int m_sendMessageStatus = 0;
    int m_addContactStatus = 0;

    protected Widget m_Device;
    protected Widget m_PageHost;
    protected FENR_PDA_UI_Page m_CurrentPage;

    protected ref map<Widget, ref FENR_PDA_UI_Button> m_ButtonMap;
    protected ref array<ref FENR_PDA_UI_Input> m_Inputs;
    protected ref array<MultilineTextWidget> m_ScaledTexts;

    protected FENR_PDA_UI_Button m_NavMessages;
    protected FENR_PDA_UI_Button m_NavAnnouncements;
    protected FENR_PDA_UI_Button m_NavGroups;
    protected FENR_PDA_UI_Button m_NavTrade;
    protected FENR_PDA_UI_Button m_NavBounties;
    protected FENR_PDA_UI_Button m_NavMap;
    protected FENR_PDA_UI_Button m_NavContacts;
    protected FENR_PDA_UI_Button m_NavDrives;
    protected FENR_PDA_UI_Button m_NavSystem;
    protected FENR_PDA_UI_Button m_NavAdmin;
    protected FENR_PDA_UI_Button m_ActiveNav;

    protected TextWidget m_User;
    protected TextWidget m_BattPct;
    protected TextWidget m_BatteryLine;
    protected Widget m_BattFill;
    protected float m_BattFillW;
    protected float m_BattFillH;
    protected ref array<Widget> m_SignalBars;

    protected ref FENR_PDA_PageMessages m_Messages;
    protected ref FENR_PDA_PageAnnouncements m_Announcements;
    protected ref FENR_PDA_PageGroups m_Groups;
    protected ref FENR_PDA_PageContacts m_Contacts;
    protected ref FENR_PDA_PageSystem m_System;
    protected ref FENR_PDA_PageAdmin m_Admin;
    protected ref FENR_PDA_PageTrade m_Trade;
    protected ref FENR_PDA_PageBounty m_Bounties;
    protected ref FENR_PDA_PageDrives m_Drives;
    protected ref FENR_PDA_PageMap m_Map;

    protected int m_ScreenW;
    protected int m_ScreenH;
    protected float m_TextScale = 1.0;
    protected float m_StatusTimer;
    protected int m_BatteryPercent = -1;
    protected int m_PdaUsers = -1;
    protected int m_ServerPlayers = -1;
    protected float m_NetworkTimer;
    protected bool m_MapActive;
    protected int m_UsageMode = -1;
    protected int m_EmptyReads;
    protected bool m_PdaInputLocked;
    protected bool m_PdaClosing;
    protected FENR_PDA_UI_Button m_PdaCloseButton;
    protected ref map<Widget, int> m_ThemeRoles;
    protected FENR_PDA_UI_Button m_SosQuick;

    // Login / session
    protected ref FENR_PDA_LoginScreen m_Login;
    protected bool m_GuestViewing;          // guest chose VIEW READ-ONLY
    protected TextWidget m_SessionLine;

    // Sidebar order (top to bottom) and the slot positions buttons fill.
    protected ref array<FENR_PDA_UI_Button> m_NavOrder;
    protected ref array<Widget> m_NavBoxes;
    protected ref array<float> m_NavSlotY;
    protected float m_NavSlotX;

    void ~FENR_PDA_Menu()
    {
        if (s_Instance == this) s_Instance = null;
        PdaUnlockInput();
    }

    static FENR_PDA_Menu GetInstance()
    {
        return s_Instance;
    }

    override Widget Init()
    {
        // FENR_PDA_Client.Open() calls Init() itself before ShowScriptedMenu();
        // never build a second shell if the engine calls Init() again.
        if (layoutRoot) return layoutRoot;

        s_Instance = this;
        m_ButtonMap = new map<Widget, ref FENR_PDA_UI_Button>();
        m_Inputs = new array<ref FENR_PDA_UI_Input>();
        m_ScaledTexts = new array<MultilineTextWidget>();
        m_SignalBars = new array<Widget>();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PDA/gui/os/FI_OS_Shell.layout");
        if (!layoutRoot)
        {
            Print("[FENR_PDA] ERROR: FI_OS_Shell.layout failed to load");
            return null;
        }

        m_Device = layoutRoot.FindAnyWidget("FI_Device");
        m_PageHost = layoutRoot.FindAnyWidget("FI_PageHost");
        if (!m_PageHost)
        {
            Print("[FENR_PDA] ERROR: page host missing from shell");
            return layoutRoot;
        }

        FENR_PDA_UI_Kit.LoadTextures(layoutRoot);

        // Theme: remember each widget's palette role, then apply the current scheme.
        m_ThemeRoles = new map<Widget, int>();
        FENR_PDA_UI_Kit.RecordThemeRoles(layoutRoot, m_ThemeRoles);
        FENR_PDA_UI_Kit.ApplyThemeRoles(m_ThemeRoles);

        m_NavAnnouncements = BindButton(layoutRoot, "FI_Nav_Announcements", FENR_PDA_UI_Button.KIND_NAV);
        m_NavMessages = BindButton(layoutRoot, "FI_Nav_Messages", FENR_PDA_UI_Button.KIND_NAV);
        m_NavGroups = BindButton(layoutRoot, "FI_Nav_Groups", FENR_PDA_UI_Button.KIND_NAV);
        m_NavTrade = BindButton(layoutRoot, "FI_Nav_Trade", FENR_PDA_UI_Button.KIND_NAV);
        m_NavBounties = BindButton(layoutRoot, "FI_Nav_Bounties", FENR_PDA_UI_Button.KIND_NAV);
        m_NavMap = BindButton(layoutRoot, "FI_Nav_Map", FENR_PDA_UI_Button.KIND_NAV);
        m_NavContacts = BindButton(layoutRoot, "FI_Nav_Contacts", FENR_PDA_UI_Button.KIND_NAV);
        m_NavDrives = BindButton(layoutRoot, "FI_Nav_Drives", FENR_PDA_UI_Button.KIND_NAV);
        m_NavSystem = BindButton(layoutRoot, "FI_Nav_System", FENR_PDA_UI_Button.KIND_NAV);
        m_NavAdmin = BindButton(layoutRoot, "FI_Nav_Admin", FENR_PDA_UI_Button.KIND_NAV);
        if (m_NavAdmin) m_NavAdmin.Show(false);   // revealed once the server confirms admin rights
        RecordNavSlots();

        m_PdaCloseButton = BindButton(layoutRoot, "FI_Close", FENR_PDA_UI_Button.KIND_ACTION);
        m_SosQuick = BindButton(layoutRoot, "FI_SosQuick", FENR_PDA_UI_Button.KIND_ACTION);

        m_User = TextWidget.Cast(layoutRoot.FindAnyWidget("FI_User"));
        m_SessionLine = TextWidget.Cast(layoutRoot.FindAnyWidget("FI_Local"));
        m_BattPct = TextWidget.Cast(layoutRoot.FindAnyWidget("FI_BattPct"));
        m_BatteryLine = TextWidget.Cast(layoutRoot.FindAnyWidget("FI_Battery"));
        m_BattFill = layoutRoot.FindAnyWidget("FI_BattFill");
        if (m_BattFill)
        {
            float bw, bh;
            m_BattFill.GetSize(bw, bh);
            // Layout shows 82%; store the 100% width.
            m_BattFillW = bw / 0.82;
            m_BattFillH = bh;
        }
        for (int i = 0; i < 6; i++)
        {
            Widget bar = layoutRoot.FindAnyWidget("FI_Sig" + i.ToString());
            if (bar) m_SignalBars.Insert(bar);
        }

        m_Messages = new FENR_PDA_PageMessages(this);
        m_Announcements = new FENR_PDA_PageAnnouncements(this);
        m_Groups = new FENR_PDA_PageGroups(this);
        m_Contacts = new FENR_PDA_PageContacts(this);
        m_System = new FENR_PDA_PageSystem(this);
        m_Admin = new FENR_PDA_PageAdmin(this);
        m_Trade = new FENR_PDA_PageTrade(this);
        m_Bounties = new FENR_PDA_PageBounty(this);
        m_Drives = new FENR_PDA_PageDrives(this);
        m_Map = new FENR_PDA_PageMap(this);

        m_Messages.Build(m_PageHost);
        m_Announcements.Build(m_PageHost);
        m_Groups.Build(m_PageHost);
        m_Contacts.Build(m_PageHost);
        m_System.Build(m_PageHost);
        m_Admin.Build(m_PageHost);
        m_Trade.Build(m_PageHost);
        m_Bounties.Build(m_PageHost);
        m_Drives.Build(m_PageHost);
        m_Map.Build(m_PageHost);

        // Until the server says otherwise the PDA shows its login screen.
        m_Login = new FENR_PDA_LoginScreen(this, layoutRoot);
        m_Login.Show(true);

        CollectScaledTexts(layoutRoot);
        FitDevice();

        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (client)
        {
            ref array<string> ids = new array<string>();
            foreach (FENR_PDA_Contact c : client.m_Contacts)
            {
                if (c) ids.Insert(c.m_UID);
            }
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.CHECK_CONTACTS, new Param1<ref array<string>>(ids), true);
        }
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.USER_ID, new Param1<string>(""), true);
        m_Admin.RequestStatus();

        SetActiveNav(m_NavMessages);
        ShowPage(m_Messages);
        RefreshDataPages();
        UpdateStatus();
        m_active = true;
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        if (layoutRoot) layoutRoot.Show(true);
        m_ScreenW = 0;   // force a re-fit in case the resolution changed
        FitDevice();
        PdaLockInput();
        FENR_PDA_Toast.HideToast();
        SendUsage();
    }

    override void OnHide()
    {
        super.OnHide();
        m_active = false;
        PdaUnlockInput();
        SendUsage();

        // Decrypted intel left open burns its drive out now.
        if (m_Drives) m_Drives.OnPdaClosed();

        // Drop the device token: the next open reloads whichever PDA the
        // player carries then.
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (client) client.OnMenuClosed();
    }

    // ------------------------------------------------------------------
    // Battery usage reporting (server drains the PDA's 9V cell)
    // ------------------------------------------------------------------
    void SetMapActive(bool state)
    {
        m_MapActive = state;
        SendUsage();
    }

    protected void SendUsage()
    {
        int mode = FENR_PDA_Power.MODE_CLOSED;
        if (m_active && !m_PdaClosing)
        {
            mode = FENR_PDA_Power.MODE_OPEN;
            if (m_MapActive) mode = FENR_PDA_Power.MODE_MAP;
        }
        if (mode == m_UsageMode) return;
        m_UsageMode = mode;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.PDA_USAGE, new Param1<int>(mode), true);
    }

    // ------------------------------------------------------------------
    // Input lock: while the PDA is open the mouse drives the cursor only.
    // ------------------------------------------------------------------
    protected void PdaLockInput()
    {
        if (m_PdaInputLocked) return;
        m_PdaInputLocked = true;

        Mission mission = GetGame().GetMission();
        if (mission) mission.PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetInputController()) player.GetInputController().SetDisabled(true);
    }

    protected void PdaUnlockInput()
    {
        if (!m_PdaInputLocked) return;
        m_PdaInputLocked = false;

        if (!GetGame()) return;
        Mission mission = GetGame().GetMission();
        if (mission) mission.PlayerControlEnable(true);
        if (GetGame().GetUIManager()) GetGame().GetUIManager().ShowUICursor(false);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetInputController()) player.GetInputController().SetDisabled(false);
    }

    // Single close path used by the power button, Escape and FENR_PDA_Client.Close().
    void ClosePda()
    {
        if (m_PdaClosing) return;
        m_PdaClosing = true;
        m_active = false;
        SetFocus(null);
        PdaUnlockInput();
        SendUsage();
        GetGame().GetUIManager().HideScriptedMenu(this);
    }

    bool IsPdaClosing() { return m_PdaClosing; }

    // ------------------------------------------------------------------
    // Registry used by pages and controls
    // ------------------------------------------------------------------
    FENR_PDA_UI_Button BindButton(Widget root, string name, int kind)
    {
        if (!root) return null;
        ButtonWidget w = ButtonWidget.Cast(root.FindAnyWidget(name));
        if (!w)
        {
            Print("[FENR_PDA] UI: button missing: " + name);
            return null;
        }
        FENR_PDA_UI_Button existing = m_ButtonMap.Get(w);
        if (existing) return existing;
        FENR_PDA_UI_Button button = new FENR_PDA_UI_Button(w, kind);
        m_ButtonMap.Insert(w, button);
        return button;
    }

    FENR_PDA_UI_Input BindInput(Widget root, string name)
    {
        FENR_PDA_UI_Input input = new FENR_PDA_UI_Input(root, name);
        m_Inputs.Insert(input);
        if (!input.m_Edit) Print("[FENR_PDA] UI: input missing: " + name);
        return input;
    }

    float GetTextScale() { return m_TextScale; }

    protected void CollectScaledTexts(Widget w)
    {
        while (w)
        {
            MultilineTextWidget mt = MultilineTextWidget.Cast(w);
            // Chat cards size their own text.
            if (mt && !mt.GetName().Contains("_Card"))
                m_ScaledTexts.Insert(mt);
            CollectScaledTexts(w.GetChildren());
            w = w.GetSibling();
        }
    }

    // Largest 16:9 box that fits the screen (the frame art is 1600x900).
    protected void FitDevice()
    {
        int sw, sh;
        GetScreenSize(sw, sh);
        if (sw <= 0 || sh <= 0) return;
        if (sw == m_ScreenW && sh == m_ScreenH) return;
        m_ScreenW = sw;
        m_ScreenH = sh;

        float w = sw * 0.98;
        float h = w * 9.0 / 16.0;
        if (h > sh * 0.97)
        {
            h = sh * 0.97;
            w = h * 16.0 / 9.0;
        }
        if (m_Device) m_Device.SetSize(w, h);

        // Glass area is 61.556% of the device height; 554 px is the
        // reference glass height every layout value was authored against.
        m_TextScale = (h * 0.61556) / 554.0;
        int px = Math.Round(15 * m_TextScale);
        if (px < 8) px = 8;
        foreach (MultilineTextWidget mt : m_ScaledTexts)
        {
            if (mt) mt.SetTextExactSize(px);
        }
        if (m_Messages) m_Messages.Invalidate();
        if (m_Groups) m_Groups.Invalidate();
        if (m_Admin) m_Admin.Invalidate();
    }

    // ------------------------------------------------------------------
    // Navigation
    // ------------------------------------------------------------------
    protected void HideAllPages()
    {
        if (m_Messages) m_Messages.Show(false);
        if (m_Announcements) m_Announcements.Show(false);
        if (m_Groups) m_Groups.Show(false);
        if (m_Trade) m_Trade.Show(false);
        if (m_Bounties) m_Bounties.Show(false);
        if (m_Drives) m_Drives.Show(false);
        if (m_Map) m_Map.Show(false);
        if (m_Contacts) m_Contacts.Show(false);
        if (m_System) m_System.Show(false);
        if (m_Admin) m_Admin.Show(false);
    }

    // ------------------------------------------------------------------
    // Sidebar: hidden boards leave no gaps (buttons move up a slot).
    // ------------------------------------------------------------------
    protected void RecordNavSlots()
    {
        m_NavOrder = new array<FENR_PDA_UI_Button>();
        m_NavBoxes = new array<Widget>();
        m_NavSlotY = new array<float>();
        array<string> keys = {"Announcements", "Messages", "Groups", "Trade", "Bounties", "Map", "Contacts", "Drives", "System", "Admin"};
        foreach (string key : keys)
        {
            Widget box = layoutRoot.FindAnyWidget("FI_Nav_" + key + "_Box");
            FENR_PDA_UI_Button button = NavButton(key);
            if (!box || !button) continue;
            float x, y;
            box.GetPos(x, y);
            m_NavSlotX = x;
            m_NavSlotY.Insert(y);
            m_NavBoxes.Insert(box);
            m_NavOrder.Insert(button);
        }
    }

    protected FENR_PDA_UI_Button NavButton(string key)
    {
        if (key == "Announcements") return m_NavAnnouncements;
        if (key == "Messages") return m_NavMessages;
        if (key == "Groups") return m_NavGroups;
        if (key == "Trade") return m_NavTrade;
        if (key == "Bounties") return m_NavBounties;
        if (key == "Map") return m_NavMap;
        if (key == "Contacts") return m_NavContacts;
        if (key == "Drives") return m_NavDrives;
        if (key == "System") return m_NavSystem;
        if (key == "Admin") return m_NavAdmin;
        return null;
    }

    protected bool NavAllowed(FENR_PDA_UI_Button button)
    {
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (button == m_NavTrade) return !client || client.TradeEnabled();
        if (button == m_NavBounties) return !client || client.BountyEnabled();
        if (button == m_NavAdmin) return m_Admin && m_Admin.IsAdmin();
        return true;
    }

    protected void LayoutNav()
    {
        if (!m_NavOrder) return;
        int slot = 0;
        for (int i = 0; i < m_NavOrder.Count(); i++)
        {
            FENR_PDA_UI_Button button = m_NavOrder[i];
            bool show = NavAllowed(button);
            button.Show(show);
            if (!show) continue;
            if (slot < m_NavSlotY.Count())
                m_NavBoxes[i].SetPos(m_NavSlotX, m_NavSlotY[slot]);
            slot++;
        }
        // The page in view lost its button: back to the inbox.
        if (m_ActiveNav && !NavAllowed(m_ActiveNav))
        {
            SetActiveNav(m_NavMessages);
            ShowPage(m_Messages);
        }

        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (m_SosQuick) m_SosQuick.Show(!client || client.SosEnabled());
    }

    // ------------------------------------------------------------------
    // Login session
    // ------------------------------------------------------------------
    // SESSION_STATE arrived (or changed).
    void OnSessionState()
    {
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (!client) return;
        int state = client.SessionState();
        bool wasLocked = m_Login && m_Login.IsVisible();

        if (state == FENR_PDA_SessionState.OWNER)
        {
            m_GuestViewing = false;
            ShowLogin(false);
            if (m_Admin) m_Admin.RequestStatus();
        }
        else
        {
            if (state != FENR_PDA_SessionState.GUEST) m_GuestViewing = false;
            ShowLogin(state != FENR_PDA_SessionState.GUEST || !m_GuestViewing);
            AdminReceiveStatus(false, "");
        }
        LayoutNav();
        if (wasLocked && m_Login && !m_Login.IsVisible() && m_CurrentPage)
            m_CurrentPage.OnShown();
        UpdateStatus();
        m_dirty = true;
    }

    protected void ShowLogin(bool state)
    {
        if (!m_Login) return;
        if (state) SetFocus(null);
        m_Login.Show(state);
    }

    // Guest pressed VIEW READ-ONLY.
    void ViewReadOnly()
    {
        m_GuestViewing = true;
        ShowLogin(false);
        if (m_CurrentPage) m_CurrentPage.OnShown();
        m_dirty = true;
    }

    // SYSTEM > LOG OUT (a guest just stops reading).
    void LogoutPressed()
    {
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (!client) return;
        if (client.IsGuest())
        {
            m_GuestViewing = false;
            ShowLogin(true);
            return;
        }
        client.Logout();
    }

    bool IsLoginShown()
    {
        return m_Login && m_Login.IsVisible();
    }

    // Controls that transmit or change data (blocked in guest sessions; the
    // server refuses them anyway).
    protected bool IsWriteControl(string n)
    {
        if (n == "FI_MSG_Send" || n == "FI_GRP_Send" || n == "FI_GRP_Create" || n == "FI_GRP_Rename") return true;
        if (n == "FI_GRP_Leave" || n == "FI_GRP_RemoveMember" || n == "FI_GRP_AddMember" || n == "FI_GRP_Delete") return true;
        if (n == "FI_CON_Add" || n == "FI_CON_Block" || n == "FI_CON_Rename" || n == "FI_CON_Remove") return true;
        if (n == "FI_CON_RateUp" || n == "FI_CON_RateDown") return true;
        if (n == "FI_TRD_Post" || n == "FI_TRD_PopupContact" || n == "FI_TRD_PopupBlock") return true;
        if (n == "FI_TRD_PopupRateUp" || n == "FI_TRD_PopupRateDown" || n == "FI_TRD_PopupPending") return true;
        if (n == "FI_TRD_PopupClosed" || n == "FI_TRD_PopupRemove" || n == "FI_TRD_PopupAdminRemove") return true;
        if (n == "FI_BNT_Post" || n == "FI_BNT_PopupClaimBtn" || n == "FI_BNT_PopupContact" || n == "FI_BNT_PopupContactClaimer") return true;
        if (n == "FI_BNT_PopupConfirm" || n == "FI_BNT_PopupReject" || n == "FI_BNT_PopupCancel" || n == "FI_BNT_PopupAdminRemove") return true;
        if (n == "FI_MAP_AddHere" || n == "FI_MAP_Delete" || n == "FI_SosQuick") return true;
        if (n == "FI_DRV_BrImport" || n == "FI_DRV_BrImport2") return true;
        if (n.IndexOf("FI_SYS_Sos") == 0) return true;
        return false;
    }

    protected void SetActiveNav(FENR_PDA_UI_Button button)
    {
        if (m_ActiveNav && m_ActiveNav != button) m_ActiveNav.SetActive(false);
        m_ActiveNav = button;
        if (m_ActiveNav) m_ActiveNav.SetActive(true);
    }

    void ShowPage(FENR_PDA_UI_Page page)
    {
        if (!page) return;
        if (m_CurrentPage) m_CurrentPage.OnHidden();
        HideAllPages();
        m_CurrentPage = page;
        m_CurrentPage.Show(true);
        m_CurrentPage.OnShown();
    }

    protected bool HandleNav(Widget w)
    {
        if (m_NavAnnouncements && w == m_NavAnnouncements.m_Button) { SetActiveNav(m_NavAnnouncements); ShowPage(m_Announcements); return true; }
        if (m_NavMessages && w == m_NavMessages.m_Button) { SetActiveNav(m_NavMessages); ShowPage(m_Messages); return true; }
        if (m_NavGroups && w == m_NavGroups.m_Button) { SetActiveNav(m_NavGroups); ShowPage(m_Groups); return true; }
        if (m_NavTrade && w == m_NavTrade.m_Button && NavAllowed(m_NavTrade)) { SetActiveNav(m_NavTrade); ShowPage(m_Trade); return true; }
        if (m_NavBounties && w == m_NavBounties.m_Button && NavAllowed(m_NavBounties)) { SetActiveNav(m_NavBounties); ShowPage(m_Bounties); return true; }
        if (m_NavMap && w == m_NavMap.m_Button) { SetActiveNav(m_NavMap); ShowPage(m_Map); return true; }
        if (m_NavContacts && w == m_NavContacts.m_Button) { SetActiveNav(m_NavContacts); ShowPage(m_Contacts); return true; }
        if (m_NavDrives && w == m_NavDrives.m_Button) { SetActiveNav(m_NavDrives); ShowPage(m_Drives); return true; }
        if (m_NavSystem && w == m_NavSystem.m_Button) { SetActiveNav(m_NavSystem); ShowPage(m_System); return true; }
        if (m_NavAdmin && w == m_NavAdmin.m_Button && m_Admin && m_Admin.IsAdmin()) { SetActiveNav(m_NavAdmin); ShowPage(m_Admin); return true; }
        return false;
    }

    void RefreshDataPages()
    {
        if (m_Messages) m_Messages.Refresh();
        if (m_Announcements) m_Announcements.Refresh();
        if (m_Contacts) m_Contacts.Refresh();
        m_dirty = false;
    }

    void OpenConversation(int contactIndex)
    {
        if (!m_Messages) return;
        SetActiveNav(m_NavMessages);
        ShowPage(m_Messages);
        m_Messages.OpenDirectContact(contactIndex);
    }

    // Called by the mission bridge when Enter is pressed.
    bool SendCurrentMessage()
    {
        if (m_Login && m_Login.IsVisible()) return m_Login.Submit();
        if (!m_CurrentPage) return false;
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (client && client.IsGuest() && m_CurrentPage != m_Admin)
        {
            client.NotifyReadOnly();
            return true;
        }
        return m_CurrentPage.Submit();
    }

    // ------------------------------------------------------------------
    // Header / sidebar status
    // ------------------------------------------------------------------
    protected int ReadBatteryPercent()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player) return -1;

        FENR_PDA_Device device = FENR_PDA_Device.Cast(player.GetItemInHands());
        if (!device)
        {
            array<EntityAI> items = new array<EntityAI>();
            player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
            foreach (EntityAI item : items)
            {
                device = FENR_PDA_Device.Cast(item);
                if (device) break;
            }
        }
        if (!device) return -1;

        // The attachment slot is reliable on the client; the energy source
        // link is not always synced.
        EntityAI battery = device.FindAttachmentBySlotName("BatteryD");
        if (!battery && device.GetCompEM()) battery = device.GetCompEM().GetEnergySource();
        if (!battery || !battery.GetCompEM()) return -1;
        float pct = battery.GetCompEM().GetEnergy0To100();
        int result = Math.Round(pct);
        return Math.Clamp(result, 0, 100);
    }

    protected void UpdateStatus()
    {
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (m_User)
        {
            string name = "CONNECTING...";
            if (client && client.m_UserDisplayName != "") name = client.m_UserDisplayName;
            if (client && client.IsGuest()) name = client.SessionOwner() + " [READ-ONLY]";
            m_User.SetText("USER: " + name);
        }
        if (m_SessionLine && client)
        {
            string line = "PDA LOCKED";
            if (client.IsLoggedIn())
            {
                line = "SESSION: " + FENR_PDA_LoginScreen.FormatLeft(client.SessionSecondsLeft());
                if (client.IsGuest()) line = "READ-ONLY: " + FENR_PDA_LoginScreen.FormatLeft(client.SessionSecondsLeft());
            }
            m_SessionLine.SetText(line);
            if (client.IsGuest()) m_SessionLine.SetColor(FENR_PDA_UI_Theme.Warn());
            else m_SessionLine.SetColor(FENR_PDA_UI_Theme.Text());
        }

        m_BatteryPercent = ReadBatteryPercent();

        // A flat cell shuts the PDA down (two consecutive empty reads so a
        // single unsynced frame can never close it).
        if (m_BatteryPercent == 0) m_EmptyReads++;
        else m_EmptyReads = 0;
        if (m_EmptyReads >= 2 && m_active && !m_PdaClosing)
        {
            ClosePda();
            FENR_PDA_Toast.Notify("PDA BATTERY DEPLETED", "FI-PDA-01 SHUTTING DOWN", "Replace the 9V battery to keep using your PDA.", "ic_power", false);
            return;
        }
        string pctText = "--";
        string lineText = "BATTERY: NO CELL";
        float fill = 0;
        int fillColor = FENR_PDA_UI_Theme.Accent();
        if (m_BatteryPercent >= 0)
        {
            pctText = m_BatteryPercent.ToString() + "%";
            lineText = "BATTERY: " + pctText;
            fill = m_BatteryPercent / 100.0;
            if (m_BatteryPercent <= 15) fillColor = FENR_PDA_UI_Theme.Danger();
            else if (m_BatteryPercent <= 35) fillColor = FENR_PDA_UI_Theme.Warn();
        }
        if (m_BattPct) m_BattPct.SetText(pctText);
        if (m_BatteryLine) m_BatteryLine.SetText(lineText);
        if (m_BattFill)
        {
            m_BattFill.Show(fill > 0);
            m_BattFill.SetSize(m_BattFillW * fill, m_BattFillH);
            m_BattFill.SetColor(fillColor);
        }

        // Signal: full while the PDA is connected and has power.
        int lit = 4;
        if (m_BatteryPercent == 0) lit = 0;
        for (int i = 0; i < m_SignalBars.Count(); i++)
        {
            if (i < lit) m_SignalBars[i].SetColor(FENR_PDA_UI_Theme.Accent());
            else m_SignalBars[i].SetColor(FENR_PDA_UI_Theme.LineDim());
        }

        m_NetworkTimer -= 1.0;
        if (m_NetworkTimer <= 0)
        {
            m_NetworkTimer = 15.0;
            RequestNetworkStatus();
        }

        if (m_System) m_System.UpdateInfo(m_BatteryPercent, m_PdaUsers, m_ServerPlayers);
    }

    // ------------------------------------------------------------------
    // Events
    // ------------------------------------------------------------------
    override bool OnClick(Widget w, int x, int y, int button)
    {
        super.OnClick(w, x, y, button);
        if (m_PdaCloseButton && w == m_PdaCloseButton.m_Button) { ClosePda(); return true; }
        if (m_Login && m_Login.IsVisible()) return m_Login.HandleClick(w);
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (w && client && client.IsGuest() && IsWriteControl(w.GetName()))
        {
            client.NotifyReadOnly();
            return true;
        }
        if (m_SosQuick && w == m_SosQuick.m_Button) { OpenSosConfirm(); return true; }
        if (HandleNav(w)) return true;
        if (m_CurrentPage && m_CurrentPage.HandleClick(w, x, y, button)) return true;
        return false;
    }

    override bool OnMouseEnter(Widget w, int x, int y)
    {
        super.OnMouseEnter(w, x, y);
        FENR_PDA_UI_Button button = m_ButtonMap.Get(w);
        if (button)
        {
            button.SetHover(true);
            return true;
        }
        return false;
    }

    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
    {
        super.OnMouseLeave(w, enterW, x, y);
        FENR_PDA_UI_Button button = m_ButtonMap.Get(w);
        if (button)
        {
            button.SetHover(false);
            return true;
        }
        return false;
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button)
    {
        super.OnDoubleClick(w, x, y, button);
        if (m_Login && m_Login.IsVisible()) return true;
        if (m_CurrentPage && m_CurrentPage.HandleDoubleClick(w, x, y, button)) return true;
        return false;
    }

    override bool OnMouseWheel(Widget w, int x, int y, int wheel)
    {
        super.OnMouseWheel(w, x, y, wheel);
        if (m_CurrentPage && m_CurrentPage.HandleWheel(w, x, y, wheel)) return true;
        return false;
    }

    override bool OnFocus(Widget w, int x, int y)
    {
        super.OnFocus(w, x, y);
        foreach (FENR_PDA_UI_Input input : m_Inputs)
        {
            if (input && input.m_Edit == w) input.SetFocused(true);
        }
        return false;
    }

    override bool OnFocusLost(Widget w, int x, int y)
    {
        super.OnFocusLost(w, x, y);
        foreach (FENR_PDA_UI_Input input : m_Inputs)
        {
            if (input && input.m_Edit == w) input.SetFocused(false);
        }
        return false;
    }

    override bool OnChange(Widget w, int x, int y, bool finished)
    {
        super.OnChange(w, x, y, finished);
        if (m_CurrentPage && m_CurrentPage.HandleChange(w, x, y, finished)) return true;
        return false;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);
        if (!layoutRoot || m_PdaClosing) return;

        // Escape / UI back closes the PDA.  Acting on release (not press)
        // keeps the game from also opening its pause menu on the same frame.
        UAInput back = GetUApi().GetInputByName("UAUIBack");
        if (back && back.LocalRelease())
        {
            ClosePda();
            return;
        }

        FitDevice();

        if (m_dirty || m_sendMessageStatus == 2 || m_addContactStatus == 2)
        {
            RefreshDataPages();
            m_sendMessageStatus = 0;
            m_addContactStatus = 0;
        }

        foreach (FENR_PDA_UI_Input input : m_Inputs)
        {
            if (input) input.Update();
        }

        if (m_Login && m_Login.IsVisible()) m_Login.Update(timeslice);
        else if (m_CurrentPage) m_CurrentPage.OnUpdate(timeslice);

        m_StatusTimer += timeslice;
        if (m_StatusTimer >= 1.0)
        {
            m_StatusTimer = 0;
            UpdateStatus();
        }
    }

    override bool OnKeyDown(Widget w, int x, int y, int key)
    {
        // Escape is handled on release in Update() / the mission bridge.
        if (key == KeyCode.KC_ESCAPE) return true;
        return super.OnKeyDown(w, x, y, key);
    }

    // ------------------------------------------------------------------
    // Group service callback adapters
    // ------------------------------------------------------------------
    void GroupReceiveList(array<string> ids, array<string> names, array<string> ownerIDs, array<string> unread)
    {
        if (m_Groups) m_Groups.ReceiveList(ids, names, ownerIDs, unread);
    }

    void GroupReceiveMembers(string groupID, array<string> ids, array<string> rows, string ownerID)
    {
        if (m_Groups) m_Groups.ReceiveMembers(groupID, ids, rows, ownerID);
    }

    void GroupReceiveHistory(string groupID, array<string> senderNames, array<string> bodies, array<string> times)
    {
        if (m_Groups) m_Groups.ReceiveHistory(groupID, senderNames, bodies, times);
    }

    void GroupReceiveIncoming(string groupID, string groupName, string senderName, string messageText)
    {
        if (m_Groups) m_Groups.ReceiveIncoming(groupID, groupName, senderName, messageText);
    }

    void GroupReceiveRefresh(string groupID)
    {
        if (m_Groups) m_Groups.ReceiveRefresh(groupID);
    }

    void GroupReceiveActionResult(string action, bool success, string info, string groupID)
    {
        if (m_Groups) m_Groups.ReceiveActionResult(action, success, info, groupID);
    }

    // ------------------------------------------------------------------
    // Trade board callbacks
    // ------------------------------------------------------------------
    void TradeReceiveList(array<string> fields, int total, int page, string board)
    {
        if (m_Trade) m_Trade.ReceiveList(fields, total, page, board);
    }

    void TradeReceiveResult(string action, bool success, string info)
    {
        if (m_Trade) m_Trade.ReceiveResult(action, success, info);
        if (action == "RATE" && m_Contacts) m_Contacts.ReceiveRateResult(success, info);
    }

    void RepReceive(string targetID, int score, int count, int myVote, bool canRate)
    {
        if (m_Trade) m_Trade.ReceiveRep(targetID, score, count, myVote, canRate);
        if (m_Contacts) m_Contacts.ReceiveRep(targetID, score, count, myVote, canRate);
    }

    void BountyReceiveList(array<string> fields, int total, int page, string board)
    {
        if (m_Bounties) m_Bounties.ReceiveList(fields, total, page, board);
    }

    void BountyReceiveResult(string action, bool success, string info)
    {
        if (m_Bounties) m_Bounties.ReceiveResult(action, success, info);
    }

    void BountyRefresh()
    {
        if (m_Bounties) m_Bounties.RefreshFromServer();
    }

    // ------------------------------------------------------------------
    // Drives
    // ------------------------------------------------------------------
    void DriveReceiveStatus(array<string> kinds, array<string> present, array<string> summaries)
    {
        if (m_Drives) m_Drives.ReceiveStatus(kinds, present, summaries);
    }

    void DriveReceiveData(string kind, bool success, string info, array<string> payload)
    {
        if (m_Drives) m_Drives.ReceiveData(kind, success, info, payload);
    }

    void DriveReceiveResult(string kind, bool success, string info)
    {
        if (m_Drives) m_Drives.ReceiveResult(kind, success, info);
        // Intel files are written from ADMIN > INTEL.
        if (m_Admin && kind == FENR_PDA_DriveKind.INTEL) m_Admin.ReceiveIntelResult(success, info);
    }

    // The PDA's memory arrived from the server.
    void OnDeviceSynced()
    {
        if (m_Map) m_Map.ReloadMarkers();
        if (m_System) m_System.OnDeviceSynced();
        if (m_Messages) m_Messages.Invalidate();
        if (m_Drives) m_Drives.OnDeviceSynced();
        m_dirty = true;
    }

    void OnMarkersChanged()
    {
        if (m_Map) m_Map.ReloadMarkers();
    }

    void DriveReceiveFile(int index, bool success, string info, array<string> fields)
    {
        if (m_Drives) m_Drives.ReceiveFile(index, success, info, fields);
    }

    void DriveReceiveSource(string kind, string id, array<string> fields)
    {
        if (m_Drives) m_Drives.ReceiveSource(kind, id, fields);
        if (m_System && kind == "GROUPS") m_System.ReceiveGroups(fields);
    }

    // ------------------------------------------------------------------
    // Theme / S.O.S
    // ------------------------------------------------------------------
    // Settings changed: recolour the layout and every scripted control.
    void OnThemeChanged()
    {
        if (m_ThemeRoles) FENR_PDA_UI_Kit.ApplyThemeRoles(m_ThemeRoles);
        for (int i = 0; i < m_ButtonMap.Count(); i++)
        {
            FENR_PDA_UI_Button button = m_ButtonMap.GetElement(i);
            if (button) button.Apply();
        }
        foreach (FENR_PDA_UI_Input input : m_Inputs)
        {
            if (input) input.RefreshColors();
        }
        if (m_Messages) m_Messages.Invalidate();
        if (m_Groups) m_Groups.Invalidate();
        if (m_Admin) m_Admin.Invalidate();
        if (m_System) m_System.OnThemeChanged();
        if (m_CurrentPage) m_CurrentPage.Refresh();
        m_dirty = true;
        UpdateStatus();
    }

    void SosReceiveConfig(string mode, array<string> targets, string groupID, int maxContacts)
    {
        if (m_System) m_System.ReceiveSosConfig(mode, targets, groupID, maxContacts);
    }

    void SosReceiveResult(bool success, string info)
    {
        if (m_System) m_System.ReceiveSosResult(success, info);
    }

    // S.O.S hotkey while the PDA is open: go to the S.O.S confirmation.
    void OpenSosConfirm()
    {
        if (!m_System || (m_Login && m_Login.IsVisible())) return;
        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        if (client && !client.CanWrite()) return;
        SetActiveNav(m_NavSystem);
        ShowPage(m_System);
        m_System.OpenSosConfirm();
    }

    bool IsAdminUser()
    {
        return m_Admin && m_Admin.IsAdmin();
    }

    // ------------------------------------------------------------------
    // Network status (PDA users online)
    // ------------------------------------------------------------------
    protected void RequestNetworkStatus()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.NETWORK_STATUS, new Param1<bool>(true), true);
    }

    void NetworkReceiveStatus(int pdaUsers, int playerCount)
    {
        m_PdaUsers = pdaUsers;
        m_ServerPlayers = playerCount;
        if (m_System) m_System.UpdateInfo(m_BatteryPercent, m_PdaUsers, m_ServerPlayers);
    }

    // ------------------------------------------------------------------
    // Admin service callback adapters
    // ------------------------------------------------------------------
    void AdminReceiveStatus(bool isAdmin, string retentionSummary)
    {
        if (m_Admin) m_Admin.SetAuthorized(isAdmin, retentionSummary);
        LayoutNav();
        if (!isAdmin && m_Admin && m_CurrentPage == m_Admin)
        {
            SetActiveNav(m_NavMessages);
            ShowPage(m_Messages);
        }
    }

    void AdminReceiveSearch(array<string> headers, array<string> bodies, int total, int page, int pageSize)
    {
        if (m_Admin) m_Admin.ReceiveSearch(headers, bodies, total, page, pageSize);
    }

    void AdminReceivePlayers(array<string> ids, array<string> rows)
    {
        if (m_Admin) m_Admin.ReceivePlayers(ids, rows);
    }

    void AdminReceiveBroadcastResult(bool success)
    {
        if (m_Admin) m_Admin.ReceiveBroadcastResult(success);
    }
}
