/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Mission input bridge for opening/closing the PDA.
*/

modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        // Compass HUD + S.O.S hotkey (client only).
        FENR_PDA_CompassHud.Tick(timeslice);
        FENR_PDA_SosPrompt.HandleHotkey();

        if (FENR_PDA_OpenRequest.ConsumeOpenRequest())
        {
            FENR_PDA_Client client;
            if (Class.CastTo(client, GetPlugin(FENR_PDA_Client)))
            {
                if (!client.IsOpen())
                    client.Open();
            }
        }
    }

    override void OnMissionFinish()
    {
        FENR_PDA_CompassHud.Shutdown();
        FENR_PDA_Toast.HideToast();
        super.OnMissionFinish();
    }

    override void OnKeyRelease(int key)
    {
        super.OnKeyRelease(key);

        FENR_PDA_Client client;
        if (key == KeyCode.KC_ESCAPE)
        {
            Class.CastTo(client, GetPlugin(FENR_PDA_Client));
            if (client && client.IsOpen())
                client.Close();
        }
        else if (key == KeyCode.KC_RETURN)
        {
            Class.CastTo(client, GetPlugin(FENR_PDA_Client));
            if (client && client.IsOpen())
                if (client.m_Menu)
                    client.m_Menu.SendCurrentMessage();
        }
    }
}
