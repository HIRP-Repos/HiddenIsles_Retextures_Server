////////////////////////////////////////////////////////////////////
//DeRap: equipment\pincontainers\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:50 2026 : 'file' last modified on Mon Oct 05 22:06:55 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_PinContainers_Retextures
	{
		units[] = {"HiddenIsles_PinContainer_4"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Gear_Books"};
	};
};
class CfgVehicles
{
	class SmallProtectorCase;
	class HiddenIsles_Pinbook: SmallProtectorCase
	{
		scope = 0;
		simulation = "ItemBook";
		displayName = "Pin Container";
		model = "\DZ\gear\books\Book_kniga.p3d";
		hiddenSelections[] = {"camoGround"};
		inventorySlot[] = {"Book_slot"};
		rotationFlags = 1;
		canBeDigged = 1;
		allowOwnedCargoManipulation = 1;
		isMeleeWeapon = 1;
		descriptionShort = "A book container for all your pins!";
		weight = 50;
		itemSize[] = {2,2};
		itemsCargoSize[] = {0,0};
		attachments[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6","Pin7","Pin8","Pin9","Pin10","Pin11","Pin12"};
		quantityShow = 0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1,{"DZ\gear\books\Data\book.rvmat"}},{0.7,{"DZ\gear\books\Data\book.rvmat"}},{0.5,{"DZ\gear\books\Data\book_damage.rvmat"}},{0.3,{"DZ\gear\books\Data\book_damage.rvmat"}},{0,{"DZ\gear\books\Data\book_destruct.rvmat"}}};
				};
			};
		};
	};
	class HiddenIsles_PinContainer_2: HiddenIsles_Pinbook
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack2.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack2.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack2.paa"};
	};
	class HiddenIsles_PinContainer_5: HiddenIsles_Pinbook
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack5.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack5.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack5.paa"};
	};
	class HiddenIsles_PinContainer_1: HiddenIsles_Pinbook
	{
		scope = 2;
		attachments[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6","Pin7","Pin8","Pin9"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack1.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack1.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack1.paa"};
	};
	class HiddenIsles_PinContainer_4: HiddenIsles_Pinbook
	{
		scope = 2;
		attachments[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6","Pin7"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack4.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack4.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack4.paa"};
	};
	class HiddenIsles_PinContainer_3: HiddenIsles_Pinbook
	{
		scope = 2;
		attachments[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack3.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack3.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack3.paa"};
	};
	class HiddenIsles_PinContainer_6: HiddenIsles_Pinbook
	{
		scope = 2;
		attachments[] = {"Pin1","Pin2","Pin3","Pin4","Pin5","Pin6","Pin7","Pin8"};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack6.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack6.paa","HiddenIsles_Retextures_server\Equipment\PinContainers\book_pinpack6.paa"};
	};
};
class CfgSlots
{
	class Slot_Pin4
	{
		name = "Pin4";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin5
	{
		name = "Pin5";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin6
	{
		name = "Pin6";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin7
	{
		name = "Pin7";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin8
	{
		name = "Pin8";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin9
	{
		name = "Pin9";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin10
	{
		name = "Pin10";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin11
	{
		name = "Pin11";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
	class Slot_Pin12
	{
		name = "Pin12";
		displayName = "Pin";
		ghostIcon = "missing";
		show = "true";
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class Proxypin4: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin4"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin4.p3d";
	};
	class Proxypin5: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin5"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin5.p3d";
	};
	class Proxypin6: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin6"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin6.p3d";
	};
	class Proxypin7: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin7"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin7.p3d";
	};
	class Proxypin8: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin8"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin8.p3d";
	};
	class Proxypin9: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin9"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin9.p3d";
	};
	class Proxypin10: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin10"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin10.p3d";
	};
	class Proxypin11: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin11"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin11.p3d";
	};
	class Proxypin12: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] += {"Pin12"};
		model = "\HiddenIsles_Retextures_server\clothing\pins\Proxies\pin12.p3d";
	};
};
