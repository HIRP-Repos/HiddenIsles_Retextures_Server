////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\pop\4\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:48 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Pop4
	{
		units[] = {"HiddenIsles_Cassette_DarkHorse","HiddenIsles_Cassette_Grenade","HiddenIsles_Cassette_LittleMe","HiddenIsles_Cassette_NewAmericana","HiddenIsles_Cassette_TokyoDrift","HiddenIsles_Cassette_Cannibal","HiddenIsles_Cassette_Circus","HiddenIsles_Cassette_DownUnder","HiddenIsles_Cassette_Airplanes","HiddenIsles_Cassette_Bailando","HiddenIsles_Cassette_BeatIt","HiddenIsles_Cassette_DanzaKuduro","HiddenIsles_Cassette_EatIt","HiddenIsles_Cassette_EmpireStateOfMind","HiddenIsles_Cassette_Gimme","HiddenIsles_Cassette_HollaBackGirl","HiddenIsles_Cassette_IGotAFeeling","HiddenIsles_Cassette_IWantItThatWay","HiddenIsles_Cassette_LivinLaVidaLoca","HiddenIsles_Cassette_PushTheButton","HiddenIsles_Cassette_SexyBack","HiddenIsles_Cassette_TheKetchupSong","HiddenIsles_Cassette_TheRhythmoftheNight","HiddenIsles_Cassette_Toxic","HiddenIsles_Cassette_VivalaVida","HiddenIsles_Cassette_PaperPlanes"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_DarkHorse: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Dark Horse - Katy Perry";
		descriptionShort = "Dark Horse by Katy Perry";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DarkHorse";
		};
	};
	class HiddenIsles_Cassette_PaperPlanes: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Paper Planes - M.I.A.";
		descriptionShort = "Paper Planes by M.I.A.";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PaperPlanes";
		};
	};
	class HiddenIsles_Cassette_Grenade: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Grenade - Bruno Mars";
		descriptionShort = "Grenade - Bruno Mars";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Grenade";
		};
	};
	class HiddenIsles_Cassette_LittleMe: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Little Me - Little Mix";
		descriptionShort = "Little Me by Little Mix";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LittleMe";
		};
	};
	class HiddenIsles_Cassette_NewAmericana: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "New Americana - Halsey";
		descriptionShort = "New Americana by Halsey (THYPONYX)";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_NewAmericana";
		};
	};
	class HiddenIsles_Cassette_TokyoDrift: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Tokyo Drift - Teriyaki Boyz";
		descriptionShort = "Tokyo Drift by Teriyaki Boyz";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TokyoDrift";
		};
	};
	class HiddenIsles_Cassette_Cannibal: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Cannibal - Kesha";
		descriptionShort = "Cannibal by Kesha";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Cannibal";
		};
	};
	class HiddenIsles_Cassette_Circus: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Circus - Britney Spears";
		descriptionShort = "Circus by Britney Spears";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Circus";
		};
	};
	class HiddenIsles_Cassette_DownUnder: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Men At Work - Down Under";
		descriptionShort = "Men At Work - Down Under";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DownUnder";
		};
	};
	class HiddenIsles_Cassette_Airplanes: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Airplanes - B.o.B";
		descriptionShort = "Airplanes by B.o.B";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Airplanes";
		};
	};
	class HiddenIsles_Cassette_Bailando: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Bailando - Enrique Iglesias";
		descriptionShort = "Bailando by Enrique Iglesias";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Bailando";
		};
	};
	class HiddenIsles_Cassette_BeatIt: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Beat It - Michael Jackson";
		descriptionShort = "Beat It by Michael Jackson";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BeatIt";
		};
	};
	class HiddenIsles_Cassette_DanzaKuduro: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Danza Kuduro - Don Omar";
		descriptionShort = "Danza Kuduro by Don Omar";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DanzaKuduro";
		};
	};
	class HiddenIsles_Cassette_EatIt: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Eat It - Weird Al";
		descriptionShort = "Eat It by Weird Al";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EatIt";
		};
	};
	class HiddenIsles_Cassette_EmpireStateOfMind: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Empire State Of Mind - JAYZ";
		descriptionShort = "Empire State Of Mind by JAYZ";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EmpireStateOfMind";
		};
	};
	class HiddenIsles_Cassette_Gimme: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Gimme! Gimme! Gimme! - ABBA";
		descriptionShort = "Gimme! Gimme! Gimme! by ABBA";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Gimme";
		};
	};
	class HiddenIsles_Cassette_HollaBackGirl: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "HollaBack Girl - Gwen Stefani";
		descriptionShort = "HollaBack Girl by Gwen Stefani";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HollaBackGirl";
		};
	};
	class HiddenIsles_Cassette_IGotAFeeling: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "I Got A Feeling - The Black Eyed Peas";
		descriptionShort = "I Got A Feeling by The Black Eyed Peas";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_IGotAFeeling";
		};
	};
	class HiddenIsles_Cassette_IWantItThatWay: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "I Want It That Way - Backstreet Boys";
		descriptionShort = "I Want It That Way by Backstreet Boys";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_IWantItThatWay";
		};
	};
	class HiddenIsles_Cassette_LivinLaVidaLoca: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Livin La Vida Loca - Ricky Martin";
		descriptionShort = "Livin La Vida Loca by Ricky Martin";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LivinLaVidaLoca";
		};
	};
	class HiddenIsles_Cassette_PushTheButton: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Push The Button - Sugababes";
		descriptionShort = "Push The Button by Sugababes";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PushTheButton";
		};
	};
	class HiddenIsles_Cassette_SexyBack: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "SexyBack - Justin Timberlake";
		descriptionShort = "SexyBack by Justin Timberlake";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SexyBack";
		};
	};
	class HiddenIsles_Cassette_TheKetchupSong: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Ketchup Song";
		descriptionShort = "The Ketchup Song";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheKetchupSong";
		};
	};
	class HiddenIsles_Cassette_TheRhythmoftheNight: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Rhythm of the Night - Corona";
		descriptionShort = "The Rhythm of the Night by Corona";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheRhythmoftheNight";
		};
	};
	class HiddenIsles_Cassette_Toxic: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Toxic - Britney Spears";
		descriptionShort = "Toxic by Britney Spears";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Toxic";
		};
	};
	class HiddenIsles_Cassette_VivalaVida: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Viva la Vida - Coldplay";
		descriptionShort = "Viva la Vida by Coldplay";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\paa\Pop.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_VivalaVida";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_DarkHorse
	{
		soundShaders[] = {"HiddenIsles_DarkHorse_Shader"};
	};
	class HiddenIsles_SoundSet_PaperPlanes
	{
		soundShaders[] = {"HiddenIsles_PaperPlanes_Shader"};
	};
	class HiddenIsles_SoundSet_Grenade
	{
		soundShaders[] = {"HiddenIsles_Grenade_Shader"};
	};
	class HiddenIsles_SoundSet_LittleMe
	{
		soundShaders[] = {"HiddenIsles_LittleMe_Shader"};
	};
	class HiddenIsles_SoundSet_NewAmericana
	{
		soundShaders[] = {"HiddenIsles_NewAmericana_Shader"};
	};
	class HiddenIsles_SoundSet_TokyoDrift
	{
		soundShaders[] = {"HiddenIsles_TokyoDrift_Shader"};
	};
	class HiddenIsles_SoundSet_Cannibal
	{
		soundShaders[] = {"HiddenIsles_Cannibal_Shader"};
	};
	class HiddenIsles_SoundSet_Circus
	{
		soundShaders[] = {"HiddenIsles_Circus_Shader"};
	};
	class HiddenIsles_SoundSet_DownUnder
	{
		soundShaders[] = {"HiddenIsles_DownUnder_Shader"};
	};
	class HiddenIsles_SoundSet_Airplanes
	{
		soundShaders[] = {"HiddenIsles_Airplanes_Shader"};
	};
	class HiddenIsles_SoundSet_Bailando
	{
		soundShaders[] = {"HiddenIsles_Bailando_Shader"};
	};
	class HiddenIsles_SoundSet_BeatIt
	{
		soundShaders[] = {"HiddenIsles_BeatIt_Shader"};
	};
	class HiddenIsles_SoundSet_DanzaKuduro
	{
		soundShaders[] = {"HiddenIsles_DanzaKuduro_Shader"};
	};
	class HiddenIsles_SoundSet_EatIt
	{
		soundShaders[] = {"HiddenIsles_EatIt_Shader"};
	};
	class HiddenIsles_SoundSet_EmpireStateOfMind
	{
		soundShaders[] = {"HiddenIsles_EmpireStateOfMind_Shader"};
	};
	class HiddenIsles_SoundSet_Gimme
	{
		soundShaders[] = {"HiddenIsles_Gimme_Shader"};
	};
	class HiddenIsles_SoundSet_HollaBackGirl
	{
		soundShaders[] = {"HiddenIsles_HollaBackGirl_Shader"};
	};
	class HiddenIsles_SoundSet_IGotAFeeling
	{
		soundShaders[] = {"HiddenIsles_IGotAFeeling_Shader"};
	};
	class HiddenIsles_SoundSet_IWantItThatWay
	{
		soundShaders[] = {"HiddenIsles_IWantItThatWay_Shader"};
	};
	class HiddenIsles_SoundSet_LivinLaVidaLoca
	{
		soundShaders[] = {"HiddenIsles_LivinLaVidaLoca_Shader"};
	};
	class HiddenIsles_SoundSet_PushTheButton
	{
		soundShaders[] = {"HiddenIsles_PushTheButton_Shader"};
	};
	class HiddenIsles_SoundSet_SexyBack
	{
		soundShaders[] = {"HiddenIsles_SexyBack_Shader"};
	};
	class HiddenIsles_SoundSet_TheKetchupSong
	{
		soundShaders[] = {"HiddenIsles_TheKetchupSong_Shader"};
	};
	class HiddenIsles_SoundSet_TheRhythmoftheNight
	{
		soundShaders[] = {"HiddenIsles_TheRhythmoftheNight_Shader"};
	};
	class HiddenIsles_SoundSet_Toxic
	{
		soundShaders[] = {"HiddenIsles_Toxic_Shader"};
	};
	class HiddenIsles_SoundSet_VivalaVida
	{
		soundShaders[] = {"HiddenIsles_VivalaVida_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_DarkHorse_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\DarkHorse",1}};
	};
	class HiddenIsles_PaperPlanes_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\PaperPlanes",1}};
	};
	class HiddenIsles_Grenade_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Grenade",1}};
	};
	class HiddenIsles_LittleMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\LittleMe",1}};
	};
	class HiddenIsles_NewAmericana_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\NewAmericana",1}};
	};
	class HiddenIsles_TokyoDrift_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\TokyoDrift",1}};
	};
	class HiddenIsles_Cannibal_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Cannibal",1}};
	};
	class HiddenIsles_Circus_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Circus",1}};
	};
	class HiddenIsles_DownUnder_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\DownUnder",1}};
	};
	class HiddenIsles_Airplanes_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Airplanes",1}};
	};
	class HiddenIsles_Bailando_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Bailando",1}};
	};
	class HiddenIsles_BeatIt_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\BeatIt",1}};
	};
	class HiddenIsles_DanzaKuduro_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\DanzaKuduro",1}};
	};
	class HiddenIsles_EatIt_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\EatIt",1}};
	};
	class HiddenIsles_EmpireStateOfMind_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\EmpireStateOfMind",1}};
	};
	class HiddenIsles_Gimme_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Gimme",1}};
	};
	class HiddenIsles_HollaBackGirl_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\HollaBackGirl",1}};
	};
	class HiddenIsles_IGotAFeeling_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\IGotAFeeling",1}};
	};
	class HiddenIsles_IWantItThatWay_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\IWantItThatWay",1}};
	};
	class HiddenIsles_LivinLaVidaLoca_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\LivinLaVidaLoca",1}};
	};
	class HiddenIsles_PushTheButton_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\PushTheButton",1}};
	};
	class HiddenIsles_SexyBack_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\SexyBack",1}};
	};
	class HiddenIsles_TheKetchupSong_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\TheKetchupSong",1}};
	};
	class HiddenIsles_TheRhythmoftheNight_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\TheRhythmoftheNight",1}};
	};
	class HiddenIsles_VivalaVida_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\VivalaVida",1}};
	};
	class HiddenIsles_Toxic_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\4\sounds\Toxic",1}};
	};
};
