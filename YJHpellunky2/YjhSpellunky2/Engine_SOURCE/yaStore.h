#pragma once
#include "yaMerchant.h"
#include "yaScript.h"
#include "yaInventory.h"
#include "yaItem.h"

namespace ya
{
	class Store
	{
	public:

		void Buy();
		void Stole();
		void SetMerchant();

	private:

		std::vector<Item> sell_item_list;
	};
	enum class eStoreType
	{
		WeaponeStore,
		ToolStore,
	};
}

