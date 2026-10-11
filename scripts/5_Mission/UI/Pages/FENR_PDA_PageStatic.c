/*
    Fenrir Industries PDA - Field OS 7.0
    Placeholder pages (Trade, Map, Network) - layout only.
*/
class FENR_PDA_PageStatic extends FENR_PDA_UI_Page
{
    void FENR_PDA_PageStatic(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
    }

    Widget BuildRoot(Widget parent, string rootName)
    {
        return Bind(parent, rootName);
    }
}
