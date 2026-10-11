/*
    Fenrir Industries PDA - Field OS 8.0
    S.O.S prompt (outside the PDA).

    Double-tapping the S.O.S key (Controls > Fenrir PDA, default End) opens
    this confirmation while a powered, logged-in PDA is carried (the server
    only accepts it from a PDA logged in as the sender).  With the PDA open the
    hotkey jumps to the PDA's own S.O.S confirmation instead.
*/
class FENR_PDA_SosPrompt extends UIScriptedMenu
{
    static const int DOUBLE_TAP_MS = 600;
    protected static int s_LastTap = -100000;
    protected static ref FENR_PDA_SosPrompt s_Prompt;   // kept alive while shown

    protected ref FENR_PDA_UI_Button m_Send;
    protected ref FENR_PDA_UI_Button m_Cancel;
    protected ref map<Widget, int> m_ThemeRoles;
    protected bool m_Locked;
    protected bool m_Done;

    override Widget Init()
    {
        if (layoutRoot) return layoutRoot;
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PDA/gui/os/FI_SOS_Prompt.layout");
        if (!layoutRoot) return null;

        m_ThemeRoles = new map<Widget, int>();
        FENR_PDA_UI_Kit.RecordThemeRoles(layoutRoot, m_ThemeRoles);
        FENR_PDA_UI_Kit.ApplyThemeRoles(m_ThemeRoles);

        m_Send = new FENR_PDA_UI_Button(ButtonWidget.Cast(layoutRoot.FindAnyWidget("FI_SOSP_Send")), FENR_PDA_UI_Button.KIND_ACTION);
        m_Cancel = new FENR_PDA_UI_Button(ButtonWidget.Cast(layoutRoot.FindAnyWidget("FI_SOSP_Cancel")), FENR_PDA_UI_Button.KIND_ACTION);
        MultilineTextWidget body = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("FI_SOSP_Body"));
        if (body)
            body.SetText("Your position goes out to this PDA's S.O.S recipients as a red ping with an alarm.\n\nThe signal burst burns out your PDA, its battery and every drive in it.");
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        if (m_Locked) return;
        m_Locked = true;
        Mission mission = GetGame().GetMission();
        if (mission) mission.PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    override void OnHide()
    {
        super.OnHide();
        Unlock();
    }

    void ~FENR_PDA_SosPrompt()
    {
        Unlock();
    }

    protected void Unlock()
    {
        if (!m_Locked || !GetGame()) return;
        m_Locked = false;
        Mission mission = GetGame().GetMission();
        if (mission) mission.PlayerControlEnable(true);
        if (GetGame().GetUIManager()) GetGame().GetUIManager().ShowUICursor(false);
    }

    protected void Finish()
    {
        if (m_Done) return;
        m_Done = true;
        GetGame().GetUIManager().HideScriptedMenu(this);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (m_Send && w == m_Send.m_Button)
        {
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_SEND, new Param1<bool>(true), true);
            Finish();
            return true;
        }
        if (m_Cancel && w == m_Cancel.m_Button)
        {
            Finish();
            return true;
        }
        return super.OnClick(w, x, y, button);
    }

    override bool OnMouseEnter(Widget w, int x, int y)
    {
        if (m_Send && w == m_Send.m_Button) m_Send.SetHover(true);
        if (m_Cancel && w == m_Cancel.m_Button) m_Cancel.SetHover(true);
        return super.OnMouseEnter(w, x, y);
    }

    override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
    {
        if (m_Send && w == m_Send.m_Button) m_Send.SetHover(false);
        if (m_Cancel && w == m_Cancel.m_Button) m_Cancel.SetHover(false);
        return super.OnMouseLeave(w, enterW, x, y);
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);
        UAInput back = GetUApi().GetInputByName("UAUIBack");
        if (back && back.LocalRelease())
            Finish();
    }

    // ------------------------------------------------------------------
    // Hotkey (called every frame from MissionGameplay.OnUpdate)
    // ------------------------------------------------------------------
    static void HandleHotkey()
    {
        UAInput input = GetUApi().GetInputByName("UAFenrPdaSOS");
        if (!input || !input.LocalPress()) return;

        int now = GetGame().GetTime();
        if (now - s_LastTap > DOUBLE_TAP_MS)
        {
            s_LastTap = now;
            return;
        }
        s_LastTap = -100000;

        FENR_PDA_Menu pda = FENR_PDA_Menu.GetInstance();
        if (pda && pda.m_active)
        {
            pda.OpenSosConfirm();
            return;
        }
        if (GetGame().GetUIManager().GetMenu() != null) return;
        if (!FENR_PDA_CompassHud.HasPoweredPda())
        {
            FENR_PDA_Toast.Notify("S.O.S UNAVAILABLE", "FENRIR SECURE NETWORK", "You need a powered PDA you are logged in on to send an S.O.S.", "ic_warning", false, true);
            return;
        }
        s_Prompt = new FENR_PDA_SosPrompt();
        if (!s_Prompt.Init())
        {
            s_Prompt = null;
            return;
        }
        GetGame().GetUIManager().ShowScriptedMenu(s_Prompt, null);
    }
}
