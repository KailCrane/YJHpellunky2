#pragma once

#include "yaGameObject.h"

namespace ya
{
	class CharSelectUI : public GameObject
	{
	public:

		CharSelectUI();
		virtual ~CharSelectUI();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void ComeDownTo();
		void UnfoldScroll();

		void StoneDoorUpTo();

		void SetUpBoard(GameObject* object) { up_board = object; }
		void SetDownBoard(GameObject* object) { down_board = object; }
		void SetLeftScroll(GameObject* object) { left_scroll = object; }
		void SetMiddleScroll(GameObject* object) { middle_scroll = object; }
		void SetRightScroll(GameObject* object) { right_scroll = object; }
		void SetStoneDoor(GameObject* object) { stone_door = object; }
		void DoorMove() {uiState = DoorUpTo; }
		void SetZButton(GameObject* object) { z_button = object; };


		bool IsStandBy() {
			if (uiState == Standby)
			{
				return true;
			}
			else
			{
				return false;
			}
			;
		}

		bool IsSlotSelect() {
			if (uiState == SlotSelect)
			{
				return true;
			}
			else
			{
				return false;
			}
			;
		}

		void Action() { uiState =DownTo ; }

	

	private:

		GameObject* up_board;
		GameObject* down_board;

		GameObject* left_scroll;
		GameObject* middle_scroll;
		GameObject* right_scroll;

		GameObject* stone_door;
		GameObject* z_button;

		float come_down_speed;
		float come_down_dist;

		float added_dist;
		float scroll_spread_dist;

		float door_move_speed;
		float door_move_dist;

		enum UIState
		{
			DownTo,
			UnFold,
			SlotSelect,
			DoorUpTo,
			DoorDownTo,
			Standby,
			Fold,
			UpTo
		};
		UIState uiState;

		
	};
}

