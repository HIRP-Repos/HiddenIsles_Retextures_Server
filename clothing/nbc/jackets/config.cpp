////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\jackets\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_NBCJackets_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Tops"};
	};
};
class CfgVehicles
{
	class NBCJacketGray;
	class HiddenIsles_NBCJacket_Black: NBCJacketGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_black.paa"};
	};
	class HiddenIsles_NBCJacket_Camo: NBCJacketGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_camo.paa"};
	};
	class HiddenIsles_NBCJacket_CDC: NBCJacketGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\jackets\nbc_jacket_cdc.paa"};
	};
};
