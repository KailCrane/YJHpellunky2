#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Door : public GameObject
	{
	public:
		
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void SetCenter() {};

	private:
		Vector3 teleport_pos;
		Vector3 center;
		
	};
}