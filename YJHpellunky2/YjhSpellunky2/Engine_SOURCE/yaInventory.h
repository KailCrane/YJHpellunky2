#pragma once
#include "yaItem.h"
#include "yaScript.h"

namespace ya
{
	class Gamehud;
	class Inventory : public Script
	{
	public:
		Inventory();
		virtual ~Inventory();

		void AddRope(int amount);
		void AddBomb(int amount);
		void AddItem(eItemType item_type);
		void DeletItem(eItemType item_type);
		void AddMoney(int amount);
		int GetMoney() { return money; }
		int GetBomb() { return bomb_amount; }
		int GetRope() { return bomb_amount; }
		void RemoveMoney(int amount) { money -= amount; }
		void SetUp(GameHud* _hud);
		bool FindItem(eItemType type);
		void Reset() { list.clear(); }

		std::map<int, eItemType> GetList() { return list; }

	private:

		int bomb_amount;
		int rope_amount;
		int money;
		GameHud* hud;
		std::map<int, eItemType> list;
	};
}