/*
    Fenrir Industries PDA - Field OS 8.1
    Login screen.

    Covers the whole display while the PDA in hands is locked (or logged in
    as someone else and the player has not chosen to read it).
      LOCKED   LOG IN (session length 1-4 h, server configurable) / POWER OFF
      GUEST    VIEW READ-ONLY, or LOG IN AS ME (takes the PDA over and ends
               the other player's session)
      NO POWER only POWER OFF
*/
class FENR_PDA_LoginScreen
{
    protected FENR_PDA_Menu m_Menu;
    protected Widget m_Root;
    protected TextWidget m_Title;
    protected TextWidget m_Sub;
    protected TextWidget m_User;
    protected TextWidget m_HoursValue;
    protected MultilineTextWidget m_Status;
    protected FENR_PDA_UI_Button m_Login;
    protected FENR_PDA_UI_Button m_View;
    protected FENR_PDA_UI_Button m_Power;
    protected FENR_PDA_UI_Button m_HoursPrev;
    protected FENR_PDA_UI_Button m_HoursNext;

    protected int m_Hours = -1;
    protected bool m_Waiting;
    protected float m_WaitTimer;
    protected float m_TickTimer;

    void FENR_PDA_LoginScreen(FENR_PDA_Menu menu, Widget layoutRoot)
    {
        m_Menu = menu;
        if (!layoutRoot) return;
        m_Root = layoutRoot.FindAnyWidget("FI_LOGIN_Root");
        if (!m_Root)
        {
            Print("[FENR_PDA] UI: login screen missing from shell");
            return;
        }
        m_Title = TextWidget.Cast(m_Root.FindAnyWidget("FI_LOGIN_Title"));
        m_Sub = TextWidget.Cast(m_Root.FindAnyWidget("FI_LOGIN_Sub"));
        m_User = TextWidget.Cast(m_Root.FindAnyWidget("FI_LOGIN_User"));
        m_HoursValue = TextWidget.Cast(m_Root.FindAnyWidget("FI_LOGIN_HoursValue"));
        m_Status = MultilineTextWidget.Cast(m_Root.FindAnyWidget("FI_LOGIN_Status"));
        m_Login = menu.BindButton(m_Root, "FI_LOGIN_Login", FENR_PDA_UI_Button.KIND_ACTION);
        m_View = menu.BindButton(m_Root, "FI_LOGIN_View", FENR_PDA_UI_Button.KIND_ACTION);
        m_Power = menu.BindButton(m_Root, "FI_LOGIN_Power", FENR_PDA_UI_Button.KIND_ACTION);
        m_HoursPrev = menu.BindButton(m_Root, "FI_LOGIN_HoursPrev", FENR_PDA_UI_Button.KIND_ACTION);
        m_HoursNext = menu.BindButton(m_Root, "FI_LOGIN_HoursNext", FENR_PDA_UI_Button.KIND_ACTION);
    }

    protected FENR_PDA_Client PdaClient()
    {
        return FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
    }

    bool IsVisible()
    {
        return m_Root && m_Root.IsVisible();
    }

    void Show(bool state)
    {
        if (!m_Root) return;
        m_Root.Show(state);
        if (state)
        {
            m_Waiting = false;
            Refresh();
        }
    }

    // "1H 42M", "12M", "<1M"
    static string FormatLeft(int seconds)
    {
        int minutes = seconds / 60;
        int hours = minutes / 60;
        minutes = minutes % 60;
        if (hours > 0)
            return hours.ToString() + "H " + minutes.ToString() + "M";
        if (minutes > 0)
            return minutes.ToString() + "M";
        return "<1M";
    }

    protected void ClampHours(FENR_PDA_Client client)
    {
        if (m_Hours < 0)
            m_Hours = FENR_PDA_SettingsStore.Get().LoginHours;
        if (!client) return;
        if (m_Hours < client.MinHours()) m_Hours = client.MinHours();
        if (m_Hours > client.MaxHours()) m_Hours = client.MaxHours();
    }

