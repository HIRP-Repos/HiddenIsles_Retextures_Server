/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Writes pending PDA memory to disk when the server mission ends.
*/

modded class MissionServer
{
    override void OnMissionFinish()
    {
        FENR_PDA_AccountStore.Flush();
        super.OnMissionFinish();
    }
}
