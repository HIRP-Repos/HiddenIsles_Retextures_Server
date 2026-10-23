////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\phonkedm\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_PhonkEdm
	{
		units[] = {"HiddenIsles_Cassette_DevilNight","HiddenIsles_Cassette_MoneyOnTheDash","HiddenIsles_Cassette_LandOfFire","HiddenIsles_Cassette_Crystals","HiddenIsles_Cassette_Goodbye","HiddenIsles_Cassette_FlyAway","HiddenIsles_Cassette_TheStorm","HiddenIsles_Cassette_CloseToTheSun","HiddenIsles_Cassette_WhyDoI","HiddenIsles_Cassette_Buster"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_DevilNight: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Tokyomane - Devil Night";
		descriptionShort = "Devil Night by Tokyomane";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\DevilNight.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DevilNight";
		};
	};
	class HiddenIsles_Cassette_MoneyOnTheDash: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Elley Duhe - Money On The Dash";
		descriptionShort = "Money On The Dash by Elley Duhe & Whethan";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\MoneyOnTheDash.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_MoneyOnTheDash";
		};
	};
	class HiddenIsles_Cassette_LandOfFire: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Kordhell - Land Of Fire";
		descriptionShort = "Land Of Fire by Kordhell";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\LandOfFire.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LandOfFire";
		};
	};
	class HiddenIsles_Cassette_Crystals: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "isolate.exe - Crystals";
		descriptionShort = "Crystals by isolate.exe";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\Crystals.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Crystals";
		};
	};
	class HiddenIsles_Cassette_Goodbye: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "AREZRA - Goodbye";
		descriptionShort = "Goodbye by AREZRA";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\Goodbye.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Goodbye";
		};
	};
	class HiddenIsles_Cassette_FlyAway: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "TheFatRat - Fly Away";
		descriptionShort = "Fly Away by TheFatRat";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\FlyAway.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FlyAway";
		};
	};
	class HiddenIsles_Cassette_TheStorm: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "TheFatRat - The Storm";
		descriptionShort = "The Storm by TheFatRat";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\TheStorm.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheStorm";
		};
	};
	class HiddenIsles_Cassette_CloseToTheSun: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "TheFatRat - Close To The Sun";
		descriptionShort = "Close To The Sun by TheFatRat";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\CloseToTheSun.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_CloseToTheSun";
		};
	};
	class HiddenIsles_Cassette_WhyDoI: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Unknown Brain - Why Do I";
		descriptionShort = "Why Do I by Unknown Brain";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\WhyDoI.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WhyDoI";
		};
	};
	class HiddenIsles_Cassette_Buster: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "$atori Zoom - Buster";
		descriptionShort = "Buster by $atori Zoom";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\paa\Buster.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Buster";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_DevilNight
	{
		soundShaders[] = {"HiddenIsles_DevilNight_Shader"};
	};
	class HiddenIsles_SoundSet_MoneyOnTheDash
	{
		soundShaders[] = {"HiddenIsles_MoneyOnTheDash_Shader"};
	};
	class HiddenIsles_SoundSet_LandOfFire
	{
		soundShaders[] = {"HiddenIsles_LandOfFire_Shader"};
	};
	class HiddenIsles_SoundSet_Crystals
	{
		soundShaders[] = {"HiddenIsles_Crystals_Shader"};
	};
	class HiddenIsles_SoundSet_Goodbye
	{
		soundShaders[] = {"HiddenIsles_Goodbye_Shader"};
	};
	class HiddenIsles_SoundSet_FlyAway
	{
		soundShaders[] = {"HiddenIsles_FlyAway_Shader"};
	};
	class HiddenIsles_SoundSet_TheStorm
	{
		soundShaders[] = {"HiddenIsles_TheStorm_Shader"};
	};
	class HiddenIsles_SoundSet_CloseToTheSun
	{
		soundShaders[] = {"HiddenIsles_CloseToTheSun_Shader"};
	};
	class HiddenIsles_SoundSet_WhyDoI
	{
		soundShaders[] = {"HiddenIsles_WhyDoI_Shader"};
	};
	class HiddenIsles_SoundSet_Buster
	{
		soundShaders[] = {"HiddenIsles_Buster_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_DevilNight_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\DevilNight",1}};
	};
	class HiddenIsles_MoneyOnTheDash_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\MoneyOnTheDash",1}};
	};
	class HiddenIsles_LandOfFire_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\LandOfFire",1}};
	};
	class HiddenIsles_Crystals_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\Crystals",1}};
	};
	class HiddenIsles_Goodbye_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\Goodbye",1}};
	};
	class HiddenIsles_FlyAway_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\FlyAway",1}};
	};
	class HiddenIsles_TheStorm_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\TheStorm",1}};
	};
	class HiddenIsles_CloseToTheSun_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\CloseToTheSun",1}};
	};
	class HiddenIsles_WhyDoI_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\WhyDoI",1}};
	};
	class HiddenIsles_Buster_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\phonkedm\sounds\Buster",1}};
	};
};
