#include "yaUIDisk.h"
#include "yaTime.h"

namespace ya
{
	UIDisk::UIDisk()
		: left_disk(nullptr),
		right_disk(nullptr),
		turn_speed(1.0f),
		move_speed(2.0f),
		move_dist(4.0f),
		isActive(false),
		isComplete(false),
		init_left_pos(0.0f, 0.0f, 0.0f),
		init_right_pos(0.0f, 0.0f, 0.0f),
		diskState(Standby)
	{

	}

	UIDisk::~UIDisk()
	{

	}

	void UIDisk::Initialize()
	{
		GameObject::Initialize();
	}				

	void UIDisk::Update()
	{
		GameObject::Update();

		switch (diskState)
		{
		case ya::UIDisk::Standby:
			break;
		case ya::UIDisk::Turn:
			DiskTurn();
			break;
		case ya::UIDisk::Move:
			DiskMove();
			break;
		case ya::UIDisk::Complete:
			break;
		}
	}

	void UIDisk::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UIDisk::Render()
	{
		GameObject::Render();
	}

	void UIDisk::DiskTurn()
	{
		Vector3 curr_left_rot = left_disk->GetComponent<Transform>()->GetRotation();
		Vector3 fixed_left_rot = Vector3(curr_left_rot.x, curr_left_rot.y, curr_left_rot.z += turn_speed * Time::DeltaTime());
		left_disk->GetComponent<Transform>()->SetRotation(fixed_left_rot);

		Vector3 curr_right_rot = right_disk->GetComponent<Transform>()->GetRotation();;
		Vector3 fixed_right_rot = Vector3(curr_right_rot.x, curr_right_rot.y, curr_right_rot.z += turn_speed * Time::DeltaTime());
		right_disk->GetComponent<Transform>()->SetRotation(fixed_right_rot);

		Vector3 curr_head_rot = stone_head->GetComponent<Transform>()->GetRotation();;
		Vector3 fixed_head_rot = Vector3(curr_head_rot.x, curr_head_rot.y, curr_head_rot.z -= turn_speed * Time::DeltaTime());
		stone_head->GetComponent<Transform>()->SetRotation(fixed_head_rot);

		if (curr_left_rot.z >= 3.15f)
		{
			init_left_pos = left_disk->GetComponent<Transform>()->GetPosition();
			init_right_pos = right_disk->GetComponent<Transform>()->GetPosition();
			diskState = Move;
		}
	}

	void UIDisk::DiskMove()
	{
		Vector3 curr_left_pos = left_disk->GetComponent<Transform>()->GetPosition();
		left_disk->GetComponent<Transform>()->SetPosition(Vector3(curr_left_pos.x + move_speed * Time::DeltaTime(),
			curr_left_pos.y,
			curr_left_pos.z));

		Vector3 right_curr_pos = right_disk->GetComponent<Transform>()->GetPosition();
		right_disk->GetComponent<Transform>()->SetPosition(Vector3(right_curr_pos.x - move_speed * Time::DeltaTime(),
			right_curr_pos.y,
			right_curr_pos.z));

		if ((curr_left_pos.x - init_left_pos.x) >= move_dist)
		{
			diskState = Complete;
			//init_pos = stone_head_obj->GetComponent<Transform>()->GetPosition();
		}
	}
}