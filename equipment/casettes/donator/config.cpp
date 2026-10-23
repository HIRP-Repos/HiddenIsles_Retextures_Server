////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\donator\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:46 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_Donators
	{
		units[] = {"HiddenIsles_Cassette_TimberlandRanch","HiddenIsles_Cassette_310","HiddenIsles_Cassette_Smoke"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Donator_Cassette_TimberlandRanch: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "She Left Her Boots & Took My Heart";
		descriptionShort = "[DONATOR ITEM] Timberland Ranch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\paa\TimberlandRanch.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_TimberlandRanch";
		};
	};
	class HiddenIsles_Donator_Cassette_310: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "American Civil War Song - Battle Cry of Freedom";
		descriptionShort = "[DONATOR ITEM] 310 / Jimmy Caldwell";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\paa\310.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_310";
		};
	};
	class HiddenIsles_Donator_Cassette_Smoke: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Smokes Tape";
		descriptionShort = "[DONATOR ITEM] Smoke Timberland";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\paa\smoke.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_smoke";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_TimberlandRanch
	{
		soundShaders[] = {"HiddenIsles_TimberlandRanch_Shader"};
	};
	class HiddenIsles_SoundSet_310
	{
		soundShaders[] = {"HiddenIsles_310_Shader"};
	};
	class HiddenIsles_SoundSet_smoke
	{
		soundShaders[] = {"HiddenIsles_smoke_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_TimberlandRanch_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\TimberlandRanch",1}};
	};
	class HiddenIsles_310_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\310",1}};
	};
	class HiddenIsles_smoke_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_Server\Equipment\Casettes\donator\sounds\smoke",1}};
	};
};
