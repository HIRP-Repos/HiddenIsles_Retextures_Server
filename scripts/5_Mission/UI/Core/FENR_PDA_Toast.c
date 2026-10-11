/*
    Fenrir Industries PDA - Field OS 7.4
    HUD popup ("toast") + chime for incoming PDA traffic.

    Shown on the normal game screen while the PDA is closed.  While the PDA
    is open only the chime plays (the inbox already shows unread counts).
*/
class FENR_PDA_Toast
{
    static const int SHOW_MS = 5000;

    protected static Widget s_Root;
    protected static TextWidget s_Title;
    protected static TextWidget s_From;
    protected static TextWidget s_Body;
    protected static ImageWidget s_Icon;
    protected static EffectSound s_Chime;
    protected static EffectSound s_Alarm;
    protected static ref map<Widget, int> s_ThemeRoles;

    protected static bool EnsureWidgets()
    {
        if (s_Root) return true;
        if (!GetGame() || !GetGame().GetWorkspace()) return false;

        s_Root = GetGame().GetWorkspace().CreateWidgets("PDA/gui/os/FI_Toast.layout");
        if (!s_Root)
        {
            Print("[FENR_PDA] ERROR: FI_Toast.layout failed to load");
            return false;
        }
        s_Root.SetSort(1024);
        s_ThemeRoles = new map<Widget, int>();
        FENR_PDA_UI_Kit.RecordThemeRoles(s_Root, s_ThemeRoles);
        FENR_PDA_UI_Kit.ApplyThemeRoles(s_ThemeRoles);
        s_Title = TextWidget.Cast(s_Root.FindAnyWidget("FI_Toast_Title"));
        s_From = TextWidget.Cast(s_Root.FindAnyWidget("FI_Toast_From"));
        s_Body = TextWidget.Cast(s_Root.FindAnyWidget("FI_Toast_Body"));
        s_Icon = ImageWidget.Cast(s_Root.FindAnyWidget("FI_Toast_Icon"));
        s_Root.Show(false);
        return true;
    }

    static void OnThemeChanged()
    {
        if (s_ThemeRoles) FENR_PDA_UI_Kit.ApplyThemeRoles(s_ThemeRoles);
    }

    // S.O.S alarm (distinct from the message chime).
    static void PlayAlarm()
    {
        if (!GetGame()) return;
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player) player.PlaySoundSet(s_Alarm, "FENR_PDA_SOS_SoundSet", 0, 0);
    }

    static void PlayChime()
    {
        if (!GetGame()) return;
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player) player.PlaySoundSet(s_Chime, "FENR_PDA_Message_SoundSet", 0, 0);
    }

    protected static bool PdaOpen()
    {
        FENR_PDA_Menu menu = FENR_PDA_Menu.GetInstance();
        return menu && menu.m_active;
    }

    // title: small green header, from: bright line, body: one-line preview.
    // overPda: also show while the PDA is open (refused requests etc.).
    static void Notify(string title, string from, string body, string icon = "ic_messages", bool chime = true, bool overPda = false)
    {
        if (chime) PlayChime();
        if (PdaOpen() && !overPda) return;
        if (!EnsureWidgets()) return;

        if (s_Title)
        {
            s_Title.SetText(title);
            s_Title.SetColor(FENR_PDA_UI_Theme.Accent());
        }
        if (s_From) s_From.SetText(from);
        if (s_Body) s_Body.SetText(FENR_PDA_UI_Kit.Clip(body, 52));
        if (s_Icon)
        {
            s_Icon.LoadImageFile(0, "PDA/gui/os/textures/" + icon + ".edds");
            s_Icon.SetImage(0);
        }

        s_Root.Show(true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(HideToast);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(HideToast, SHOW_MS, false);
    }

    // S.O.S received: red title, alarm, shown over the PDA, stays longer.
    static void NotifySos(string from, string body)
    {
        PlayAlarm();
        if (!EnsureWidgets()) return;
        if (s_Title)
        {
            s_Title.SetText("!! S.O.S SIGNAL RECEIVED !!");
            s_Title.SetColor(FENR_PDA_UI_Theme.Danger());
        }
        if (s_From) s_From.SetText(from);
        if (s_Body) s_Body.SetText(FENR_PDA_UI_Kit.Clip(body, 52));
        if (s_Icon)
        {
            s_Icon.LoadImageFile(0, "PDA/gui/os/textures/ic_warning.edds");
            s_Icon.SetImage(0);
        }
        s_Root.Show(true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(HideToast);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(HideToast, SHOW_MS * 3, false);
    }

    static void HideToast()
    {
        if (s_Root) s_Root.Show(false);
    }
};
