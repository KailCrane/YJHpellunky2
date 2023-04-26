#include "yaUIStatue.h"
#include "yaTime.h"

namespace ya
{
	UIStatue::UIStatue()
		:move_speed(4.0f),
		move_dist(6.0f),
		isActive(false),
		isComplete(false)
	{

	}
	UIStatue::~UIStatue()
	{
	}
	void UIStatue::Initialize()
	{
		GameObject::Initialize();
	}
	void UIStatue::Update()
	{
		GameObject::Update();
		if (isActive)
		{
			Move();
		}
	}
	void UIStatue::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void UIStatue::Render()
	{
		GameObject::Render();
	}

	void UIStatue::Move()
	{
		Vector3 curr_head_pos = head->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_head_pos = Vector3(curr_head_pos.x, curr_head_pos.y -= move_speed * Time::DeltaTime(), curr_head_pos.z);
		head->GetComponent<Transform>()->SetPosition(fixed_head_pos);
		
		Vector3 curr_body_pos = body->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_body_pos = Vector3(curr_body_pos.x, curr_body_pos.y -= move_speed * Time::DeltaTime(), curr_body_pos.z);
		body->GetComponent<Transform>()->SetPosition(fixed_body_pos);

		if (init_pos.y - curr_head_pos.y >= move_dist)
		{
			isComplete = true;
			isActive = false;
		}

	}
}