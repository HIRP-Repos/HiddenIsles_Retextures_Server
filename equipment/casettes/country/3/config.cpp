////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\country\3\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Country3
	{
		units[] = {"HiddenIsles_Cassette_Country3"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Country3: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Country Mixtape 3";
		descriptionShort = "Best old Country hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\paa\Country3.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 6;
			soundSets[] = {"HiddenIsles_SoundSet_onecountry3","HiddenIsles_SoundSet_twocountry3","HiddenIsles_SoundSet_threecountry3","HiddenIsles_SoundSet_fourcountry3","HiddenIsles_SoundSet_fivecountry3","HiddenIsles_SoundSet_sixcountry3"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twocountry3
	{
		soundShaders[] = {"HiddenIsles_twocountry3_Shader"};
	};
	class HiddenIsles_SoundSet_threecountry3
	{
		soundShaders[] = {"HiddenIsles_threecountry3_Shader"};
	};
	class HiddenIsles_SoundSet_fourcountry3
	{
		soundShaders[] = {"HiddenIsles_fourcountry3_Shader"};
	};
	class HiddenIsles_SoundSet_fivecountry3
	{
		soundShaders[] = {"HiddenIsles_fivecountry3_Shader"};
	};
	class HiddenIsles_SoundSet_sixcountry3
	{
		soundShaders[] = {"HiddenIsles_sixcountry3_Shader"};
	};
	class HiddenIsles_SoundSet_onecountry3
	{
		soundShaders[] = {"HiddenIsles_onecountry3_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twocountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\two",1}};
	};
	class HiddenIsles_threecountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\three",1}};
	};
	class HiddenIsles_fourcountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\four",1}};
	};
	class HiddenIsles_fivecountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\five",1}};
	};
	class HiddenIsles_sixcountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\six",1}};
	};
	class HiddenIsles_onecountry3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\Country\3\sounds\one",1}};
	};
};
