////////////////////////////////////////////////////////////////////
//DeRap: clothing\vests\police\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_PoliceVest_Retextures
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Characters_Headgear","DZ_Data"};
	};
};
class CfgVehicles
{
	class Clothing;
	class FOG_Vest_MMAC_Black;
	class HiddenIsles_MMAC_SWAT: FOG_Vest_MMAC_Black
	{
		scope = 2;
		displayName = "SWAT Vest";
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\police\mmac_SWAT.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_SWAT.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_SWAT.paa"};
	};
	class HiddenIsles_MMAC_police: FOG_Vest_MMAC_Black
	{
		scope = 2;
		displayName = "FLPD Vest";
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\police\mmac_police.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_police.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_police.paa"};
	};
	class HiddenIsles_MMAC_ems: FOG_Vest_MMAC_Black
	{
		scope = 2;
		displayName = "EMS Vest";
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\police\mmac_ems.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_ems.paa","HiddenIsles_Retextures_Server\clothing\vests\police\mmac_ems.paa"};
	};
};
