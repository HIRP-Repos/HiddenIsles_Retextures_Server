////////////////////////////////////////////////////////////////////
//DeRap: clothing\nbc\gloves\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:42 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_NBCGloves_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Gloves"};
	};
};
class CfgVehicles
{
	class NBCGlovesGray;
	class HiddenIsles_NBCGloves_Black: NBCGlovesGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_black.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_black.paa"};
	};
	class HiddenIsles_NBCGloves_Camo: NBCGlovesGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_camo.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_camo.paa"};
	};
	class HiddenIsles_NBCGloves_CDC: NBCGlovesGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_cdc.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_cdc.paa"};
	};
	class HiddenIsles_NBCGloves_White: NBCGlovesGray
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_white.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_white.paa","HiddenIsles_Retextures_Server\clothing\nbc\gloves\nbc_gloves_white.paa"};
	};
};
