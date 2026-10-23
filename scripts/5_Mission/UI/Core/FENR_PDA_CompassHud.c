/*
    Fenrir Industries PDA - Field OS 8.0
    Compass HUD.

    Shown while the player carries a powered, logged-in PDA (and no menu is
    open); a PDA logged in as someone else shows that player's markers:
    a heading strip with cardinal points, bearing numbers, the PDA's map
    markers as amber dots and received S.O.S pings as red beacons.
    Everything is configurable on SYSTEM > COMPASS (FENR_PDA_Settings).
*/
class FENR_PDA_CompassHud
{
    static const float FOV = 180.0;
    static const int MAX_MARKS = 40;
    static const int MAX_PINGS = 6;

    protected static ref FENR_PDA_CompassHud s_Instance;

    protected Widget m_Root;
    protected TextWidget m_Heading;
    protected Widget m_HeadBG;
    protected Widget m_BG;
    protected Widget m_LineT;
    protected Widget m_LineB;
    protected Widget m_Caret;
    protected ref array<Widget> m_Ticks;
    protected ref array<TextWidget> m_Labels;
    protected ref array<TextWidget> m_Numbers;
    protected ref array<Widget> m_Dots;
    protected ref array<TextWidget> m_DotTexts;
    protected ref array<Widget> m_Pings;
    protected ref array<TextWidget> m_PingTexts;

    protected bool m_Failed;
    protected bool m_Visible;
    protected bool m_LayoutDirty = true;
    protected bool m_HasDevice;
    protected float m_CheckTimer;
    protected EntityAI m_LastDevice;
    protected bool m_AwaitingMarkers;
    protected int m_RequestTime;

    protected int m_ColText;
    protected int m_ColBright;
    protected int m_ColDim;
    protected int m_ColLine;
    protected int m_ColAccent;
    protected int m_ColBg;

    void FENR_PDA_CompassHud()
    {
        m_Ticks = new array<Widget>();
        m_Labels = new array<TextWidget>();
        m_Numbers = new array<TextWidget>();
        m_Dots = new array<Widget>();
        m_DotTexts = new array<TextWidget>();
        m_Pings = new array<Widget>();
        m_PingTexts = new array<TextWidget>();
    }

    void ~FENR_PDA_CompassHud()
    {
        if (m_Root) m_Root.Unlink();
    }

    // Called every frame from MissionGameplay.OnUpdate.
    static void Tick(float timeslice)
    {
        if (!s_Instance) s_Instance = new FENR_PDA_CompassHud();
        s_Instance.Update(timeslice);
    }

    // Mission ending (logout, kick): remove the HUD widgets.
    static void Shutdown()
    {
        s_Instance = null;
    }

    // The server answered a marker request.
    static void OnMarkersReceived()
    {
        if (s_Instance) s_Instance.m_AwaitingMarkers = false;
    }

    static void OnSettingsChanged()
    {
        if (s_Instance) s_Instance.m_LayoutDirty = true;
    }

