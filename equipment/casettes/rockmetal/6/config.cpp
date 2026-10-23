////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\6\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rock6
	{
		units[] = {"HiddenIsles_Cassette_PsychoKiller","HiddenIsles_Cassette_LikeaStone","HiddenIsles_Cassette_DownWithTheSickness","HiddenIsles_Cassette_EyeOfTheStorm","HiddenIsles_Cassette_AlwaysRunning","HiddenIsles_Cassette_AreYouReady","HiddenIsles_Cassette_BatCountry","HiddenIsles_Cassette_BeautyofAnnihilation","HiddenIsles_Cassette_BloodBrothers","HiddenIsles_Cassette_BurnMeBeautiful","HiddenIsles_Cassette_Chaos","HiddenIsles_Cassette_City","HiddenIsles_Cassette_EvenIfItKillsMe","HiddenIsles_Cassette_EverywhereIGo","HiddenIsles_Cassette_Evil","HiddenIsles_Cassette_FallingApart","HiddenIsles_Cassette_FeelsLikeHome","HiddenIsles_Cassette_Gunslinger","HiddenIsles_Cassette_HalfwayToHell","HiddenIsles_Cassette_HeartOfAChampion","HiddenIsles_Cassette_HeyYou","HiddenIsles_Cassette_HollywoodForever","HiddenIsles_Cassette_LastResort","HiddenIsles_Cassette_Levitate","HiddenIsles_Cassette_LikeAVillain","HiddenIsles_Cassette_Medicine","HiddenIsles_Cassette_NotListening","HiddenIsles_Cassette_Radioactive","HiddenIsles_Cassette_Rain","HiddenIsles_Cassette_Riot","HiddenIsles_Cassette_SAVIOR","HiddenIsles_Cassette_SeeUinHell","HiddenIsles_Cassette_Swerve","HiddenIsles_Cassette_WeAre","HiddenIsles_Cassette_DontStopBelievin","HiddenIsles_Cassette_EyeOfTheTiger","HiddenIsles_Cassette_LivinOnAPrayer","HiddenIsles_Cassette_TheFinalCountdown","HiddenIsles_Cassette_Thunderstruck","HiddenIsles_Cassette_AintNoRestfortheWicked"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_PsychoKiller: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Talking Heads - Psycho Killer";
		descriptionShort = "Psycho Killer by Talking Heads";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_PsychoKiller";
		};
	};
	class HiddenIsles_Cassette_AintNoRestfortheWicked: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Cage The Elephant - Ain't No Rest for the Wicked";
		descriptionShort = "Ain't No Rest for the Wicked by Cage The Elephant";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_AintNoRestfortheWicked";
		};
	};
	class HiddenIsles_Cassette_LikeaStone: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Audioslave - Like a Stone";
		descriptionShort = "Like a Stone by Audioslave";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LikeaStone";
		};
	};
	class HiddenIsles_Cassette_DownWithTheSickness: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Disturbed - Down With The Sickness";
		descriptionShort = "Down With The Sickness by Disturbed";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DownWithTheSickness";
		};
	};
	class HiddenIsles_Cassette_EyeOfTheStorm: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "FFDP - Eye Of The Storm";
		descriptionShort = "Eye Of The Storm by FFDP";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EyeOfTheStorm";
		};
	};
	class HiddenIsles_Cassette_AlwaysRunning: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Always Running - Malukah";
		descriptionShort = "Always Running by Malukah";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_AlwaysRunning";
		};
	};
	class HiddenIsles_Cassette_AreYouReady: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Are You Ready - Disturbed";
		descriptionShort = "Are You Ready by Disturbed";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_AreYouReady";
		};
	};
	class HiddenIsles_Cassette_BatCountry: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Bat Country - Avenged Sevnfold";
		descriptionShort = "Bat Country by Avenged Sevnfold";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BatCountry";
		};
	};
	class HiddenIsles_Cassette_BeautyofAnnihilation: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Beauty of Annihilation - Elena Siegman";
		descriptionShort = "Beauty of Annihilation by Elena Siegman";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BeautyofAnnihilation";
		};
	};
	class HiddenIsles_Cassette_BloodBrothers: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Blood Brothers - Papa Roach";
		descriptionShort = "Blood Brothers by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BloodBrothers";
		};
	};
	class HiddenIsles_Cassette_BurnMeBeautiful: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Burn Me Beautiful - Shadow Beloved";
		descriptionShort = "Burn Me Beautiful by Shadow Beloved";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BurnMeBeautiful";
		};
	};
	class HiddenIsles_Cassette_Chaos: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Chaos - Hollywood Undead";
		descriptionShort = "Chaos by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Chaos";
		};
	};
	class HiddenIsles_Cassette_City: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "City - Hollywood Undead";
		descriptionShort = "City by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_City";
		};
	};
	class HiddenIsles_Cassette_EvenIfItKillsMe: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "EVEN IF IT KILLS ME  - Papa Roach";
		descriptionShort = "EVEN IF IT KILLS ME by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EvenIfItKillsMe";
		};
	};
	class HiddenIsles_Cassette_EverywhereIGo: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Everywhere I Go - Hollywood Undead";
		descriptionShort = "Everywhere I Go by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EverywhereIGo";
		};
	};
	class HiddenIsles_Cassette_Evil: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Evil - Hollywood Undead";
		descriptionShort = "Evil by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Evil";
		};
	};
	class HiddenIsles_Cassette_FallingApart: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Falling Apart  - Papa Roach";
		descriptionShort = "Falling Apart by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FallingApart";
		};
	};
	class HiddenIsles_Cassette_FeelsLikeHome: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Feels Like Home - Hollywood Undead";
		descriptionShort = "Feels Like Home by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FeelsLikeHome";
		};
	};
	class HiddenIsles_Cassette_Gunslinger: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Gunslinger - Avenged Sevenfold";
		descriptionShort = "Gunslinger by Avenged Sevenfold";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Gunslinger";
		};
	};
	class HiddenIsles_Cassette_HalfwayToHell: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Halfway To Hell - Jelly Roll";
		descriptionShort = "Halfway To Hell by Jelly Roll";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HalfwayToHell";
		};
	};
	class HiddenIsles_Cassette_HeartOfAChampion: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Heart Of A Champion - Hollywood Undead";
		descriptionShort = "Heart Of A Champion by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HeartOfAChampion";
		};
	};
	class HiddenIsles_Cassette_HollywoodForever: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Hollywood Forever - Hollywood Undead";
		descriptionShort = "Hollywood Forever by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HollywoodForever";
		};
	};
	class HiddenIsles_Cassette_HeyYou: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Hey You - Disturbed";
		descriptionShort = "Hey You by Disturbed";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_HeyYou";
		};
	};
	class HiddenIsles_Cassette_LastResort: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Last Resort  - Papa Roach";
		descriptionShort = "Last Resort by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LastResort";
		};
	};
	class HiddenIsles_Cassette_Levitate: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Levitate - Hollywood Undead";
		descriptionShort = "Levitate by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Levitate";
		};
	};
	class HiddenIsles_Cassette_LikeAVillain: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Like A Villain - Bad Omens";
		descriptionShort = "Like A Villain by Bad Omens";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LikeAVillain";
		};
	};
	class HiddenIsles_Cassette_Medicine: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Medicine - Hollywood Undead";
		descriptionShort = "Medicine by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Medicine";
		};
	};
	class HiddenIsles_Cassette_NotListening: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Not Listening  - Papa Roach";
		descriptionShort = "Not Listening by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_NotListening";
		};
	};
	class HiddenIsles_Cassette_Radioactive: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Radioactive - Imagine Dragons";
		descriptionShort = "Radioactive by Imagine Dragons";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Radioactive";
		};
	};
	class HiddenIsles_Cassette_Rain: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Rain - Sleep Token";
		descriptionShort = "Rain by Sleep Token";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Rain";
		};
	};
	class HiddenIsles_Cassette_Riot: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Riot - Hollywood Undead";
		descriptionShort = "Riot by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Riot";
		};
	};
	class HiddenIsles_Cassette_SAVIOR: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "SAVIOR - Hollywood Undead";
		descriptionShort = "SAVIOR by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SAVIOR";
		};
	};
	class HiddenIsles_Cassette_SeeUinHell: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "See U in Hell - Papa Roach";
		descriptionShort = "See U in Hell by Papa Roach";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SeeUinHell";
		};
	};
	class HiddenIsles_Cassette_Swerve: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Swerve - Hollywood Undead";
		descriptionShort = "Swerve by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Swerve";
		};
	};
	class HiddenIsles_Cassette_WeAre: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "We Are - Hollywood Undead";
		descriptionShort = "We Are by Hollywood Undead";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_WeAre";
		};
	};
	class HiddenIsles_Cassette_DontStopBelievin: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Dont Stop Believin - Journey";
		descriptionShort = "Dont Stop Believin by Journey";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DontStopBelievin";
		};
	};
	class HiddenIsles_Cassette_EyeOfTheTiger: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Eye Of The Tiger - Survivor";
		descriptionShort = "Eye Of The Tiger by Survivor";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EyeOfTheTiger";
		};
	};
	class HiddenIsles_Cassette_LivinOnAPrayer: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Livin On A Prayer - Bon Jovi";
		descriptionShort = "Livin On A Prayer by Bon Jovi";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_LivinOnAPrayer";
		};
	};
	class HiddenIsles_Cassette_TheFinalCountdown: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Final Countdown - Europe";
		descriptionShort = "The Final Countdown by Europe";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TheFinalCountdown";
		};
	};
	class HiddenIsles_Cassette_Thunderstruck: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Thunderstruck - ACDC";
		descriptionShort = "Thunderstruck by ACDC";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\paa\rock.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Thunderstruck";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_PsychoKiller
	{
		soundShaders[] = {"HiddenIsles_PsychoKiller_Shader"};
	};
	class HiddenIsles_SoundSet_AintNoRestfortheWicked
	{
		soundShaders[] = {"HiddenIsles_AintNoRestfortheWicked_Shader"};
	};
	class HiddenIsles_SoundSet_LikeaStone
	{
		soundShaders[] = {"HiddenIsles_LikeaStone_Shader"};
	};
	class HiddenIsles_SoundSet_DownWithTheSickness
	{
		soundShaders[] = {"HiddenIsles_DownWithTheSickness_Shader"};
	};
	class HiddenIsles_SoundSet_EyeOfTheStorm
	{
		soundShaders[] = {"HiddenIsles_EyeOfTheStorm_Shader"};
	};
	class HiddenIsles_SoundSet_AlwaysRunning
	{
		soundShaders[] = {"HiddenIsles_AlwaysRunning_Shader"};
	};
	class HiddenIsles_SoundSet_AreYouReady
	{
		soundShaders[] = {"HiddenIsles_AreYouReady_Shader"};
	};
	class HiddenIsles_SoundSet_BatCountry
	{
		soundShaders[] = {"HiddenIsles_BatCountry_Shader"};
	};
	class HiddenIsles_SoundSet_BeautyofAnnihilation
	{
		soundShaders[] = {"HiddenIsles_BeautyofAnnihilation_Shader"};
	};
	class HiddenIsles_SoundSet_BloodBrothers
	{
		soundShaders[] = {"HiddenIsles_BloodBrothers_Shader"};
	};
	class HiddenIsles_SoundSet_BurnMeBeautiful
	{
		soundShaders[] = {"HiddenIsles_BurnMeBeautiful_Shader"};
	};
	class HiddenIsles_SoundSet_Chaos
	{
		soundShaders[] = {"HiddenIsles_Chaos_Shader"};
	};
	class HiddenIsles_SoundSet_City
	{
		soundShaders[] = {"HiddenIsles_City_Shader"};
	};
	class HiddenIsles_SoundSet_EvenIfItKillsMe
	{
		soundShaders[] = {"HiddenIsles_EvenIfItKillsMe_Shader"};
	};
	class HiddenIsles_SoundSet_EverywhereIGo
	{
		soundShaders[] = {"HiddenIsles_EverywhereIGo_Shader"};
	};
	class HiddenIsles_SoundSet_Evil
	{
		soundShaders[] = {"HiddenIsles_Evil_Shader"};
	};
	class HiddenIsles_SoundSet_FallingApart
	{
		soundShaders[] = {"HiddenIsles_FallingApart_Shader"};
	};
	class HiddenIsles_SoundSet_FeelsLikeHome
	{
		soundShaders[] = {"HiddenIsles_FeelsLikeHome_Shader"};
	};
	class HiddenIsles_SoundSet_Gunslinger
	{
		soundShaders[] = {"HiddenIsles_Gunslinger_Shader"};
	};
	class HiddenIsles_SoundSet_HalfwayToHell
	{
		soundShaders[] = {"HiddenIsles_HalfwayToHell_Shader"};
	};
	class HiddenIsles_SoundSet_HeartOfAChampion
	{
		soundShaders[] = {"HiddenIsles_HeartOfAChampion_Shader"};
	};
	class HiddenIsles_SoundSet_HeyYou
	{
		soundShaders[] = {"HiddenIsles_HeyYou_Shader"};
	};
	class HiddenIsles_SoundSet_HollywoodForever
	{
		soundShaders[] = {"HiddenIsles_HollywoodForever_Shader"};
	};
	class HiddenIsles_SoundSet_LastResort
	{
		soundShaders[] = {"HiddenIsles_LastResort_Shader"};
	};
	class HiddenIsles_SoundSet_Levitate
	{
		soundShaders[] = {"HiddenIsles_Levitate_Shader"};
	};
	class HiddenIsles_SoundSet_LikeAVillain
	{
		soundShaders[] = {"HiddenIsles_LikeAVillain_Shader"};
	};
	class HiddenIsles_SoundSet_Medicine
	{
		soundShaders[] = {"HiddenIsles_Medicine_Shader"};
	};
	class HiddenIsles_SoundSet_NotListening
	{
		soundShaders[] = {"HiddenIsles_NotListening_Shader"};
	};
	class HiddenIsles_SoundSet_Radioactive
	{
		soundShaders[] = {"HiddenIsles_Radioactive_Shader"};
	};
	class HiddenIsles_SoundSet_Rain
	{
		soundShaders[] = {"HiddenIsles_Rain_Shader"};
	};
	class HiddenIsles_SoundSet_Riot
	{
		soundShaders[] = {"HiddenIsles_Riot_Shader"};
	};
	class HiddenIsles_SoundSet_SAVIOR
	{
		soundShaders[] = {"HiddenIsles_SAVIOR_Shader"};
	};
	class HiddenIsles_SoundSet_SeeUinHell
	{
		soundShaders[] = {"HiddenIsles_SeeUinHell_Shader"};
	};
	class HiddenIsles_SoundSet_Swerve
	{
		soundShaders[] = {"HiddenIsles_Swerve_Shader"};
	};
	class HiddenIsles_SoundSet_WeAre
	{
		soundShaders[] = {"HiddenIsles_WeAre_Shader"};
	};
	class HiddenIsles_SoundSet_DontStopBelievin
	{
		soundShaders[] = {"HiddenIsles_DontStopBelievin_Shader"};
	};
	class HiddenIsles_SoundSet_EyeOfTheTiger
	{
		soundShaders[] = {"HiddenIsles_EyeOfTheTiger_Shader"};
	};
	class HiddenIsles_SoundSet_LivinOnAPrayer
	{
		soundShaders[] = {"HiddenIsles_LivinOnAPrayer_Shader"};
	};
	class HiddenIsles_SoundSet_TheFinalCountdown
	{
		soundShaders[] = {"HiddenIsles_TheFinalCountdown_Shader"};
	};
	class HiddenIsles_SoundSet_Thunderstruck
	{
		soundShaders[] = {"HiddenIsles_Thunderstruck_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_PsychoKiller_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\PsychoKiller",1}};
	};
	class HiddenIsles_AintNoRestfortheWicked_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\AintNoRestfortheWicked",1}};
	};
	class HiddenIsles_LikeaStone_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\LikeaStone",1}};
	};
	class HiddenIsles_DownWithTheSickness_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\DownWithTheSickness",1}};
	};
	class HiddenIsles_EyeOfTheStorm_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\EyeOfTheStorm",1}};
	};
	class HiddenIsles_AlwaysRunning_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\AlwaysRunning",1}};
	};
	class HiddenIsles_AreYouReady_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\AreYouReady",1}};
	};
	class HiddenIsles_BatCountry_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\BatCountry",1}};
	};
	class HiddenIsles_BeautyofAnnihilation_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\BeautyofAnnihilation",1}};
	};
	class HiddenIsles_BloodBrothers_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\BloodBrothers",1}};
	};
	class HiddenIsles_BurnMeBeautiful_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\BurnMeBeautiful",1}};
	};
	class HiddenIsles_Chaos_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Chaos",1}};
	};
	class HiddenIsles_City_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\City",1}};
	};
	class HiddenIsles_EvenIfItKillsMe_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\EvenIfItKillsMe",1}};
	};
	class HiddenIsles_EverywhereIGo_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\EverywhereIGo",1}};
	};
	class HiddenIsles_Evil_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Evil",1}};
	};
	class HiddenIsles_FallingApart_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\FallingApart",1}};
	};
	class HiddenIsles_FeelsLikeHome_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\FeelsLikeHome",1}};
	};
	class HiddenIsles_Gunslinger_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Gunslinger",1}};
	};
	class HiddenIsles_HalfwayToHell_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\HalfwayToHell",1}};
	};
	class HiddenIsles_HeartOfAChampion_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\HeartOfAChampion",1}};
	};
	class HiddenIsles_HeyYou_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\HeyYou",1}};
	};
	class HiddenIsles_HollywoodForever_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\HollywoodForever",1}};
	};
	class HiddenIsles_LastResort_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\LastResort",1}};
	};
	class HiddenIsles_Levitate_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Levitate",1}};
	};
	class HiddenIsles_LikeAVillain_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\LikeAVillain",1}};
	};
	class HiddenIsles_Medicine_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Medicine",1}};
	};
	class HiddenIsles_NotListening_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\NotListening",1}};
	};
	class HiddenIsles_Radioactive_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Radioactive",1}};
	};
	class HiddenIsles_Rain_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Rain",1}};
	};
	class HiddenIsles_Riot_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Riot",1}};
	};
	class HiddenIsles_SAVIOR_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\SAVIOR",1}};
	};
	class HiddenIsles_SeeUinHell_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\SeeUinHell",1}};
	};
	class HiddenIsles_Swerve_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Swerve",1}};
	};
	class HiddenIsles_WeAre_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\WeAre",1}};
	};
	class HiddenIsles_DontStopBelievin_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\DontStopBelievin",1}};
	};
	class HiddenIsles_EyeOfTheTiger_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\EyeOfTheTiger",1}};
	};
	class HiddenIsles_LivinOnAPrayer_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\LivinOnAPrayer",1}};
	};
	class HiddenIsles_TheFinalCountdown_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\TheFinalCountdown",1}};
	};
	class HiddenIsles_Thunderstruck_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\6\sounds\Thunderstruck",1}};
	};
};
