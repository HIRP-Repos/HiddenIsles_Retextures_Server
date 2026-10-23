////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\folk\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Folk
	{
		units[] = {"HiddenIsles_Cassette_LetItGo","HiddenIsles_Cassette_LetHerGo","HiddenIsles_Cassette_HoHey","HiddenIsles_Cassette_Riptide","HiddenIsles_Cassette_ScaredToStart","HiddenIsles_Cassette_BadBoys"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_LetItGo: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "James Bay - Let It Go";
		descriptionShort = "Let It Go by James Bay";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\letitgo.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LetItGo";
		};
	};
	class HiddenIsles_Cassette_LetHerGo: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Passenger - Let Her Go";
		descriptionShort = "Let Her Go by Passenger";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\lethergo.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LetHerGo";
		};
	};
	class HiddenIsles_Cassette_HoHey: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Lumineers - Ho Hey";
		descriptionShort = "Scared to Start, by Michael Marcagi";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\HoHey.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HoHey";
		};
	};
	class HiddenIsles_Cassette_ScaredToStart: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Michael Marcagi - Scared To Start";
		descriptionShort = "Scared to Start by Michael Marcagi";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\ScaredToStart.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_ScaredToStart";
		};
	};
	class HiddenIsles_Cassette_Riptide: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Vance Joy - Riptide";
		descriptionShort = "Riptide by Vance Joy";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\Riptide.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Riptide";
		};
	};
	class HiddenIsles_Cassette_BadBoys: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Inner Circle - Bad Boys";
		descriptionShort = "BadBoys by Inner Circle";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\paa\BadBoys.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BadBoys";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_LetItGo
	{
		soundShaders[] = {"HiddenIsles_LetItGo_Shader"};
	};
	class HiddenIsles_SoundSet_LetHerGo
	{
		soundShaders[] = {"HiddenIsles_LetHerGo_Shader"};
	};
	class HiddenIsles_SoundSet_HoHey
	{
		soundShaders[] = {"HiddenIsles_HoHey_Shader"};
	};
	class HiddenIsles_SoundSet_Riptide
	{
		soundShaders[] = {"HiddenIsles_Riptide_Shader"};
	};
	class HiddenIsles_SoundSet_ScaredToStart
	{
		soundShaders[] = {"HiddenIsles_ScaredToStart_Shader"};
	};
	class HiddenIsles_SoundSet_BadBoys
	{
		soundShaders[] = {"HiddenIsles_BadBoys_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_LetItGo_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\LetItGo",1}};
	};
	class HiddenIsles_LetHerGo_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\LetHerGo",1}};
	};
	class HiddenIsles_HoHey_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\HoHey",1}};
	};
	class HiddenIsles_Riptide_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\Riptide",1}};
	};
	class HiddenIsles_ScaredToStart_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\ScaredToStart",1}};
	};
	class HiddenIsles_BadBoys_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\folk\sounds\BadBoys",1}};
	};
};
