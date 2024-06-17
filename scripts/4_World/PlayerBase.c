modded class PlayerBase extends ManBase
{
    private int m_RadiationExposure;
    private int m_RadiationStatLevel;
    private float m_TotalResistValue;
    private ref Timer m_RadiationStatTimer;
    private ref Timer m_Delay;
    private const float RADIATION_RESIST_COEFFICIENT = 0.8; // 20% облучения при 100% защите

    void PlayerBase()
    {
        m_RadiationExposure = 0;
        m_RadiationStatLevel = 0;

        UpdateRadiationStat();

    //    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateRadiationStat, 1000, true);

        m_RadiationStatTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_Delay = new Timer(CALL_CATEGORY_SYSTEM);
        m_RadiationStatTimer.Run(5, this, "UpdateRadiationResist", null, false);
    }

    void UpdateRadiationResist()
    {
        m_TotalResistValue = ResistManager.Get().GetTotalResistValue(this);
    }

    void UpdateRadiationStat()
    {
        GetRPCManager().SendRPC("RadiationMod", "RadRPc", new Param2<int, int>(m_RadiationExposure, m_RadiationStatLevel), true);
    }

    void ResetRadiationStatLevel()
    {
        m_RadiationStatLevel = 0;
        UpdateRadiationStat();
    }

    int GetRadiationResist()
    {
        return m_TotalResistValue;
    }

    int GetRadiationExposure()
    {
        return m_RadiationExposure;
    }

    int GetRadiationStatLevel()
    {
        return m_RadiationStatLevel;
    }

     void AddRadiationExposure(int amount)
    {
        m_RadiationStatTimer.Stop();

        m_TotalResistValue = Math.Round(ResistManager.Get().GetTotalResistValue(this));

        int resist = Math.Round(amount * RADIATION_RESIST_COEFFICIENT * (m_TotalResistValue / 100.0));

        int adjustedAmount = amount - resist;

        m_RadiationExposure += adjustedAmount;
        m_RadiationStatLevel = adjustedAmount;

        if (m_RadiationExposure > 1200)
        {
            m_RadiationExposure = 1200;
        }

        UpdateRadiationStat();

        SendMessage("[Radiation] Реальная радиация: " + amount);
        SendMessage("[Radiation] Радиация с защитой: " + m_RadiationStatLevel);
        SendMessage("[Radiation] Защита от радиации: " + m_TotalResistValue);
        SendMessage("[Radiation] resist: " + resist);

        m_RadiationStatTimer.Run(5, this, "ResetRadiationStatLevel", null, false);
    }

    void SendMessage(string message)
    {
        if (GetIdentity())
        {
            GetGame().RPCSingleParam(this, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>(message), true, GetIdentity());
        }
    }

    void DecreaseRadiationExposure(int amount)
    {
        m_RadiationStatTimer.Stop();

        m_RadiationExposure -= amount;
        m_RadiationStatLevel = amount;

        if (m_RadiationExposure < 0)
        {
            m_RadiationExposure = 0;
        }

        UpdateRadiationStat();

        m_RadiationStatTimer.Run(5, this, "ResetRadiationStatLevel", null, false);
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_RadiationExposure);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
        {
            return false;
        }

        if (!ctx.Read(m_RadiationExposure))
        {
            return false;
        }

        return true;
    }
}
