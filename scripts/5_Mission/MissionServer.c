modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        InitRadiationMod();
        InitRadiationManager();
        InitResistManager();  
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
}
