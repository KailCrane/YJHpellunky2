#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Arrow : public GameObject
	{
	public:

		Arrow();
		virtual ~Arrow();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void InitPostionSet(Vector3 pos) { init_pos = pos; }
		bool GetCompleteState() { return isComplete; }

		void RepeatOn() { isRepeat = true; }
		void RepeatOff() { isRepeat = false; }

		void SetDirectLeft() { direct = Direct(Left); }
		void SetDirectRight() { direct = Direct(Right); }

		void MoveActive() { isActive = true; }
		void MoveUnActive() { isActive = false; }

		void SetMoveSpeed(float _speed) { move_speed = _speed; }
		void SetMoveDist(float _dist) { move_dist = _dist; }


		void Move();
		void Select();



	private:

		bool isRepeat;
		bool isComplete;
		bool isActive;

		Vector3 init_pos;

		float move_dist;
		float move_speed;
		
		enum Direct
		{
			None,
			Left,
			Right
		};

		Direct direct;
	};
}

