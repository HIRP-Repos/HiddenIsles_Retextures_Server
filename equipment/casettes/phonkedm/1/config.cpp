////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\phonkedm\1\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Phonk1
	{
		units[] = {"HiddenIsles_Cassette_Phonk1"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Phonk1: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Phonk Mixtape 1";
		descriptionShort = "Best old Phonk hits";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\paa\Phonk1.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 5;
			soundSets[] = {"HiddenIsles_SoundSet_onephonk1","HiddenIsles_SoundSet_twophonk1","HiddenIsles_SoundSet_threephonk1","HiddenIsles_SoundSet_fourphonk1","HiddenIsles_SoundSet_fivephonk1"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_twophonk1
	{
		soundShaders[] = {"HiddenIsles_twophonk1_Shader"};
	};
	class HiddenIsles_SoundSet_threephonk1
	{
		soundShaders[] = {"HiddenIsles_threephonk1_Shader"};
	};
	class HiddenIsles_SoundSet_fourphonk1
	{
		soundShaders[] = {"HiddenIsles_fourphonk1_Shader"};
	};
	class HiddenIsles_SoundSet_fivephonk1
	{
		soundShaders[] = {"HiddenIsles_fivephonk1_Shader"};
	};
	class HiddenIsles_SoundSet_onephonk1
	{
		soundShaders[] = {"HiddenIsles_onephonk1_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_twophonk1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\two",1}};
	};
	class HiddenIsles_threephonk1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\three",1}};
	};
	class HiddenIsles_fourphonk1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\four",1}};
	};
	class HiddenIsles_fivephonk1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\five",1}};
	};
	class HiddenIsles_onephonk1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\Phonkedm\1\sounds\one",1}};
	};
};
