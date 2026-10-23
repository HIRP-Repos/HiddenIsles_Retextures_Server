////////////////////////////////////////////////////////////////////
//DeRap: clothing\masks\halfmask\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:41 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_HalfMask_Retextures
	{
		units[] = {"HiddenIsles_halfmask_USA"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters","DZ_Characters_Tops","DZ_Characters_Headgear","DZ_Characters_Backpacks","DZ_Characters_Glasses","DZ_Characters_Masks","DZ_Characters_Gloves","DZ_Characters_Shoes","DZ_Characters_Belts","DZ_Characters_Vests","DZ_Gear_Camping","DZ_Gear_Containers","DZ_Gear_Consumables","DZ_Gear_Drinks","DZ_Gear_Books","ACO_Headgear","ACO_Lower","ACO_Other","ACO_Upper","WindstrideClothing","FOG_Data_Patches","ACO_Core_Attachments","ACO_Headgear_Glasses","ACO_Headgear_Headgear","ACO_Headgear_Masks","ACO_Headgear_Scarves","ACO_Other_Armband","ACO_Other_Backpacks","ACO_Upper_Vests","ACO_Lower_Belts","ACO_Lower_Pants","ACO_Lower_Shoes","ACO_Other_Other","ACO_Upper_Gloves","ACO_Upper_Jackets","ACO_Upper_Tops"};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Clothing;
	class FOG_HalfMask_Black;
	class HiddenIsles_halfmask_USA: FOG_HalfMask_Black
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\halfmask\halfmask_USA.paa","HiddenIsles_Retextures_Server\clothing\masks\halfmask\halfmask_USA.paa","HiddenIsles_Retextures_Server\clothing\masks\halfmask\halfmask_USA.paa"};
	};
};
