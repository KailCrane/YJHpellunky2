#pragma once
#include "yaGameObject.h"

namespace ya
{

	class RopeThrow : public GameObject
	{
	public:
		RopeThrow();
		~RopeThrow();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	private:

	};
}