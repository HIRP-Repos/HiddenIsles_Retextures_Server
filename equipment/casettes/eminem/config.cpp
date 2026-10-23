////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\eminem\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Em
	{
		units[] = {"HiddenIsles_Cassette_Eminem"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Eminem: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Eminem";
		descriptionShort = "Best old hits from Eminem";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\paa\eminem.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 8;
			soundSets[] = {"HiddenIsles_SoundSet_WhiteAmerica","HiddenIsles_SoundSet_NotAfraid","HiddenIsles_SoundSet_CleaningOutMyCloset","HiddenIsles_SoundSet_Stan","HiddenIsles_SoundSet_Darkness","HiddenIsles_SoundSet_LoseYourself","HiddenIsles_SoundSet_SlimShady","HiddenIsles_SoundSet_WithoutMe"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_NotAfraid
	{
		soundShaders[] = {"HiddenIsles_NotAfraid_Shader"};
	};
	class HiddenIsles_SoundSet_CleaningOutMyCloset
	{
		soundShaders[] = {"HiddenIsles_CleaningOutMyCloset_Shader"};
	};
	class HiddenIsles_SoundSet_Stan
	{
		soundShaders[] = {"HiddenIsles_Stan_Shader"};
	};
	class HiddenIsles_SoundSet_Darkness
	{
		soundShaders[] = {"HiddenIsles_Darkness_Shader"};
	};
	class HiddenIsles_SoundSet_LoseYourself
	{
		soundShaders[] = {"HiddenIsles_LoseYourself_Shader"};
	};
	class HiddenIsles_SoundSet_SlimShady
	{
		soundShaders[] = {"HiddenIsles_SlimShady_Shader"};
	};
	class HiddenIsles_SoundSet_WithoutMe
	{
		soundShaders[] = {"HiddenIsles_WithoutMe_Shader"};
	};
	class HiddenIsles_SoundSet_WhiteAmerica
	{
		soundShaders[] = {"HiddenIsles_WhiteAmerica_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_NotAfraid_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\NotAfraid",1}};
	};
	class HiddenIsles_CleaningOutMyCloset_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\CleaningOutMyCloset",1}};
	};
	class HiddenIsles_Stan_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\Stan",1}};
	};
	class HiddenIsles_Darkness_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\Darkness",1}};
	};
	class HiddenIsles_LoseYourself_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\LoseYourself",1}};
	};
	class HiddenIsles_SlimShady_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\SlimShady",1}};
	};
	class HiddenIsles_WithoutMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\WithoutMe",1}};
	};
	class HiddenIsles_WhiteAmerica_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\eminem\sounds\WhiteAmerica",1}};
	};
};
