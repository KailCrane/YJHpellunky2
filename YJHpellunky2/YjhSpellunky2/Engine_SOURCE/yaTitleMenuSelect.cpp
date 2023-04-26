#include "yaTitleMenuSelect.h"
#include "yaTime.h"

namespace ya
{
	TitleMenuSelect::TitleMenuSelect()
		:init_pos_x(0),
		move_speed(20.0f)
	{

	}
	TitleMenuSelect::~TitleMenuSelect()
	{

	}
	void TitleMenuSelect::Initialize()
	{
		GameObject::Initialize();
	}
	void TitleMenuSelect::Update()
	{
		GameObject::Update();
		switch (spearState)
		{
		case ya::TitleMenuSelect::Forward:
			SpearForward();
			break;
		case ya::TitleMenuSelect::Backward:
			SpearBackward();
			break;
		}
	}
	void TitleMenuSelect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void TitleMenuSelect::Render()
	{
		GameObject::Render();
	}
	void TitleMenuSelect::MenuUp()
	{
		if (menu_num <= 0)
		{
			return;
		}
		menu_num--;
		spearState = Backward;
	}
	void TitleMenuSelect::MenuDown()
	{
		if (menu_num >= max_size)
		{
			return;
		}
		menu_num++;
		spearState = Backward;
	}

	void TitleMenuSelect::SpearForward()
	{
	float changed_y = 0.0f;

	switch (menu_num)
	{
	case 0:
		changed_y = 2.0f;
		break;
	case 1:
		changed_y = 1.0f;
		break;
	case 2:
		changed_y = 0.0f;
		break;
	case 3:
		changed_y = -1.0f;
		break;
	}

		curr_left_pos = left_spear->GetComponent<Transform>()->GetPosition();
		curr_right_pos = right_spear->GetComponent<Transform>()->GetPosition();

		fixed_left_pos = Vector3(curr_left_pos.x += move_speed * Time::DeltaTime(), changed_y, curr_left_pos.z);
		fixed_right_pos = Vector3(curr_right_pos.x -= move_speed * Time::DeltaTime(), changed_y, curr_right_pos.z);


		left_spear->GetComponent<Transform>()->SetPosition(fixed_left_pos);
		right_spear->GetComponent<Transform>()->SetPosition(fixed_right_pos);

		if (left_spear->GetComponent<Transform>()->GetPosition().x >= -1.5f)
		{
			spearState = Standby;
			isComplete = true;
			return;
		}
	}

	void TitleMenuSelect::SpearBackward()
	{
	
		curr_left_pos = left_spear->GetComponent<Transform>()->GetPosition();
		curr_right_pos = right_spear->GetComponent<Transform>()->GetPosition();

		fixed_left_pos = Vector3(curr_left_pos.x -= move_speed * Time::DeltaTime(), curr_left_pos.y, curr_left_pos.z);
		fixed_right_pos = Vector3(curr_right_pos.x += move_speed * Time::DeltaTime(), curr_right_pos.y, curr_right_pos.z);

		left_spear->GetComponent<Transform>()->SetPosition(fixed_left_pos);
		right_spear->GetComponent<Transform>()->SetPosition(fixed_right_pos);
		
		if (left_spear->GetComponent<Transform>()->GetPosition().x <= -4.0f)
		{
			spearState = Forward;
			return;
		}

	}
}