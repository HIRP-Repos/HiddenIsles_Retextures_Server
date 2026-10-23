/*
    Fenrir Industries PDA - Field OS 8.0
    System: unit information and three settings panels.

      DISPLAY  theme presets + hue / saturation / brightness / backlight
      COMPASS  compass HUD options
      S.O.S    who receives this PDA's S.O.S signal, and the S.O.S button

    Display and compass settings are personal (saved on the player's
    computer, FENR_PDA_SettingsStore).  S.O.S recipients belong to the PDA
    and are stored on the server with its memory.
*/
class FENR_PDA_PageSystem extends FENR_PDA_UI_Page
{
    static const string TAB_DISPLAY = "DISPLAY";
    static const string TAB_COMPASS = "COMPASS";
    static const string TAB_SOS = "SOS";
    static const string SOS_CONTACTS = "CONTACTS";
    static const string SOS_GROUP = "GROUP";

    protected MultilineTextWidget m_Info;
    protected string m_Tab = TAB_DISPLAY;

    protected FENR_PDA_UI_Button m_TabDisplay;
    protected FENR_PDA_UI_Button m_TabCompass;
    protected FENR_PDA_UI_Button m_TabSos;
    protected FENR_PDA_UI_Button m_Logout;
    protected Widget m_DisplayView;
    protected Widget m_CompassView;
    protected Widget m_SosView;

    // display
    protected ref array<FENR_PDA_UI_Button> m_PresetTiles;
    protected ref array<Widget> m_PresetSwatches;
    protected FENR_PDA_UI_Button m_DisplayReset;

    // steppers: name -> prev / next / value
    protected ref array<string> m_StepNames;
    protected ref array<FENR_PDA_UI_Button> m_StepPrev;
    protected ref array<FENR_PDA_UI_Button> m_StepNext;
    protected ref array<TextWidget> m_StepValue;

    // S.O.S
    protected ref FENR_PDA_UI_RowList m_SosList;
    protected TextWidget m_SosListLabel;
    protected MultilineTextWidget m_SosStatus;
    protected FENR_PDA_UI_Button m_SosSend;
    protected Widget m_SosConfirm;
    protected MultilineTextWidget m_SosBody;
    protected FENR_PDA_UI_Button m_SosConfirmSend;
    protected FENR_PDA_UI_Button m_SosConfirmCancel;
    protected bool m_SosConfirmOpen;
    protected bool m_SosLoaded;
    protected bool m_SosSending;
    protected string m_SosMode = SOS_CONTACTS;
    protected ref array<string> m_SosTargets;
    protected string m_SosGroup = "";
    protected int m_SosMax = 5;
    protected ref array<string> m_SosRowIds;
    protected ref array<string> m_GroupIds;
    protected ref array<string> m_GroupNames;

    void FENR_PDA_PageSystem(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_PresetTiles = new array<FENR_PDA_UI_Button>();
        m_PresetSwatches = new array<Widget>();
        m_StepNames = new array<string>();
        m_StepPrev = new array<FENR_PDA_UI_Button>();
        m_StepNext = new array<FENR_PDA_UI_Button>();
        m_StepValue = new array<TextWidget>();
        m_SosTargets = new array<string>();
        m_SosRowIds = new array<string>();
        m_GroupIds = new array<string>();
        m_GroupNames = new array<string>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_SYS_Root");
        if (!root) return null;
        m_Info = MultilineTextWidget.Cast(root.FindAnyWidget("FI_SYS_Info"));

        m_TabDisplay = Btn("FI_SYS_TabDisplay");
        m_TabCompass = Btn("FI_SYS_TabCompass");
        m_TabSos = Btn("FI_SYS_TabSos");
        m_Logout = Btn("FI_SYS_Logout");
        m_DisplayView = root.FindAnyWidget("FI_SYS_DisplayView");
        m_CompassView = root.FindAnyWidget("FI_SYS_CompassView");
        m_SosView = root.FindAnyWidget("FI_SYS_SosView");

        for (int i = 0; i < 10; i++)
        {
            m_PresetTiles.Insert(Btn("FI_SYS_Pre" + i.ToString()));
            m_PresetSwatches.Insert(root.FindAnyWidget("FI_SYS_Pre" + i.ToString() + "Swatch"));
        }
        m_DisplayReset = Btn("FI_SYS_DisplayReset");

        BindStepper("Hue");
        BindStepper("Sat");
        BindStepper("Bright");
        BindStepper("Back");
        BindStepper("CmpOn");
        BindStepper("CmpPos");
        BindStepper("CmpSize");
        BindStepper("CmpAlpha");
        BindStepper("CmpColor");
        BindStepper("CmpHue");
        BindStepper("CmpMarks");
        BindStepper("CmpDist");
        BindStepper("CmpDeg");
        BindStepper("SosMode");

        m_SosList = new FENR_PDA_UI_RowList(m_Menu, root, "FI_SYS_SosList");
        m_SosList.SetSelectable(false);
        m_SosListLabel = Txt("FI_SYS_SosListLabel");
        m_SosStatus = MultilineTextWidget.Cast(root.FindAnyWidget("FI_SYS_SosStatus"));
        m_SosSend = Btn("FI_SYS_SosSend");
        m_SosConfirm = root.FindAnyWidget("FI_SYS_SosConfirm");
        m_SosBody = MultilineTextWidget.Cast(root.FindAnyWidget("FI_SYS_SosBody"));
        m_SosConfirmSend = Btn("FI_SYS_SosConfirmSend");
        m_SosConfirmCancel = Btn("FI_SYS_SosConfirmCancel");
        Btn("FI_SYS_SosShade");
        CloseSosConfirm();

        SelectTab(TAB_DISPLAY);
        return root;
    }

