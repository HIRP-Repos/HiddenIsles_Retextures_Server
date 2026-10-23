////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\pop\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Pop1
	{
		units[] = {"HiddenIsles_Cassette_Pop1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Pop1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Pop Mixtape 1";
		descriptionShort = "Best old Pop hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\paa\Pop1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onepop1","HiddenIsles_SoundSet_twopop1","HiddenIsles_SoundSet_threepop1","HiddenIsles_SoundSet_fourpop1","HiddenIsles_SoundSet_fivepop1"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twopop1
	{
		soundShaders[] = {"HiddenIsles_twopop1_Shader"};
	};
	class HiddenIsles_SoundSet_threepop1
	{
		soundShaders[] = {"HiddenIsles_threepop1_Shader"};
	};
	class HiddenIsles_SoundSet_fourpop1
	{
		soundShaders[] = {"HiddenIsles_fourpop1_Shader"};
	};
	class HiddenIsles_SoundSet_fivepop1
	{
		soundShaders[] = {"HiddenIsles_fivepop1_Shader"};
	};
	class HiddenIsles_SoundSet_onepop1
	{
		soundShaders[] = {"HiddenIsles_onepop1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twopop1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\two",1}};
	};
	class HiddenIsles_threepop1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\three",1}};
	};
	class HiddenIsles_fourpop1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\four",1}};
	};
	class HiddenIsles_fivepop1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\five",1}};
	};
	class HiddenIsles_onepop1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\1\sounds\one",1}};
	};
};
