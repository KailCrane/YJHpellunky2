#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Rope : public GameObject
	{
	public:

		Rope();
		virtual ~Rope();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	};


}