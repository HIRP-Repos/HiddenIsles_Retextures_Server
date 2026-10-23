////////////////////////////////////////////////////////////////////
//DeRap: equipment\compass\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:50 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Compasses_Retextures
	{
		units[] = {"HiddenIsles_Compass_Grey"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Gear_Navigation"};
	};
};
class CfgVehicles
{
	class Compass;
	class HiddenIsles_Compass_Grey: Compass
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Compass\Compass_Grey.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Grey.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Grey.paa"};
	};
	class HiddenIsles_Compass_Clouds: Compass
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Compass\Compass_Clouds.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Clouds.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Clouds.paa"};
	};
	class HiddenIsles_Compass_Mint: Compass
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Compass\Compass_Mint.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Mint.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Mint.paa"};
	};
	class HiddenIsles_Compass_Tiger: Compass
	{
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Compass\Compass_Tiger.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Tiger.paa","HiddenIsles_Retextures_server\Equipment\Compass\Compass_Tiger.paa"};
	};
};
