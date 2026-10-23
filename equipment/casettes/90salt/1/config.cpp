////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\90salt\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_90sAlt1
	{
		units[] = {"HiddenIsles_Cassette_90sAlt1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_90sAlt1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "90s Alt Mixtape 1";
		descriptionShort = "Best old 90s Alt hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\paa\90s1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onealt1","HiddenIsles_SoundSet_twoalt1","HiddenIsles_SoundSet_threealt1","HiddenIsles_SoundSet_fouralt1","HiddenIsles_SoundSet_fivealt1"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twoalt1
	{
		soundShaders[] = {"HiddenIsles_twoalt1_Shader"};
	};
	class HiddenIsles_SoundSet_threealt1
	{
		soundShaders[] = {"HiddenIsles_threealt1_Shader"};
	};
	class HiddenIsles_SoundSet_fouralt1
	{
		soundShaders[] = {"HiddenIsles_fouralt1_Shader"};
	};
	class HiddenIsles_SoundSet_fivealt1
	{
		soundShaders[] = {"HiddenIsles_fivealt1_Shader"};
	};
	class HiddenIsles_SoundSet_onealt1
	{
		soundShaders[] = {"HiddenIsles_onealt1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twoalt1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\two",1}};
	};
	class HiddenIsles_threealt1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\three",1}};
	};
	class HiddenIsles_fouralt1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\four",1}};
	};
	class HiddenIsles_fivealt1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\five",1}};
	};
	class HiddenIsles_onealt1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\1\sounds\one",1}};
	};
};
