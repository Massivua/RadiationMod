modded class MissionServer
{
    static ref RadiationMod g_gRadiationMod;

    override void OnInit()
    {
        super.OnInit();
        InitRadiationMod();
        InitRadiationManager();
    }

    static void InitRadiationMod()
    {
        g_gRadiationMod = new RadiationMod();
        g_gRadiationMod.RegisterTriggers();

        Print("[RadiationMod] Initialised");
    }

    static void InitRadiationManager()
    {
        RadiationManager.Get();

        Print("[RadiationManager] Initialised");
    }
}
