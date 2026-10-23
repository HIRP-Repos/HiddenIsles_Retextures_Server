////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\90salt\2\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_90sAlt2
	{
		units[] = {"HiddenIsles_Cassette_90sAlt2"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_90sAlt2: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "90s Alt Mixtape 2";
		descriptionShort = "Best old 90s Alt hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\paa\90s2.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onealt2","HiddenIsles_SoundSet_twoalt2","HiddenIsles_SoundSet_threealt2","HiddenIsles_SoundSet_fouralt2","HiddenIsles_SoundSet_fivealt2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twoalt2
	{
		soundShaders[] = {"HiddenIsles_twoalt2_Shader"};
	};
	class HiddenIsles_SoundSet_threealt2
	{
		soundShaders[] = {"HiddenIsles_threealt2_Shader"};
	};
	class HiddenIsles_SoundSet_fouralt2
	{
		soundShaders[] = {"HiddenIsles_fouralt2_Shader"};
	};
	class HiddenIsles_SoundSet_fivealt2
	{
		soundShaders[] = {"HiddenIsles_fivealt2_Shader"};
	};
	class HiddenIsles_SoundSet_onealt2
	{
		soundShaders[] = {"HiddenIsles_onealt2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twoalt2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\two",1}};
	};
	class HiddenIsles_threealt2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\three",1}};
	};
	class HiddenIsles_fouralt2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\four",1}};
	};
	class HiddenIsles_fivealt2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\five",1}};
	};
	class HiddenIsles_onealt2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\2\sounds\one",1}};
	};
};
