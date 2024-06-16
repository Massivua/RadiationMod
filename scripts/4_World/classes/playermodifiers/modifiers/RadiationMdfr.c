class RadiationMdfr : ModifierBase
{
    static const int RADIATION_EXPOSURE_THRESHOLD_ACTIVATE = 50; // Порог активации радиации
    static const int RADIATION_EXPOSURE_THRESHOLD_DEACTIVATE = 20; // Порог деактивации радиации

    override void Init()
    {
        m_TrackActivatedTime = false;
        m_ID = tModifiers.MDF_RADIATION;
        m_TickIntervalInactive = 10; // Интервал для неактивного состояния (в секундах)
        m_TickIntervalActive = 30;   // Интервал для активного состояния (в секундах)
        DisableDeactivateCheck();
    }
    
    override protected bool ActivateCondition(PlayerBase player)
    {
        if (player.GetRadiationExposure() >= RADIATION_EXPOSURE_THRESHOLD_ACTIVATE)
        {
            return true;
        }
        return false;
    }

    override protected void OnActivate(PlayerBase player)
    {
        Print(player.GetIdentity().GetName() + " RadiationModifier OnActivate");
    }

    override protected bool DeactivateCondition(PlayerBase player)
    {
        if (player.GetRadiationExposure() <= RADIATION_EXPOSURE_THRESHOLD_DEACTIVATE)
        {
            return true;
        }
        return false;
    }

    override protected void OnDeactivate(PlayerBase player)
    {
        Print(player.GetIdentity().GetName() + " RadiationModifier OnDeactivate");
    }

    override protected void OnTick(PlayerBase player, float deltaT)
    {
        
    }
};
