////////////////////////////////////////////////////////////////////
//DeRap: clothing\hats\witchhood\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:41 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_WitchHood_Retextures
	{
		units[] = {"HiddenIsles_witchhood_purple"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters"};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Clothing;
	class WitchHood_Black;
	class HiddenIsles_witchhood_white: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_white.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_white.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_white.paa"};
	};
	class HiddenIsles_witchhood_purple: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_purple.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_purple.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_purple.paa"};
	};
	class HiddenIsles_witchhood_pink: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_pink.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_pink.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_pink.paa"};
	};
	class HiddenIsles_witchhood_grey: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_grey.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_grey.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_grey.paa"};
	};
	class HiddenIsles_witchhood_green: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_green.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_green.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_green.paa"};
	};
	class HiddenIsles_witchhood_cyan: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_cyan.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_cyan.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_cyan.paa"};
	};
	class HiddenIsles_witchhood_blue: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_blue.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_blue.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_blue.paa"};
	};
	class HiddenIsles_witchhood_yellow: WitchHood_Black
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_yellow.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_yellow.paa","HiddenIsles_Retextures_Server\clothing\hats\witchhood\witchhood_yellow.paa"};
	};
};
