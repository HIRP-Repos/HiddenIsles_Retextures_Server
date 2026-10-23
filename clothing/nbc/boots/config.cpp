////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\boots\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_NBCBoots_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Shoes"};
	};
};
class CfgVehicles
{
	class NBCBootsGray;
	class HiddenIsles_NBCBoots_Black: NBCBootsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_black.paa"};
	};
	class HiddenIsles_NBCBoots_Camo: NBCBootsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_camo.paa"};
	};
	class HiddenIsles_NBCBoots_CDC: NBCBootsGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\boots\nbc_boots_cdc.paa"};
	};
};
