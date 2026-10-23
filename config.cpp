////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:45 2026 : 'file' last modified on Mon Oct 05 22:06:57 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Retextures
	{
		units[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters","DZ_Scripts","FOG_MOD_Bags","FOG_MOD_Clothes","FOG_MOD_Data","FOG_MOD_Gear","FOG_MOD_Helmets","FOG_MOD_Scripts","FOG_MOD_Vests","FOG_MOD_Weapons","FOG_Retexture"};
		weapons[] = {};
	};
};
class CfgMods
{
	class HiddenIsles_Retextures
	{
		dir = "clothing";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "HiddenIsles_Retextures";
		credits = "Plague";
		author = "Plague";
		authorID = "0";
		version = "0.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"HiddenIsles_Retextures_Server/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"HiddenIsles_Retextures_Server/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"HiddenIsles_Retextures_Server/scripts/5_Mission"};
			};
		};
	};
};
