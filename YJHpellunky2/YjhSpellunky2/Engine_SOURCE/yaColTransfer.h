#pragma once
#include "yaGameObject.h"

namespace ya
{
	class ColTransfer : public GameObject
	{
	public:
		ColTransfer();
		virtual ~ColTransfer();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	private:

	};
}

