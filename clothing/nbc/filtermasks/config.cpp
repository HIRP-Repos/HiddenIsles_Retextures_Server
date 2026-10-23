////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\filtermasks\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_FilterMasks_Retextures
	{
		units[] = {"HiddenIsles_GP5GasMask_Lavender"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Masks"};
	};
};
class CfgVehicles
{
	class GP5GasMask;
	class HiddenIsles_GP5GasMask_Lavender: GP5GasMask
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_lavender.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_lavender.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_lavender.paa"};
	};
	class HiddenIsles_GP5GasMask_Black: GP5GasMask
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_black.paa"};
	};
	class HiddenIsles_GP5GasMask_Blue: GP5GasMask
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_blue.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_blue.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_blue.paa"};
	};
	class HiddenIsles_GP5GasMask_GreenPink: GP5GasMask
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_greenpink.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_greenpink.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_greenpink.paa"};
	};
	class HiddenIsles_GP5GasMask_PinkPurple: GP5GasMask
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_pinkpurple.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_pinkpurple.paa","HiddenIsles_Retextures_Server\clothing\nbc\filtermasks\gp5gasmask_pinkpurple.paa"};
	};
};
