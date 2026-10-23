////////////////////////////////////////////////////////////////////
//DeRap: clothing\belts\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:38 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Belts_Retextures
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters","ACO_Headgear","ACO_Lower","ACO_Other","ACO_Upper","WindstrideClothing","FOG_Data_Patches","ACO_Core_Attachments","ACO_Headgear_Glasses","ACO_Headgear_Headgear","ACO_Headgear_Masks","ACO_Headgear_Scarves","ACO_Other_Armband","ACO_Other_Backpacks","ACO_Upper_Vests","ACO_Lower_Belts","ACO_Lower_Pants","ACO_Lower_Shoes","ACO_Other_Other","ACO_Upper_Gloves","ACO_Upper_Jackets","ACO_Upper_Tops"};
	};
};
class CfgVehicles
{
	class Clothing;
	class CivilianBelt;
	class HiddenIsles_CivilianBelt_Black: CivilianBelt
	{
		displayName = "Black Civilian Belt";
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_black.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_black.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_black.paa"};
	};
	class HiddenIsles_CivilianBelt_White: CivilianBelt
	{
		displayName = "White Civilian Belt";
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_white.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_white.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_white.paa"};
	};
	class HiddenIsles_CivilianBelt_Red: CivilianBelt
	{
		displayName = "Red Civilian Belt";
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_red.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_red.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_red.paa"};
	};
	class HiddenIsles_CivilianBelt_Tan: CivilianBelt
	{
		displayName = "Tan Civilian Belt";
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_tan.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_tan.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_tan.paa"};
	};
	class HiddenIsles_CivilianBelt_Brown: CivilianBelt
	{
		displayName = "Brown Civilian Belt";
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_brown.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_brown.paa","HiddenIsles_Retextures_Server\clothing\belts\civilianbelt_brown.paa"};
	};
};
