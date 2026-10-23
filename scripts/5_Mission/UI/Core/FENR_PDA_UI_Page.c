/*
    Fenrir Industries PDA - Field OS 7.0
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Page base.  Every page is a container inside FI_OS_Shell.layout; pages
    bind to their root by name and never create layouts at runtime.
*/
class FENR_PDA_UI_Page
{
    protected FENR_PDA_Menu m_Menu;
    protected Widget m_Root;

    void FENR_PDA_UI_Page()
    {
    }

    Widget Bind(Widget parent, string rootName)
    {
        if (!parent) return null;
        m_Root = parent.FindAnyWidget(rootName);
        if (m_Root) m_Root.Show(false);
        else Print("[FENR_PDA] UI: page root missing: " + rootName);
        return m_Root;
    }

    Widget GetRoot() { return m_Root; }

    bool IsShown() { return m_Root && m_Root.IsVisible(); }

    void Show(bool state)
    {
        if (m_Root) m_Root.Show(state);
    }

    protected FENR_PDA_UI_Button Btn(string name, int kind = 0)
    {
        if (!m_Menu) return null;
        return m_Menu.BindButton(m_Root, name, kind);
    }

    protected FENR_PDA_UI_Input Field(string name)
    {
        if (!m_Menu) return null;
        return m_Menu.BindInput(m_Root, name);
    }

    protected TextWidget Txt(string name)
    {
        if (!m_Root) return null;
        return TextWidget.Cast(m_Root.FindAnyWidget(name));
    }

    protected FENR_PDA_Client PdaClient()
    {
        return FENR_PDA_Client.Cast(GetPlugin(FENR_PDA_Client));
    }

    protected static bool Clicked(FENR_PDA_UI_Button button, Widget w)
    {
        return button && button.IsEnabled() && w == button.m_Button;
    }

    void Refresh() {}
    void OnShown() { Refresh(); }
    void OnHidden() {}
    void OnUpdate(float timeslice) {}
    bool Submit() { return false; }
    bool HandleClick(Widget w, int x, int y, int button) { return false; }
    bool HandleChange(Widget w, int x, int y, bool finished) { return false; }
    bool HandleWheel(Widget w, int x, int y, int wheel) { return false; }
    bool HandleDoubleClick(Widget w, int x, int y, int button) { return false; }
}
