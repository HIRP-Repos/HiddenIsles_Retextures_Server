/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Cross-script-layer open request bridge.
*/

// Bridge between the 4_World item action and the 5_Mission PDA UI.
// 4_World cannot directly reference the FENR_PDA_Menu/FENR_PDA_Client classes that live in 5_Mission.
class FENR_PDA_OpenRequest
{
    protected static bool s_OpenRequested = false;

    static void RequestOpen()
    {
        s_OpenRequested = true;
    }

    static bool ConsumeOpenRequest()
    {
        if (!s_OpenRequested)
            return false;

        s_OpenRequested = false;
        return true;
    }
}
