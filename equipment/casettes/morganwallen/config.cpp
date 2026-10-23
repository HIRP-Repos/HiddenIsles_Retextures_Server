////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\morganwallen\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Morgan
	{
		units[] = {"HiddenIsles_Cassette_MorganWallen"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_MorganWallen: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Morgan Wallen";
		descriptionShort = "Featuring 10 Hits from Morgan Wallen";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\paa\morganwallen.paa"};
		class CfgCassette
		{
			isPlaylist = 1;
			trackCount = 10;
			soundSets[] = {"HiddenIsles_SoundSet_LastNight","HiddenIsles_SoundSet_LoveSomebody","HiddenIsles_SoundSet_LiesLiesLies","HiddenIsles_SoundSet_WastedOnYou","HiddenIsles_SoundSet_JustInCase","HiddenIsles_SoundSet_ThoughtYouShouldKnow","HiddenIsles_SoundSet_ManMadeABar","HiddenIsles_SoundSet_ThinkingAboutMe","HiddenIsles_SoundSet_WhiskeyGlasses","HiddenIsles_SoundSet_Cowgirls"};
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_LoveSomebody
	{
		soundShaders[] = {"HiddenIsles_LoveSomebody_Shader"};
	};
	class HiddenIsles_SoundSet_LiesLiesLies
	{
		soundShaders[] = {"HiddenIsles_LiesLiesLies_Shader"};
	};
	class HiddenIsles_SoundSet_WastedOnYou
	{
		soundShaders[] = {"HiddenIsles_WastedOnYou_Shader"};
	};
	class HiddenIsles_SoundSet_JustInCase
	{
		soundShaders[] = {"HiddenIsles_JustInCase_Shader"};
	};
	class HiddenIsles_SoundSet_ThoughtYouShouldKnow
	{
		soundShaders[] = {"HiddenIsles_ThoughtYouShouldKnow_Shader"};
	};
	class HiddenIsles_SoundSet_ManMadeABar
	{
		soundShaders[] = {"HiddenIsles_ManMadeABar_Shader"};
	};
	class HiddenIsles_SoundSet_ThinkingAboutMe
	{
		soundShaders[] = {"HiddenIsles_ThinkingAboutMe_Shader"};
	};
	class HiddenIsles_SoundSet_LastNight
	{
		soundShaders[] = {"HiddenIsles_LastNight_Shader"};
	};
	class HiddenIsles_SoundSet_WhiskeyGlasses
	{
		soundShaders[] = {"HiddenIsles_WhiskeyGlasses_Shader"};
	};
	class HiddenIsles_SoundSet_Cowgirls
	{
		soundShaders[] = {"HiddenIsles_Cowgirls_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_LoveSomebody_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\LoveSomebody",1}};
	};
	class HiddenIsles_LiesLiesLies_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\LiesLiesLies",1}};
	};
	class HiddenIsles_WastedOnYou_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\WastedOnYou",1}};
	};
	class HiddenIsles_JustInCase_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\JustInCase",1}};
	};
	class HiddenIsles_ThoughtYouShouldKnow_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\ThoughtYouShouldKnow",1}};
	};
	class HiddenIsles_ManMadeABar_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\ManMadeABar",1}};
	};
	class HiddenIsles_ThinkingAboutMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\ThinkingAboutMe",1}};
	};
	class HiddenIsles_LastNight_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\LastNight",1}};
	};
	class HiddenIsles_WhiskeyGlasses_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\WhiskeyGlasses",1}};
	};
	class HiddenIsles_Cowgirls_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\morganwallen\sounds\Cowgirls",1}};
	};
};
