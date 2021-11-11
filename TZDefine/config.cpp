class CfgPatches
{
	class TZDefine
	{
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class TZDefine
	{
		dir="TZDefine";
        name="TZ";
        type="mod";
	    dependencies[]={ "GameLib", "Game", "World", "Mission"};
	    class defs
	    {
			
			class gameLibScriptModule
			{
				value = "";
				files[] = {
					"TZDefine/scripts/Common"
					};
			};
			class gameScriptModule
            {
				value = "";
                files[]={
					"TZDefine/scripts/Common"
					};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"TZDefine/scripts/Common"
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"TZDefine/scripts/Common"
				};
            };
        };
    };
};