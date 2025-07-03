////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.10
//https://mikero.bytex.digital/Downloads
//'now' is Thu Jul 03 08:32:56 2025 : 'file' last modified on Fri Feb 18 19:06:54 2022
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class ToxicZone_Script
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"TZDefine","DZ_Scripts"};
	};
};
class CfgMods
{
	class ToxicZone
	{
		dir = "ToxicZone";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ToxicZone";
		credits = "TheDmitri";
		author = "TheDmitri";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"ToxicZone/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"ToxicZone/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"ToxicZone/scripts/5_Mission"};
			};
		};
	};
};
