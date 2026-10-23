////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\90salt\3\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_90sAlt3
	{
		units[] = {"HiddenIsles_Cassette_90sAlt3"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_90sAlt3: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "90s Alt Mixtape 3";
		descriptionShort = "Best old 90s Alt hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\paa\90s3.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onealt3","HiddenIsles_SoundSet_twoalt3","HiddenIsles_SoundSet_threealt3","HiddenIsles_SoundSet_fouralt3","HiddenIsles_SoundSet_fivealt3"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twoalt3
	{
		soundShaders[] = {"HiddenIsles_twoalt3_Shader"};
	};
	class HiddenIsles_SoundSet_threealt3
	{
		soundShaders[] = {"HiddenIsles_threealt3_Shader"};
	};
	class HiddenIsles_SoundSet_fouralt3
	{
		soundShaders[] = {"HiddenIsles_fouralt3_Shader"};
	};
	class HiddenIsles_SoundSet_fivealt3
	{
		soundShaders[] = {"HiddenIsles_fivealt3_Shader"};
	};
	class HiddenIsles_SoundSet_onealt3
	{
		soundShaders[] = {"HiddenIsles_onealt3_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twoalt3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\two",1}};
	};
	class HiddenIsles_threealt3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\three",1}};
	};
	class HiddenIsles_fouralt3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\four",1}};
	};
	class HiddenIsles_fivealt3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\five",1}};
	};
	class HiddenIsles_onealt3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\3\sounds\one",1}};
	};
};
