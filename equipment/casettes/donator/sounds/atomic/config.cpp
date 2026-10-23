////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\donator\sounds\atomic\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_DonatorAtomic
	{
		units[] = {"HiddenIsles_Donator_Cassette_Atomic"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Donator_Cassette_Atomic: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Daz's Epic Australian Mix Tape";
		descriptionShort = "[DONATOR ITEM] Daz";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\paa\Atomic.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_oneAtomic","HiddenIsles_SoundSet_twoAtomic","HiddenIsles_SoundSet_threeAtomic","HiddenIsles_SoundSet_fourAtomic","HiddenIsles_SoundSet_fiveAtomic","HiddenIsles_SoundSet_sixAtomic","HiddenIsles_SoundSet_sevenAtomic","HiddenIsles_SoundSet_eightAtomic"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_oneAtomic
	{
		soundShaders[] = {"HiddenIsles_oneAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_twoAtomic
	{
		soundShaders[] = {"HiddenIsles_twoAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_threeAtomic
	{
		soundShaders[] = {"HiddenIsles_threeAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_fourAtomic
	{
		soundShaders[] = {"HiddenIsles_fourAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_fiveAtomic
	{
		soundShaders[] = {"HiddenIsles_fiveAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_sixAtomic
	{
		soundShaders[] = {"HiddenIsles_sixAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_sevenAtomic
	{
		soundShaders[] = {"HiddenIsles_sevenAtomic_Shader"};
	};
	class HiddenIsles_SoundSet_eightAtomic
	{
		soundShaders[] = {"HiddenIsles_eightAtomic_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_oneAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\one",1}};
	};
	class HiddenIsles_twoAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\two",1}};
	};
	class HiddenIsles_threeAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\three",1}};
	};
	class HiddenIsles_fourAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\four",1}};
	};
	class HiddenIsles_fiveAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\five",1}};
	};
	class HiddenIsles_sixAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\six",1}};
	};
	class HiddenIsles_sevenAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\seven",1}};
	};
	class HiddenIsles_eightAtomic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_files\Equipment\Casettes\donator\sounds\Atomic\eight",1}};
	};
};
