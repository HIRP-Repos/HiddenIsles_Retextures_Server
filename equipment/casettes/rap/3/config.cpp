////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rap\3\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:48 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rap3
	{
		units[] = {"HiddenIsles_Cassette_Rap3"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Rap3: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rap Mixtape 3";
		descriptionShort = "Best old rap hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\paa\rap3.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onerap3","HiddenIsles_SoundSet_tworap3","HiddenIsles_SoundSet_threerap3","HiddenIsles_SoundSet_fourrap3","HiddenIsles_SoundSet_fiverap3"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworap3
	{
		soundShaders[] = {"HiddenIsles_tworap3_Shader"};
	};
	class HiddenIsles_SoundSet_threerap3
	{
		soundShaders[] = {"HiddenIsles_threerap3_Shader"};
	};
	class HiddenIsles_SoundSet_fourrap3
	{
		soundShaders[] = {"HiddenIsles_fourrap3_Shader"};
	};
	class HiddenIsles_SoundSet_fiverap3
	{
		soundShaders[] = {"HiddenIsles_fiverap3_Shader"};
	};
	class HiddenIsles_SoundSet_onerap3
	{
		soundShaders[] = {"HiddenIsles_onerap3_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworap3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\two",1}};
	};
	class HiddenIsles_threerap3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\three",1}};
	};
	class HiddenIsles_fourrap3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\four",1}};
	};
	class HiddenIsles_fiverap3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\five",1}};
	};
	class HiddenIsles_onerap3_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\3\sounds\one",1}};
	};
};
