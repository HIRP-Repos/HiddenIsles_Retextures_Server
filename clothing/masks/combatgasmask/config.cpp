////////////////////////////////////////////////////////////////////
//DeRap: clothing\masks\combatgasmask\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:41 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_GasMasks_Retextures
	{
		units[] = {"HiddenIsles_Gasmask_colors"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Masks"};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Clothing: Clothing_Base{};
	class GasMask: Clothing{};
	class HiddenIsles_Gasmask_BlueGraffiti: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_bluegraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_bluegraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_bluegraffiti.paa"};
	};
	class HiddenIsles_Gasmask_Graffiti: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_graffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_graffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_graffiti.paa"};
	};
	class HiddenIsles_Gasmask_PinkGraffiti: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkgraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkgraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkgraffiti.paa"};
	};
	class HiddenIsles_Gasmask_PurpleGraffiti: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_purplegraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_purplegraffiti.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_purplegraffiti.paa"};
	};
	class HiddenIsles_Gasmask_Colors: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_colors.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_colors.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_colors.paa"};
	};
	class HiddenIsles_Gasmask_PinkRed: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkred.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkred.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkred.paa"};
	};
	class HiddenIsles_Gasmask_PinkUSA: GasMask
	{
		scope = 2;
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkusa.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkusa.paa","HiddenIsles_Retextures_Server\clothing\masks\combatgasmask\gasmask_pinkusa.paa"};
	};
};
