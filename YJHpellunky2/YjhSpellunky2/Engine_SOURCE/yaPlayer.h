#pragma once
#include "yaGameObject.h"


namespace ya
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetLife(int num) { life = num; }
		int GetLife(int num) { return life; }


	private:
		int life;

	};
}

