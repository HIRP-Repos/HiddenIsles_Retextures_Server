////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\90salt\4\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_90sAlt4
	{
		units[] = {"HiddenIsles_Cassette_90sAlt4"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_90sAlt4: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "90s Alt Mixtape 4";
		descriptionShort = "Best old 90s Alt hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\4\sounds\paa\90s4.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 4;
			soundSets[] = {"HiddenIsles_SoundSet_onealt4","HiddenIsles_SoundSet_twoalt4","HiddenIsles_SoundSet_threealt4","HiddenIsles_SoundSet_fouralt4"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twoalt4
	{
		soundShaders[] = {"HiddenIsles_twoalt4_Shader"};
	};
	class HiddenIsles_SoundSet_threealt4
	{
		soundShaders[] = {"HiddenIsles_threealt4_Shader"};
	};
	class HiddenIsles_SoundSet_fouralt4
	{
		soundShaders[] = {"HiddenIsles_fouralt4_Shader"};
	};
	class HiddenIsles_SoundSet_onealt4
	{
		soundShaders[] = {"HiddenIsles_onealt4_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twoalt4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\4\sounds\two",1}};
	};
	class HiddenIsles_threealt4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\4\sounds\three",1}};
	};
	class HiddenIsles_fouralt4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\4\sounds\four",1}};
	};
	class HiddenIsles_onealt4_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\90salt\4\sounds\one",1}};
	};
};
