////////////////////////////////////////////////////////////////////
//DeRap: clothing\tops\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Tue Oct 06 19:35:44 2026 : 'file' last modified on Mon Oct 05 22:06:54 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class HiddenIsles_Tops_Retextures
	{
		units[] = {"HiddenIsles_Hoodie_Japanese"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters","DZ_Characters_Tops"};
	};
};
class CfgVehicles
{
	class ClothingBase;
	class Clothing;
	class Blouse_ColorBase;
	class DenimJacket;
	class Hoodie_Blue;
	class MiniDress_Pink;
	class Raincoat_ColorBase;
	class Raincoat_Red;
	class RidersJacket_ColorBase;
	class Shirt_BlueCheck;
	class Shirt_ColorBase;
	class Sweater_Gray;
	class TelnyashkaShirt;
	class TrackSuitJacket_Red;
	class TShirt_Beige;
	class TShirt_ColorBase;
	class QuiltedJacket_ColorBase;
	class BomberJacket_ColorBase;
	class ALV_PoliceShirt_Blue;
	class PoliceJacket;
	class ParamedicJacket_Blue;
	class BushlatPoliceJacket_ColorBase;
	class ManSuit_Blue;
	class ManSuit_LightGrey;
	class ALV_PulloverHoodie_Black;
	class HiddenIsles_EMT: ParamedicJacket_Blue
	{
		scope = 2;
		displayName = "EMT Jacket";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_emt.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_emt.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_emt.paa"};
	};
	class HiddenIsles_AEMT: ParamedicJacket_Blue
	{
		scope = 2;
		displayName = "A-EMT Jacket";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_aemt.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_aemt.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_aemt.paa"};
	};
	class HiddenIsles_Paramedic: ParamedicJacket_Blue
	{
		scope = 2;
		displayName = "Paramedic Jacket";
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_paramedic.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_paramedic.paa","HiddenIsles_Retextures_Server\clothing\tops\medical\paramedic_jacket_paramedic.paa"};
	};
	class HiddenIsles_Hoodie_Japanese: Hoodie_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Japanese_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Japanese_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Japanese_F.paa"};
	};
	class HiddenIsles_Hoodie_Skeleton: Hoodie_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Skeleton_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Skeleton_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_Skeleton_F.paa"};
	};
	class HiddenIsles_Hoodie_YellowSkull: Hoodie_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_YellowSkull_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_YellowSkull_F.paa","HiddenIsles_Retextures_Server\clothing\tops\hoodie\Hoodie_YellowSkull_F.paa"};
	};
	class HiddenIsles_MiniDress_blueflowers: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_blueflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_blueflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_blueflowers.paa"};
	};
	class HiddenIsles_MiniDress_cottonflowers: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_cottonflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_cottonflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_cottonflowers.paa"};
	};
	class HiddenIsles_MiniDress_japaneseflowers: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_japaneseflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_japaneseflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_japaneseflowers.paa"};
	};
	class HiddenIsles_MiniDress_koifish: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_koifish.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_koifish.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_koifish.paa"};
	};
	class HiddenIsles_MiniDress_purplerose: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_purplerose.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_purplerose.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_purplerose.paa"};
	};
	class HiddenIsles_MiniDress_redblackbunny: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redblackbunny.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redblackbunny.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redblackbunny.paa"};
	};
	class HiddenIsles_MiniDress_redjapanese: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redjapanese.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redjapanese.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\miniDress_redjapanese.paa"};
	};
	class HiddenIsles_MiniDress_blackgold: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_blackgold.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_blackgold.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_blackgold.paa"};
	};
	class HiddenIsles_MiniDress_brownflowers: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_brownflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_brownflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_brownflowers.paa"};
	};
	class HiddenIsles_MiniDress_greenflower: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_greenflower.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_greenflower.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_greenflower.paa"};
	};
	class HiddenIsles_Minidress_nightsky: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_nightsky.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_nightsky.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_nightsky.paa"};
	};
	class HiddenIsles_Minidress_roselace: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_roselace.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_roselace.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_roselace.paa"};
	};
	class HiddenIsles_Minidress_striped: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_striped.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_striped.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_striped.paa"};
	};
	class HiddenIsles_Minidress_sunny: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_sunny.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_sunny.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_sunny.paa"};
	};
	class HiddenIsles_Minidress_tanflowers: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tanflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tanflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tanflowers.paa"};
	};
	class HiddenIsles_Minidress_tangold: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tangold.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tangold.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_tangold.paa"};
	};
	class HiddenIsles_Minidress_white: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_white.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_white.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_white.paa"};
	};
	class HiddenIsles_Minidress_whitelace: MiniDress_Pink
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_whitelace.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_whitelace.paa","HiddenIsles_Retextures_Server\clothing\tops\minidress\minidress_whitelace.paa"};
	};
	class HiddenIsles_QuiltedJacket_greyroses: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greyroses.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greyroses.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greyroses.paa"};
	};
	class HiddenIsles_QuiltedJacket_pinkred: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkred.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkred.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkred.paa"};
	};
	class HiddenIsles_QuiltedJacket_yellowtoxic: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowtoxic.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowtoxic.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowtoxic.paa"};
	};
	class HiddenIsles_QuiltedJacket_black: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_black.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_black.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_black.paa"};
	};
	class HiddenIsles_QuiltedJacket_bluewhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_bluewhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_bluewhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_bluewhite.paa"};
	};
	class HiddenIsles_QuiltedJacket_greenpink: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenpink.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenpink.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenpink.paa"};
	};
	class HiddenIsles_QuiltedJacket_greenwhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_greenwhite.paa"};
	};
	class HiddenIsles_QuiltedJacket_pinkblue: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkblue.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkblue.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkblue.paa"};
	};
	class HiddenIsles_QuiltedJacket_pinkwhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_pinkwhite.paa"};
	};
	class HiddenIsles_QuiltedJacket_purplewhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_purplewhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_purplewhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_purplewhite.paa"};
	};
	class HiddenIsles_QuiltedJacket_redwhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_redwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_redwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_redwhite.paa"};
	};
	class HiddenIsles_QuiltedJacket_yellowwhite: QuiltedJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowwhite.paa","HiddenIsles_Retextures_Server\clothing\tops\quiltedjacket\quiltedjacket_yellowwhite.paa"};
	};
	class HiddenIsles_RidersJacket_bluegreyflowers: RidersJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_bluegreyflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_bluegreyflowers.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_bluegreyflowers.paa"};
	};
	class HiddenIsles_RidersJacket_blueskeletons: RidersJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_blueskeletons.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_blueskeletons.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_blueskeletons.paa"};
	};
	class HiddenIsles_RidersJacket_patches: RidersJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_patches.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_patches.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_patches.paa"};
	};
	class HiddenIsles_RidersJacket_red: RidersJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_red.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_red.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_red.paa"};
	};
	class HiddenIsles_RidersJacket_white: RidersJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_white.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_white.paa","HiddenIsles_Retextures_Server\clothing\tops\ridersjacket\RidersJacket_white.paa"};
	};
	class HiddenIsles_Shirt_darkgrey: Shirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_darkgrey.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_darkgrey.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_darkgrey.paa"};
	};
	class HiddenIsles_Shirt_denimblue: Shirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimblue.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimblue.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimblue.paa"};
	};
	class HiddenIsles_Shirt_denimhawaii: Shirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimhawaii.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimhawaii.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_denimhawaii.paa"};
	};
	class HiddenIsles_Shirt_santahawaii: Shirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_santahawaii.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_santahawaii.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_santahawaii.paa"};
	};
	class HiddenIsles_Shirt_silver: Shirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_silver.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_silver.paa","HiddenIsles_Retextures_Server\clothing\tops\shirt\shirt_silver.paa"};
	};
	class HiddenIsles_Telnyashka_blackyellow: TelnyashkaShirt
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_blackyellow.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_blackyellow.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_blackyellow.paa"};
	};
	class HiddenIsles_Telnyashka_greyblack: TelnyashkaShirt
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_greyblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_greyblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_greyblack.paa"};
	};
	class HiddenIsles_Telnyashka_whiteblack: TelnyashkaShirt
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_whiteblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_whiteblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_whiteblack.paa"};
	};
	class HiddenIsles_Telnyashka_yellowblack: TelnyashkaShirt
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_yellowblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_yellowblack.paa","HiddenIsles_Retextures_Server\clothing\tops\telnyashka\telnyashka_yellowblack.paa"};
	};
	class HiddenIsles_BomberJacket_dragon: BomberJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_dragon.paa","HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_dragon.paa","HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_dragon.paa"};
	};
	class HiddenIsles_BomberJacket_flowers: BomberJacket_ColorBase
	{
		scope = 2;
		itemSize[] = {3,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_flowers.paa","HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_flowers.paa","HiddenIsles_Retextures_Server\clothing\tops\bomberjacket\bomberjacket_flowers.paa"};
	};
	class HiddenIsles_Sweater_GreenXMas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_greenxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_greenxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_greenxmas.paa"};
	};
	class HiddenIsles_Sweater_AussieXMas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas.paa"};
	};
	class HiddenIsles_Sweater_AussieXMas2: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas2.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas2.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas2.paa"};
	};
	class HiddenIsles_Sweater_AussieXMas3: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas3.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas3.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_aussiexmas3.paa"};
	};
	class HiddenIsles_Sweater_BlackCandyCanes: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_blackcandycanes.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_blackcandycanes.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_blackcandycanes.paa"};
	};
	class HiddenIsles_Sweater_CatXmas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_catxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_catxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_catxmas.paa"};
	};
	class HiddenIsles_Sweater_DinoXmas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_dinoxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_dinoxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_dinoxmas.paa"};
	};
	class HiddenIsles_Sweater_Grinch: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_grinch.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_grinch.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_grinch.paa"};
	};
	class HiddenIsles_Sweater_PlaidedXmas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_plaidedxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_plaidedxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_plaidedxmas.paa"};
	};
	class HiddenIsles_Sweater_PupperXmas: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas.paa"};
	};
	class HiddenIsles_Sweater_PupperXmas2: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas2.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas2.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_pupperxmas2.paa"};
	};
	class HiddenIsles_Sweater_Santa: Sweater_Gray
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_santa.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_santa.paa","HiddenIsles_Retextures_Server\clothing\tops\sweater\sweater_santa.paa"};
	};
	class HiddenIsles_TShirt_Santa: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_santa.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_santa.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_santa.paa"};
	};
	class HiddenIsles_TShirt_Black: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_black.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_black.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_black.paa"};
	};
	class HiddenIsles_TShirt_DarkRed: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_darkred.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_darkred.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_darkred.paa"};
	};
	class HiddenIsles_TShirt_White: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_white.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_white.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_white.paa"};
	};
	class HiddenIsles_TShirt_Grey: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_grey.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_grey.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_grey.paa"};
	};
	class HiddenIsles_TShirt_America: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_america.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_america.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_america.paa"};
	};
	class HiddenIsles_TShirt_AmericaGrey: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americagrey.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americagrey.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americagrey.paa"};
	};
	class HiddenIsles_TShirt_AmericaWhite: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americawhite.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americawhite.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_americawhite.paa"};
	};
	class HiddenIsles_TShirt_Anarchy: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_anarchy.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_anarchy.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_anarchy.paa"};
	};
	class HiddenIsles_TShirt_Skull: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_skull.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_skull.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_skull.paa"};
	};
	class HiddenIsles_TShirt_Sassy: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_sassy.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_sassy.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_sassy.paa"};
	};
	class HiddenIsles_TShirt_Butterflies: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_butterflies.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_butterflies.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_butterflies.paa"};
	};
	class HiddenIsles_TShirt_Slurp: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_slurp.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_slurp.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_slurp.paa"};
	};
	class HiddenIsles_TShirt_Ghost: TShirt_ColorBase
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_ghost.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_ghost.paa","HiddenIsles_Retextures_Server\clothing\tops\tshirt\tshirt_ghost.paa"};
	};
	class HiddenIsles_Suit_LightPink: ManSuit_LightGrey
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_lightpink.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_lightpink.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_lightpink.paa"};
	};
	class HiddenIsles_Suit_Green: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_green.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_green.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_green.paa"};
	};
	class HiddenIsles_Suit_DarkGrey: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_darkgrey.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_darkgrey.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_darkgrey.paa"};
	};
	class HiddenIsles_Suit_Red: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_red.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_red.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_red.paa"};
	};
	class HiddenIsles_Suit_Silver: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_silver.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_silver.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_silver.paa"};
	};
	class HiddenIsles_Suit_Pattern: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_pattern.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_pattern.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_pattern.paa"};
	};
	class HiddenIsles_Suit_WhiteBlackTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteblacktie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteblacktie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteblacktie.paa"};
	};
	class HiddenIsles_Suit_WhiteRedTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_whiteredtie.paa"};
	};
	class HiddenIsles_Suit_MrBean: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_mrbean.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_mrbean.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_mrbean.paa"};
	};
	class HiddenIsles_Suit_BrownRedTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownredtie.paa"};
	};
	class HiddenIsles_Suit_BrownBlackTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownblacktie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownblacktie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_brownblacktie.paa"};
	};
	class HiddenIsles_Suit_BlackRedTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackredtie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackredtie.paa"};
	};
	class HiddenIsles_Suit_BlackBlueTie: ManSuit_Blue
	{
		scope = 2;
		itemSize[] = {2,2};
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackbluetie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackbluetie.paa","HiddenIsles_Retextures_Server\clothing\tops\suits\man_suit_blackbluetie.paa"};
	};
	class HiddenIsles_TrackSuit_HalfCamo: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfcamo.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfcamo.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfcamo.paa"};
	};
	class HiddenIsles_TrackSuit_Camo: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_camo.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_camo.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_camo.paa"};
	};
	class HiddenIsles_TrackSuit_HalfPattern: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfpattern.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfpattern.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_halfpattern.paa"};
	};
	class HiddenIsles_TrackSuit_Black: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_black.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_black.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_black.paa"};
	};
	class HiddenIsles_TrackSuit_BlackGold: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_blackgold.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_blackgold.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_blackgold.paa"};
	};
	class HiddenIsles_TrackSuit_GreyBlack: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_greyblack.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_greyblack.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_greyblack.paa"};
	};
	class HiddenIsles_TrackSuit_WhiteBlack: TrackSuitJacket_Red
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_whiteblack.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_whiteblack.paa","HiddenIsles_Retextures_Server\clothing\tops\tracksuit\tracksuitjacket_whiteblack.paa"};
	};
};
