////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\donator\sounds\kaine\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_DonatorKaine
	{
		units[] = {"HiddenIsles_Donator_Cassette_Kaine"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Donator_Cassette_Kaine: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Blacksite Tape";
		descriptionShort = "[DONATOR ITEM] Adrian Kaine";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\paa\Kaine.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_onekaine","HiddenIsles_SoundSet_twokaine","HiddenIsles_SoundSet_threekaine","HiddenIsles_SoundSet_fourkaine","HiddenIsles_SoundSet_fivekaine","HiddenIsles_SoundSet_sixkaine","HiddenIsles_SoundSet_sevenkaine","HiddenIsles_SoundSet_eightkaine"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_onekaine
	{
		soundShaders[] = {"HiddenIsles_onekaine_Shader"};
	};
	class HiddenIsles_SoundSet_twokaine
	{
		soundShaders[] = {"HiddenIsles_twokaine_Shader"};
	};
	class HiddenIsles_SoundSet_threekaine
	{
		soundShaders[] = {"HiddenIsles_threekaine_Shader"};
	};
	class HiddenIsles_SoundSet_fourkaine
	{
		soundShaders[] = {"HiddenIsles_fourkaine_Shader"};
	};
	class HiddenIsles_SoundSet_fivekaine
	{
		soundShaders[] = {"HiddenIsles_fivekaine_Shader"};
	};
	class HiddenIsles_SoundSet_sixkaine
	{
		soundShaders[] = {"HiddenIsles_sixkaine_Shader"};
	};
	class HiddenIsles_SoundSet_sevenkaine
	{
		soundShaders[] = {"HiddenIsles_sevenkaine_Shader"};
	};
	class HiddenIsles_SoundSet_eightkaine
	{
		soundShaders[] = {"HiddenIsles_eightkaine_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_onekaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\one",1}};
	};
	class HiddenIsles_twokaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\two",1}};
	};
	class HiddenIsles_threekaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\three",1}};
	};
	class HiddenIsles_fourkaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\four",1}};
	};
	class HiddenIsles_fivekaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\five",1}};
	};
	class HiddenIsles_sixkaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\six",1}};
	};
	class HiddenIsles_sevenkaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\seven",1}};
	};
	class HiddenIsles_eightkaine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Kaine\eight",1}};
	};
};
