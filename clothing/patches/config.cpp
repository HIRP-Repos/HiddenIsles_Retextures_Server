////////////////////////////////////////////////////////////////////
//DeRap: clothing\patches\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:43 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Patches_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Shoes"};
	};
};
class CfgVehicles
{
	class ALV_Patch_USA;
	class FOG_Big_Patch_Base;
	class FOG_Small_Patch_Base;
	class HiddenIsles_Patch_SWAT: ALV_Patch_USA
	{
		scope = 2;
		displayName = "ALV SWAT Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\patch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\patch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\patch_swat.paa"};
	};
	class HiddenIsles_BigPatch_SWAT: FOG_Big_Patch_Base
	{
		scope = 2;
		displayName = "FOG Big SWAT Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\bigpatch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\bigpatch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\bigpatch_swat.paa"};
	};
	class HiddenIsles_SmallPatch_SWAT: FOG_Small_Patch_Base
	{
		scope = 2;
		displayName = "FOG Small SWAT Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\smallpatch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\smallpatch_swat.paa","HiddenIsles_Retextures_Server\clothing\patches\smallpatch_swat.paa"};
	};
	class HiddenIsles_Patch_EMS: ALV_Patch_USA
	{
		scope = 2;
		displayName = "ALV EMS Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\patch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\patch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\patch_ems.paa"};
	};
	class HiddenIsles_BigPatch_EMS: FOG_Big_Patch_Base
	{
		scope = 2;
		displayName = "FOG Big EMS Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\bigpatch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\bigpatch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\bigpatch_ems.paa"};
	};
	class HiddenIsles_SmallPatch_EMS: FOG_Small_Patch_Base
	{
		scope = 2;
		displayName = "FOG Small EMS Patch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\patches\smallpatch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\smallpatch_ems.paa","HiddenIsles_Retextures_Server\clothing\patches\smallpatch_ems.paa"};
	};
};
