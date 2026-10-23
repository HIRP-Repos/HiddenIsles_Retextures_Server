////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rap\2\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:48 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rap2
	{
		units[] = {"HiddenIsles_Cassette_Rap2"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Rap2: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rap Mixtape 2";
		descriptionShort = "Best old rap hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\paa\rap2.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 6;
			soundSets[] = {"HiddenIsles_SoundSet_onerap2","HiddenIsles_SoundSet_tworap2","HiddenIsles_SoundSet_threerap2","HiddenIsles_SoundSet_fourrap2","HiddenIsles_SoundSet_fiverap2","HiddenIsles_SoundSet_sixrap2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_tworap2
	{
		soundShaders[] = {"HiddenIsles_tworap2_Shader"};
	};
	class HiddenIsles_SoundSet_threerap2
	{
		soundShaders[] = {"HiddenIsles_threerap2_Shader"};
	};
	class HiddenIsles_SoundSet_fourrap2
	{
		soundShaders[] = {"HiddenIsles_fourrap2_Shader"};
	};
	class HiddenIsles_SoundSet_fiverap2
	{
		soundShaders[] = {"HiddenIsles_fiverap2_Shader"};
	};
	class HiddenIsles_SoundSet_sixrap2
	{
		soundShaders[] = {"HiddenIsles_sixrap2_Shader"};
	};
	class HiddenIsles_SoundSet_onerap2
	{
		soundShaders[] = {"HiddenIsles_onerap2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\two",1}};
	};
	class HiddenIsles_threerap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\three",1}};
	};
	class HiddenIsles_fourrap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\four",1}};
	};
	class HiddenIsles_fiverap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\five",1}};
	};
	class HiddenIsles_sixrap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\six",1}};
	};
	class HiddenIsles_onerap2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\2\sounds\one",1}};
	};
};
