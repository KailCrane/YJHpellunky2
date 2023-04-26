#include "yaArrow.h"
#include "yaTime.h"
namespace ya
{


	Arrow::Arrow()
		:isActive(false),
		isComplete(false),
		direct(Direct(None)),
		isRepeat(false),
		move_dist(0.0f)
	{

	}

	Arrow::~Arrow()
	{
	}

	void Arrow::Initalize()
	{
		GameObject::Initialize();
	}

	void Arrow::Update()
	{
		GameObject::Update();

		if (isActive)
		{
			Move();
		}
	}

	void Arrow::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Arrow::Render()
	{
		GameObject::Render();
	}

	void Arrow::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 curr_pos = tr->GetPosition();
		Vector3 fixed_pos;


		switch (direct)
		{
		case ya::Arrow::None:
			return;
			break;
		case ya::Arrow::Left:
			if (init_pos.x - curr_pos.x <= move_dist)
			{
				fixed_pos = Vector3(curr_pos.x - move_speed * Time::DeltaTime(), curr_pos.y, curr_pos.z);
				tr->SetPosition(fixed_pos);
			}
			else
			{
				if (isRepeat)
				{
					tr->SetPosition(init_pos);
				}
				else
				{
					isComplete = true;
				}
			}
			break;
		case ya::Arrow::Right:
			if (curr_pos.x - init_pos.x<= move_dist)
			{
				fixed_pos = Vector3(curr_pos.x + move_speed * Time::DeltaTime(), curr_pos.y, curr_pos.z);
				tr->SetPosition(fixed_pos);
			}
			else
			{
				if (isRepeat)
				{
					tr->SetPosition(init_pos);
				}
				else
				{
					isComplete = true;
				}
			}
			break;
		}
	}

	void Arrow::Select()
	{
	}

}