#pragma once
#include "..\Engine_SOURCE\yaGameObject.h"


namespace ya
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;

	private:
		GameObject* test;
	};
}
