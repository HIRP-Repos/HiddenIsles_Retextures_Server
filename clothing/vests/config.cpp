////////////////////////////////////////////////////////////////////
//DeRap: clothing\vests\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Vests_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Data","DZ_Characters_Headgear","DZ_Characters_Pants","DZ_Characters_Tops","DZ_Characters_Vests"};
	};
};
class CfgVehicles
{
	class Clothing;
	class PlateCarrierVest: Clothing
	{
		mappack = 1;
	};
	class PlateCarrierPouches;
	class PlateCarrierHolster;
	class HiddenIsles_PlateCarrierVest_Colorful: PlateCarrierVest
	{
		scope = 2;
		displayName = "Colorful Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Colorful.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Colorful.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Colorful.paa"};
	};
	class HiddenIsles_PlateCarrierVest_GreenSquares: PlateCarrierVest
	{
		scope = 2;
		displayName = "Green Squared Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_GreenSquares.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_GreenSquares.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_GreenSquares.paa"};
	};
	class HiddenIsles_PlateCarrierVest_Hazard: PlateCarrierVest
	{
		scope = 2;
		displayName = "Hazard Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Hazard.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Hazard.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_Hazard.paa"};
	};
	class HiddenIsles_PlateCarrierVest_EvilDevil: PlateCarrierVest
	{
		scope = 2;
		displayName = "Evil Devil Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_EvilDevil.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_EvilDevil.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_EvilDevil.paa"};
	};
	class HiddenIsles_PlateCarrierVest_RedLeopard: PlateCarrierVest
	{
		scope = 2;
		displayName = "Red Leopard Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_RedLeopard.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_RedLeopard.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_RedLeopard.paa"};
	};
	class HiddenIsles_PlateCarrierVest_graffiti: PlateCarrierVest
	{
		scope = 2;
		displayName = "Graffiti Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_graffiti.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_graffiti.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_graffiti.paa"};
	};
	class HiddenIsles_PlateCarrierVest_colorgraffiti: PlateCarrierVest
	{
		scope = 2;
		displayName = "Colored Graffiti Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_colorgraffiti.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_colorgraffiti.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_colorgraffiti.paa"};
	};
	class HiddenIsles_PlateCarrierVest_galaxy: PlateCarrierVest
	{
		scope = 2;
		displayName = "Galaxy Plate Carrier";
		hiddenSelections[] = {"camoGround","camoMale","camoFemale"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_galaxy.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_galaxy.paa","HiddenIsles_Retextures_Server\clothing\vests\data\PlateCarrierVest_galaxy.paa"};
	};
};
