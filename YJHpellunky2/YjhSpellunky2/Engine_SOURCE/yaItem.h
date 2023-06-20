#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Item : public GameObject
	{
	public:

		Item();
		virtual ~Item();

	    virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//void SetItemType(eItemType type) { item_type = type; }
		

	private:

	};
}
