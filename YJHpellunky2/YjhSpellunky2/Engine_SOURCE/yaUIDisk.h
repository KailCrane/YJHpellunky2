#pragma once

#include"yaGameObject.h"

namespace ya
{
	class UIDisk : public GameObject
	{
	public:

		UIDisk();
		virtual ~UIDisk();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		
		void SetActive() { diskState = Turn; }

		void DiskTurn();
		void DiskMove();

		void SetLeftObject(GameObject* obj) { left_disk = obj; }
		void SetRightObject(GameObject* obj) { right_disk = obj; }
		void SetHeadObject(GameObject* obj) { stone_head = obj; }
		
		bool GetCompleteState() { return isComplete; }
		
		bool GetIsComplete() {
			if (diskState == Complete)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


	private:
		GameObject* left_disk;
		GameObject* right_disk;
		GameObject* stone_head;

		float turn_speed;
		float move_speed;

		bool isActive;
		bool isComplete;

		Vector3 init_left_pos;
		Vector3 init_right_pos;

		float move_dist;


		enum DiskState
		{
			Standby,
			Turn,
			Move,
			Complete
		};
		DiskState diskState;
	};

}
