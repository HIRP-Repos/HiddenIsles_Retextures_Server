////////////////////////////////////////////////////////////////////
//DeRap: equipment\books\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Book_Retextures
	{
		units[] = {"HiddenIsles_Book_DIYManual"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Gear_Books"};
	};
};
class CfgVehicles
{
	class SmallProtectorCase;
	class HiddenIsles_Book: SmallProtectorCase
	{
		scope = 0;
		simulation = "ItemBook";
		displayName = "Books";
		model = "\DZ\gear\books\Book_kniga.p3d";
		hiddenSelections[] = {"camoGround"};
		inventorySlot[] = {"Book_slot"};
		rotationFlags = 1;
		canBeDigged = 1;
		allowOwnedCargoManipulation = 1;
		isMeleeWeapon = 1;
		descriptionShort = "Knowledge is power!";
		weight = 50;
		itemSize[] = {2,2};
		itemsCargoSize[] = {0,0};
		attachments[] = {"Pen1"};
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
	class HiddenIsles_Book_DIYManual: HiddenIsles_Book
	{
		scope = 2;
		displayName = "DIY Manual";
		descriptionShort = "The most complete home improvement manual on the market! Covers all your questions and inquiries of home improvement and construction to make your home more sound!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Books\diymanual.paa","HiddenIsles_Retextures_Server\Equipment\Books\diymanual.paa","HiddenIsles_Retextures_Server\Equipment\Books\diymanual.paa"};
	};
	class HiddenIsles_Book_FirstAidManual: HiddenIsles_Book
	{
		scope = 2;
		displayName = "First-Aid Manual";
		descriptionShort = "A comprehensive course in emergency/wilderness medicine, including how to maximize survival in any climate or when injured.";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Books\firstaidmanual.paa","HiddenIsles_Retextures_Server\Equipment\Books\firstaidmanual.paa","HiddenIsles_Retextures_Server\Equipment\Books\firstaidmanual.paa"};
	};
	class HiddenIsles_Book_ZombieSurvivalGuide: HiddenIsles_Book
	{
		scope = 2;
		displayName = "Zombie Survival Guide";
		descriptionShort = "The Zombie Survival Guide is your key to survival against the hordes of undead who may be stalking you right now. Exhaustively comprehensive, this book covers everything you need to know, including how to understand zombie physiology and behavior, the most effective defense tactics and weaponry, ways to outfit your home for a long siege, and how to survive and adapt in any territory or terrain.";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Books\zombiesurvivalguide.paa","HiddenIsles_Retextures_Server\Equipment\Books\zombiesurvivalguide.paa","HiddenIsles_Retextures_Server\Equipment\Books\zombiesurvivalguide.paa"};
	};
};
