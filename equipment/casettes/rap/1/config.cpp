////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rap\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:48 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rap1
	{
		units[] = {"HiddenIsles_Cassette_Rap1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Rap1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rap Mixtape 1";
		descriptionShort = "Best old rap hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\paa\rap1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 7;
			soundSets[] = {"HiddenIsles_SoundSet_rap1one","HiddenIsles_SoundSet_rap1two","HiddenIsles_SoundSet_rap1three","HiddenIsles_SoundSet_rap1four","HiddenIsles_SoundSet_rap1five","HiddenIsles_SoundSet_rap1six","HiddenIsles_SoundSet_rap1seven"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_rap1two
	{
		soundShaders[] = {"HiddenIsles_tworap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1three
	{
		soundShaders[] = {"HiddenIsles_threerap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1four
	{
		soundShaders[] = {"HiddenIsles_fourrap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1five
	{
		soundShaders[] = {"HiddenIsles_fiverap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1six
	{
		soundShaders[] = {"HiddenIsles_sixrap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1seven
	{
		soundShaders[] = {"HiddenIsles_sevenrap1_Shader"};
	};
	class HiddenIsles_SoundSet_rap1one
	{
		soundShaders[] = {"HiddenIsles_onerap1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_tworap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\two",1}};
	};
	class HiddenIsles_threerap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\three",1}};
	};
	class HiddenIsles_fourrap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\four",1}};
	};
	class HiddenIsles_fiverap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\five",1}};
	};
	class HiddenIsles_sixrap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\six",1}};
	};
	class HiddenIsles_sevenrap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\seven",1}};
	};
	class HiddenIsles_onerap1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\1\sounds\one",1}};
	};
};
