////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Sat Oct 10 21:56:09 2026 : 'file' last modified on Sat Oct 10 21:56:09 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class FENR_PDA
	{
		units[] = {"FENR_PDA_FlashDrive","FENR_PDA_IntelDrive","FENR_PDA_EncryptedDrive","FENR_PDA_Device"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts","JM_CF_Scripts","DZM_VPPAdminToolsScripts"};
	};
};
class CfgMods
{
	class FENR_Industries_PDA
	{
		dir = "PDA";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "Fenrir Industries PDA";
		author = "Fenr.EXE";
		credits = "Fenrir Industries";
		authorID = "";
		version = "8.1.0";
		extra = 0;
		type = "mod";
		inputs = "PDA/data/inputs.xml";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"PDA/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"PDA/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"PDA/scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class FENR_PDA_FlashDrive: Inventory_Base
	{
		scope = 2;
		title = "#pda_flashdrive_name";
		displayName = "#pda_flashdrive_name";
		descriptionShort = "#pda_flashdrive_desc";
		model = "PDA\data\flashdrive.p3d";
		itemSize[] = {1,1};
		weight = 250;
		inventorySlot[] = {"FENR_PDAFlashDrive"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"PDA\data\flashdrive.rvmat"}},{0.7,{"PDA\data\flashdrive.rvmat"}},{0.5,{"PDA\data\flashdrive_damage.rvmat"}},{0.3,{"PDA\data\flashdrive_damage.rvmat"}},{0,{"PDA\data\flashdrive_destruct.rvmat"}}};
				};
			};
		};
	};
	class FENR_PDA_IntelDrive: FENR_PDA_FlashDrive
	{
		scope = 2;
		title = "Intel Drive";
		displayName = "Intel Drive";
		descriptionShort = "A recovered data drive. Insert it into a PDA to read the files stored on it.";
		inventorySlot[] = {"FENR_PDAIntelDrive"};
	};
	class FENR_PDA_EncryptedDrive: FENR_PDA_FlashDrive
	{
		scope = 2;
		title = "Encrypted Drive";
		displayName = "Encrypted Drive";
		descriptionShort = "A PIN-protected Fenrir Industries drive. Stores map markers and group records behind a 4 digit PIN.";
		inventorySlot[] = {"FENR_PDAEncryptedDrive"};
	};
	class FENR_PDA_Device: Inventory_Base
	{
		scope = 2;
		title = "#pda_item_name";
		displayName = "#pda_item_name";
		descriptionShort = "#pda_item_desc";
		model = "PDA\data\pda.p3d";
		animClass = "ItemPDA";
		itemSize[] = {2,2};
		weight = 250;
		repairableWithKits[] = {5,7};
		repairCosts[] = {30,25};
		oldpower = 0;
		attachments[] = {"BatteryD","FENR_PDAFlashDrive","FENR_PDAIntelDrive","FENR_PDAEncryptedDrive"};
		class EnergyManager
		{
			hasIcon = 1;
			autoSwitchOff = 1;
			energyUsagePerSecond = 0.0001;
			plugType = 1;
			attachmentAction = 1;
			wetnessExposure = 0.1;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1,{"PDA\data\pda.rvmat"}},{0.7,{"PDA\data\pda.rvmat"}},{0.5,{"PDA\data\pda_damage.rvmat"}},{0.3,{"PDA\data\pda_damage.rvmat"}},{0,{"PDA\data\pda_destruct.rvmat"}}};
				};
			};
		};
	};
};
class CfgSlots
{
	class Slot_FENR_PDAFlashDrive
	{
		name = "FENR_PDAFlashDrive";
		displayName = "FENR_PDAFlashDrive";
		ghostIcon = "default";
	};
	class Slot_FENR_PDAIntelDrive
	{
		name = "FENR_PDAIntelDrive";
		displayName = "Intel Drive";
		ghostIcon = "default";
	};
	class Slot_FENR_PDAEncryptedDrive
	{
		name = "FENR_PDAEncryptedDrive";
		displayName = "Encrypted Drive";
		ghostIcon = "default";
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class FENR_PDA_Message_SoundShader: baseCharacter_SoundShader
	{
		samples[] = {{"PDA\sounds\new_message",1}};
		volume = 0.5;
	};
	class FENR_PDA_SOS_SoundShader: baseCharacter_SoundShader
	{
		samples[] = {{"PDA\sounds\sos_alarm",1}};
		volume = 0.9;
	};
};
class CfgSoundSets
{
	class baseCharacter_SoundSet;
	class FENR_PDA_Message_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[] = {"FENR_PDA_Message_SoundShader"};
	};
	class FENR_PDA_SOS_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[] = {"FENR_PDA_SOS_SoundShader"};
	};
};
