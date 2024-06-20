class RadiationManager
{
    private static ref RadiationManager s_Instance;

    protected bool m_IsEnterRadiationZone;

    private const float RADIATION_SCALE_FACTOR = 0.01; // 10/1000 = 0.01

    private void RadiationManager()
    {
        m_IsEnterRadiationZone = false;
    }

    static RadiationManager Get()
    {
        if (!s_Instance)
        {
            s_Instance = new RadiationManager();
        }
        return s_Instance;
    }

    bool IsEnterRadiationZone()
    {
        return m_IsEnterRadiationZone;
    }

    void EnterRadiationZone(PlayerBase player, int radiationBackground)
    {
        m_IsEnterRadiationZone = true;

        int radiationIncreaseRate = radiationBackground * RADIATION_SCALE_FACTOR; 

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(IncreaseRadiation, 1000, true, player, radiationIncreaseRate);
    }

    void LeaveRadiationZone(PlayerBase player)
    {
        m_IsEnterRadiationZone = false;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(IncreaseRadiation);
    }

    void IncreaseRadiation(PlayerBase player, int radiationIncreaseRate)
    {
        player.AddRadiationExposure(radiationIncreaseRate);
    }
};