    protected void BindStepper(string key)
    {
        m_StepNames.Insert(key);
        m_StepPrev.Insert(Btn("FI_SYS_" + key + "Prev"));
        m_StepNext.Insert(Btn("FI_SYS_" + key + "Next"));
        m_StepValue.Insert(Txt("FI_SYS_" + key + "Value"));
    }

    protected void SetStepValue(string key, string value)
    {
        int index = m_StepNames.Find(key);
        if (index >= 0 && m_StepValue[index]) m_StepValue[index].SetText(value);
    }

    override void OnShown()
    {
        CloseSosConfirm();
        SelectTab(m_Tab);
    }

    override void OnHidden()
    {
        CloseSosConfirm();
    }

    // The PDA's memory was reloaded: S.O.S recipients belong to it.
    void OnDeviceSynced()
    {
        m_SosLoaded = false;
        m_SosTargets.Clear();
        m_SosGroup = "";
        if (IsShown() && m_Tab == TAB_SOS) RequestSosConfig();
    }

    void OnThemeChanged()
    {
        RefreshDisplay();
        RefreshCompass();
        if (m_Tab == TAB_SOS) RefreshSos();
    }

    // ------------------------------------------------------------------
    // Tabs
    // ------------------------------------------------------------------
    protected void SelectTab(string tab)
    {
        m_Tab = tab;
        if (m_TabDisplay) m_TabDisplay.SetActive(tab == TAB_DISPLAY);
        if (m_TabCompass) m_TabCompass.SetActive(tab == TAB_COMPASS);
        if (m_TabSos) m_TabSos.SetActive(tab == TAB_SOS);
        if (m_DisplayView) m_DisplayView.Show(tab == TAB_DISPLAY);
        if (m_CompassView) m_CompassView.Show(tab == TAB_COMPASS);
        if (m_SosView) m_SosView.Show(tab == TAB_SOS);
        if (tab == TAB_DISPLAY) RefreshDisplay();
        if (tab == TAB_COMPASS) RefreshCompass();
        if (tab == TAB_SOS)
        {
            RefreshSos();
            RequestSosConfig();
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_SOURCE, new Param2<string, string>("GROUPS", ""), true);
        }
    }

    // ------------------------------------------------------------------
    // Display
    // ------------------------------------------------------------------
    protected string ShortName(string preset)
    {
        if (preset == "FENRIR GREEN") return "GREEN";
        if (preset == "ARCTIC CYAN") return "CYAN";
        if (preset == "BLOOD RED") return "RED";
        if (preset == "ROYAL VIOLET") return "VIOLET";
        if (preset == "TOXIC LIME") return "LIME";
        if (preset == "ICE WHITE") return "ICE";
        if (preset == "MONOCHROME") return "MONO";
        return preset;
    }

    protected void RefreshDisplay()
    {
        FENR_PDA_Settings settings = FENR_PDA_SettingsStore.Get();
        array<ref FENR_PDA_ThemePreset> presets = FENR_PDA_UI_Theme.Presets();
        for (int i = 0; i < m_PresetTiles.Count(); i++)
        {
            FENR_PDA_UI_Button tile = m_PresetTiles[i];
            Widget swatch = m_PresetSwatches[i];
            bool hasPreset = i < presets.Count();
            if (tile) tile.Show(hasPreset);
            if (!hasPreset) continue;
            FENR_PDA_ThemePreset preset = presets[i];
            if (tile)
            {
                tile.SetText(ShortName(preset.Name));
                tile.SetActive(settings.Preset == preset.Name);
            }
            if (swatch) swatch.SetColor(FENR_PDA_UI_Theme.Swatch(preset.Hue, preset.Saturation));
        }
        SetStepValue("Hue", settings.Hue.ToString() + " DEG");
        SetStepValue("Sat", settings.Saturation.ToString() + "%");
        SetStepValue("Bright", settings.Brightness.ToString() + "%");
        SetStepValue("Back", settings.Backlight.ToString() + "%");
    }

    protected string OnOff(bool state)
    {
        if (state) return "ON";
        return "OFF";
    }

    protected void RefreshCompass()
    {
        FENR_PDA_Settings settings = FENR_PDA_SettingsStore.Get();
        SetStepValue("CmpOn", OnOff(settings.CompassEnabled));
        if (settings.CompassPosition == 0) SetStepValue("CmpPos", "TOP");
        else SetStepValue("CmpPos", "BOTTOM");
        if (settings.CompassSize == 0) SetStepValue("CmpSize", "SMALL");
        else if (settings.CompassSize == 1) SetStepValue("CmpSize", "MEDIUM");
        else SetStepValue("CmpSize", "LARGE");
        SetStepValue("CmpAlpha", settings.CompassOpacity.ToString() + "%");
        if (settings.CompassMatchTheme) SetStepValue("CmpColor", "MATCH THEME");
        else SetStepValue("CmpColor", "CUSTOM");
        if (settings.CompassMatchTheme) SetStepValue("CmpHue", "--");
        else SetStepValue("CmpHue", settings.CompassHue.ToString() + " DEG");
        SetStepValue("CmpMarks", OnOff(settings.CompassMarkers));
        SetStepValue("CmpDist", OnOff(settings.CompassDistances));
        SetStepValue("CmpDeg", OnOff(settings.CompassBearing));
    }

    // dir: -1 previous, +1 next
    protected void StepSetting(string key, int dir)
    {
        FENR_PDA_Settings settings = FENR_PDA_SettingsStore.Get();
        if (key == "SosMode")
        {
            if (!m_SosLoaded) return;   // never overwrite settings that have not arrived
            if (m_SosMode == SOS_CONTACTS) m_SosMode = SOS_GROUP;
            else m_SosMode = SOS_CONTACTS;
            SaveSosConfig();
            RefreshSos();
            return;
        }

        if (key == "Hue") { settings.Hue = FENR_PDA_SettingsStore.WrapHue(settings.Hue + dir * 10); settings.Preset = "CUSTOM"; }
        else if (key == "Sat") { settings.Saturation = settings.Saturation + dir * 10; settings.Preset = "CUSTOM"; }
        else if (key == "Bright") settings.Brightness = settings.Brightness + dir * 10;
        else if (key == "Back") settings.Backlight = settings.Backlight + dir * 20;
        else if (key == "CmpOn") settings.CompassEnabled = !settings.CompassEnabled;
        else if (key == "CmpPos") settings.CompassPosition = 1 - settings.CompassPosition;
        else if (key == "CmpSize") settings.CompassSize = WrapIndex(settings.CompassSize + dir, 3);
        else if (key == "CmpAlpha") settings.CompassOpacity = settings.CompassOpacity + dir * 10;
        else if (key == "CmpColor") settings.CompassMatchTheme = !settings.CompassMatchTheme;
        else if (key == "CmpHue") { settings.CompassHue = FENR_PDA_SettingsStore.WrapHue(settings.CompassHue + dir * 10); settings.CompassMatchTheme = false; }
        else if (key == "CmpMarks") settings.CompassMarkers = !settings.CompassMarkers;
        else if (key == "CmpDist") settings.CompassDistances = !settings.CompassDistances;
        else if (key == "CmpDeg") settings.CompassBearing = !settings.CompassBearing;
        else return;

        FENR_PDA_SettingsStore.Changed();
        RefreshDisplay();
        RefreshCompass();
    }

    protected int WrapIndex(int value, int count)
    {
        int result = value;
        while (result < 0) result += count;
        while (result >= count) result -= count;
        return result;
    }

    // ------------------------------------------------------------------
    // S.O.S configuration
    // ------------------------------------------------------------------
    protected void RequestSosConfig()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || !client.IsDeviceSynced()) return;
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_GET, new Param1<string>(client.DeviceToken()), true);
    }

    void ReceiveSosConfig(string mode, array<string> targets, string groupID, int maxContacts)
    {
        m_SosLoaded = true;
        m_SosMode = mode;
        if (m_SosMode != SOS_GROUP) m_SosMode = SOS_CONTACTS;
        m_SosTargets.Clear();
        if (targets) m_SosTargets.Copy(targets);
        m_SosGroup = groupID;
        if (maxContacts > 0) m_SosMax = maxContacts;
        RefreshSos();
    }

    void ReceiveGroups(array<string> fields)
    {
        m_GroupIds.Clear();
        m_GroupNames.Clear();
        for (int i = 0; i + 2 <= fields.Count(); i += 2)
        {
            m_GroupIds.Insert(fields[i]);
            m_GroupNames.Insert(fields[i + 1]);
        }
        if (m_Tab == TAB_SOS) RefreshSos();
    }

    protected void SaveSosConfig()
    {
        if (!m_SosLoaded) return;
        FENR_PDA_Client client = PdaClient();
        if (!client || !client.IsDeviceSynced()) return;
        ref array<string> targets = new array<string>();
        targets.Copy(m_SosTargets);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_SET, new Param4<string, string, ref array<string>, string>(client.DeviceToken(), m_SosMode, targets, m_SosGroup), true);
    }

    protected void RefreshSos()
    {
        if (m_SosMode == SOS_GROUP) SetStepValue("SosMode", "A GROUP");
        else SetStepValue("SosMode", "CONTACTS");

        m_SosRowIds.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        array<bool> marks = new array<bool>();
        FENR_PDA_Client client = PdaClient();

        if (m_SosMode == SOS_CONTACTS)
        {
            if (m_SosListLabel) m_SosListLabel.SetText("SELECT UP TO " + m_SosMax.ToString() + " CONTACTS");
            if (m_SosList) m_SosList.SetEmptyText("No contacts on this PDA.");
            if (client)
            {
                foreach (FENR_PDA_Contact contact : client.m_Contacts)
                {
                    if (!contact || FENR_PDA_Client.IsGlobalChannel(contact.m_UID) || client.IsTestContact(contact.m_UID)) continue;
                    bool chosen = m_SosTargets.Find(contact.m_UID) != -1;
                    m_SosRowIds.Insert(contact.m_UID);
                    labels.Insert(contact.m_Name);
                    if (chosen) metas.Insert("S.O.S");
                    else metas.Insert("");
                    marks.Insert(chosen);
                }
            }
        }
        else
        {
            if (m_SosListLabel) m_SosListLabel.SetText("SELECT ONE GROUP");
            if (m_SosList) m_SosList.SetEmptyText("You are in no groups.");
            for (int g = 0; g < m_GroupIds.Count(); g++)
            {
                bool selected = m_GroupIds[g] == m_SosGroup;
                m_SosRowIds.Insert(m_GroupIds[g]);
                labels.Insert(m_GroupNames[g]);
                if (selected) metas.Insert("S.O.S");
                else metas.Insert("");
                marks.Insert(selected);
            }
        }
        if (m_SosList)
        {
            m_SosList.SetItems(labels, metas);
            m_SosList.SetMarks(marks);
        }

        string status;
        int color = FENR_PDA_UI_Theme.Text();
        if (!client || !client.IsDeviceSynced())
        {
            status = "Loading this PDA's memory...";
            color = FENR_PDA_UI_Theme.TextDim();
        }
        else if (!m_SosLoaded)
        {
            status = "Loading S.O.S settings...";
            color = FENR_PDA_UI_Theme.TextDim();
        }
        else if (!HasSosTargets())
        {
            status = "No recipients set. Pick who receives your S.O.S.";
            color = FENR_PDA_UI_Theme.Warn();
        }
        else if (m_SosMode == SOS_CONTACTS)
        {
            int count = m_SosTargets.Count();
            status = "ARMED  |  " + count.ToString() + " CONTACT(S) WILL RECEIVE YOUR PING";
        }
        else
        {
            status = "ARMED  |  GROUP " + GroupName(m_SosGroup) + " WILL RECEIVE YOUR PING";
        }
        if (m_SosStatus)
        {
            m_SosStatus.SetText(status);
            m_SosStatus.SetColor(color);
        }
        if (m_SosSend)
        {
            m_SosSend.SetEnabled(m_SosLoaded && HasSosTargets() && !m_SosSending);
            m_SosSend.SetText("SEND S.O.S");
        }
    }

    protected bool HasSosTargets()
    {
        if (m_SosMode == SOS_GROUP) return m_SosGroup != "";
        return m_SosTargets.Count() > 0;
    }

    protected string GroupName(string groupID)
    {
        int index = m_GroupIds.Find(groupID);
        if (index >= 0) return m_GroupNames[index];
        return "(not loaded)";
    }

    protected void ToggleSosRow(int row)
    {
        if (!m_SosLoaded) return;
        if (row < 0 || row >= m_SosRowIds.Count()) return;
        string id = m_SosRowIds[row];
        if (m_SosMode == SOS_GROUP)
        {
            if (m_SosGroup == id) m_SosGroup = "";
            else m_SosGroup = id;
        }
        else
        {
            int index = m_SosTargets.Find(id);
            if (index != -1)
            {
                m_SosTargets.Remove(index);
            }
            else
            {
                if (m_SosTargets.Count() >= m_SosMax)
                {
                    if (m_SosStatus)
                    {
                        m_SosStatus.SetText("At most " + m_SosMax.ToString() + " contacts. Deselect one first.");
                        m_SosStatus.SetColor(FENR_PDA_UI_Theme.Warn());
                    }
                    return;
                }
                m_SosTargets.Insert(id);
            }
        }
        SaveSosConfig();
        RefreshSos();
    }

    // ------------------------------------------------------------------
    // S.O.S send
    // ------------------------------------------------------------------
    void OpenSosConfirm()
    {
        if (!m_SosConfirm) return;
        string who;
        if (m_SosMode == SOS_GROUP) who = "everyone in " + GroupName(m_SosGroup);
        else who = m_SosTargets.Count().ToString() + " contact(s)";
        if (!m_SosLoaded) who = "this PDA's S.O.S recipients";
        if (m_SosBody)
            m_SosBody.SetText("Your position will be sent to " + who + " as a red ping with an alarm.\n\nThe signal burst burns out this PDA, its battery and every drive in it. This cannot be undone.");
        m_SosConfirmOpen = true;
        m_SosConfirm.Show(true);
    }

    protected void CloseSosConfirm()
    {
        m_SosConfirmOpen = false;
        if (m_SosConfirm) m_SosConfirm.Show(false);
    }

    protected void SendSos()
    {
        CloseSosConfirm();
        m_SosSending = true;
        if (m_SosStatus)
        {
            m_SosStatus.SetText("TRANSMITTING S.O.S...");
            m_SosStatus.SetColor(FENR_PDA_UI_Theme.Danger());
        }
        if (m_SosSend) m_SosSend.SetEnabled(false);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.SOS_SEND, new Param1<bool>(true), true);
    }

    void ReceiveSosResult(bool success, string info)
    {
        m_SosSending = false;
        if (success) return;   // the PDA is gone; the menu closes
        if (m_SosStatus)
        {
            m_SosStatus.SetText(info);
            m_SosStatus.SetColor(FENR_PDA_UI_Theme.Danger());
        }
        if (m_SosSend) m_SosSend.SetEnabled(m_SosLoaded && HasSosTargets());
    }

    // ------------------------------------------------------------------
    // Info panel
    // ------------------------------------------------------------------
    void UpdateInfo(int batteryPercent, int pdaUsers, int serverPlayers)
    {
        if (!m_Info) return;
        FENR_PDA_Client client = PdaClient();

        string pdaId = "--";
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) pdaId = player.GetIdentity().GetPlainId();

        // Session line + the logout button's label.
        string session = "LOCKED";
        if (client && client.IsLoggedIn())
        {
            session = FENR_PDA_LoginScreen.FormatLeft(client.SessionSecondsLeft()) + " LEFT";
            if (client.IsGuest()) session = "READ-ONLY, " + session;
        }
        if (m_Logout)
        {
            if (client && client.IsGuest()) m_Logout.SetText("STOP READING");
            else m_Logout.SetText("LOG OUT");
        }

        int contacts = 0;
        int online = 0;
        int unreadDirect = 0;
        int unreadGlobal = 0;
        if (client)
        {
            foreach (FENR_PDA_Contact c : client.m_Contacts)
            {
                if (!c) continue;
                if (FENR_PDA_Client.IsGlobalChannel(c.m_UID))
                {
                    if (c.m_UID == FENR_PDA_ChannelIds.GLOBAL) unreadGlobal += c.m_Unreaded;
                    continue;
                }
                contacts++;
                unreadDirect += c.m_Unreaded;
                if (!c.m_IsBanned && client.m_OnlineContactIds.Find(c.m_UID) != -1) online++;
            }
        }

        string battery = "NO CELL";
        if (batteryPercent >= 0) battery = batteryPercent.ToString() + "%";

        string users = "CHECKING...";
        if (pdaUsers >= 0) users = pdaUsers.ToString() + " / " + serverPlayers.ToString();

        string memoryState = "NOT LOADED";
        if (client && client.IsDeviceSynced()) memoryState = "LOADED";
        else if (client && client.IsDeviceSyncPending()) memoryState = "LOADING...";

        string text = "UNIT: FI-PDA-01\n";
        text += "PDA ID: " + pdaId + "\n";
        text += "SESSION: " + session + "\n";
        text += "MEMORY: " + memoryState + "\n";
        text += "CONTACTS ONLINE: " + online.ToString() + " / " + contacts.ToString() + "\n";
        text += "PDA USERS: " + users + "\n";
        text += "UNREAD: " + unreadDirect.ToString() + " DIRECT\n";
        text += "        " + unreadGlobal.ToString() + " GLOBAL\n";
        text += "BATTERY: " + battery + "\n";
        text += "CLOCK: " + FENR_PDA_UI_Kit.GameTime();
        m_Info.SetText(text);
    }

    // ------------------------------------------------------------------
    // Clicks
    // ------------------------------------------------------------------
    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_SosConfirmOpen)
        {
            if (Clicked(m_SosConfirmSend, w)) { SendSos(); return true; }
            if (Clicked(m_SosConfirmCancel, w)) { CloseSosConfirm(); return true; }
            return true;
        }

        if (Clicked(m_Logout, w)) { if (m_Menu) m_Menu.LogoutPressed(); return true; }
        if (Clicked(m_TabDisplay, w)) { SelectTab(TAB_DISPLAY); return true; }
        if (Clicked(m_TabCompass, w)) { SelectTab(TAB_COMPASS); return true; }
        if (Clicked(m_TabSos, w)) { SelectTab(TAB_SOS); return true; }

        if (m_Tab == TAB_DISPLAY)
        {
            array<ref FENR_PDA_ThemePreset> presets = FENR_PDA_UI_Theme.Presets();
            for (int i = 0; i < m_PresetTiles.Count() && i < presets.Count(); i++)
            {
                if (Clicked(m_PresetTiles[i], w))
                {
                    FENR_PDA_SettingsStore.ApplyPreset(presets[i]);
                    RefreshDisplay();
                    return true;
                }
            }
            if (Clicked(m_DisplayReset, w))
            {
                FENR_PDA_SettingsStore.ResetDisplay();
                RefreshDisplay();
                return true;
            }
        }

        for (int s = 0; s < m_StepNames.Count(); s++)
        {
            if (Clicked(m_StepPrev[s], w)) { StepSetting(m_StepNames[s], -1); return true; }
            if (Clicked(m_StepNext[s], w)) { StepSetting(m_StepNames[s], 1); return true; }
        }

        if (m_Tab == TAB_SOS)
        {
            if (Clicked(m_SosSend, w)) { OpenSosConfirm(); return true; }
            if (m_SosList)
            {
                int result = m_SosList.HandleClick(w);
                if (result == FENR_PDA_UI_RowList.RESULT_SELECT)
                {
                    ToggleSosRow(m_SosList.GetSelected());
                    return true;
                }
                if (result != FENR_PDA_UI_RowList.RESULT_NONE) return true;
            }
        }
        return false;
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_Tab == TAB_SOS && m_SosList) return m_SosList.HandleWheel(x, y, wheel);
        return false;
    }
}
