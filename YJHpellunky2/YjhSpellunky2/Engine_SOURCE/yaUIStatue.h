#pragma once
#include "yaGameObject.h"

namespace ya
{

	class UIStatue : public GameObject
	{
	public:
		UIStatue();
		virtual ~UIStatue();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetBodyObject(GameObject* obj) { body = obj; }
		void SetHeadObject(GameObject* obj) { head = obj; }

		void SetActive() { isActive = true; }

		void InitPositionSet(Vector3 pos) { init_pos = pos; }

		bool GetIsComplete() { return isComplete; }
	
	private:
		void Move();

		GameObject* head;
		GameObject* body;

		Vector3 init_pos;

		float move_speed;
		float move_dist;

		bool isActive;
		bool isComplete;
	};
}