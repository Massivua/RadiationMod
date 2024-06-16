class RadiationTriggerConfig
{
     string Name;
     vector Position;
     vector Size;
     int RadiationBackground;

     void RadiationTriggerConfig(string name, vector position, vector size, int radiationBackground)
     {
          Name = name;
          Position = position;
          Size = size;
          RadiationBackground = radiationBackground;
     }
}

class RadiationTrigger : ManTrigger
{
     string m_Name;
     int m_RadiationBackground;

     void SetTriggerName(string Name)
     {
          m_Name = Name;
     }

     void SetRadiationBackground(int radiationBackground)
     {
          m_RadiationBackground = radiationBackground;
     }

     override void OnEnter(Object obj)
     {
          super.OnEnter(obj);

          if (obj.IsInherited(PlayerBase))
          {
               PlayerBase player = PlayerBase.Cast(obj);
               
               string playername = player.GetIdentity().GetName();
               string steamid = player.GetIdentity().GetPlainId();
               string name = m_Name;

               Print("[RadiationMod] Игрок \"" + playername + "\" (steamid=" + steamid + ") вошел в: \"" + name + "\"");

               RadiationManager.Get().EnterRadiationZone(player, m_RadiationBackground);
          }
     }

     override void OnLeave(Object obj)
     {
          super.OnLeave(obj);
          if (obj.IsInherited(PlayerBase))
          {
                PlayerBase player = PlayerBase.Cast(obj);

               if (player)
               {
                    RadiationManager.Get().LeaveRadiationZone(player);

                    string playerName = player.GetIdentity().GetName();
                    string steamId = player.GetIdentity().GetPlainId();
                    string name = m_Name;

                    Print("[RadiationMod] Игрок \"" + playerName + "\" (steamid=" + steamId + ") покинул: \"" + name + "\"");
               }
               else
               {
                    Print("[RadiationMod] Игрок \"" + playerName + "\" (steamid=" + steamId + ") покинул: \"" + name + "\" (игрок отключился от сервера)");
               }
          }
     }
}
