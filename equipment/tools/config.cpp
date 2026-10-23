////////////////////////////////////////////////////////////////////
//DeRap: equipment\tools\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:51 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Tools_Retextures
	{
		units[] = {"HiddenIsles_Hammer_Xmas","HiddenIsles_Handcuffs_Xmas","HiddenIsles_Shovel_Xmas","HiddenIsles_Fishing_Rod_Xmas"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Melee","DZ_Gear_Tools"};
	};
};
class CfgVehicles
{
	class FishingRod;
	class Hammer;
	class Handcuffs;
	class Shovel;
	class HiddenIsles_Hammer_Xmas: Hammer
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\hammer_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\hammer_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\hammer_xmas.paa"};
	};
	class HiddenIsles_Handcuffs_Xmas: Handcuffs
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\handcuff_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\handcuff_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\handcuff_xmas.paa"};
	};
	class HiddenIsles_Handcuffs_Pink: Handcuffs
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\handcuff_pink.paa","HiddenIsles_Retextures_server\Equipment\Tools\handcuff_pink.paa","HiddenIsles_Retextures_server\Equipment\Tools\handcuff_pink.paa"};
	};
	class HiddenIsles_Shovel_Xmas: Shovel
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\shovel_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\shovel_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\shovel_xmas.paa"};
	};
	class HiddenIsles_FishingRod_Xmas: FishingRod
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_xmas.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_xmas.paa"};
	};
	class HiddenIsles_FishingRod_Blue: FishingRod
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_blue.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_blue.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_blue.paa"};
	};
	class HiddenIsles_FishingRod_Green: FishingRod
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_green.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_green.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_green.paa"};
	};
	class HiddenIsles_FishingRod_Pink: FishingRod
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_pink.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_pink.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_pink.paa"};
	};
	class HiddenIsles_FishingRod_Purple: FishingRod
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_purple.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_purple.paa","HiddenIsles_Retextures_server\Equipment\Tools\fishing_rod_purple.paa"};
	};
};