    // ------------------------------------------------------------------
    protected bool Ensure()
    {
        if (m_Root) return true;
        if (m_Failed || !GetGame() || !GetGame().GetWorkspace()) return false;
        m_Root = GetGame().GetWorkspace().CreateWidgets("PDA/gui/os/FI_Compass.layout");
        if (!m_Root)
        {
            m_Failed = true;
            Print("[FENR_PDA] ERROR: FI_Compass.layout failed to load");
            return false;
        }
        m_Root.SetSort(900);
        m_Heading = TextWidget.Cast(m_Root.FindAnyWidget("FI_CMP_Heading"));
        m_HeadBG = m_Root.FindAnyWidget("FI_CMP_HeadBG");
        m_BG = m_Root.FindAnyWidget("FI_CMP_BG");
        m_LineT = m_Root.FindAnyWidget("FI_CMP_LineT");
        m_LineB = m_Root.FindAnyWidget("FI_CMP_LineB");
        m_Caret = m_Root.FindAnyWidget("FI_CMP_Caret");
        for (int t = 0; t < 24; t++) m_Ticks.Insert(m_Root.FindAnyWidget("FI_CMP_T" + t.ToString()));
        for (int l = 0; l < 8; l++) m_Labels.Insert(TextWidget.Cast(m_Root.FindAnyWidget("FI_CMP_L" + l.ToString())));
        for (int n = 0; n < 8; n++) m_Numbers.Insert(TextWidget.Cast(m_Root.FindAnyWidget("FI_CMP_N" + n.ToString())));
        for (int m = 0; m < MAX_MARKS; m++)
        {
            m_Dots.Insert(m_Root.FindAnyWidget("FI_CMP_M" + m.ToString()));
            m_DotTexts.Insert(TextWidget.Cast(m_Root.FindAnyWidget("FI_CMP_MT" + m.ToString())));
        }
        for (int p = 0; p < MAX_PINGS; p++)
        {
            m_Pings.Insert(m_Root.FindAnyWidget("FI_CMP_S" + p.ToString()));
            m_PingTexts.Insert(TextWidget.Cast(m_Root.FindAnyWidget("FI_CMP_ST" + p.ToString())));
        }
        string names[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
        for (int k = 0; k < 8; k++)
        {
            if (m_Labels[k]) m_Labels[k].SetText(names[k]);
        }
        int numberAngles[8] = {30, 60, 120, 150, 210, 240, 300, 330};
        for (int q = 0; q < 8; q++)
        {
            int angle = numberAngles[q];
            if (m_Numbers[q]) m_Numbers[q].SetText(angle.ToString());
        }
        m_Root.Show(false);
        return true;
    }

    // ------------------------------------------------------------------
    // Visibility
    // ------------------------------------------------------------------
    protected static bool IsWorking(EntityAI entity)
    {
        FENR_PDA_Device device = FENR_PDA_Device.Cast(entity);
        if (!device || device.IsRuined() || !device.GetCompEM()) return false;
        // v8.1: a locked PDA shows nothing (logging in is synced to clients).
        if (!device.FenrIsLoggedIn()) return false;
        return device.GetCompEM().CanWork();
    }

    protected void CheckDevice()
    {
        m_HasDevice = false;
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.IsAlive()) return;

        EntityAI found = null;
        EntityAI inHands = player.GetItemInHands();
        if (IsWorking(inHands)) found = inHands;
        if (!found)
        {
            array<EntityAI> inventory = new array<EntityAI>();
            player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
            foreach (EntityAI entity : inventory)
            {
                if (IsWorking(entity))
                {
                    found = entity;
                    break;
                }
            }
        }
        if (!found)
        {
            // Locked or put away: reload markers when a PDA shows up again
            // (it may be logged in as someone else by then).
            m_LastDevice = null;
            return;
        }
        m_HasDevice = true;

        // No answer to the last request (e.g. throttled): ask again.
        if (m_AwaitingMarkers && GetGame().GetTime() - m_RequestTime > 6000)
            m_LastDevice = null;

        // A different PDA: load its markers.
        if (found != m_LastDevice)
        {
            m_LastDevice = found;
            m_AwaitingMarkers = true;
            m_RequestTime = GetGame().GetTime();
            FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
            if (client) client.RequestHudMarkers();
        }
    }

