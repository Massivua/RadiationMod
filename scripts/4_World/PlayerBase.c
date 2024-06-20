modded class PlayerBase extends ManBase
{
    private int m_RadiationExposure;
    private int m_RadiationStatLevel;
    private float m_TotalResistValue;
    private int m_CureValuePerSecond;
    private int m_Duration;
    private ref Timer m_RadiationStatTimer;
    private ref Timer m_Delay;
    private ref Timer m_RadiationCureTimer
    private const float RADIATION_RESIST_COEFFICIENT = 0.8; // 20% облучения при 100% защите

    void PlayerBase()
    {
        m_RadiationExposure = 0;
        m_RadiationStatLevel = 0;
        m_TotalResistValue = 0;
        m_CureValuePerSecond = 0;

    //    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateRadiationStat, 1000, true);

        m_RadiationStatTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_RadiationCureTimer = new Timer(CALL_CATEGORY_SYSTEM);
        m_Delay = new Timer(CALL_CATEGORY_SYSTEM);

        m_RadiationStatTimer.Run(10, this, "UpdateRadiationResist", null, false);
        m_Delay.Run(10, this, "UpdateRadiationStat", null, false);
    }

    override bool Consume(ItemBase source, float amount, EConsumeType consume_type)
    {
        if (super.Consume(source, amount, consume_type))
        {
            RadiationCureItemConfig config = RadiationCureManager.Get().GetCureItemConfig(source.GetType());
            if (config)
            {
                UseRadiationCureItem(config.ItemName, config.CureValuePerSecond, config.Duration);
            }
            return true;
        }
        return false;
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

        SendMessage("[Radiation] Облучение: " + m_RadiationExposure);
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

    void UseRadiationCureItem(string itemName, int cureValuePerSecond, int duration)
    {
        m_CureValuePerSecond = cureValuePerSecond;
        m_Duration = duration;

        CureRadiation();

        SendMessage("Вы использовали " + itemName + ". Ваша радиация будет уменьшена на " + cureValuePerSecond + " единиц в секунду в течение " + duration + " секунд.");
    }

    void CureRadiation()
    {
        m_RadiationCureTimer.Stop();

        if (m_Duration > 0)
        {
            DecreaseRadiationExposure(m_CureValuePerSecond);

            m_Duration -= 1;

            m_RadiationCureTimer.Run(1, this, "CureRadiation", null, false);
        }
        else
        {
            m_RadiationCureTimer.Stop();
            m_CureValuePerSecond = 0;
        }
    }

    void DecreaseRadiationExposure(int amount)
    {
        m_RadiationStatTimer.Stop();

        m_RadiationExposure -= amount;
        m_RadiationStatLevel = -amount;

        if (m_RadiationExposure < 0)
        {
            m_RadiationExposure = 0;
        }

        SendMessage("[Radiation] Облучение: " + m_RadiationExposure);

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
