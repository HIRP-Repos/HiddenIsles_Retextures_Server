////////////////////////////////////////////////////////////////////
//DeRap: equipment\casettes\rockmetal\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:50 2026 : 'file' last modified on Mon Oct 05 22:06:56 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Cassettes_RockMetal
	{
		units[] = {"HiddenIsles_Cassette_BadCompany","HiddenIsles_Cassette_StillCounting","HiddenIsles_Cassette_DoIWannaKnow","HiddenIsles_Cassette_EnterSandman","HiddenIsles_Cassette_BoulevardOfBrokenDreams","HiddenIsles_Cassette_MrBrightSide","HiddenIsles_Cassette_FreeBird"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgVehicles
{
	class GRP_Cassette_Base;
	class HiddenIsles_Cassette_BadCompany: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Five Finger Death Punch - Bad Company";
		descriptionShort = "Bad Company by Five Finger Death Punch";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\BadCompany.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BadCompany";
		};
	};
	class HiddenIsles_Cassette_StillCounting: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Volbeat - Still Counting";
		descriptionShort = "Still Counting by Volbeat";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\StillCounting.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_StillCounting";
		};
	};
	class HiddenIsles_Cassette_DoIWannaKnow: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Arctic Monkeys - Do I Wanna Know";
		descriptionShort = "Do I Wanna Know by Arctic Monkeys";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\DoIWannaKnow.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_DoIWannaKnow";
		};
	};
	class HiddenIsles_Cassette_EnterSandman: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Metallica - Enter Sandman";
		descriptionShort = "Enter Sandman by Metallica";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\EnterSandman.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_EnterSandman";
		};
	};
	class HiddenIsles_Cassette_BoulevardOfBrokenDreams: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Green Day - Boulevard Of Broken Dreams";
		descriptionShort = "Boulevard Of Broken Dreams by Green Day";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\BoulevardOfBrokenDreams.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_BoulevardOfBrokenDreams";
		};
	};
	class HiddenIsles_Cassette_MrBrightSide: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "The Killers - MrBrightSide";
		descriptionShort = "MrBrightSide by The Killers";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\MrBrightSide.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_MrBrightSide";
		};
	};
	class HiddenIsles_Cassette_FreeBird: GRP_Cassette_Base
	{
		scope = 2;
		displayName = "Lynyrd Skynyrd - Free Bird";
		descriptionShort = "Free Bird by Lynyrd Skynyrd";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\paa\FreeBird.paa"};
		class CfgCassette
		{
			soundSet = "HiddenIsles_SoundSet_FreeBird";
		};
	};
};
class CfgSoundSets
{
	class Mods_SoundSet_Base;
	class HiddenIsles_SoundSet_BadCompany
	{
		soundShaders[] = {"HiddenIsles_BadCompany_Shader"};
	};
	class HiddenIsles_SoundSet_StillCounting
	{
		soundShaders[] = {"HiddenIsles_StillCounting_Shader"};
	};
	class HiddenIsles_SoundSet_DoIWannaKnow
	{
		soundShaders[] = {"HiddenIsles_DoIWannaKnow_Shader"};
	};
	class HiddenIsles_SoundSet_EnterSandman
	{
		soundShaders[] = {"HiddenIsles_EnterSandman_Shader"};
	};
	class HiddenIsles_SoundSet_BoulevardOfBrokenDreams
	{
		soundShaders[] = {"HiddenIsles_BoulevardOfBrokenDreams_Shader"};
	};
	class HiddenIsles_SoundSet_MrBrightSide
	{
		soundShaders[] = {"HiddenIsles_MrBrightSide_Shader"};
	};
	class HiddenIsles_SoundSet_FreeBird
	{
		soundShaders[] = {"HiddenIsles_FreeBird_Shader"};
	};
};
class CfgSoundShaders
{
	class GRP_Cassette_SoundShader_Base;
	class HiddenIsles_BadCompany_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\BadCompany",1}};
	};
	class HiddenIsles_StillCounting_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\StillCounting",1}};
	};
	class HiddenIsles_DoIWannaKnow_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\DoIWannaKnow",1}};
	};
	class HiddenIsles_EnterSandman_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\EnterSandman",1}};
	};
	class HiddenIsles_BoulevardOfBrokenDreams_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\BoulevardOfBrokenDreams",1}};
	};
	class HiddenIsles_MrBrightSide_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\MrBrightSide",1}};
	};
	class HiddenIsles_FreeBird_Shader: GRP_Cassette_SoundShader_Base
	{
		samples[] = {{"HiddenIsles_Retextures_server\Equipment\Casettes\rockmetal\sounds\FreeBird",1}};
	};
};