    void Refresh()
    {
        if (!m_Root) return;
        FENR_PDA_Client client = PdaClient();
        ClampHours(client);

        string me = "--";
        if (client && client.m_UserDisplayName != "") me = client.m_UserDisplayName;
        if (m_User) m_User.SetText(me);

        if (m_HoursValue)
        {
            string hoursText = m_Hours.ToString() + " HOUR";
            if (m_Hours != 1) hoursText += "S";
            m_HoursValue.SetText(hoursText);
        }

        int state = -1;
        if (client) state = client.SessionState();

        string title = "CONNECTING...";
        string sub = "ESTABLISHING SECURE LINK";
        string status = "Contacting the Fenrir secure network...";
        string loginText = "LOG IN";
        bool canLogin = false;
        bool canView = false;
        bool canStep = false;

        if (state == FENR_PDA_SessionState.NO_POWER)
        {
            title = "NO POWER";
            sub = "PDA OFFLINE";
            status = "Hold a powered PDA in your hands to log in.";
        }
        else if (state == FENR_PDA_SessionState.LOCKED)
        {
            title = "AUTHENTICATION REQUIRED";
            sub = "THIS PDA IS LOCKED";
            status = "No active session.\nLog in to use this PDA. Your contacts, markers and messages follow you to any PDA you log in on.";
            canLogin = true;
            canStep = true;
        }
        else if (state == FENR_PDA_SessionState.GUEST)
        {
            string owner = client.SessionOwner();
            title = "PDA IN USE";
            sub = "LOGGED IN AS ANOTHER USER";
            status = "ACTIVE SESSION: " + owner + "  |  " + FormatLeft(client.SessionSecondsLeft()) + " LEFT\nRead it without logging in, or log in as yourself to take it over. That ends " + owner + "'s session.";
            loginText = "LOG IN AS " + me;
            canLogin = true;
            canView = true;
            canStep = true;
        }

        if (m_Waiting)
        {
            status = "Authenticating...";
            canLogin = false;
            canView = false;
        }

        if (m_Title) m_Title.SetText(title);
        if (m_Sub) m_Sub.SetText(sub);
        if (m_Status) m_Status.SetText(status);
        if (m_Login)
        {
            m_Login.SetText(loginText);
            m_Login.SetEnabled(canLogin);
        }
        if (m_View) m_View.SetEnabled(canView);
        if (m_HoursPrev) m_HoursPrev.SetEnabled(canStep && client && m_Hours > client.MinHours());
        if (m_HoursNext) m_HoursNext.SetEnabled(canStep && client && m_Hours < client.MaxHours());
    }

    protected void StepHours(int delta)
    {
        m_Hours += delta;
        ClampHours(PdaClient());
        Refresh();
    }

    protected void PressLogin()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || m_Waiting) return;
        int state = client.SessionState();
        if (state != FENR_PDA_SessionState.LOCKED && state != FENR_PDA_SessionState.GUEST) return;
        m_Waiting = true;
        m_WaitTimer = 6.0;
        client.Login(m_Hours);
        Refresh();
    }

    // Enter on the login screen logs in.
    bool Submit()
    {
        PressLogin();
        return true;
    }

    // Every click while the screen is up ends here (nothing behind it reacts).
    bool HandleClick(Widget w)
    {
        if (m_Login && w == m_Login.m_Button && m_Login.IsEnabled()) { PressLogin(); return true; }
        if (m_View && w == m_View.m_Button && m_View.IsEnabled()) { if (m_Menu) m_Menu.ViewReadOnly(); return true; }
        if (m_Power && w == m_Power.m_Button) { if (m_Menu) m_Menu.ClosePda(); return true; }
        if (m_HoursPrev && w == m_HoursPrev.m_Button && m_HoursPrev.IsEnabled()) { StepHours(-1); return true; }
        if (m_HoursNext && w == m_HoursNext.m_Button && m_HoursNext.IsEnabled()) { StepHours(1); return true; }
        return true;
    }

    void Update(float timeslice)
    {
        if (!IsVisible()) return;
        if (m_Waiting)
        {
            m_WaitTimer -= timeslice;
            if (m_WaitTimer <= 0)
            {
                // No answer: let the player try again.
                m_Waiting = false;
                Refresh();
            }
        }
        m_TickTimer -= timeslice;
        if (m_TickTimer <= 0)
        {
            m_TickTimer = 1.0;
            Refresh();
        }
    }
}
