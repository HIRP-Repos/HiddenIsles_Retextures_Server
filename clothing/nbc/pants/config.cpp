////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\pants\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_NBCPants_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Pants"};
	};
};
class CfgVehicles
{
	class NBCPantsGray;
	class HiddenIsles_NBCPants_Black: NBCPantsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_black.paa"};
	};
	class HiddenIsles_NBCPants_Camo: NBCPantsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_camo.paa"};
	};
	class HiddenIsles_NBCPants_CDC: NBCPantsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\pants\nbc_pants_cdc.paa"};
	};
};
