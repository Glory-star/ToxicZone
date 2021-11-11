#ifndef GASMASKADDON
modded class GP5GasMask
{
	static float 			m_WorkingTimePerPills=60;

	void GP5GasMask()
	{

	}

	void ~GP5GasMask()
	{
		PlayerBase player;
		Class.CastTo(player, GetHierarchyRootPlayer());
		if( player )
		{
			MutePlayer(player,false);
		}
	}

	override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;

		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}

		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			MutePlayer(player,false);
			GetCompEM().SwitchOff();
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		//Print("OnWasAttached");

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			MutePlayer(player,true);
			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void MutePlayer(PlayerBase player, bool state)
	{
		if( GetGame() )
		{
			if (( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().GetPlayer() == player ))
			{
				GetGame().SetVoiceEffect(player, VoiceEffectObstruction, state);
			}
		}
	}

	override bool IsObstructingVoice()
	{
		return true;
	}

	//----------------Filter PART--------------------//

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		if (att && att.IsFullQuantity())
			return false;

		return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		//Print(slot_name);
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			if(m_filter.GetQuantity() >= 1)
			{
				m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
				//Print("CanStartGasMask: GP5GasMask :"+m_filter.GetQuantity().ToString());
			}
		}
	}

	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();

	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{
			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());

			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());
			//Print("OnWork GP5: EnergyUsage :"+GetCompEM().GetEnergyUsage().ToString());
			//Print("OnWork GP5: UpdateInterval :"+GetCompEM().GetUpdateInterval().ToString());

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{
				//Print("OnWork : player is dead");
				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
	}

	void ConsumeFilter()
	{
		GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
				GetCompEM().SwitchOff();
				return;
			}
			//Print("ConsumeFilter : m_gasmaskfilter");
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}

	GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return GP5GasMask_Filter.Cast(GetAttachmentByType(GP5GasMask_Filter));
	}

};

modded class GasMask extends GP5GasMask
{
	static float 			m_WorkingTimePerPills=60;

	void GasMask()
	{

	}

	void ~GasMask()
	{
		PlayerBase player;
		Class.CastTo(player, GetHierarchyRootPlayer());
		if( player )
		{
			MutePlayer(player,false);
		}
	}

	override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;

		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}

		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			MutePlayer(player,false);
			GetCompEM().SwitchOff();
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		//Print("OnWasAttached");

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			MutePlayer(player,true);
			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void MutePlayer(PlayerBase player, bool state)
	{
		if( GetGame() )
		{
			if (( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().GetPlayer() == player ))
			{
				GetGame().SetVoiceEffect(player, VoiceEffectObstruction, state);
			}
		}
	}

	override bool IsObstructingVoice()
	{
		return true;
	}

	//----------------Filter PART--------------------//

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		if (att && att.IsFullQuantity())
			return false;

		return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		//Print(slot_name);
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			if(m_filter.GetQuantity() >= 1)
			{
				m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
				//Print("CanStartGasMask: GP5GasMask :"+m_filter.GetQuantity().ToString());
			}
		}
	}

	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();

	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{
			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());

			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());
			//Print("OnWork GP5: EnergyUsage :"+GetCompEM().GetEnergyUsage().ToString());
			//Print("OnWork GP5: UpdateInterval :"+GetCompEM().GetUpdateInterval().ToString());

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{
				//Print("OnWork : player is dead");
				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
	}

	void ConsumeFilter()
	{
		GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
				GetCompEM().SwitchOff();
				return;
			}
			//Print("ConsumeFilter : m_gasmaskfilter");
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}

	GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return GP5GasMask_Filter.Cast(GetAttachmentByType(GP5GasMask_Filter));
	}

};

