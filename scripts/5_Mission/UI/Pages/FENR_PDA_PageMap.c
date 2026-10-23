/*
    Fenrir Industries PDA - Field OS 7.4
    Map: native DayZ MapWidget, so it always shows whatever terrain the
    server runs (Chernarus, Livonia, Sakhal, Deer Isle, Bitterroot, Namalsk...).
    Markers are part of the PDA's memory (stored per device and terrain
    on the server, cached in FENR_PDA_Client).
*/
class FENR_PDA_PageMap extends FENR_PDA_UI_Page
{
    static const int MAX_MARKERS = 40;

    protected MapWidget m_MapW;
    protected TextWidget m_Subtitle;
    protected TextWidget m_Coords;
    protected ref FENR_PDA_UI_RowList m_Marks;
    protected FENR_PDA_UI_Input m_NameInput;
    protected FENR_PDA_UI_Button m_AddHere;
    protected FENR_PDA_UI_Button m_Center;
    protected FENR_PDA_UI_Button m_Delete;

    protected ref array<ref FENR_PDA_MapMarker> m_Markers;
    protected string m_World = "";
    protected string m_WorldLabel = "";
    protected bool m_Centered;
    protected float m_RedrawTimer;

    void FENR_PDA_PageMap(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_Markers = new array<ref FENR_PDA_MapMarker>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_MAP_Root");
        if (!root) return null;
        m_MapW = MapWidget.Cast(root.FindAnyWidget("FI_MAP_Widget"));
        m_Subtitle = Txt("FI_MAP_Subtitle");
        m_Coords = Txt("FI_MAP_Coords");
        m_Marks = new FENR_PDA_UI_RowList(m_Menu, root, "FI_MAP_Marks");
        m_Marks.SetEmptyText("No markers. Double-click the map.");
        m_NameInput = Field("FI_MAP_MarkName");
        m_AddHere = Btn("FI_MAP_AddHere");
        m_Center = Btn("FI_MAP_Center");
        m_Delete = Btn("FI_MAP_Delete");

        GetGame().GetWorldName(m_World);
        m_WorldLabel = WorldLabel(m_World);
        LoadMarkers();
        return root;
    }

    protected string WorldLabel(string world)
    {
        return FENR_PDA_UI_Kit.TerrainLabel(world);
    }

