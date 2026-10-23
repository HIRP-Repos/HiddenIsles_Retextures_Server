////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\7\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:50 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rock7
	{
		units[] = {"HiddenIsles_Cassette_NeroForte","HiddenIsles_Cassette_BadDream","HiddenIsles_Cassette_SISOSIG","HiddenIsles_Cassette_TimesLikeThese","HiddenIsles_Cassette_WelcomeToTheCircus","HiddenIsles_Cassette_YallWantaSingle","HiddenIsles_Cassette_CatsInTheCradle","HiddenIsles_Cassette_DangerLine","HiddenIsles_Cassette_HouseOfMirrors","HiddenIsles_Cassette_InkSpots","HiddenIsles_Cassette_HowYouRemindMe","HiddenIsles_Cassette_SummerOf69"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_NeroForte: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Nero Forte - Slipknot";
		descriptionShort = "Nero Forte by Slipknot";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_NeroForte";
		};
	};
	class HiddenIsles_Cassette_PianoMan: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Piano Man - Billy Joel ";
		descriptionShort = "Piano Man by Billy Joel";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PianoMan";
		};
	};
	class HiddenIsles_Cassette_SISOSIG: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Should I Stay or Should I Go - The Clash ";
		descriptionShort = "Should I Stay or Should I Go by The Clash ";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SISOSIG";
		};
	};
	class HiddenIsles_Cassette_TimesLikeThese: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Times Like These - FFDP ";
		descriptionShort = "Times Like These by FFDP";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TimesLikeThese";
		};
	};
	class HiddenIsles_Cassette_WelcomeToTheCircus: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Welcome To The Circus - FFDP";
		descriptionShort = "Welcome To The Circus by FFDP";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WelcomeToTheCircus";
		};
	};
	class HiddenIsles_Cassette_YallWantaSingle: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Y'all Want a Single - Korn";
		descriptionShort = "Y'all Want a Single by Korn";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_YallWantaSingle";
		};
	};
	class HiddenIsles_Cassette_CatsInTheCradle: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Cat's In The Cradle - Harry Chaplin";
		descriptionShort = "Cat's In The Cradle - Harry Chaplin";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_CatsInTheCradle";
		};
	};
	class HiddenIsles_Cassette_DangerLine: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Danger Line - Avenged Sevenfold";
		descriptionShort = "Danger Line - Avenged Sevenfold";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DangerLine";
		};
	};
	class HiddenIsles_Cassette_HouseOfMirrors: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "House of Mirrors - Hollywood Undead";
		descriptionShort = "House of Mirrors - Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HouseOfMirrors";
		};
	};
	class HiddenIsles_Cassette_InkSpots: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "I dont want to set the world on fire - Ink Spots";
		descriptionShort = "I dont want to set the world on fire - Ink Spots";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_InkSpots";
		};
	};
	class HiddenIsles_Cassette_HowYouRemindMe: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "How You Remind Me - Nickelback";
		descriptionShort = "How You Remind Me - Nickelback";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HowYouRemindMe";
		};
	};
	class HiddenIsles_Cassette_Zombie: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Zombie - The Cranberries";
		descriptionShort = "Zombie by The Cranberries";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Zombie";
		};
	};
	class HiddenIsles_Cassette_SummerOf69: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Summer of 69 - Bryan Adams";
		descriptionShort = "Summer of 69 by Bryan Adams";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SummerOf69";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_NeroForte
	{
		soundShaders[] = {"HiddenIsles_NeroForte_Shader"};
	};
	class HiddenIsles_SoundSet_PianoMan
	{
		soundShaders[] = {"HiddenIsles_PianoMan_Shader"};
	};
	class HiddenIsles_SoundSet_SISOSIG
	{
		soundShaders[] = {"HiddenIsles_SISOSIG_Shader"};
	};
	class HiddenIsles_SoundSet_TimesLikeThese
	{
		soundShaders[] = {"HiddenIsles_TimesLikeThese_Shader"};
	};
	class HiddenIsles_SoundSet_WelcomeToTheCircus
	{
		soundShaders[] = {"HiddenIsles_WelcomeToTheCircus_Shader"};
	};
	class HiddenIsles_SoundSet_YallWantaSingle
	{
		soundShaders[] = {"HiddenIsles_YallWantaSingle_Shader"};
	};
	class HiddenIsles_SoundSet_CatsInTheCradle
	{
		soundShaders[] = {"HiddenIsles_CatsInTheCradle_Shader"};
	};
	class HiddenIsles_SoundSet_DangerLine
	{
		soundShaders[] = {"HiddenIsles_DangerLine_Shader"};
	};
	class HiddenIsles_SoundSet_HouseOfMirrors
	{
		soundShaders[] = {"HiddenIsles_HouseOfMirrors_Shader"};
	};
	class HiddenIsles_SoundSet_InkSpots
	{
		soundShaders[] = {"HiddenIsles_InkSpots_Shader"};
	};
	class HiddenIsles_SoundSet_HowYouRemindMe
	{
		soundShaders[] = {"HiddenIsles_HowYouRemindMe_Shader"};
	};
	class HiddenIsles_SoundSet_Zombie
	{
		soundShaders[] = {"HiddenIsles_Zombie_Shader"};
	};
	class HiddenIsles_SoundSet_SummerOf69
	{
		soundShaders[] = {"HiddenIsles_SummerOf69_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_NeroForte_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\NeroForte",1}};
	};
	class HiddenIsles_PianoMan_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\PianoMan",1}};
	};
	class HiddenIsles_SISOSIG_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\SISOSIG",1}};
	};
	class HiddenIsles_TimesLikeThese_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\TimesLikeThese",1}};
	};
	class HiddenIsles_WelcomeToTheCircus_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\WelcomeToTheCircus",1}};
	};
	class HiddenIsles_YallWantaSingle_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\YallWantaSingle",1}};
	};
	class HiddenIsles_CatsInTheCradle_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\CatsInTheCradle",1}};
	};
	class HiddenIsles_DangerLine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\DangerLine",1}};
	};
	class HiddenIsles_HouseOfMirrors_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\HouseOfMirrors",1}};
	};
	class HiddenIsles_InkSpots_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\InkSpots",1}};
	};
	class HiddenIsles_HowYouRemindMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\HowYouRemindMe",1}};
	};
	class HiddenIsles_Zombie_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\Zombie",1}};
	};
	class HiddenIsles_SummerOf69_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\7\sounds\SummerOf69",1}};
	};
};
