/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Registers Fenrir Industries PDA plugins.
*/

modded class PluginManager
{
    override void Init()
    {
        super.Init();

        RegisterPlugin("FENR_PDA_Client", true, false);
        RegisterPlugin("FENR_PDA_Server", true, true);
    }
}