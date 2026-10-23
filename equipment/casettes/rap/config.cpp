////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rap\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:49 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Rap
	{
		units[] = {"HiddenIsles_Cassette_Lust","HiddenIsles_Cassette_DearGod","HiddenIsles_Cassette_StarShopping","HiddenIsles_Cassette_BaduFlow","HiddenIsles_Cassette_FeelIt","HiddenIsles_Cassette_Sad","HiddenIsles_Cassette_FightBack","HiddenIsles_Cassette_Go","HiddenIsles_Cassette_SoundOfDaPolice","HiddenIsles_Cassette_Riders","HiddenIsles_Cassette_GetLow"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_Lust: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "LIL SKIES - Lust";
		descriptionShort = "Lust by LIL SKIES";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\Lust.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Lust";
		};
	};
	class HiddenIsles_Cassette_DearGod: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Dax - Dear God";
		descriptionShort = "Dear God by Dax";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\DearGod.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DearGod";
		};
	};
	class HiddenIsles_Cassette_StarShopping: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Lil Peep - Star Shopping";
		descriptionShort = "Star Shopping by Lil Peep";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\StarShopping.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_StarShopping";
		};
	};
	class HiddenIsles_Cassette_BaduFlow: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "BigXthaPlug - Badu Flow";
		descriptionShort = "Badu Flow by BigXthaPlug";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\BaduFlow.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BaduFlow";
		};
	};
	class HiddenIsles_Cassette_FeelIt: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "D4vd - Feel It";
		descriptionShort = "Feel It by D4vd";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\FeelIt.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FeelIt";
		};
	};
	class HiddenIsles_Cassette_Sad: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "XXXTENTACION - Sad!";
		descriptionShort = "Sad! by XXXTENTACION";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\Sad.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Sad";
		};
	};
	class HiddenIsles_Cassette_FightBack: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "NEFFEX - Fight Back";
		descriptionShort = "Fight Back by NEFFEX";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\FightBack.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FightBack";
		};
	};
	class HiddenIsles_Cassette_Go: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "NEFFEX - Go";
		descriptionShort = "Go by NEFFEX";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\Go.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Go";
		};
	};
	class HiddenIsles_Cassette_SoundOfDaPolice: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "KRS-One - Sound Of Da Police";
		descriptionShort = "Sound Of Da Police by KRS-One";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\SoundOfDaPolice.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_SoundOfDaPolice";
		};
	};
	class HiddenIsles_Cassette_Riders: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Riders on the Storm - The Doors & Snoop Dogg";
		descriptionShort = "Riders on the Storm by The Doors & Snoop Dogg";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\SoundOfDaPolice.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_Riders";
		};
	};
	class HiddenIsles_Cassette_GetLow: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Get Low - LiL Jon";
		descriptionShort = "Get Low by LiL Jon";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\paa\SoundOfDaPolice.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_GetLow";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_Lust
	{
		soundShaders[] = {"HiddenIsles_Lust_Shader"};
	};
	class HiddenIsles_SoundSet_DearGod
	{
		soundShaders[] = {"HiddenIsles_DearGod_Shader"};
	};
	class HiddenIsles_SoundSet_StarShopping
	{
		soundShaders[] = {"HiddenIsles_StarShopping_Shader"};
	};
	class HiddenIsles_SoundSet_BaduFlow
	{
		soundShaders[] = {"HiddenIsles_BaduFlow_Shader"};
	};
	class HiddenIsles_SoundSet_FeelIt
	{
		soundShaders[] = {"HiddenIsles_FeelIt_Shader"};
	};
	class HiddenIsles_SoundSet_Sad
	{
		soundShaders[] = {"HiddenIsles_Sad_Shader"};
	};
	class HiddenIsles_SoundSet_FightBack
	{
		soundShaders[] = {"HiddenIsles_FightBack_Shader"};
	};
	class HiddenIsles_SoundSet_Go
	{
		soundShaders[] = {"HiddenIsles_Go_Shader"};
	};
	class HiddenIsles_SoundSet_SoundOfDaPolice
	{
		soundShaders[] = {"HiddenIsles_SoundOfDaPolice_Shader"};
	};
	class HiddenIsles_SoundSet_Riders
	{
		soundShaders[] = {"HiddenIsles_Riders_Shader"};
	};
	class HiddenIsles_SoundSet_GetLow
	{
		soundShaders[] = {"HiddenIsles_GetLow_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_Lust_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\Lust",1}};
	};
	class HiddenIsles_DearGod_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\DearGod",1}};
	};
	class HiddenIsles_StarShopping_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\StarShopping",1}};
	};
	class HiddenIsles_BaduFlow_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\BaduFlow",1}};
	};
	class HiddenIsles_FeelIt_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\FeelIt",1}};
	};
	class HiddenIsles_Sad_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\Sad",1}};
	};
	class HiddenIsles_FightBack_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\FightBack",1}};
	};
	class HiddenIsles_Go_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\Go",1}};
	};
	class HiddenIsles_SoundOfDaPolice_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\SoundOfDaPolice",1}};
	};
	class HiddenIsles_Riders_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\Riders",1}};
	};
	class HiddenIsles_GetLow_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rap\sounds\GetLow",1}};
	};
};
