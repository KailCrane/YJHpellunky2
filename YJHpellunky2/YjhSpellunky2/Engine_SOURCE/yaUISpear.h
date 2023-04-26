#pragma once

#include "yaGameObject.h"

namespace ya
{
	class UISpear : public GameObject
	{
	public:

		UISpear();
		virtual ~UISpear();


		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetLeftSpear();
		void SetRightSpear();
		void Move();
		
		bool GetIsComplete() { return isComplete; }

	private:
		GameObject* left_spear;
		GameObject* right_spear;
		
		float init_pos_x;
		float move_dist;

		enum State
		{
			Standby,
			Forward,
			Backward,
			Complete
		};
		State state;
		
		bool isInit;
		bool isComplete;
		
		float move_speed;

	};
}
