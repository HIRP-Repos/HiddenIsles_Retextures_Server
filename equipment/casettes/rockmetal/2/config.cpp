////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\2\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_RockMetal2
	{
		units[] = {"HiddenIsles_Cassette_RockMetal2"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_RockMetal2: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rock Metal Mixtape 2";
		descriptionShort = "Best old rock & metal hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\paa\rockmetal2.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_onerock2","HiddenIsles_SoundSet_tworock2","HiddenIsles_SoundSet_threerock2","HiddenIsles_SoundSet_fourrock2","HiddenIsles_SoundSet_fiverock2","HiddenIsles_SoundSet_sixrock2","HiddenIsles_SoundSet_sevenrock2","HiddenIsles_SoundSet_eightrock2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworock2
	{
		soundShaders[] = {"HiddenIsles_tworock2_Shader"};
	};
	class HiddenIsles_SoundSet_threerock2
	{
		soundShaders[] = {"HiddenIsles_threerock2_Shader"};
	};
	class HiddenIsles_SoundSet_fourrock2
	{
		soundShaders[] = {"HiddenIsles_fourrock2_Shader"};
	};
	class HiddenIsles_SoundSet_fiverock2
	{
		soundShaders[] = {"HiddenIsles_fiverock2_Shader"};
	};
	class HiddenIsles_SoundSet_sixrock2
	{
		soundShaders[] = {"HiddenIsles_sixrock2_Shader"};
	};
	class HiddenIsles_SoundSet_sevenrock2
	{
		soundShaders[] = {"HiddenIsles_sevenrock2_Shader"};
	};
	class HiddenIsles_SoundSet_eightrock2
	{
		soundShaders[] = {"HiddenIsles_eightrock2_Shader"};
	};
	class HiddenIsles_SoundSet_onerock2
	{
		soundShaders[] = {"HiddenIsles_onerock2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\two",1}};
	};
	class HiddenIsles_threerock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\three",1}};
	};
	class HiddenIsles_fourrock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\four",1}};
	};
	class HiddenIsles_fiverock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\five",1}};
	};
	class HiddenIsles_sixrock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\six",1}};
	};
	class HiddenIsles_sevenrock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\seven",1}};
	};
	class HiddenIsles_eightrock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\eight",1}};
	};
	class HiddenIsles_onerock2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\2\sounds\one",1}};
	};
};
