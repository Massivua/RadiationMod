modded class JMESPModule
{
    override void RegisterTypes(out TTypenameArray types)
	{
		types.Insert(JMESPViewTypeTrigger);

          types.Insert( JMESPViewTypePlayer );
		types.Insert( JMESPViewTypePlayerAI );
		types.Insert( JMESPViewTypeInfected );
		types.Insert( JMESPViewTypeAnimal );

		types.Insert( JMESPViewTypeCar );
		
		types.Insert( JMESPViewTypeBoltActionRifle );
		types.Insert( JMESPViewTypeBoltRifle );
		types.Insert( JMESPViewTypeRifle );
		types.Insert( JMESPViewTypePistol );

		types.Insert( JMESPViewTypeTent );
		types.Insert( JMESPViewTypeBaseBuilding );
		types.Insert( JMESPViewTypeFood );
		types.Insert( JMESPViewTypeExplosive );
		types.Insert( JMESPViewTypeBook );
		types.Insert( JMESPViewTypeContainer );
		types.Insert( JMESPViewTypeTransmitter );
		types.Insert( JMESPViewTypeClothing );
		types.Insert( JMESPViewTypeMagazine );
		types.Insert( JMESPViewTypeAmmo );
		types.Insert( JMESPViewTypeUnknown );
		types.Insert( JMESPViewTypeImmovable );
	}
}