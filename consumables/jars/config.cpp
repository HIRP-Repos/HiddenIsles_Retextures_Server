////////////////////////////////////////////////////////////////////
//DeRap: consumables\jars\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Food_Jars_Retextures
	{
		units[] = {"HiddenIsles_Applesauce"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Gear_Food"};
	};
};
class CfgVehicles
{
	class Marmalade;
	class HiddenIsles_Applesauce: Marmalade
	{
		displayName = "Jar full of Applesauce";
		descriptionShort = "Works great with most foods!";
		hiddenSelections[] = {"zbytek","camo"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\consumables\Jars\Applesauce.paa"};
	};
	class HiddenIsles_OrangeMarmalade: Marmalade
	{
		displayName = "Jar of Orange Marmalade";
		descriptionShort = "Great on some toast";
		hiddenSelections[] = {"zbytek","camo"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\consumables\Jars\OrangeMarmalade.paa"};
	};
	class HiddenIsles_PeanutButter: Marmalade
	{
		displayName = "Jar of Peanut butter";
		descriptionShort = "Great with some jam, or, on its own!";
		hiddenSelections[] = {"zbytek","camo"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\consumables\Jars\PeanutButter.paa"};
	};
};
