#pragma once
#include "yaGameObject.h"

namespace ya
{

	class Dispenser : public GameObject
	{
	public:
		Dispenser();
		virtual ~Dispenser();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Fire();
		void Ditection();	
	private:



	};
}