    // A powered, logged-in PDA in hands or inventory (S.O.S hotkey).
    static bool HasPoweredPda()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.IsAlive()) return false;
        if (IsWorking(player.GetItemInHands())) return true;
        array<EntityAI> inventory = new array<EntityAI>();
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, inventory);
        foreach (EntityAI entity : inventory)
        {
            if (IsWorking(entity)) return true;
        }
        return false;
    }

    void Update(float timeslice)
    {
        FENR_PDA_Settings settings = FENR_PDA_SettingsStore.Get();
        m_CheckTimer -= timeslice;
        if (m_CheckTimer <= 0)
        {
            m_CheckTimer = 0.5;
            CheckDevice();
        }

        bool show = settings.CompassEnabled && m_HasDevice && GetGame().GetUIManager().GetMenu() == null;
        if (!show)
        {
            if (m_Root && m_Visible) m_Root.Show(false);
            m_Visible = false;
            return;
        }
        if (!Ensure()) return;
        if (!m_Visible)
        {
            m_Root.Show(true);
            m_Visible = true;
            m_LayoutDirty = true;
        }
        if (m_LayoutDirty) ApplyLayout(settings);
        Draw(settings);
    }

    // ------------------------------------------------------------------
    // Layout + colours
    // ------------------------------------------------------------------
    protected int CompassColor(FENR_PDA_Settings settings, int role)
    {
        if (settings.CompassMatchTheme) return FENR_PDA_UI_Theme.Role(role);
        return FENR_PDA_UI_Theme.RoleForHue(role, settings.CompassHue);
    }

    protected void ApplyLayout(FENR_PDA_Settings settings)
    {
        m_LayoutDirty = false;
        float width = 0.40;
        float height = 0.085;
        if (settings.CompassSize == 0) { width = 0.30; height = 0.07; }
        if (settings.CompassSize == 2) { width = 0.52; height = 0.10; }
        float y = 0.012;
        if (settings.CompassPosition == 1) y = 0.80 - height;
        m_Root.SetPos(0, y);
        m_Root.SetSize(width, height);
        m_Root.SetAlpha(settings.CompassOpacity / 100.0);

        m_ColText = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_TEXT);
        m_ColBright = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_TEXTBRIGHT);
        m_ColDim = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_TEXTDIM);
        m_ColLine = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_LINE);
        m_ColAccent = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_ACCENT);
        m_ColBg = CompassColor(settings, FENR_PDA_UI_Theme.ROLE_LCD);

        if (m_BG) m_BG.SetColor(FENR_PDA_UI_Theme.WithAlpha(m_ColBg, 190));
        if (m_HeadBG) m_HeadBG.SetColor(FENR_PDA_UI_Theme.WithAlpha(m_ColBg, 215));
        if (m_LineT) m_LineT.SetColor(m_ColLine);
        if (m_LineB) m_LineB.SetColor(m_ColLine);
        if (m_Caret) m_Caret.SetColor(m_ColAccent);
        if (m_Heading) m_Heading.SetColor(m_ColBright);
        foreach (Widget tick : m_Ticks)
        {
            if (tick) tick.SetColor(m_ColLine);
        }
        for (int i = 0; i < m_Labels.Count(); i++)
        {
            if (!m_Labels[i]) continue;
            if (i == 0) m_Labels[i].SetColor(m_ColAccent);
            else if (i % 2 == 0) m_Labels[i].SetColor(m_ColBright);
            else m_Labels[i].SetColor(m_ColText);
        }
        foreach (TextWidget number : m_Numbers)
        {
            if (number) number.SetColor(m_ColDim);
        }
        foreach (TextWidget dotText : m_DotTexts)
        {
            if (dotText) dotText.SetColor(m_ColText);
        }
    }

    // ------------------------------------------------------------------
    // Per-frame drawing
    // ------------------------------------------------------------------
    protected static float Delta(float angle, float heading)
    {
        float d = angle - heading;
        while (d > 180) d -= 360;
        while (d < -180) d += 360;
        return d;
    }

    protected static float Bearing(vector from, float x, float z)
    {
        float b = Math.Atan2(x - from[0], z - from[2]) * Math.RAD2DEG;
        if (b < 0) b += 360;
        return b;
    }

    protected static string Cardinal(float heading)
    {
        string names[8] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
        int index = Math.Round(heading / 45.0);
        if (index >= 8) index = 0;
        if (index < 0) index = 0;
        return names[index];
    }

    protected void Draw(FENR_PDA_Settings settings)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player) return;
        vector me = player.GetPosition();
        vector dir = GetGame().GetCurrentCameraDirection();
        float heading = Math.Atan2(dir[0], dir[2]) * Math.RAD2DEG;
        if (heading < 0) heading += 360;

        float rootW, rootH;
        m_Root.GetScreenSize(rootW, rootH);
        if (rootW < 2) return;
        float half = FOV * 0.5;

        int shown = Math.Round(heading);
        if (shown >= 360) shown = 0;
        if (m_Heading) m_Heading.SetText(shown.ToStringLen(3) + "  " + Cardinal(heading));
        if (m_Caret) m_Caret.SetPos(0.5 - 6.0 / rootW, 0.22);

        // Ticks every 15 degrees; taller every 45.
        for (int t = 0; t < m_Ticks.Count(); t++)
        {
            Widget tick = m_Ticks[t];
            if (!tick) continue;
            float d = Delta(t * 15, heading);
            if (Math.AbsFloat(d) > half) { tick.Show(false); continue; }
            tick.Show(true);
            float tickH = 0.28;
            if (t % 3 == 0) tickH = 0.5;
            tick.SetSize(2, tickH);
            tick.SetPos(0.5 + d / FOV, 1.0 - tickH);
        }
        for (int l = 0; l < m_Labels.Count(); l++)
        {
            TextWidget label = m_Labels[l];
            if (!label) continue;
            float dl = Delta(l * 45, heading);
            if (Math.AbsFloat(dl) > half - 4) { label.Show(false); continue; }
            label.Show(true);
            label.SetPos(0.5 + dl / FOV - 0.04, 0.02);
        }
        int numberAngles[8] = {30, 60, 120, 150, 210, 240, 300, 330};
        for (int n = 0; n < m_Numbers.Count(); n++)
        {
            TextWidget number = m_Numbers[n];
            if (!number) continue;
            float dn = Delta(numberAngles[n], heading);
            if (!settings.CompassBearing || Math.AbsFloat(dn) > half - 4) { number.Show(false); continue; }
            number.Show(true);
            number.SetPos(0.5 + dn / FOV - 0.03, 0.12);
        }

        FENR_PDA_Client client = FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
        DrawMarkers(settings, client, me, heading, rootW);
        DrawPings(client, me, heading, rootW);
    }

    protected void DrawMarkers(FENR_PDA_Settings settings, FENR_PDA_Client client, vector me, float heading, float rootW)
    {
        int used = 0;
        if (client && settings.CompassMarkers)
        {
            float half = FOV * 0.5;
            foreach (FENR_PDA_MapMarker marker : client.m_Markers)
            {
                if (!marker || used >= m_Dots.Count()) continue;
                float d = Delta(Bearing(me, marker.X, marker.Z), heading);
                if (Math.AbsFloat(d) > half) continue;
                Widget dot = m_Dots[used];
                TextWidget label = m_DotTexts[used];
                float x = 0.5 + d / FOV;
                if (dot)
                {
                    dot.SetPos(x - 4.5 / rootW, 0.75);
                    dot.Show(true);
                }
                if (label)
                {
                    float dx = marker.X - me[0];
                    float dz = marker.Z - me[2];
                    float metres = Math.Sqrt(dx * dx + dz * dz);
                    string text = "";
                    if (Math.AbsFloat(d) < 6) text = FENR_PDA_UI_Kit.Clip(marker.Name, 14) + " ";
                    if (settings.CompassDistances) text += FENR_PDA_UI_Kit.Distance(metres);
                    label.SetText(text);
                    label.SetPos(x - 0.05, 0.86);
                    label.Show(text != "");
                }
                used++;
            }
        }
        for (int i = used; i < m_Dots.Count(); i++)
        {
            if (m_Dots[i]) m_Dots[i].Show(false);
            if (m_DotTexts[i]) m_DotTexts[i].Show(false);
        }
    }

    protected void DrawPings(FENR_PDA_Client client, vector me, float heading, float rootW)
    {
        int used = 0;
        if (client)
        {
            array<ref FENR_PDA_SosPing> pings = client.ActiveSosPings();
            bool blinkOn = (GetGame().GetTime() / 400) % 2 == 0;
            foreach (FENR_PDA_SosPing ping : pings)
            {
                if (!ping || used >= m_Pings.Count()) continue;
                float d = Delta(Bearing(me, ping.X, ping.Z), heading);
                // Off screen: pinned to the edge so the player knows which way to turn.
                bool edge = false;
                if (d > FOV * 0.5) { d = FOV * 0.5 - 3; edge = true; }
                if (d < -FOV * 0.5) { d = -FOV * 0.5 + 3; edge = true; }
                float x = 0.5 + d / FOV;
                float dx = ping.X - me[0];
                float dz = ping.Z - me[2];
                float metres = Math.Sqrt(dx * dx + dz * dz);
                Widget beacon = m_Pings[used];
                TextWidget label = m_PingTexts[used];
                if (beacon)
                {
                    beacon.SetPos(x - 7.0 / rootW, 0.74);
                    beacon.Show(blinkOn || !edge);
                }
                if (label)
                {
                    string arrow = "";
                    if (edge && d < 0) arrow = "< ";
                    if (edge && d > 0) arrow = "> ";
                    label.SetText(arrow + "S.O.S " + FENR_PDA_UI_Kit.Clip(ping.Name, 12) + " " + FENR_PDA_UI_Kit.Distance(metres));
                    float lx = x - 0.08;
                    if (lx < 0) lx = 0;
                    if (lx > 0.84) lx = 0.84;
                    label.SetPos(lx, 0.86);
                    label.Show(true);
                }
                used++;
            }
        }
        for (int i = used; i < m_Pings.Count(); i++)
        {
            if (m_Pings[i]) m_Pings[i].Show(false);
            if (m_PingTexts[i]) m_PingTexts[i].Show(false);
        }
    }
}
