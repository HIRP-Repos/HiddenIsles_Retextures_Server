/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Item-in-hands animation registration.
*/

modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);

        pType.AddItemInHandsProfileIK("FENR_PDA_Device", "dz/anims/workspaces/player/player_main/props/player_main_1h_compass.asi", pBehavior, "dz/anims/anm/player/ik/gear/compass.anm");
        pType.AddItemInHandsProfileIK("FENR_PDA_FlashDrive", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/battery_d.anm");
        pType.AddItemInHandsProfileIK("FENR_PDA_IntelDrive", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/battery_d.anm");
        pType.AddItemInHandsProfileIK("FENR_PDA_EncryptedDrive", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/battery_d.anm");
    }
}
