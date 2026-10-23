////////////////////////////////////////////////////////////////////
//DeRap: clothing\vests\pressvest\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_PressVest_Retextures
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
	class PressVest_ColorBase;
	class HiddenIsles_PressVest_death: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_death.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_death.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_death.paa"};
	};
	class HiddenIsles_PressVest_greycrow: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_greycrow.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_greycrow.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_greycrow.paa"};
	};
	class HiddenIsles_PressVest_pissoff: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_pissoff.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_pissoff.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_pissoff.paa"};
	};
	class HiddenIsles_PressVest_redcrow: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_redcrow.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_redcrow.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_redcrow.paa"};
	};
	class HiddenIsles_PressVest_whitekobra: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_whitekobra.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_whitekobra.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_whitekobra.paa"};
	};
	class HiddenIsles_PressVest_wild: PressVest_ColorBase
	{
		scope = 2;
		visibilityModifier = 0.95;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_wild.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_wild.paa","HiddenIsles_Retextures_Server\clothing\vests\pressvest\Pressvest_wild.paa"};
	};
};
