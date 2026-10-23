////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\3\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_RockMetal3
	{
		units[] = {"HiddenIsles_Cassette_RockMetal3"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_RockMetal3: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rock Metal Mixtape 3";
		descriptionShort = "Best old rock & metal hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\paa\rockmetal3.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_onerock3","HiddenIsles_SoundSet_tworock3","HiddenIsles_SoundSet_threerock3","HiddenIsles_SoundSet_fourrock3","HiddenIsles_SoundSet_fiverock3","HiddenIsles_SoundSet_sixrock3","HiddenIsles_SoundSet_sevenrock3","HiddenIsles_SoundSet_eightrock3"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworock3
	{
		soundShaders[] = {"HiddenIsles_tworock3_Shader"};
	};
	class HiddenIsles_SoundSet_threerock3
	{
		soundShaders[] = {"HiddenIsles_threerock3_Shader"};
	};
	class HiddenIsles_SoundSet_fourrock3
	{
		soundShaders[] = {"HiddenIsles_fourrock3_Shader"};
	};
	class HiddenIsles_SoundSet_fiverock3
	{
		soundShaders[] = {"HiddenIsles_fiverock3_Shader"};
	};
	class HiddenIsles_SoundSet_sixrock3
	{
		soundShaders[] = {"HiddenIsles_sixrock3_Shader"};
	};
	class HiddenIsles_SoundSet_sevenrock3
	{
		soundShaders[] = {"HiddenIsles_sevenrock3_Shader"};
	};
	class HiddenIsles_SoundSet_eightrock3
	{
		soundShaders[] = {"HiddenIsles_eightrock3_Shader"};
	};
	class HiddenIsles_SoundSet_onerock3
	{
		soundShaders[] = {"HiddenIsles_onerock3_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\two",1}};
	};
	class HiddenIsles_threerock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\three",1}};
	};
	class HiddenIsles_fourrock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\four",1}};
	};
	class HiddenIsles_fiverock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\five",1}};
	};
	class HiddenIsles_sixrock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\six",1}};
	};
	class HiddenIsles_sevenrock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\seven",1}};
	};
	class HiddenIsles_eightrock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\eight",1}};
	};
	class HiddenIsles_onerock3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\3\sounds\one",1}};
	};
};
