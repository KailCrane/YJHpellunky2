#include "yaInventory.h"
#include "yaGameHud.h"

namespace ya
{
	Inventory::Inventory()
		:bomb_amount(3),
		rope_amount(3)
	{

	}
	Inventory::~Inventory()
	{

	} 
	void Inventory::AddRope(int amount)
	{
		rope_amount += amount;
		hud->RefreshRope();
	}

	void Inventory::AddBomb(int amount)
	{
		bomb_amount += amount;
		hud->RefreshBomb();
	}


	void Inventory::AddItem(eItemType item_type)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == item_type)
			{
				//점수 추가
				return;
			}
		}
		list.insert({ 1,item_type });

	}
	void Inventory::DeletItem(eItemType item_type)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == item_type)
			{
				list.erase(i);
				return;
			}
		}
	}
	void Inventory::AddMoney(int amount)
	{
		money += amount;
		hud->ShowMoney();
		//hud->add();
	}
	void Inventory::SetUp(GameHud* _hud)
	{
		hud = _hud;
		hud->SetInventory(this);
		hud->RefreshBomb();
		hud->RefreshRope();
	}
	bool Inventory::FindItem(eItemType type)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == type)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		return false;
	}
}