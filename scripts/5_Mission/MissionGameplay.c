modded class MissionGameplay extends MissionBase
{
    	ref Widget m_RadiationPanel;

	void MissionGameplay()
    	{
		GetRPCManager().AddRPC("RadiationMod", "RadRPc", this, SingleplayerExecutionType.Both);
    	}

	void RadRPc(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    	{
        	Param2<int, int> data;
        	if (!ctx.Read(data))
          {
        		return;
		}

        	int radiationExposure = data.param1;
        	int radiationStatLevel = data.param2;

        	if (type == CallType.Client)
        	{
           	UpdateRadiationPanel(radiationExposure, radiationStatLevel);
        	}
    	}

	override void OnInit()
    	{
		if ( m_Initialized )
		{
			return;
		}
			
		PPEffects.Init();
		
		m_UIManager = GetGame().GetUIManager();
			
		m_Initialized = true;

		if (!m_HudRootWidget)
		{
			m_HudRootWidget = GetGame().GetWorkspace().CreateWidgets("RadiationMod/scripts/5_Mission/gui/radiation_day_z_hud.layout");
			
			m_HudRootWidget.Show(false);

			m_RadiationPanel = m_HudRootWidget.FindAnyWidget("Radiation");
			
			m_Chat.Init(m_HudRootWidget.FindAnyWidget("ChatFrameWidget"));
			
			m_ActionMenu.Init( m_HudRootWidget.FindAnyWidget("ActionsPanel"), TextWidget.Cast( m_HudRootWidget.FindAnyWidget("DefaultActionWidget") ) );
			
			m_Hud.Init(m_HudRootWidget.FindAnyWidget("HudPanel"));
			
			m_MicrophoneIcon = ImageWidget.Cast( m_HudRootWidget.FindAnyWidget("mic") );
			m_MicrophoneIcon.Show(false);
			
			m_VoiceLevels = m_HudRootWidget.FindAnyWidget("VoiceLevelsPanel");
			m_VoiceLevelsWidgets = new map<int, ImageWidget>;
			m_VoiceLevelTimers = new map<int,ref WidgetFadeTimer>; 
		
			if( m_VoiceLevels )
			{
				m_VoiceLevelsWidgets.Set(VoiceLevelWhisper, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Whisper") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelTalk, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Talk") ));
				m_VoiceLevelsWidgets.Set(VoiceLevelShout, ImageWidget.Cast( m_VoiceLevels.FindAnyWidget("Shout") ));
				
				m_VoiceLevelTimers.Set(VoiceLevelWhisper, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelTalk, new WidgetFadeTimer);
				m_VoiceLevelTimers.Set(VoiceLevelShout, new WidgetFadeTimer);
			}
			
			HideVoiceLevelWidgets();
			
			m_ChatChannelArea = m_HudRootWidget.FindAnyWidget("ChatChannelPanel");
			m_ChatChannelText = TextWidget.Cast( m_HudRootWidget.FindAnyWidget("ChatChannelText") );
		}
		
		if ( GetGame().IsDebug() )
		{
			m_HudDebug = new HudDebug;
			
			if ( !m_HudDebug.IsInitialized() )
			{
				m_HudDebug.Init( GetGame().GetWorkspace().CreateWidgets("gui/layouts/debug/day_z_hud_debug.layout") );
				
				PluginConfigDebugProfile.GetInstance().SetLogsEnabled(LogManager.IsLogsEnable());
			}
		}
		
		if( GetGame().IsMultiplayer() )
		{
			OnlineServices.m_MuteUpdateAsyncInvoker.Insert(SendMuteListToServer);
		}
	}

    	void UpdateRadiationPanel(int radiationExposure, int radiationStatLevel)
	{
    		Widget arrowUp1 = m_RadiationPanel.FindAnyWidget("RadiationArrowUp1");
    		Widget arrowUp2 = m_RadiationPanel.FindAnyWidget("RadiationArrowUp2");
    		Widget arrowUp3 = m_RadiationPanel.FindAnyWidget("RadiationArrowUp3");

    		Widget arrowDown1 = m_RadiationPanel.FindAnyWidget("RadiationArrowDown1");
    		Widget arrowDown2 = m_RadiationPanel.FindAnyWidget("RadiationArrowDown2");
    		Widget arrowDown3 = m_RadiationPanel.FindAnyWidget("RadiationArrowDown3");

		Widget icon0 = m_RadiationPanel.FindAnyWidget("IconRadiation_0");
    		Widget icon1 = m_RadiationPanel.FindAnyWidget("IconRadiation_1");
    		Widget icon2 = m_RadiationPanel.FindAnyWidget("IconRadiation_2");
		Widget icon3 = m_RadiationPanel.FindAnyWidget("IconRadiation_3");
		Widget icon4 = m_RadiationPanel.FindAnyWidget("IconRadiation_4");

		if (radiationExposure == 0)
		{
			StopBlinkingRadiationIcon();
			float alpha0 = icon0.GetAlpha();
			icon0.SetColor(ARGB(alpha0 * 100, 220, 220, 220));
			icon0.Show(true);
			icon1.Show(false);
			icon2.Show(false);
			icon3.Show(false);
			icon4.Show(false);
		}
		if (radiationExposure >= 250)
		{
			StopBlinkingRadiationIcon();
			float alpha1 = icon1.GetAlpha();
			icon1.SetColor(ARGB(alpha1 * 255, 220, 220, 0));
			icon0.Show(false);
			icon1.Show(true);
			icon2.Show(false);
			icon3.Show(false);
			icon4.Show(false);
		}
		if (radiationExposure >= 500)
		{
			StopBlinkingRadiationIcon();
			float alpha2 = icon2.GetAlpha();
			icon2.SetColor(ARGB(alpha2 * 255, 220, 220, 0));
			icon0.Show(false);
			icon1.Show(false);
			icon2.Show(true);
			icon3.Show(false);
			icon4.Show(false);
		}
		if (radiationExposure >= 750)
		{
			StopBlinkingRadiationIcon();
			float alpha3 = icon3.GetAlpha();
			icon3.SetColor(ARGB(alpha3 * 255, 220, 0, 0));
			icon0.Show(false);
			icon1.Show(false);
			icon2.Show(false);
			icon3.Show(true);
			icon4.Show(false);
		}
		if (radiationExposure >= 1000)
		{
			float alpha4 = icon4.GetAlpha();
			icon4.SetColor(ARGB(alpha4 * 255, 220, 0, 0));
			icon0.Show(false);
			icon1.Show(false);
			icon2.Show(false);
			icon3.Show(false);
			icon4.Show(true);
			StartBlinkingRadiationIcon(icon4);
		}

    		if (radiationStatLevel == 0)
    		{
        		arrowUp1.Show(false);
        		arrowUp2.Show(false);
        		arrowUp3.Show(false);

        		arrowDown1.Show(false);
        		arrowDown2.Show(false);
        		arrowDown3.Show(false);
    		}
    		else if (radiationStatLevel > 0)
    		{
        		arrowUp1.Show(radiationStatLevel >= 3);
        		arrowUp2.Show(radiationStatLevel >= 5);
        		arrowUp3.Show(radiationStatLevel >= 7);

        		arrowDown1.Show(false);
        		arrowDown2.Show(false);
        		arrowDown3.Show(false);
    		}
    		else if (radiationStatLevel < 0)
    		{
        		arrowUp1.Show(false);
        		arrowUp2.Show(false);
        		arrowUp3.Show(false);

        		arrowDown1.Show(radiationStatLevel <= -1);
        		arrowDown2.Show(radiationStatLevel <= -3);
        		arrowDown3.Show(radiationStatLevel <= -5);
    		}
	}

	void StartBlinkingRadiationIcon(Widget icon)
	{
    		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ToggleRadiationIconVisibility, 300, true, new Param1<Widget>(icon));
	}

	void ToggleRadiationIconVisibility(Param param)
	{
    		Param1<Widget> p = Param1<Widget>.Cast(param);
    		Widget icon = p.param1;

    		if (icon)
    		{
       		icon.Show(!icon.IsVisible());
    		}
	}

	void StopBlinkingRadiationIcon()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(ToggleRadiationIconVisibility);
	}
}
