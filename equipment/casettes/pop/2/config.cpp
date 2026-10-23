////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\pop\2\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Pop2
	{
		units[] = {"HiddenIsles_Cassette_Pop2"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Pop2: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Pop Mixtape 2";
		descriptionShort = "Best old Pop hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\paa\Pop2.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 6;
			soundSets[] = {"HiddenIsles_SoundSet_onepop2","HiddenIsles_SoundSet_twopop2","HiddenIsles_SoundSet_threepop2","HiddenIsles_SoundSet_fourpop2","HiddenIsles_SoundSet_fivepop2","HiddenIsles_SoundSet_sixpop2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twopop2
	{
		soundShaders[] = {"HiddenIsles_twopop2_Shader"};
	};
	class HiddenIsles_SoundSet_threepop2
	{
		soundShaders[] = {"HiddenIsles_threepop2_Shader"};
	};
	class HiddenIsles_SoundSet_fourpop2
	{
		soundShaders[] = {"HiddenIsles_fourpop2_Shader"};
	};
	class HiddenIsles_SoundSet_fivepop2
	{
		soundShaders[] = {"HiddenIsles_fivepop2_Shader"};
	};
	class HiddenIsles_SoundSet_sixpop2
	{
		soundShaders[] = {"HiddenIsles_sixpop2_Shader"};
	};
	class HiddenIsles_SoundSet_onepop2
	{
		soundShaders[] = {"HiddenIsles_onepop2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twopop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\two",1}};
	};
	class HiddenIsles_threepop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\three",1}};
	};
	class HiddenIsles_fourpop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\four",1}};
	};
	class HiddenIsles_fivepop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\five",1}};
	};
	class HiddenIsles_sixpop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\six",1}};
	};
	class HiddenIsles_onepop2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Pop\2\sounds\one",1}};
	};
};
