#pragma once
#include "yaGameObject.h"
#include "yaShotGunScript.h"

namespace ya
{

	class Shotgun : public GameObject
	{
	public:

		Shotgun();
		virtual ~Shotgun();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}

