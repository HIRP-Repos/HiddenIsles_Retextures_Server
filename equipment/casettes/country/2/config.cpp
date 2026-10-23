////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\country\2\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Country2
	{
		units[] = {"HiddenIsles_Cassette_Country2"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Country2: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Country Mixtape 2";
		descriptionShort = "Best old Country hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\paa\Country2.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onecountry2","HiddenIsles_SoundSet_twocountry2","HiddenIsles_SoundSet_threecountry2","HiddenIsles_SoundSet_fourcountry2","HiddenIsles_SoundSet_fivecountry2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twocountry2
	{
		soundShaders[] = {"HiddenIsles_twocountry2_Shader"};
	};
	class HiddenIsles_SoundSet_threecountry2
	{
		soundShaders[] = {"HiddenIsles_threecountry2_Shader"};
	};
	class HiddenIsles_SoundSet_fourcountry2
	{
		soundShaders[] = {"HiddenIsles_fourcountry2_Shader"};
	};
	class HiddenIsles_SoundSet_fivecountry2
	{
		soundShaders[] = {"HiddenIsles_fivecountry2_Shader"};
	};
	class HiddenIsles_SoundSet_onecountry2
	{
		soundShaders[] = {"HiddenIsles_onecountry2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twocountry2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\two",1}};
	};
	class HiddenIsles_threecountry2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\three",1}};
	};
	class HiddenIsles_fourcountry2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\four",1}};
	};
	class HiddenIsles_fivecountry2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\five",1}};
	};
	class HiddenIsles_onecountry2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\2\sounds\one",1}};
	};
};
