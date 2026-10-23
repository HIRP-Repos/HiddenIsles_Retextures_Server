////////////////////////////////////////////////////////////////////
//DeRap: clothing\pins\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:43 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Pins_Retextures
	{
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters"};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Inventory_Base;
	class HiddenIsles_Pin_Rain: Inventory_Base
	{
		scope = 2;
		displayName = "Rain's Pin";
		descriptionShort = "A cute red panda pin, just for Rain!";
		simulation = "inventoryItem";
		weight = 50;
		itemSize[] = {1,1};
		model = "\WindstrideClothing\Models\Pins\Button_Pin\button_pin.p3d";
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_rain.paa"};
		inventorySlot[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6","Pin7","Pin8","Pin9","Pin10","Pin11","Pin12"};
	};
	class HiddenIsles_Pin_Prize1: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "1st Pin";
		descriptionShort = "1st place winner!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_prize1.paa"};
	};
	class HiddenIsles_Pin_Prize2: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "2nd Pin";
		descriptionShort = "2nd place winner!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_prize2.paa"};
	};
	class HiddenIsles_Pin_Prize3: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "3rd Pin";
		descriptionShort = "3rd place winner!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_prize3.paa"};
	};
	class HiddenIsles_Pin_1_Cat: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Cat Pin";
		descriptionShort = "Pin Collection Pack 1, 1/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_cat.paa"};
	};
	class HiddenIsles_Pin_1_Cow: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Cow Pin";
		descriptionShort = "Pin Collection Pack 1, 2/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_cow.paa"};
	};
	class HiddenIsles_Pin_1_Dog: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Dog Pin";
		descriptionShort = "Pin Collection Pack 1, 3/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_dog.paa"};
	};
	class HiddenIsles_Pin_1_Fox: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Fox Pin";
		descriptionShort = "Pin Collection Pack 1, 4/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_fox.paa"};
	};
	class HiddenIsles_Pin_1_Koala: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Koala Pin";
		descriptionShort = "Pin Collection Pack 1, 5/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_koala.paa"};
	};
	class HiddenIsles_Pin_1_Mouse: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Mouse Pin";
		descriptionShort = "Pin Collection Pack 1, 6/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_mouse.paa"};
	};
	class HiddenIsles_Pin_1_Raccoon: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Raccoon Pin";
		descriptionShort = "Pin Collection Pack 1, 7/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_raccoon.paa"};
	};
	class HiddenIsles_Pin_1_Redpanda: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Redpanda Pin";
		descriptionShort = "Pin Collection Pack 1, 8/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_redpanda.paa"};
	};
	class HiddenIsles_Pin_1_Skunk: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Skunk Pin";
		descriptionShort = "Pin Collection Pack 1, 9/9";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_1_skunk.paa"};
	};
	class HiddenIsles_Pin_2_Aquarius: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Aquarius Pin";
		descriptionShort = "Pin Collection Pack 2, 1/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_aquarius.paa"};
	};
	class HiddenIsles_Pin_2_Aries: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Aries Pin";
		descriptionShort = "Pin Collection Pack 2, 2/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_aries.paa"};
	};
	class HiddenIsles_Pin_2_Cancer: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Cancer Pin";
		descriptionShort = "Pin Collection Pack 2, 3/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_cancer.paa"};
	};
	class HiddenIsles_Pin_2_Capricorn: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Capricorn Pin";
		descriptionShort = "Pin Collection Pack 2, 4/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_capricorn.paa"};
	};
	class HiddenIsles_Pin_2_Gemini: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Gemini Pin";
		descriptionShort = "Pin Collection Pack 2, 5/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_gemini.paa"};
	};
	class HiddenIsles_Pin_2_Leo: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Leo Pin";
		descriptionShort = "Pin Collection Pack 2, 6/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_leo.paa"};
	};
	class HiddenIsles_Pin_2_Libra: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Libra Pin";
		descriptionShort = "Pin Collection Pack 2, 7/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_libra.paa"};
	};
	class HiddenIsles_Pin_2_Pisces: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Pisces Pin";
		descriptionShort = "Pin Collection Pack 2, 8/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_pisces.paa"};
	};
	class HiddenIsles_Pin_2_Sagittarius: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Sagittarius Pin";
		descriptionShort = "Pin Collection Pack 2, 9/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_sagittarius.paa"};
	};
	class HiddenIsles_Pin_2_Scorpio: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Scorpio Pin";
		descriptionShort = "Pin Collection Pack 2, 10/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_scorpio.paa"};
	};
	class HiddenIsles_Pin_2_Taurus: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Taurus Pin";
		descriptionShort = "Pin Collection Pack 2, 11/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_taurus.paa"};
	};
	class HiddenIsles_Pin_2_Virgo: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Virgo Pin";
		descriptionShort = "Pin Collection Pack 2, 12/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_2_virgo.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyWink: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Wink Pin";
		descriptionShort = "Pin Collection Pack 3, 1/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittywink.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyWave: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Wave Pin";
		descriptionShort = "Pin Collection Pack 3, 2/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittywave.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyScared: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Scared Pin";
		descriptionShort = "Pin Collection Pack 3, 3/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittyscared.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyCool: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Cool Pin";
		descriptionShort = "Pin Collection Pack 3, 4/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittycool.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyLaugh: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Laugh Pin";
		descriptionShort = "Pin Collection Pack 3, 5/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittylaugh.paa"};
	};
	class HiddenIsles_Pin_3_HelloKittyCry: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Hellokitty Cry Pin";
		descriptionShort = "Pin Collection Pack 3, 6/6";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_3_hellokittycry.paa"};
	};
	class HiddenIsles_Pin_4_Apocalypse: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Apocalypse Pin";
		descriptionShort = "Pin Collection Pack 4, 1/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_apocalypse.paa"};
	};
	class HiddenIsles_Pin_4_Apocalypse2: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Apocalypse 2 Pin";
		descriptionShort = "Pin Collection Pack 4, 2/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_apocalypse2.paa"};
	};
	class HiddenIsles_Pin_4_ApocalypseBunny: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Apocalypse Bunny Pin";
		descriptionShort = "Pin Collection Pack 4, 3/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_apocalypsebunny.paa"};
	};
	class HiddenIsles_Pin_4_Gasmask: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Gasmask Pin";
		descriptionShort = "Pin Collection Pack 4, 4/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_gasmask.paa"};
	};
	class HiddenIsles_Pin_4_ResponseTeam: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Response Team Pin";
		descriptionShort = "Pin Collection Pack 4, 5/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_responseteam.paa"};
	};
	class HiddenIsles_Pin_4_SpongebobWar: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Spongebob War Pin";
		descriptionShort = "Pin Collection Pack 4, 6/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_spongebobwar.paa"};
	};
	class HiddenIsles_Pin_4_ZombieHand: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Zombie Hand Pin";
		descriptionShort = "Pin Collection Pack 4, 7/7";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_4_zombiehand.paa"};
	};
	class HiddenIsles_Pin_5_Girl1: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 1 Pin";
		descriptionShort = "Pin Collection Pack 5, 1/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl1.paa"};
	};
	class HiddenIsles_Pin_5_Girl2: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 2 Pin";
		descriptionShort = "Pin Collection Pack 5, 2/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl2.paa"};
	};
	class HiddenIsles_Pin_5_Girl3: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 3 Pin";
		descriptionShort = "Pin Collection Pack 5, 3/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl3.paa"};
	};
	class HiddenIsles_Pin_5_Girl4: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 4 Pin";
		descriptionShort = "Pin Collection Pack 5, 4/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl4.paa"};
	};
	class HiddenIsles_Pin_5_Girl5: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 5 Pin";
		descriptionShort = "Pin Collection Pack 5, 5/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl5.paa"};
	};
	class HiddenIsles_Pin_5_Girl6: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 6 Pin";
		descriptionShort = "Pin Collection Pack 5, 6/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl6.paa"};
	};
	class HiddenIsles_Pin_5_Girl7: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 7 Pin";
		descriptionShort = "Pin Collection Pack 5, 7/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl7.paa"};
	};
	class HiddenIsles_Pin_5_Girl8: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 8 Pin";
		descriptionShort = "Pin Collection Pack 5, 8/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl8.paa"};
	};
	class HiddenIsles_Pin_5_Girl9: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 9 Pin";
		descriptionShort = "Pin Collection Pack 5, 9/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl9.paa"};
	};
	class HiddenIsles_Pin_5_Girl10: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 10 Pin";
		descriptionShort = "Pin Collection Pack 5, 10/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl10.paa"};
	};
	class HiddenIsles_Pin_5_Girl11: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 11 Pin";
		descriptionShort = "Pin Collection Pack 5, 11/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl11.paa"};
	};
	class HiddenIsles_Pin_5_Girl12: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Girl 12 Pin";
		descriptionShort = "Pin Collection Pack 5, 12/12";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_5_girl12.paa"};
	};
	class HiddenIsles_Pin_6_Santa: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Santa Pin";
		descriptionShort = "Pin Collection Pack 6, 1/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_santa.paa"};
	};
	class HiddenIsles_Pin_6_Deer: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Deer Pin";
		descriptionShort = "Pin Collection Pack 6, 2/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_deer.paa"};
	};
	class HiddenIsles_Pin_6_Snowman: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Snowman Pin";
		descriptionShort = "Pin Collection Pack 6, 3/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_snowman.paa"};
	};
	class HiddenIsles_Pin_6_Polarbear: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Polarbear Pin";
		descriptionShort = "Pin Collection Pack 6, 4/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_polarbear.paa"};
	};
	class HiddenIsles_Pin_6_GingerBreadMan: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Gingerbread Man Pin";
		descriptionShort = "Pin Collection Pack 6, 5/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_gingerbreadman.paa"};
	};
	class HiddenIsles_Pin_6_XmasTree: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Xmas Tree Pin";
		descriptionShort = "Pin Collection Pack 6, 6/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_xmastree.paa"};
	};
	class HiddenIsles_Pin_6_CandyCane: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Candy Cane Pin";
		descriptionShort = "Pin Collection Pack 6, 7/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_candycane.paa"};
	};
	class HiddenIsles_Pin_6_Ribbon: HiddenIsles_Pin_Rain
	{
		scope = 2;
		displayName = "Ribbon Pin";
		descriptionShort = "Pin Collection Pack 6, 8/8";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\pins\pin_6_ribbon.paa"};
	};
};
