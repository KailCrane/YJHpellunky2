#pragma once
#include "yaGameObject.h"

namespace ya
{
	class TitleMenuSelect : public GameObject
	{
	public:
		TitleMenuSelect();
		virtual ~TitleMenuSelect();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetLeftSpear(GameObject* object) { left_spear = object; };;
		void SetRightSpear(GameObject* object) { right_spear = object; }

		void SetMaxSize(int size) { max_size = size; }

		void MenuUp();
		void MenuDown();


		void SpearForward();
		void SpearBackward();

		int Select() { return menu_num; }

		enum SpearState
		{
			Standby,
			Forward,
			Backward,
			Complete
		};
		SpearState spearState;
		
	private:
		//MenuSelect
		int menu_num;
		
		int max_size;

		//Spear
		GameObject* left_spear;
		GameObject* right_spear;

		Vector3 curr_left_pos ;
		Vector3 curr_right_pos;

		Vector3 fixed_left_pos ;
		Vector3 fixed_right_pos;

		float init_pos_x;

		bool isComplete;

		float move_speed;
	};
}