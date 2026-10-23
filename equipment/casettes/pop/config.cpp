////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\pop\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:48 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Pop
	{
		units[] = {"HiddenIsles_Cassette_BDOML","HiddenIsles_Cassette_BadDream","HiddenIsles_Cassette_BadDreams","HiddenIsles_Cassette_LoveGoesOn","HiddenIsles_Cassette_WomanoftheHour","HiddenIsles_Cassette_Circles","HiddenIsles_Cassette_TheDayItRained","HiddenIsles_Cassette_LovinOnMe","HiddenIsles_Cassette_TeAmo","HiddenIsles_Cassette_OopsIDidItAgain","HiddenIsles_Cassette_YMCA","HiddenIsles_Cassette_GimmeMore","HiddenIsles_Cassette_PopMuzik"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_BDOML: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "American Authors - Best Day Of My Life";
		descriptionShort = "Best Day Of My Life by American Authors";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\BDOML.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BDOML";
		};
	};
	class HiddenIsles_Cassette_BadDream: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Stellar - Bad Dream";
		descriptionShort = "Bad Dream by Stellar";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\BadDream.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BadDream";
		};
	};
	class HiddenIsles_Cassette_BadDreams: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Teddy Swims - Bad Dreams";
		descriptionShort = "Bad Dreams by Teddy Swims";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\BadDreams.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BadDreams";
		};
	};
	class HiddenIsles_Cassette_LoveGoesOn: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Lindsey Stirling - Love Goes On and On";
		descriptionShort = "Love Goes On and On by Lindsey Stirling feat. Amy Lee-Love";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\LoveGoesOn.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LoveGoesOn";
		};
	};
	class HiddenIsles_Cassette_WomanoftheHour: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Stela Cole - Woman of the Hour";
		descriptionShort = "Woman of the Hour by Stela Cole";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\WomanoftheHour.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WomanoftheHour";
		};
	};
	class HiddenIsles_Cassette_Circles: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "SAINt JHN - Circles";
		descriptionShort = "Circles by SAINt JHN";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\Circles.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Circles";
		};
	};
	class HiddenIsles_Cassette_TheDayItRained: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Stela Cole - The Day It Rained in Southern California";
		descriptionShort = "The Day It Rained in Southern California by Stela Cole";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\TheDayItRained.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheDayItRained";
		};
	};
	class HiddenIsles_Cassette_LovinOnMe: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Jack Harlow - Lovin On Me";
		descriptionShort = "lovin On Me by Jack Harlow";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\LovinOnMe.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LovinOnMe";
		};
	};
	class HiddenIsles_Cassette_TeAmo: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rihanna - Te Amo";
		descriptionShort = "Te Amo by Rihanna";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\TeAmo.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TeAmo";
		};
	};
	class HiddenIsles_Cassette_OopsIDidItAgain: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Britney Spears - Oops!... I Did It Again";
		descriptionShort = "Oops!... I Did It Again by Britney Spears";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\OopsIDidItAgain.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_OopsIDidItAgain";
		};
	};
	class HiddenIsles_Cassette_YMCA: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Village People - YMCA";
		descriptionShort = "YMCA by Village People";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\YMCA.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_YMCA";
		};
	};
	class HiddenIsles_Cassette_GimmeMore: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Britney Spears - Gimme More";
		descriptionShort = "Gimme More by Britney Spears";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\GimmeMore.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_GimmeMore";
		};
	};
	class HiddenIsles_Cassette_PopMuzik: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Robin Scott - Pop Muzik";
		descriptionShort = "Pop Muzik by Robin Scott";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\paa\PopMuzik.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PopMuzik";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_BDOML
	{
		soundShaders[] = {"HiddenIsles_BDOML_Shader"};
	};
	class HiddenIsles_SoundSet_BadDream
	{
		soundShaders[] = {"HiddenIsles_BadDream_Shader"};
	};
	class HiddenIsles_SoundSet_BadDreams
	{
		soundShaders[] = {"HiddenIsles_BadDreams_Shader"};
	};
	class HiddenIsles_SoundSet_LoveGoesOn
	{
		soundShaders[] = {"HiddenIsles_LoveGoesOn_Shader"};
	};
	class HiddenIsles_SoundSet_WomanoftheHour
	{
		soundShaders[] = {"HiddenIsles_WomanoftheHour_Shader"};
	};
	class HiddenIsles_SoundSet_Circles
	{
		soundShaders[] = {"HiddenIsles_Circles_Shader"};
	};
	class HiddenIsles_SoundSet_TheDayItRained
	{
		soundShaders[] = {"HiddenIsles_TheDayItRained_Shader"};
	};
	class HiddenIsles_SoundSet_LovinOnMe
	{
		soundShaders[] = {"HiddenIsles_LovinOnMe_Shader"};
	};
	class HiddenIsles_SoundSet_TeAmo
	{
		soundShaders[] = {"HiddenIsles_TeAmo_Shader"};
	};
	class HiddenIsles_SoundSet_OopsIDidItAgain
	{
		soundShaders[] = {"HiddenIsles_OopsIDidItAgain_Shader"};
	};
	class HiddenIsles_SoundSet_YMCA
	{
		soundShaders[] = {"HiddenIsles_YMCA_Shader"};
	};
	class HiddenIsles_SoundSet_GimmeMore
	{
		soundShaders[] = {"HiddenIsles_GimmeMore_Shader"};
	};
	class HiddenIsles_SoundSet_PopMuzik
	{
		soundShaders[] = {"HiddenIsles_PopMuzik_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_BDOML_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\BDOML",1}};
	};
	class HiddenIsles_BadDream_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\BadDream",1}};
	};
	class HiddenIsles_BadDreams_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\BadDreams",1}};
	};
	class HiddenIsles_LoveGoesOn_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\LoveGoesOn",1}};
	};
	class HiddenIsles_WomanoftheHour_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\WomanoftheHour",1}};
	};
	class HiddenIsles_Circles_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\Circles",1}};
	};
	class HiddenIsles_TheDayItRained_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\TheDayItRained",1}};
	};
	class HiddenIsles_LovinOnMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\LovinOnMe",1}};
	};
	class HiddenIsles_TeAmo_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\TeAmo",1}};
	};
	class HiddenIsles_OopsIDidItAgain_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\OopsIDidItAgain",1}};
	};
	class HiddenIsles_YMCA_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\YMCA",1}};
	};
	class HiddenIsles_GimmeMore_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\GimmeMore",1}};
	};
	class HiddenIsles_PopMuzik_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\sounds\PopMuzik",1}};
	};
};
