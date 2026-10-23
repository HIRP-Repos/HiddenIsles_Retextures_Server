////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\donator\sounds\mcmann\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_DonatorMcMann
	{
		units[] = {"HiddenIsles_Donator_Cassette_McMann"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Donator_Cassette_McMann: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "USA National Anthem & America The Beautiful";
		descriptionShort = "[DONATOR ITEM] Tyler McMann";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\paa\mcmann.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 2;
			soundSets[] = {"HiddenIsles_SoundSet_mcmann","HiddenIsles_SoundSet_mcmann2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_mcmann
	{
		soundShaders[] = {"HiddenIsles_mcmann_Shader"};
	};
	class HiddenIsles_SoundSet_mcmann2
	{
		soundShaders[] = {"HiddenIsles_mcmann2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_mcmann_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\mcmann\mcmann",1}};
	};
	class HiddenIsles_mcmann2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\mcmann\mcmann2",1}};
	};
};
