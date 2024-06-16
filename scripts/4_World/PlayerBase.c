modded class PlayerBase extends ManBase
{
    private int m_RadiationExposure;
    private int m_RadiationStatLevel;
    private ref Timer m_RadiationStatTimer;

    void PlayerBase()
    {
        m_RadiationExposure = 0;
        m_RadiationStatLevel = 0;

        UpdateRadiationStat();
        
    //    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateRadiationStat, 1000, true);

        m_RadiationStatTimer = new Timer(CALL_CATEGORY_SYSTEM);
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

        m_RadiationExposure += amount;
        m_RadiationStatLevel = amount;

        if (m_RadiationExposure > 1200)
        {
            m_RadiationExposure = 1200;
        }

        UpdateRadiationStat();

        SendMessage("[Radiation] Текущая радиация: " + m_RadiationExposure);
        SendMessage("[Radiation] Доза облучения: " + m_RadiationStatLevel);

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
