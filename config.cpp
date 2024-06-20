class CfgPatches
{
    class RadiationMod
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class RadiationMod
    {
        dir = "RadiationMod";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "RadiationMod";
        credits = "YourName";
        author = "YourName";
        authorID = "0";
        version = "1.0";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {  
            class imageSets
			{
				files[]=
				{
					"RadiationMod/images/rad_gui.imageset"
				};
			};
            class missionScriptModule
            {
                value = "";
                files[] = {"RadiationMod/scripts/5_Mission",};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"RadiationMod/scripts/4_World"};
            };
            class gameScriptModule
            {
                value = "";
                files[] = {"RadiationMod/scripts/3_Game"};
            };
        };
    };
};
