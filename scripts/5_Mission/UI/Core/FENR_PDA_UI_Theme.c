/*
    Fenrir Industries PDA - Field OS 8.0
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Terminal palette (themeable) + small widget helpers shared by every page.
    The layout is authored in the green reference palette; FENR_PDA_UI_Theme
    rebuilds every role from the player's colour settings.
*/
// One named colour scheme for the settings page.
class FENR_PDA_ThemePreset
{
    string Name;
    int Hue;          // 0-359
    int Saturation;   // percent of the reference saturation

    void FENR_PDA_ThemePreset(string name = "", int hue = 150, int saturation = 100)
    {
        Name = name;
        Hue = hue;
        Saturation = saturation;
    }
};

/*
    Theme engine.  The layout is authored in the green reference palette
    below; every role is rebuilt from a hue, a saturation scale and two
    brightness scales (foreground and backlight), keeping each role's own
    saturation/value so contrast stays intact in every scheme.
*/
class FENR_PDA_UI_Theme
{
    static const int ROLE_LCD = 0;
    static const int ROLE_PANEL = 1;
    static const int ROLE_CARD = 2;
    static const int ROLE_INPUT = 3;
    static const int ROLE_HOVER = 4;
    static const int ROLE_ACTIVE = 5;
    static const int ROLE_LINE = 6;
    static const int ROLE_LINEDIM = 7;
    static const int ROLE_LINEBRIGHT = 8;
    static const int ROLE_TEXT = 9;
    static const int ROLE_TEXTBRIGHT = 10;
    static const int ROLE_TEXTDIM = 11;
    static const int ROLE_TEXTOFF = 12;
    static const int ROLE_ACCENT = 13;
    static const int ROLE_COUNT = 14;
    static const int REFERENCE_HUE = 150;

    protected static ref array<int> s_Base;       // reference (layout) palette
    protected static ref array<int> s_Palette;    // current palette
    protected static ref array<ref FENR_PDA_ThemePreset> s_Presets;
    protected static int s_Version;

    protected static void EnsureBase()
    {
        if (s_Base) return;
        s_Base = new array<int>();
        s_Base.Insert(ARGB(255, 2, 18, 11));      // lcd
        s_Base.Insert(ARGB(255, 0, 22, 13));      // panel
        s_Base.Insert(ARGB(255, 0, 27, 16));      // card
        s_Base.Insert(ARGB(255, 0, 12, 7));       // input
        s_Base.Insert(ARGB(255, 3, 44, 27));      // hover
        s_Base.Insert(ARGB(255, 4, 65, 40));      // active
        s_Base.Insert(ARGB(255, 34, 138, 88));    // line
        s_Base.Insert(ARGB(255, 18, 84, 54));     // lineDim
        s_Base.Insert(ARGB(255, 80, 220, 150));   // lineBright
        s_Base.Insert(ARGB(255, 150, 236, 185));  // text
        s_Base.Insert(ARGB(255, 205, 255, 225));  // textBright
        s_Base.Insert(ARGB(255, 92, 182, 132));   // textDim
        s_Base.Insert(ARGB(255, 52, 100, 74));    // textOff
        s_Base.Insert(ARGB(255, 60, 215, 95));    // accent
        s_Palette = new array<int>();
        s_Palette.Copy(s_Base);
    }

    static int Role(int role)
    {
        EnsureBase();
        if (role < 0 || role >= ROLE_COUNT) return s_Palette[ROLE_TEXT];
        return s_Palette[role];
    }

