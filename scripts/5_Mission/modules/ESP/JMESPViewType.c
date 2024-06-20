class JMESPViewTypeTrigger: JMESPViewType
{
	void JMESPViewTypeTrigger()
	{
		Permission = "Trigger";
		Localisation = "Trigger";

		Colour = ARGB( 255, 250, 105, 218 );
	}

	override bool IsValid(Object obj, out JMESPMeta meta)
	{
		#ifdef JM_COT_ESP_DEBUG
		#ifdef COT_DEBUGLOGS
		Print("+JMESPViewTypeImmovable::IsValid( obj = " + Object.GetDebugName( obj ) + ", out ) bool;");
		#endif
		#endif

		Trigger trg;
		if(Class.CastTo(trg, obj))
		{
			return false;
		}

          if (obj.IsKindOf("RadiationTrigger"))
          {
			return true;
		}
          
          ManTrigger mtrg;
          if(Class.CastTo(mtrg, obj))
		{
			return false;
		}
				
		CreateMeta(meta);
		
		meta.target = obj;
		meta.colour = Colour;
		meta.type = this;

	//	obj.GetNetworkID(meta.networkLow, meta.networkHigh);
		
		meta.name = obj.GetDisplayName();
	//	if (meta.name == "")
	//	{
	//		meta.name = obj.GetType();
	//	}
		return true;
	}
}