#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Bomb : public GameObject
	{
	public:

		Bomb();
		virtual ~Bomb();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void Throw();
		void Explode();

		void Ignition();


	private:

		enum Direction
		{
			LeftUp,
			Left,
			LeftDown,
			
			RightUp,
			Right,
			RightDown,
			Down
		};
		Direction direction;
	};
}
