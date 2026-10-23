////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\5\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rock5
	{
		units[] = {"HiddenIsles_Cassette_TheWhiteStripes","HiddenIsles_Cassette_BadDream","HiddenIsles_Cassette_FingerEleven","HiddenIsles_Cassette_Bullet","HiddenIsles_Cassette_Ireallywanttostayatyourhouse","HiddenIsles_Cassette_Bawitdaba","HiddenIsles_Cassette_Legacy","HiddenIsles_Cassette_SweetDreams","HiddenIsles_Cassette_TheBeautifulPeople","HiddenIsles_Cassette_TheUnforgiven","HiddenIsles_Cassette_CrazyTrain","HiddenIsles_Cassette_LivingDeadGirl","HiddenIsles_Cassette_SadButTrue"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_TheWhiteStripes: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Seven Nation Army - The White Stripes";
		descriptionShort = "The White Stripes by Seven Nation Army";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheWhiteStripes";
		};
	};
	class HiddenIsles_Cassette_WrongSideOfHeaven: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Wrong Side Of Heaven - FFDP";
		descriptionShort = "Wrong Side Of Heaven by FFDP";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WrongSideOfHeaven";
		};
	};
	class HiddenIsles_Cassette_FingerEleven: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Finger Eleven - Paralyzer";
		descriptionShort = "Finger Eleven by Paralyzer";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FingerEleven";
		};
	};
	class HiddenIsles_Cassette_Bullet: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Hollywood Undead - Bullet";
		descriptionShort = "Bullet by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Bullet";
		};
	};
	class HiddenIsles_Cassette_Ireallywanttostayatyourhouse: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "I really want to stay at your house - C2077";
		descriptionShort = "I really want to stay at your house by C2077";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Ireallywanttostayatyourhouse";
		};
	};
	class HiddenIsles_Cassette_Bawitdaba: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Kid Rock - Bawitdaba";
		descriptionShort = "Bawitdaba by Kid Rock";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Bawitdaba";
		};
	};
	class HiddenIsles_Cassette_Legacy: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Legacy - FFDP";
		descriptionShort = "Legacy by FFDP";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Legacy";
		};
	};
	class HiddenIsles_Cassette_SweetDreams: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Marilyn Manson - Sweet Dreams";
		descriptionShort = "Sweet Dreams by Marilyn Manson";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SweetDreams";
		};
	};
	class HiddenIsles_Cassette_TheBeautifulPeople: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Marilyn Manson - The Beautiful People";
		descriptionShort = "The Beautiful People by Marilyn Manson";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheBeautifulPeople";
		};
	};
	class HiddenIsles_Cassette_TheUnforgiven: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Metallica - The Unforgiven";
		descriptionShort = "The Unforgiven by Metallica";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheUnforgiven";
		};
	};
	class HiddenIsles_Cassette_CrazyTrain: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Ozzy Osbourne - Crazy Train";
		descriptionShort = "Crazy Train by Ozzy Osbourne";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_CrazyTrain";
		};
	};
	class HiddenIsles_Cassette_LivingDeadGirl: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rob Zombie - Living Dead Girl";
		descriptionShort = "Living Dead Girl by Rob Zombie";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LivingDeadGirl";
		};
	};
	class HiddenIsles_Cassette_SadButTrue: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Metallica - Sad But True";
		descriptionShort = "Sad But True by Metallica";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SadButTrue";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_TheWhiteStripes
	{
		soundShaders[] = {"HiddenIsles_TheWhiteStripes_Shader"};
	};
	class HiddenIsles_SoundSet_WrongSideOfHeaven
	{
		soundShaders[] = {"HiddenIsles_WrongSideOfHeaven_Shader"};
	};
	class HiddenIsles_SoundSet_FingerEleven
	{
		soundShaders[] = {"HiddenIsles_FingerEleven_Shader"};
	};
	class HiddenIsles_SoundSet_Bullet
	{
		soundShaders[] = {"HiddenIsles_Bullet_Shader"};
	};
	class HiddenIsles_SoundSet_Ireallywanttostayatyourhouse
	{
		soundShaders[] = {"HiddenIsles_Ireallywanttostayatyourhouse_Shader"};
	};
	class HiddenIsles_SoundSet_Bawitdaba
	{
		soundShaders[] = {"HiddenIsles_Bawitdaba_Shader"};
	};
	class HiddenIsles_SoundSet_Legacy
	{
		soundShaders[] = {"HiddenIsles_Legacy_Shader"};
	};
	class HiddenIsles_SoundSet_SweetDreams
	{
		soundShaders[] = {"HiddenIsles_SweetDreams_Shader"};
	};
	class HiddenIsles_SoundSet_TheBeautifulPeople
	{
		soundShaders[] = {"HiddenIsles_TheBeautifulPeople_Shader"};
	};
	class HiddenIsles_SoundSet_TheUnforgiven
	{
		soundShaders[] = {"HiddenIsles_TheUnforgiven_Shader"};
	};
	class HiddenIsles_SoundSet_CrazyTrain
	{
		soundShaders[] = {"HiddenIsles_CrazyTrain_Shader"};
	};
	class HiddenIsles_SoundSet_LivingDeadGirl
	{
		soundShaders[] = {"HiddenIsles_LivingDeadGirl_Shader"};
	};
	class HiddenIsles_SoundSet_SadButTrue
	{
		soundShaders[] = {"HiddenIsles_SadButTrue_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_TheWhiteStripes_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\TheWhiteStripes",1}};
	};
	class HiddenIsles_WrongSideOfHeaven_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\WrongSideOfHeaven",1}};
	};
	class HiddenIsles_FingerEleven_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\FingerEleven",1}};
	};
	class HiddenIsles_Bullet_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\Bullet",1}};
	};
	class HiddenIsles_Ireallywanttostayatyourhouse_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\Ireallywanttostayatyourhouse",1}};
	};
	class HiddenIsles_Bawitdaba_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\Bawitdaba",1}};
	};
	class HiddenIsles_Legacy_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\Legacy",1}};
	};
	class HiddenIsles_SweetDreams_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\SweetDreams",1}};
	};
	class HiddenIsles_TheBeautifulPeople_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\TheBeautifulPeople",1}};
	};
	class HiddenIsles_TheUnforgiven_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\TheUnforgiven",1}};
	};
	class HiddenIsles_CrazyTrain_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\CrazyTrain",1}};
	};
	class HiddenIsles_LivingDeadGirl_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\LivingDeadGirl",1}};
	};
	class HiddenIsles_SadButTrue_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\5\sounds\SadButTrue",1}};
	};
};