modded class AirborneMask extends GP5GasMask
{
	static float 			m_WorkingTimePerPills=60;

	void AirborneMask()
	{

	}

	void ~AirborneMask()
	{
		PlayerBase player;
		Class.CastTo(player, GetHierarchyRootPlayer());
		if( player )
		{
			MutePlayer(player,false);
		}
	}

	override bool CanPutAsAttachment( EntityAI parent )
	{
		if(!super.CanPutAsAttachment(parent)) {return false;}
		bool headgear_present = false;

		if ( parent.FindAttachmentBySlotName( "Headgear" ) )
		{
			headgear_present = parent.FindAttachmentBySlotName( "Headgear" ).ConfigGetBool( "noMask" );
		}

		if ( ( GetNumberOfItems() == 0 || !parent || parent.IsMan() ) && !headgear_present )
		{
			return true;
		}
		return false;
	}

	override void OnWasDetached(EntityAI parent, int slot_id)
	{
		super.OnWasDetached(parent,slot_id);

		PlayerBase player = PlayerBase.Cast(parent);

		if ( player )
		{
			MutePlayer(player,false);
			GetCompEM().SwitchOff();
		}
	}

	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent,slot_id);

		//Print("OnWasAttached");

		PlayerBase player;
		Class.CastTo(player, parent.GetHierarchyRootPlayer());

		if ( player && slot_id == InventorySlots.MASK )
		{
			MutePlayer(player,true);
			EntityAI m_item = this.FindAttachmentBySlotName("GasMaskFilter");
			if( m_item )
			{
				CanStartGasMask(m_item, "GasMaskFilter");
			}
		}
	}

	override void MutePlayer(PlayerBase player, bool state)
	{
		if( GetGame() )
		{
			if (( GetGame().IsServer() && GetGame().IsMultiplayer() ) || ( GetGame().GetPlayer() == player ))
			{
				GetGame().SetVoiceEffect(player, VoiceEffectObstruction, state);
			}
		}
	}

	override bool IsObstructingVoice()
	{
		return true;
	}

	//----------------Filter PART--------------------//

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		if (att && att.IsFullQuantity())
			return false;

		return true;
	}

	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached( item, slot_name );
		//Print(slot_name);
		CanStartGasMask(item,slot_name);
	}

	void CanStartGasMask(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			ItemBase m_filter = ItemBase.Cast(item);
			if(m_filter.GetQuantity() >= 1)
			{
				m_filter.AddQuantity(-1);
				GetCompEM().AddEnergy(m_WorkingTimePerPills);
				GetCompEM().SwitchOn();
				//Print("CanStartGasMask: GP5GasMask :"+m_filter.GetQuantity().ToString());
			}
		}
	}

	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();

	}

	override void OnWork ( float consumed_energy )
	{
		if ( GetGame().IsServer() )
		{
			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());

			//Print("OnWork GP5: Energy :"+GetCompEM().GetEnergy().ToString());
			//Print("OnWork GP5: EnergyUsage :"+GetCompEM().GetEnergyUsage().ToString());
			//Print("OnWork GP5: UpdateInterval :"+GetCompEM().GetUpdateInterval().ToString());

			ConsumeFilter();

			PlayerBase player;
			Class.CastTo(player, GetHierarchyRootPlayer());

			if(player && !player.IsAlive())
			{
				//Print("OnWork : player is dead");
				GetCompEM().SwitchOff();
				return;
			}
		}
	}

	override void OnWorkStart()
	{

	}

	override void OnWorkStop()
	{
		super.OnWorkStop();
	}

	void ConsumeFilter()
	{
		GP5GasMask_Filter m_gasmaskfilter = GetGP5GasMaskFilter();

		if (m_gasmaskfilter)
		{
			if(m_gasmaskfilter.GetQuantity() == 0)
			{
				GetCompEM().AddEnergy(-1*GetCompEM().GetEnergy());
				GetCompEM().SwitchOff();
				return;
			}
			//Print("ConsumeFilter : m_gasmaskfilter");
			m_gasmaskfilter.AddQuantity(-1);
			GetCompEM().AddEnergy(m_WorkingTimePerPills);
		}
	}

	GP5GasMask_Filter GetGP5GasMaskFilter()
	{
		return GP5GasMask_Filter.Cast(GetAttachmentByType(GP5GasMask_Filter));
	}

};
#else
modded class GP5GasMask
{
	override void OnWorkStop()
	{
		super.OnWorkStop();
	}
}

modded class AirborneMask extends GP5GasMask
{
	override void OnWorkStop()
	{
		super.OnWorkStop();
	}
}

modded class GasMask extends GP5GasMask
{
	override void OnWorkStop()
	{
		super.OnWorkStop();
	}
}
#endif
