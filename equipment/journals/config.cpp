////////////////////////////////////////////////////////////////////
//DeRap: equipment\journals\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:50 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Journals_Retextures
	{
		units[] = {"HiddenIsles_Donator_Journal_Rain"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Gear_Books"};
	};
};
class CfgVehicles
{
	class ItemBook;
	class Inventory_Base;
	class Pen_ColorBase: Inventory_Base
	{
		inventorySlot[] = {"EmPen1"};
	};
	class HiddenIsles_Journal: ItemBook
	{
		scope = 0;
		simulation = "ItemBook";
		model = "\DZ\gear\books\Book_kniga.p3d";
		hiddenSelections[] = {"camoGround"};
		inventorySlot[] = {"Book_slot"};
		rotationFlags = 1;
		canBeDigged = 1;
		allowOwnedCargoManipulation = 1;
		isMeleeWeapon = 1;
		weight = 50;
		itemSize[] = {2,2};
		attachments[] = {"EmPen1","Paper","DzrPaper1","DzrPaper2","DzrPaper3","DzrPaper4","DzrPaper5","DzrPaper6","DzrPaper7","DzrPaper8","DzrPaper9","DzrPaper11","DzrPaper12","DzrPaper13","DzrPaper14","DzrPaper15","DzrPaper16","DzrPaper17","DzrPaper18","DzrPaper19","DzrPaper20","DzrPaper21","DzrPaper22","DzrPaper23"};
		quantityShow = 0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\books\Data\book.rvmat"}},{0.7,{"DZ\gear\books\Data\book.rvmat"}},{0.5,{"DZ\gear\books\Data\book_damage.rvmat"}},{0.3,{"DZ\gear\books\Data\book_damage.rvmat"}},{0,{"DZ\gear\books\Data\book_destruct.rvmat"}}};
				};
			};
		};
	};
	class HiddenIsles_Journal_ColorfulCar: HiddenIsles_Journal
	{
		scope = 2;
		displayName = "Car Journal";
		descriptionShort = "A journal to write your deepest and darkest secrets in!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Journals\colorfulcar.paa","HiddenIsles_Retextures_server\Equipment\Journals\colorfulcar.paa","HiddenIsles_Retextures_server\Equipment\Journals\colorfulcar.paa"};
	};
	class HiddenIsles_Journal_StayWild: HiddenIsles_Journal
	{
		scope = 2;
		displayName = "Stay Wild Journal";
		descriptionShort = "A journal to write your deepest and darkest secrets in!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Journals\staywild.paa","HiddenIsles_Retextures_server\Equipment\Journals\staywild.paa","HiddenIsles_Retextures_server\Equipment\Journals\staywild.paa"};
	};
	class HiddenIsles_Journal_Tiger: HiddenIsles_Journal
	{
		scope = 2;
		displayName = "Tiger Journal";
		descriptionShort = "A journal to write your deepest and darkest secrets in!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Journals\tiger.paa","HiddenIsles_Retextures_server\Equipment\Journals\tiger.paa","HiddenIsles_Retextures_server\Equipment\Journals\tiger.paa"};
	};
	class HiddenIsles_Donator_Journal_Rain: HiddenIsles_Journal
	{
		scope = 2;
		displayName = "Rain's Journal";
		descriptionShort = "A journal to write your deepest and darkest secrets in!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Journals\journal_rain.paa","HiddenIsles_Retextures_server\Equipment\Journals\journal_rain.paa","HiddenIsles_Retextures_server\Equipment\Journals\journal_rain.paa"};
	};
};
class CfgSlots
{
	class Slot_EmPen1
	{
		name = "EmPen1";
		displayName = "Pen";
		ghostIcon = "default";
		show = "true";
	};
};
