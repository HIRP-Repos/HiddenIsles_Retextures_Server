////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\other\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Other
	{
		units[] = {"HiddenIsles_Cassette_TeddyPicnic","HiddenIsles_Cassette_EasyStreet","HiddenIsles_Cassette_Tulips","HiddenIsles_Cassette_TheGhost","HiddenIsles_Cassette_MusicBox","HiddenIsles_Cassette_RockAByeBaby","HiddenIsles_Cassette_WhataWonderfulWorld","HiddenIsles_Cassette_Macarena","HiddenIsles_Cassette_LoveMe","HiddenIsles_Cassette_Forever","HiddenIsles_Cassette_FlyMeToTheMoon","HiddenIsles_Cassette_BlueMoon"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_TeddyPicnic: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Teddy Bear's Picnic";
		descriptionShort = "The Teddy Bear's Picnic by Henry Hall & His Orchestra (1932)";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\teddypicnic.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TeddyPicnic";
		};
	};
	class HiddenIsles_Cassette_EasyStreet: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Easy Street";
		descriptionShort = "30 minutes of beautiful relaxing tunes...!";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\EasyStreet.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EasyStreet";
		};
	};
	class HiddenIsles_Cassette_Tulips: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Tiny Tim - Tiptoe Through the Tulips";
		descriptionShort = "Tiptoe Through the Tulips by Tiny Tim";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\tulips.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Tulips";
		};
	};
	class HiddenIsles_Cassette_TheGhost: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "NIVIRO - The Ghost";
		descriptionShort = "The Ghost by NIVIRO";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\theghost.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheGhost";
		};
	};
	class HiddenIsles_Cassette_MusicBox: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Music Box";
		descriptionShort = "Spooky Music";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\musicbox.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_MusicBox";
		};
	};
	class HiddenIsles_Cassette_RockAByeBaby: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rock-a-bye Baby";
		descriptionShort = "Spooky Music";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_RockAByeBaby";
		};
	};
	class HiddenIsles_Cassette_WhataWonderfulWorld: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "What a Wonderful World - Louis Amstrong";
		descriptionShort = "What a Wonderful World by Louis Amstrong";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WhataWonderfulWorld";
		};
	};
	class HiddenIsles_Cassette_Macarena: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Macarena - Los Del Rio";
		descriptionShort = "Macarena by Los Del Rio";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Macarena";
		};
	};
	class HiddenIsles_Cassette_LoveMe: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Love Me - Nat King Cole";
		descriptionShort = "Love Me by Nat King Cole";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LoveMe";
		};
	};
	class HiddenIsles_Cassette_Forever: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Forever - Jeff Williams";
		descriptionShort = "Forever by Jeff Williams";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Forever";
		};
	};
	class HiddenIsles_Cassette_FlyMeToTheMoon: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Fly Me To The Moon - Frank Sinatra";
		descriptionShort = "Fly Me To The Moon by Frank Sinatra";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FlyMeToTheMoon";
		};
	};
	class HiddenIsles_Cassette_BlueMoon: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Blue Moon - Frank Sinatra";
		descriptionShort = "Blue Moon by Frank Sinatra";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\paa\rockabyebaby.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BlueMoon";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_TeddyPicnic
	{
		soundShaders[] = {"HiddenIsles_TeddyPicnic_Shader"};
	};
	class HiddenIsles_SoundSet_EasyStreet
	{
		soundShaders[] = {"HiddenIsles_EasyStreet_Shader"};
	};
	class HiddenIsles_SoundSet_Tulips
	{
		soundShaders[] = {"HiddenIsles_Tulips_Shader"};
	};
	class HiddenIsles_SoundSet_TheGhost
	{
		soundShaders[] = {"HiddenIsles_TheGhost_Shader"};
	};
	class HiddenIsles_SoundSet_MusicBox
	{
		soundShaders[] = {"HiddenIsles_MusicBox_Shader"};
	};
	class HiddenIsles_SoundSet_Rockabyebaby
	{
		soundShaders[] = {"HiddenIsles_Rockabyebaby_Shader"};
	};
	class HiddenIsles_SoundSet_WhataWonderfulWorld
	{
		soundShaders[] = {"HiddenIsles_WhataWonderfulWorld_Shader"};
	};
	class HiddenIsles_SoundSet_Macarena
	{
		soundShaders[] = {"HiddenIsles_Macarena_Shader"};
	};
	class HiddenIsles_SoundSet_LoveMe
	{
		soundShaders[] = {"HiddenIsles_LoveMe_Shader"};
	};
	class HiddenIsles_SoundSet_Forever
	{
		soundShaders[] = {"HiddenIsles_Forever_Shader"};
	};
	class HiddenIsles_SoundSet_FlyMeToTheMoon
	{
		soundShaders[] = {"HiddenIsles_FlyMeToTheMoon_Shader"};
	};
	class HiddenIsles_SoundSet_BlueMoon
	{
		soundShaders[] = {"HiddenIsles_BlueMoon_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_TeddyPicnic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\teddypicnic",1}};
	};
	class HiddenIsles_EasyStreet_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\EasyStreet",1}};
	};
	class HiddenIsles_Tulips_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\Tulips",1}};
	};
	class HiddenIsles_TheGhost_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\TheGhost",1}};
	};
	class HiddenIsles_MusicBox_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\MusicBox",1}};
	};
	class HiddenIsles_RockAByeBaby_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\RockAByeBaby",1}};
	};
	class HiddenIsles_WhataWonderfulWorld_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\WhataWonderfulWorld",1}};
	};
	class HiddenIsles_Macarena_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\Macarena",1}};
	};
	class HiddenIsles_LoveMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\LoveMe",1}};
	};
	class HiddenIsles_Forever_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\Forever",1}};
	};
	class HiddenIsles_FlyMeToTheMoon_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\FlyMeToTheMoon",1}};
	};
	class HiddenIsles_BlueMoon_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\other\sounds\BlueMoon",1}};
	};
};
