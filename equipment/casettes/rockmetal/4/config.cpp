////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\4\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_RockMetal4
	{
		units[] = {"HiddenIsles_Cassette_RockMetal4"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_RockMetal4: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rock Metal Mixtape 4";
		descriptionShort = "Best old rock & metal hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\paa\rockmetal4.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_onerock4","HiddenIsles_SoundSet_tworock4","HiddenIsles_SoundSet_threerock4","HiddenIsles_SoundSet_fourrock4","HiddenIsles_SoundSet_fiverock4","HiddenIsles_SoundSet_sixrock4","HiddenIsles_SoundSet_sevenrock4","HiddenIsles_SoundSet_eightrock4"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworock4
	{
		soundShaders[] = {"HiddenIsles_tworock4_Shader"};
	};
	class HiddenIsles_SoundSet_threerock4
	{
		soundShaders[] = {"HiddenIsles_threerock4_Shader"};
	};
	class HiddenIsles_SoundSet_fourrock4
	{
		soundShaders[] = {"HiddenIsles_fourrock4_Shader"};
	};
	class HiddenIsles_SoundSet_fiverock4
	{
		soundShaders[] = {"HiddenIsles_fiverock4_Shader"};
	};
	class HiddenIsles_SoundSet_sixrock4
	{
		soundShaders[] = {"HiddenIsles_sixrock4_Shader"};
	};
	class HiddenIsles_SoundSet_sevenrock4
	{
		soundShaders[] = {"HiddenIsles_sevenrock4_Shader"};
	};
	class HiddenIsles_SoundSet_eightrock4
	{
		soundShaders[] = {"HiddenIsles_eightrock4_Shader"};
	};
	class HiddenIsles_SoundSet_onerock4
	{
		soundShaders[] = {"HiddenIsles_onerock4_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\two",1}};
	};
	class HiddenIsles_threerock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\three",1}};
	};
	class HiddenIsles_fourrock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\four",1}};
	};
	class HiddenIsles_fiverock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\five",1}};
	};
	class HiddenIsles_sixrock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\six",1}};
	};
	class HiddenIsles_sevenrock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\seven",1}};
	};
	class HiddenIsles_eightrock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\eight",1}};
	};
	class HiddenIsles_onerock4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\4\sounds\one",1}};
	};
};