    protected vector PlayerPos()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player) return player.GetPosition();
        return "0 0 0";
    }

    protected string Grid(float x, float z)
    {
        int gx = Math.Floor(x / 100.0);
        int gz = Math.Floor(z / 100.0);
        if (gx < 0) gx = 0;
        if (gz < 0) gz = 0;
        return gx.ToStringLen(3) + " " + gz.ToStringLen(3);
    }

    // ------------------------------------------------------------------
    // Markers
    // ------------------------------------------------------------------
    protected void LoadMarkers()
    {
        FENR_PDA_Client client = PdaClient();
        if (client && client.m_Markers)
            m_Markers = client.m_Markers;
        else
            m_Markers = new array<ref FENR_PDA_MapMarker>();
        RefreshList();
    }

    protected void SaveMarkers()
    {
        FENR_PDA_Client client = PdaClient();
        if (client)
            client.SaveMarkers();
    }

    // Called after the PDA's memory was loaded from the device.
    void ReloadMarkers()
    {
        if (m_Marks) m_Marks.Select(-1);
        LoadMarkers();
        RedrawMarks();
    }

    void AddMarker(string name, float x, float z)
    {
        FENR_PDA_Client writer = PdaClient();
        if (writer && !writer.CanWrite()) return;   // read-only session
        if (m_Markers.Count() >= MAX_MARKERS)
        {
            SetSubtitle("Marker limit reached (" + MAX_MARKERS.ToString() + "). Delete one first.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        string clean = name.Trim();
        if (clean == "")
        {
            int next = m_Markers.Count() + 1;
            clean = "MARKER " + next.ToString();
        }
        if (clean.LengthUtf8() > 24) clean = clean.SubstringUtf8(0, 24);
        m_Markers.Insert(new FENR_PDA_MapMarker(clean, x, z));
        SaveMarkers();
        RefreshList();
        if (m_NameInput) m_NameInput.Clear();
        SetSubtitle("Marker '" + clean + "' added at grid " + Grid(x, z) + ".", FENR_PDA_UI_Theme.Accent());
        RedrawMarks();
    }

    protected void RefreshList()
    {
        if (!m_Marks) return;
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        foreach (FENR_PDA_MapMarker marker : m_Markers)
        {
            labels.Insert(marker.Name);
            metas.Insert(Grid(marker.X, marker.Z));
        }
        m_Marks.SetItems(labels, metas);
        if (m_Delete) m_Delete.SetEnabled(m_Marks.GetSelected() >= 0);
    }

    protected void SetSubtitle(string text, int color)
    {
        if (!m_Subtitle) return;
        m_Subtitle.SetText(text);
        m_Subtitle.SetColor(color);
    }

    protected void ResetSubtitle()
    {
        SetSubtitle("TERRAIN: " + m_WorldLabel + "  |  DOUBLE-CLICK THE MAP TO PLACE A MARKER", FENR_PDA_UI_Theme.Text());
    }

    protected void CenterOn(vector pos, float scale)
    {
        if (!m_MapW) return;
        m_MapW.SetMapPos(pos);
        if (scale > 0) m_MapW.SetScale(scale);
    }

    protected void RedrawMarks()
    {
        if (!m_MapW) return;
        m_MapW.ClearUserMarks();

        foreach (FENR_PDA_MapMarker marker : m_Markers)
        {
            vector markPos = Vector(marker.X, 0, marker.Z);
            m_MapW.AddUserMark(markPos, marker.Name, FENR_PDA_UI_Theme.Warn(), "PDA/gui/os/textures/ic_mark.edds");
        }

        // Received S.O.S pings (red).
        FENR_PDA_Client client = PdaClient();
        if (client)
        {
            array<ref FENR_PDA_SosPing> pings = client.ActiveSosPings();
            foreach (FENR_PDA_SosPing ping : pings)
            {
                if (ping)
                    m_MapW.AddUserMark(Vector(ping.X, 0, ping.Z), "S.O.S " + ping.Name, FENR_PDA_UI_Theme.Danger(), "PDA/gui/os/textures/ic_sos.edds");
            }
        }

        vector me = PlayerPos();
        m_MapW.AddUserMark(me, "YOU", FENR_PDA_UI_Theme.Accent(), "PDA/gui/os/textures/ic_self.edds");

        if (m_Coords)
        {
            int elevation = Math.Round(me[1]);
            m_Coords.SetText("GRID " + Grid(me[0], me[2]) + "   |   ELEV " + elevation.ToString() + "m");
        }
    }

    // ------------------------------------------------------------------
    // Page lifecycle
    // ------------------------------------------------------------------
    override void OnShown()
    {
        if (m_Menu) m_Menu.SetMapActive(true);
        ResetSubtitle();
        if (!m_Centered)
        {
            CenterOn(PlayerPos(), 0.25);
            m_Centered = true;
        }
        RefreshList();
        RedrawMarks();
    }

    override void OnHidden()
    {
        if (m_Menu) m_Menu.SetMapActive(false);
    }

    override void OnUpdate(float timeslice)
    {
        m_RedrawTimer += timeslice;
        if (m_RedrawTimer >= 0.5)
        {
            m_RedrawTimer = 0;
            RedrawMarks();
        }
    }

    override bool HandleDoubleClick(Widget w, int x, int y, int button)
    {
        if (!m_MapW || !FENR_PDA_UI_Kit.IsPointInside(m_MapW, x, y)) return false;
        vector world = m_MapW.ScreenToMap(Vector(x, y, 0));
        string name = "";
        if (m_NameInput) name = m_NameInput.GetMessage();
        AddMarker(name, world[0], world[2]);
        return true;
    }

    override bool HandleClick(Widget w, int x, int y, int button)
    {
        int result = m_Marks.HandleClick(w);
        if (result == FENR_PDA_UI_RowList.RESULT_SELECT)
        {
            int row = m_Marks.GetSelected();
            if (row >= 0 && row < m_Markers.Count())
            {
                FENR_PDA_MapMarker marker = m_Markers[row];
                CenterOn(Vector(marker.X, 0, marker.Z), 0);
                SetSubtitle("MARKER: " + marker.Name + "  |  GRID " + Grid(marker.X, marker.Z), FENR_PDA_UI_Theme.Text());
            }
            if (m_Delete) m_Delete.SetEnabled(row >= 0);
            return true;
        }
        if (result != FENR_PDA_UI_RowList.RESULT_NONE) return true;

        if (Clicked(m_Center, w))
        {
            CenterOn(PlayerPos(), 0.2);
            ResetSubtitle();
            return true;
        }
        if (Clicked(m_AddHere, w))
        {
            vector me = PlayerPos();
            string name = "";
            if (m_NameInput) name = m_NameInput.GetMessage();
            AddMarker(name, me[0], me[2]);
            return true;
        }
        if (Clicked(m_Delete, w))
        {
            int selected = m_Marks.GetSelected();
            if (selected >= 0 && selected < m_Markers.Count())
            {
                string removed = m_Markers[selected].Name;
                m_Markers.RemoveOrdered(selected);
                m_Marks.Select(-1);
                SaveMarkers();
                RefreshList();
                RedrawMarks();
                SetSubtitle("Marker '" + removed + "' deleted.", FENR_PDA_UI_Theme.TextDim());
            }
            return true;
        }
        return false;
    }

    // Let the map widget zoom natively; only the marker list scrolls here.
    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        return m_Marks && m_Marks.HandleWheel(x, y, wheel);
    }

    override bool Submit()
    {
        // Enter with a name typed marks the current position.
        if (!m_NameInput) return false;
        string name = m_NameInput.GetMessage();
        if (name == "") return false;
        vector me = PlayerPos();
        AddMarker(name, me[0], me[2]);
        return true;
    }
}
