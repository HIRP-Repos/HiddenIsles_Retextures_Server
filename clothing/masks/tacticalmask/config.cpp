////////////////////////////////////////////////////////////////////
//DeRap: clothing\masks\tacticalmask\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_TacticalMask_Retextures
	{
		units[] = {"HiddenIsles_tacticalmask_Momento"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters","DZ_Characters_Tops","DZ_Characters_Headgear","DZ_Characters_Backpacks","DZ_Characters_Glasses","DZ_Characters_Masks","DZ_Characters_Gloves","DZ_Characters_Shoes","DZ_Characters_Belts","DZ_Characters_Vests","DZ_Gear_Camping","DZ_Gear_Containers","DZ_Gear_Consumables","DZ_Gear_Drinks","DZ_Gear_Books","ACO_Headgear","ACO_Lower","ACO_Other","ACO_Upper","WindstrideClothing","FOG_Data_Patches","ACO_Core_Attachments","ACO_Headgear_Glasses","ACO_Headgear_Headgear","ACO_Headgear_Masks","ACO_Headgear_Scarves","ACO_Other_Armband","ACO_Other_Backpacks","ACO_Upper_Vests","ACO_Lower_Belts","ACO_Lower_Pants","ACO_Lower_Shoes","ACO_Other_Other","ACO_Upper_Gloves","ACO_Upper_Jackets","ACO_Upper_Tops"};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Clothing;
	class SFP_TacticalMask_Black;
	class HiddenIsles_tacticalmask_Momento: SFP_TacticalMask_Black
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Momento.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Momento.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Momento.paa"};
	};
	class HiddenIsles_tacticalmask_Sith: SFP_TacticalMask_Black
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Sith.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Sith.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Sith.paa"};
	};
	class HiddenIsles_tacticalmask_Oni: SFP_TacticalMask_Black
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Oni.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Oni.paa","HiddenIsles_Retextures_Server\clothing\masks\tacticalmask\Tacticalmask_Oni.paa"};
	};
};
