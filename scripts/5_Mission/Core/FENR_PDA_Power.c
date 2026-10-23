/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Battery drain (server side).  Clients report whether their PDA is open
    and whether the map is active; every tick the server drains the 9V cell
    attached to that player's PDA by a configurable percentage per minute.
*/

class FENR_PDA_Power
{
    static const int MODE_CLOSED = 0;
    static const int MODE_OPEN = 1;
    static const int MODE_MAP = 2;
    static const int TICK_MS = 10000;

    protected static ref map<string, int> s_Usage;
    protected static bool s_Initialized = false;

    static void Init()
    {
        if (s_Initialized || !GetGame().IsServer())
            return;
        s_Usage = new map<string, int>();
        s_Initialized = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(PowerTick, TICK_MS, true);
    }

    static void SetUsage(PlayerIdentity identity, int mode)
    {
        if (!identity)
            return;
        if (!s_Usage)
            s_Usage = new map<string, int>();

        string id = identity.GetPlainId();
        if (mode <= MODE_CLOSED)
            s_Usage.Remove(id);
        else
            s_Usage.Set(id, mode);
    }

    static void PowerTick()
    {
        if (!s_Usage || s_Usage.Count() == 0)
            return;
        if (!FENR_PDA_Storage.BatteryDrainEnabled())
            return;

        array<string> ids = new array<string>();
        for (int i = 0; i < s_Usage.Count(); i++)
            ids.Insert(s_Usage.GetKey(i));

        float openRate = FENR_PDA_Storage.BatteryDrainOpenPerMinute();
        float mapRate = FENR_PDA_Storage.BatteryDrainMapPerMinute();
        float tickMinutes = TICK_MS / 60000.0;

        foreach (string id : ids)
        {
            PlayerBase player = FENR_PDA_Server.FindOnlinePlayer(id);
            if (!player || !player.IsAlive())
            {
                s_Usage.Remove(id);
                continue;
            }

            EntityAI battery = FENR_PDA_Server.FindDeviceBattery(player);
            if (!battery || !battery.GetCompEM())
                continue;

            float percent = openRate;
            if (s_Usage.Get(id) == MODE_MAP)
                percent += mapRate;

            float drain = battery.GetCompEM().GetEnergyMax() * (percent / 100.0) * tickMinutes;
            if (drain > 0)
                battery.GetCompEM().AddEnergy(-drain);
        }
    }
};
