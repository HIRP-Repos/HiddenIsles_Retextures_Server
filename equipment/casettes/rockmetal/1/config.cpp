////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_RockMetal1
	{
		units[] = {"HiddenIsles_Cassette_RockMetal1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_RockMetal1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rock Metal Mixtape 1";
		descriptionShort = "Best old rock & metal hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\paa\rockmetal1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_onerock1","HiddenIsles_SoundSet_tworock1","HiddenIsles_SoundSet_threerock1","HiddenIsles_SoundSet_fourrock1","HiddenIsles_SoundSet_fiverock1","HiddenIsles_SoundSet_sixrock1","HiddenIsles_SoundSet_sevenrock1","HiddenIsles_SoundSet_eightrock1"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworock1
	{
		soundShaders[] = {"HiddenIsles_tworock1_Shader"};
	};
	class HiddenIsles_SoundSet_threerock1
	{
		soundShaders[] = {"HiddenIsles_threerock1_Shader"};
	};
	class HiddenIsles_SoundSet_fourrock1
	{
		soundShaders[] = {"HiddenIsles_fourrock1_Shader"};
	};
	class HiddenIsles_SoundSet_fiverock1
	{
		soundShaders[] = {"HiddenIsles_fiverock1_Shader"};
	};
	class HiddenIsles_SoundSet_sixrock1
	{
		soundShaders[] = {"HiddenIsles_sixrock1_Shader"};
	};
	class HiddenIsles_SoundSet_sevenrock1
	{
		soundShaders[] = {"HiddenIsles_sevenrock1_Shader"};
	};
	class HiddenIsles_SoundSet_eightrock1
	{
		soundShaders[] = {"HiddenIsles_eightrock1_Shader"};
	};
	class HiddenIsles_SoundSet_onerock1
	{
		soundShaders[] = {"HiddenIsles_onerock1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\two",1}};
	};
	class HiddenIsles_threerock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\three",1}};
	};
	class HiddenIsles_fourrock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\four",1}};
	};
	class HiddenIsles_fiverock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\five",1}};
	};
	class HiddenIsles_sixrock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\six",1}};
	};
	class HiddenIsles_sevenrock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\seven",1}};
	};
	class HiddenIsles_eightrock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\eight",1}};
	};
	class HiddenIsles_onerock1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\1\sounds\one",1}};
	};
};