    static int Lcd()        { return Role(ROLE_LCD); }
    static int PanelBg()    { return Role(ROLE_PANEL); }
    static int Card()       { return Role(ROLE_CARD); }
    static int InputBg()    { return Role(ROLE_INPUT); }
    static int Hover()      { return Role(ROLE_HOVER); }
    static int Active()     { return Role(ROLE_ACTIVE); }
    static int Line()       { return Role(ROLE_LINE); }
    static int LineDim()    { return Role(ROLE_LINEDIM); }
    static int LineBright() { return Role(ROLE_LINEBRIGHT); }
    static int Text()       { return Role(ROLE_TEXT); }
    static int TextBright() { return Role(ROLE_TEXTBRIGHT); }
    static int TextDim()    { return Role(ROLE_TEXTDIM); }
    static int TextOff()    { return Role(ROLE_TEXTOFF); }
    static int Accent()     { return Role(ROLE_ACCENT); }
    static int Warn()       { return ARGB(255, 230, 170, 60); }
    static int Danger()     { return ARGB(255, 225, 80, 70); }
    static int Clear()      { return ARGB(0, 0, 0, 0); }

    // Bumped on every palette change (widgets compare it to know when to recolour).
    static int Version() { return s_Version; }

    // ------------------------------------------------------------------
    // Presets
    // ------------------------------------------------------------------
    static array<ref FENR_PDA_ThemePreset> Presets()
    {
        if (!s_Presets)
        {
            s_Presets = new array<ref FENR_PDA_ThemePreset>();
            s_Presets.Insert(new FENR_PDA_ThemePreset("FENRIR GREEN", 150, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("AMBER", 36, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("ARCTIC CYAN", 188, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("BLOOD RED", 356, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("ROYAL VIOLET", 272, 90));
            s_Presets.Insert(new FENR_PDA_ThemePreset("TOXIC LIME", 92, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("COBALT", 220, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("SUNSET", 20, 100));
            s_Presets.Insert(new FENR_PDA_ThemePreset("ICE WHITE", 205, 25));
            s_Presets.Insert(new FENR_PDA_ThemePreset("MONOCHROME", 0, 0));
        }
        return s_Presets;
    }

    // ------------------------------------------------------------------
    // Palette builder
    // ------------------------------------------------------------------
    protected static bool IsBackground(int role)
    {
        return role <= ROLE_ACTIVE;
    }

    // hue 0-359, saturation / brightness / backlight in percent.
    static void Build(int hue, int saturation, int brightness, int backlight)
    {
        EnsureBase();
        for (int role = 0; role < ROLE_COUNT; role++)
        {
            int baseColor = s_Base[role];
            float h, sat, val;
            ToHsv(baseColor, h, sat, val);

            float newHue = hue + (h - REFERENCE_HUE);
            float newSat = Math.Clamp(sat * saturation / 100.0, 0, 1);
            float scale = brightness / 100.0;
            if (IsBackground(role)) scale = backlight / 100.0;
            float newVal = Math.Clamp(val * scale, 0, 1);
            s_Palette.Set(role, FromHsv(newHue, newSat, newVal, 255));
        }
        s_Version++;
    }

    // A role in another hue at reference saturation/brightness (compass custom colour).
    static int RoleForHue(int role, int hue)
    {
        EnsureBase();
        if (role < 0 || role >= ROLE_COUNT) role = ROLE_TEXT;
        float h, sat, val;
        ToHsv(s_Base[role], h, sat, val);
        return FromHsv(hue + (h - REFERENCE_HUE), sat, val, 255);
    }

    // Reference role of a layout colour (alpha ignored), or -1.
    static int MatchBaseRole(int color)
    {
        EnsureBase();
        int a, r, g, b;
        Split(color, a, r, g, b);
        for (int role = 0; role < ROLE_COUNT; role++)
        {
            int baseColor = s_Base[role];
            int ba, br, bg, bb;
            Split(baseColor, ba, br, bg, bb);
            if (Math.AbsInt(r - br) <= 2 && Math.AbsInt(g - bg) <= 2 && Math.AbsInt(b - bb) <= 2)
                return role;
        }
        return -1;
    }

    // Current colour of a role with a given alpha (0-255).
    static int RoleWithAlpha(int role, int alpha)
    {
        return WithAlpha(Role(role), alpha);
    }

    static int WithAlpha(int color, int alpha)
    {
        int a, r, g, b;
        Split(color, a, r, g, b);
        return ARGB(alpha, r, g, b);
    }

    // ARGB int -> channels using arithmetic only (Enforce has no shift operators).
    static void Split(int color, out int a, out int r, out int g, out int b)
    {
        int rest = color;
        int high = 0;
        if (rest < 0)
        {
            // alpha >= 128: lift into the positive range (2^31 in two steps).
            rest = rest + 2147483647;
            rest = rest + 1;
            high = 128;
        }
        a = high + rest / 16777216;
        rest = rest % 16777216;
        r = rest / 65536;
        g = (rest / 256) % 256;
        b = rest % 256;
    }

    // ------------------------------------------------------------------
    // HSV helpers (hue in degrees, saturation/value 0-1)
    // ------------------------------------------------------------------
    static void ToHsv(int color, out float h, out float s, out float v)
    {
        int ca, cr, cg, cb;
        Split(color, ca, cr, cg, cb);
        float r = cr / 255.0;
        float g = cg / 255.0;
        float b = cb / 255.0;
        float maxC = Math.Max(r, Math.Max(g, b));
        float minC = Math.Min(r, Math.Min(g, b));
        float delta = maxC - minC;
        v = maxC;
        s = 0;
        if (maxC > 0) s = delta / maxC;
        h = 0;
        if (delta <= 0) return;
        if (maxC == r) h = 60.0 * ((g - b) / delta);
        else if (maxC == g) h = 60.0 * ((b - r) / delta + 2.0);
        else h = 60.0 * ((r - g) / delta + 4.0);
        if (h < 0) h += 360.0;
    }

    static int FromHsv(float h, float s, float v, int alpha)
    {
        while (h < 0) h += 360.0;
        while (h >= 360.0) h -= 360.0;
        float c = v * s;
        float hp = h / 60.0;
        float hpMod = hp - Math.Floor(hp / 2.0) * 2.0;
        float x = c * (1.0 - Math.AbsFloat(hpMod - 1.0));
        float r1 = 0;
        float g1 = 0;
        float b1 = 0;
        if (hp < 1) { r1 = c; g1 = x; }
        else if (hp < 2) { r1 = x; g1 = c; }
        else if (hp < 3) { g1 = c; b1 = x; }
        else if (hp < 4) { g1 = x; b1 = c; }
        else if (hp < 5) { r1 = x; b1 = c; }
        else { r1 = c; b1 = x; }
        float m = v - c;
        int r = Math.Round((r1 + m) * 255.0);
        int g = Math.Round((g1 + m) * 255.0);
        int b = Math.Round((b1 + m) * 255.0);
        return ARGB(alpha, r, g, b);
    }

    // A swatch colour for a hue/saturation (used by the settings page).
    static int Swatch(int hue, int saturation)
    {
        return FromHsv(hue, Math.Clamp(0.72 * saturation / 100.0, 0, 1), 0.86, 255);
    }

    // Legacy names kept so any external code that still uses them compiles.
    static int Green()      { return Text(); }
    static int GreenDim()   { return TextDim(); }
    static int GreenDark()  { return Active(); }
    static int GreenDeep()  { return PanelBg(); }
    static int Black()      { return InputBg(); }
};

class FENR_PDA_UI_Kit
{
    // Records the theme role of every widget coloured with a reference
    // palette colour (role + alpha * 256).  Widgets named *Swatch* are skipped.
    static void RecordThemeRoles(Widget w, map<Widget, int> roles)
    {
        while (w)
        {
            if (w.GetName().IndexOf("Swatch") == -1)
            {
                int color = w.GetColor();
                int role = FENR_PDA_UI_Theme.MatchBaseRole(color);
                if (role >= 0)
                {
                    int ca, cr, cg, cb;
                    FENR_PDA_UI_Theme.Split(color, ca, cr, cg, cb);
                    roles.Set(w, role + ca * 256);
                }
            }
            RecordThemeRoles(w.GetChildren(), roles);
            w = w.GetSibling();
        }
    }

    static void ApplyThemeRoles(map<Widget, int> roles)
    {
        for (int i = 0; i < roles.Count(); i++)
        {
            Widget w = roles.GetKey(i);
            if (!w) continue;
            int packed = roles.GetElement(i);
            w.SetColor(FENR_PDA_UI_Theme.RoleWithAlpha(packed % 256, packed / 256));
        }
    }

    // Colours the four exact-pixel lines inside a *_Bd border frame.
    static void ColorBorder(Widget borderFrame, int color)
    {
        if (!borderFrame) return;
        Widget line = borderFrame.GetChildren();
        while (line)
        {
            line.SetColor(color);
            line = line.GetSibling();
        }
    }

    static bool EndsWith(string value, string suffix)
    {
        int vl = value.Length();
        int sl = suffix.Length();
        if (sl > vl) return false;
        return value.Substring(vl - sl, sl) == suffix;
    }

    static bool IsPointInside(Widget w, int x, int y)
    {
        if (!w || !w.IsVisibleHierarchy()) return false;
        float wx, wy, ww, wh;
        w.GetScreenPos(wx, wy);
        w.GetScreenSize(ww, wh);
        return x >= wx && x <= wx + ww && y >= wy && y <= wy + wh;
    }

    static string Pad2(int value)
    {
        return value.ToStringLen(2);
    }

    // In-game clock as HH:MM.
    static string GameTime()
    {
        int year, month, day, hour, minute;
        if (!GetGame() || !GetGame().GetWorld()) return "";
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);
        return Pad2(hour) + ":" + Pad2(minute);
    }

    // "850m" / "1.4km"
    static string Distance(float metres)
    {
        if (metres < 1000)
        {
            int m = Math.Round(metres);
            return m.ToString() + "m";
        }
        int tenths = Math.Round(metres / 100.0);
        int whole = tenths / 10;
        int frac = tenths - whole * 10;
        return whole.ToString() + "." + frac.ToString() + "km";
    }

    // Friendly names for common terrains; anything else shows its raw name.
    static string TerrainLabel(string world)
    {
        string w = world;
        w.ToLower();
        if (w == "chernarusplus") return "CHERNARUS";
        if (w == "enoch") return "LIVONIA";
        if (w == "sakhal") return "SAKHAL";
        if (w == "deerisle") return "DEER ISLE";
        if (w == "bitterroot") return "BITTERROOT";
        if (w == "namalsk") return "NAMALSK";
        if (w == "takistanplus") return "TAKISTAN";
        if (w == "esseker") return "ESSEKER";
        if (w == "banov") return "BANOV";
        if (w == "pripyat") return "PRIPYAT";
        if (w == "chiemsee") return "CHIEMSEE";
        if (w == "iztek") return "IZTEK";
        if (w == "alteria") return "ALTERIA";
        if (w == "valning") return "VALNING";
        string label = world;
        label.ToUpper();
        if (label == "") label = "UNKNOWN TERRAIN";
        return label;
    }

    static string Clip(string text, int maxChars)
    {
        if (text.LengthUtf8() <= maxChars) return text;
        return text.SubstringUtf8(0, maxChars - 3) + "...";
    }

    // Greedy word-wrap estimate used to size message cards.
    static int EstimateLines(string body, float widthPx, float fontPx)
    {
        float charW = fontPx * 0.40;   // Metron average glyph width, measured in-game
        if (charW <= 0) return 1;
        int cpl = Math.Floor(widthPx / charW);
        if (cpl < 8) cpl = 8;

        int lines = 0;
        array<string> paragraphs = new array<string>();
        body.Split("\n", paragraphs);
        if (paragraphs.Count() == 0) return 1;

        foreach (string para : paragraphs)
        {
            array<string> words = new array<string>();
            para.Split(" ", words);
            int current = 0;
            int paraLines = 1;
            foreach (string word : words)
            {
                int wl = word.LengthUtf8();
                if (current == 0)
                    current = wl;
                else if (current + 1 + wl <= cpl)
                    current += 1 + wl;
                else
                {
                    paraLines++;
                    current = wl;
                }
                while (current > cpl)
                {
                    paraLines++;
                    current -= cpl;
                }
            }
            lines += paraLines;
        }
        if (lines < 1) lines = 1;
        return lines;
    }

    // Loads the PDA textures from script as well as from the layout, so the
    // icons appear even if a layout image0 path is not resolved.
    static void LoadTextures(Widget w)
    {
        while (w)
        {
            ImageWidget img = ImageWidget.Cast(w);
            if (img)
            {
                string tex = TextureFor(img.GetName());
                if (tex != "")
                {
                    img.LoadImageFile(0, "PDA/gui/os/textures/" + tex + ".edds");
                    img.SetImage(0);
                }
            }
            LoadTextures(w.GetChildren());
            w = w.GetSibling();
        }
    }

    protected static string TextureFor(string n)
    {
        if (n == "FI_Brand") return "brand";
        if (n == "FI_Close_Icon") return "ic_power";
        if (n.IndexOf("FI_TRD_Cat") == 0 && EndsWith(n, "_Icon"))
        {
            string category = n.Substring(10, n.Length() - 15);
            return FENR_PDA_TradeCategory.Icon(category);
        }
        if (EndsWith(n, "_UpIcon")) return "ic_up";
        if (EndsWith(n, "_DownIcon")) return "ic_down";
        if (EndsWith(n, "_Prompt")) return "ic_prompt";
        if (EndsWith(n, "_Dot")) return "ic_dot";
        if (n == "FI_Nav_Messages_Icon") return "ic_messages";
        if (n == "FI_Nav_Announcements_Icon") return "ic_announcements";
        if (n == "FI_Nav_Groups_Icon") return "ic_groups";
        if (n == "FI_Nav_Trade_Icon") return "ic_trade";
        if (n == "FI_Nav_Bounties_Icon") return "ic_bounty";
        if (n == "FI_Nav_Drives_Icon") return "ic_drive";
        if (n == "FI_DRV_IntelIcon") return "ic_drive";
        if (n == "FI_DRV_EncIcon") return "ic_lock";
        if (n == "FI_DRV_BrIcon" || n == "FI_DRV_WrIcon") return "ic_lock";
        if (n.IndexOf("FI_DRV_BrDir") == 0 && EndsWith(n, "_Icon")) return "ic_folder";
        if (n == "FI_DRV_BrDirConv_Glyph") return "ic_messages";
        if (n == "FI_DRV_BrDirGroup_Glyph") return "ic_groups";
        if (n == "FI_DRV_BrDirMark_Glyph" || n == "FI_DRV_BrActIcon") return "ic_map";
        if (n == "FI_DRV_BrCorruptIcon" || n == "FI_SYS_SosIcon") return "ic_warning";
        if (n == "FI_Nav_Map_Icon") return "ic_map";
        if (n == "FI_Nav_Contacts_Icon") return "ic_contacts";
        if (n == "FI_Nav_System_Icon") return "ic_system";
        if (n == "FI_Nav_Admin_Icon") return "ic_admin";
        if (n == "FI_ADM_BcIcon") return "ic_announcements";
        if (n == "FI_ADM_IntelIcon") return "ic_drive";
        if (n == "FI_LOGIN_Brand") return "brand";
        if (n == "FI_LOGIN_Icon") return "ic_lock";
        if (n == "FI_DRV_DecIcon") return "ic_warning";
        return "";
    }
};
