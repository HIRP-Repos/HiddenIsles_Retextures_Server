////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\country\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Country1
	{
		units[] = {"HiddenIsles_Cassette_Country1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Country1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Country Mixtape 1";
		descriptionShort = "Best old Country hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\paa\Country1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onecountry1","HiddenIsles_SoundSet_twocountry1","HiddenIsles_SoundSet_threecountry1","HiddenIsles_SoundSet_fourcountry1","HiddenIsles_SoundSet_fivecountry1"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twocountry1
	{
		soundShaders[] = {"HiddenIsles_twocountry1_Shader"};
	};
	class HiddenIsles_SoundSet_threecountry1
	{
		soundShaders[] = {"HiddenIsles_threecountry1_Shader"};
	};
	class HiddenIsles_SoundSet_fourcountry1
	{
		soundShaders[] = {"HiddenIsles_fourcountry1_Shader"};
	};
	class HiddenIsles_SoundSet_fivecountry1
	{
		soundShaders[] = {"HiddenIsles_fivecountry1_Shader"};
	};
	class HiddenIsles_SoundSet_onecountry1
	{
		soundShaders[] = {"HiddenIsles_onecountry1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twocountry1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\two",1}};
	};
	class HiddenIsles_threecountry1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\three",1}};
	};
	class HiddenIsles_fourcountry1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\four",1}};
	};
	class HiddenIsles_fivecountry1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\five",1}};
	};
	class HiddenIsles_onecountry1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\1\sounds\one",1}};
	};
};
