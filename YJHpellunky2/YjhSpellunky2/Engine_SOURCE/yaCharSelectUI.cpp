#include "yaCharSelectUI.h"
#include "yaTime.h"

namespace ya
{


	CharSelectUI::CharSelectUI()
		:come_down_dist(4.0f),
		come_down_speed(8.0f),
		scroll_spread_dist(3.0f),
		door_move_dist(2.0f),
		door_move_speed(4.0f),
		uiState(Standby)
	{
	}

	CharSelectUI::~CharSelectUI()
	{
	}

	void CharSelectUI::Initialize()
	{
	}

	void CharSelectUI::Update()
	{
		switch (uiState)
		{
		case ya::CharSelectUI::DownTo:
			ComeDownTo();
			break;
		case ya::CharSelectUI::UnFold:
			UnfoldScroll();
			break;
		case ya::CharSelectUI::DoorUpTo:
			StoneDoorUpTo();
			break;
		case ya::CharSelectUI::DoorDownTo:
			break;
		case ya::CharSelectUI::Fold:
			break;
		case ya::CharSelectUI::UpTo:
			break;
		}


	}

	void CharSelectUI::FixedUpdate()
	{
	}

	void CharSelectUI::Render()
	{
	}

	void CharSelectUI::ComeDownTo()
	{
		Vector3 curr_upboard_pos = up_board->GetComponent<Transform>()->GetPosition();
		up_board->GetComponent<Transform>()->SetPosition(Vector3(curr_upboard_pos.x,
			curr_upboard_pos.y - come_down_speed * Time::DeltaTime(),
			curr_upboard_pos.z));

		Vector3 curr_scroll_L_pos = left_scroll->GetComponent<Transform>()->GetPosition();
		left_scroll->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_L_pos.x,
			curr_scroll_L_pos.y - come_down_speed * Time::DeltaTime(),
			curr_scroll_L_pos.z));
		Vector3 curr_scroll_R_pos = right_scroll->GetComponent<Transform>()->GetPosition();
		right_scroll->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_R_pos.x,
			curr_scroll_R_pos.y - come_down_speed * Time::DeltaTime(),
			curr_scroll_R_pos.z));
		Vector3 curr_scroll_middle_pos = middle_scroll->GetComponent<Transform>()->GetPosition();
		middle_scroll ->GetComponent<Transform>()->SetPosition(Vector3(curr_scroll_middle_pos.x,
			curr_scroll_middle_pos.y - come_down_speed * Time::DeltaTime(),
			curr_scroll_middle_pos.z));

		Vector3 curr_downboard_pos = down_board->GetComponent<Transform>()->GetPosition();
		down_board->GetComponent<Transform>()->SetPosition(Vector3(curr_downboard_pos.x,
			curr_downboard_pos.y + come_down_speed * Time::DeltaTime(),
			curr_downboard_pos.z));

		added_dist += come_down_speed * Time::DeltaTime();

		if(added_dist >= come_down_dist)
		{
			added_dist = 0;
			uiState = UnFold;
		}
	}
	
	void CharSelectUI::UnfoldScroll()
	{
		Vector3 scroll_L_curr_pos = left_scroll->GetComponent<Transform>()->GetPosition();
		left_scroll->GetComponent<Transform>()->SetPosition(Vector3(scroll_L_curr_pos.x - 8 * Time::DeltaTime(),
			scroll_L_curr_pos.y,
			scroll_L_curr_pos.z));

		Vector3 scrollMiddl_curr_scale = middle_scroll->GetComponent<Transform>()->GetScale();
		middle_scroll->GetComponent<Transform>()->SetScale(Vector3(scrollMiddl_curr_scale.x + 16 * Time::DeltaTime(),
																   scrollMiddl_curr_scale.y,
																   scrollMiddl_curr_scale.z));

		Vector3 scroll_R_curr_pos = right_scroll->GetComponent<Transform>()->GetPosition();
		right_scroll->GetComponent<Transform>()->SetPosition(Vector3(scroll_R_curr_pos.x + 8 * Time::DeltaTime(),
																	 scroll_R_curr_pos.y,
																	 scroll_R_curr_pos.z));
		 
		added_dist += 8 * Time::DeltaTime();

		if (added_dist >= scroll_spread_dist)
		{
			uiState = SlotSelect;
			added_dist = 0.0f;
		}
	}

	void CharSelectUI::StoneDoorUpTo()
	{
		Vector3 door_curr_pos = stone_door->GetComponent<Transform>()->GetPosition();
		stone_door->GetComponent<Transform>()->SetPosition(Vector3(door_curr_pos.x,
																   door_curr_pos.y + door_move_speed * Time::DeltaTime(),
																   door_curr_pos.z));


		Vector3 z_button_pos = z_button->GetComponent<Transform>()->GetPosition();
		z_button->GetComponent<Transform>()->SetPosition(Vector3(z_button_pos.x,
																 z_button_pos.y + door_move_speed * Time::DeltaTime(),
																 z_button_pos.z));
		





		added_dist += door_move_speed * Time::DeltaTime();

		if (added_dist >= door_move_dist)
		{
			added_dist = 0.0f;
			uiState = Standby;
		}
	}
}