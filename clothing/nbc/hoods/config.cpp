////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\hoods\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_NBCHoods_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Headgear"};
	};
};
class CfgVehicles
{
	class NBCHoodGray;
	class HiddenIsles_NBCHood_Black: NBCHoodGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_black.paa"};
	};
	class HiddenIsles_NBCHood_Camo: NBCHoodGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_camo.paa"};
	};
	class HiddenIsles_NBCHood_CDC: NBCHoodGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\hoods\nbc_hood_cdc.paa"};
	};
};
