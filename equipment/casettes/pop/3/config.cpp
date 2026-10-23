////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\pop\3\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:47 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Pop3
	{
		units[] = {"HiddenIsles_Cassette_HotNCold","HiddenIsles_Cassette_BadDream","HiddenIsles_Cassette_Stronger","HiddenIsles_Cassette_PokerFace","HiddenIsles_Cassette_PartyInTheUSA","HiddenIsles_Cassette_Replay","HiddenIsles_Cassette_Disturbia","HiddenIsles_Cassette_Titanium"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_KPHotNCold: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Katy Perry - Hot N Cold";
		descriptionShort = "Hot N Cold by Katy Perry";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\HotNCold.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HotNCold";
		};
	};
	class HiddenIsles_Cassette_KPIKissedGirl: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Katy Perry - I Kissed A Girl";
		descriptionShort = "I Kissed A Girl by Katy Perry";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\IKissedAGirl.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_IKissedAGirl";
		};
	};
	class HiddenIsles_Cassette_StrongerKellyClarkson: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Kelly Clarkson - Stronger";
		descriptionShort = "Stronger by Kelly Clarkson";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\Stronger.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Stronger";
		};
	};
	class HiddenIsles_Cassette_PokerFace: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Lady Gaga - Poker Face";
		descriptionShort = "Poker Face by Lady Gaga";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\PokerFace.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PokerFace";
		};
	};
	class HiddenIsles_Cassette_PartyInTheUSA: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Miley Cyrus - Party In The USA";
		descriptionShort = "Party In The USA by Miley Cyrus";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\PartyInTheUSA.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PartyInTheUSA";
		};
	};
	class HiddenIsles_Cassette_Replay: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Iyaz - Replay";
		descriptionShort = "Replay by Iyaz";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\Replay.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Replay";
		};
	};
	class HiddenIsles_Cassette_Disturbia: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rihanna - Disturbia";
		descriptionShort = "Disturbia by Rihanna";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\Disturbia.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Disturbia";
		};
	};
	class HiddenIsles_Cassette_Titanium: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "David Guetta ft. Sia - Titanium";
		descriptionShort = "Titanium by David Guetta ft. Sia";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\paa\Titanium.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Titanium";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_HotNCold
	{
		soundShaders[] = {"HiddenIsles_HotNCold_Shader"};
	};
	class HiddenIsles_SoundSet_IKissedAGirl
	{
		soundShaders[] = {"HiddenIsles_IKissedAGirl_Shader"};
	};
	class HiddenIsles_SoundSet_Stronger
	{
		soundShaders[] = {"HiddenIsles_Stronger_Shader"};
	};
	class HiddenIsles_SoundSet_PokerFace
	{
		soundShaders[] = {"HiddenIsles_PokerFace_Shader"};
	};
	class HiddenIsles_SoundSet_PartyInTheUSA
	{
		soundShaders[] = {"HiddenIsles_PartyInTheUSA_Shader"};
	};
	class HiddenIsles_SoundSet_Replay
	{
		soundShaders[] = {"HiddenIsles_Replay_Shader"};
	};
	class HiddenIsles_SoundSet_Disturbia
	{
		soundShaders[] = {"HiddenIsles_Disturbia_Shader"};
	};
	class HiddenIsles_SoundSet_Titanium
	{
		soundShaders[] = {"HiddenIsles_Titanium_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_HotNCold_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\HotNCold",1}};
	};
	class HiddenIsles_IKissedAGirl_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\IKissedAGirl",1}};
	};
	class HiddenIsles_Stronger_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\Stronger",1}};
	};
	class HiddenIsles_PokerFace_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\PokerFace",1}};
	};
	class HiddenIsles_PartyInTheUSA_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\PartyInTheUSA",1}};
	};
	class HiddenIsles_Replay_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\Replay",1}};
	};
	class HiddenIsles_Disturbia_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\Disturbia",1}};
	};
	class HiddenIsles_Titanium_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\pop\3\sounds\Titanium",1}};
	};
};
