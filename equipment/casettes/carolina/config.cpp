////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\carolina\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Carol
	{
		units[] = {"HiddenIsles_Cassette_Carolina"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Carolina: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Carolina";
		descriptionShort = "Featuring 2 songs: Heads Carolina, Tails Carolina & She Had Me At Heads Carolina";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\carolina\sounds\paa\carolina.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			soundSets[] = {"HiddenIsles_SoundSet_Carolina1","HiddenIsles_SoundSet_Carolina2"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_Carolina1
	{
		soundShaders[] = {"HiddenIsles_Carolina1_Shader"};
	};
	class HiddenIsles_SoundSet_Carolina2
	{
		soundShaders[] = {"HiddenIsles_Carolina2_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_Carolina1_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\carolina\sounds\Carolina1",1}};
	};
	class HiddenIsles_Carolina2_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\carolina\sounds\Carolina2",1}};
	};
};
