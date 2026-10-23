////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\donator\sounds\koden\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_DonatorKoden
	{
		units[] = {"HiddenIsles_Donator_Cassette_Koden"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Donator_Cassette_Koden: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Holdings Tape";
		descriptionShort = "[DONATOR ITEM] Koden";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\paa\koden.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_vivelerap","HiddenIsles_SoundSet_nottherightplace","HiddenIsles_SoundSet_darkzone","HiddenIsles_SoundSet_unitydarkedm","HiddenIsles_SoundSet_bloodloss","HiddenIsles_SoundSet_sunsetserenade","HiddenIsles_SoundSet_tunetrove","HiddenIsles_SoundSet_brazilianphonk"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_nottherightplace
	{
		soundShaders[] = {"HiddenIsles_nottherightplace_Shader"};
	};
	class HiddenIsles_SoundSet_darkzone
	{
		soundShaders[] = {"HiddenIsles_darkzone_Shader"};
	};
	class HiddenIsles_SoundSet_unitydarkedm
	{
		soundShaders[] = {"HiddenIsles_unitydarkedm_Shader"};
	};
	class HiddenIsles_SoundSet_bloodloss
	{
		soundShaders[] = {"HiddenIsles_bloodloss_Shader"};
	};
	class HiddenIsles_SoundSet_sunsetserenade
	{
		soundShaders[] = {"HiddenIsles_sunsetserenade_Shader"};
	};
	class HiddenIsles_SoundSet_tunetrove
	{
		soundShaders[] = {"HiddenIsles_tunetrove_Shader"};
	};
	class HiddenIsles_SoundSet_brazilianphonk
	{
		soundShaders[] = {"HiddenIsles_brazilianphonk_Shader"};
	};
	class HiddenIsles_SoundSet_vivelerap
	{
		soundShaders[] = {"HiddenIsles_vivelerap_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_nottherightplace_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\nottherightplace",1}};
	};
	class HiddenIsles_darkzone_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\darkzone",1}};
	};
	class HiddenIsles_unitydarkedm_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\unitydarkedm",1}};
	};
	class HiddenIsles_bloodloss_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\bloodloss",1}};
	};
	class HiddenIsles_sunsetserenade_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\sunsetserenade",1}};
	};
	class HiddenIsles_tunetrove_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\tunetrove",1}};
	};
	class HiddenIsles_brazilianphonk_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\brazilianphonk",1}};
	};
	class HiddenIsles_vivelerap_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\koden\vivelerap",1}};
	};
};
