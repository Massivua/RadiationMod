modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        
        InitRadiationManager();
        InitResistManager(); 
        InitRadiationCureManager(); 

        InitRadiationMod();
    }
    
    static void InitRadiationMod()
    {
        RadiationMod.Get().RegisterTriggers();

        Print("[RadiationMod] Initialised");
    }

    static void InitRadiationManager()
    {
        RadiationManager.Get();

        Print("[RadiationManager] Initialised");
    }

    static void InitResistManager()
    {
        ResistManager.Get().LoadResistValues();

        Print("[ResistManager] Initialised");
    }

     static void InitRadiationCureManager()
    {
        RadiationCureManager.Get().LoadCureValues();

        Print("[RadiationCureManager] Initialised");
    }
}
