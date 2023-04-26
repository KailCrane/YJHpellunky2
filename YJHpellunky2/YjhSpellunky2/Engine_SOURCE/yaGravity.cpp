#include "yaGravity.h"
#include "yaTime.h"


namespace ya
{
	Gravity::Gravity()
		:Component(eComponentType::Gravity),
		velocity(0.0f),
		max_velocity(10.0f),
		acc(0.0f),
		isGravity(true)
	{

	}
	Gravity::~Gravity()
	{

	}
	void Gravity::Initialize()
	{

	}

	void Gravity::Update()
	{
		if (isGravity)
		{
			if (!this->GetOwner()->IsDead())
			{
				acc = max_velocity / 0.3;

				if (velocity <= max_velocity)
				{
					velocity += acc * Time::DeltaTime();
				}	 

				Vector3 curr_pos =  this->GetOwner()->GetComponent<Transform>()->GetPosition();
				Vector3 fixed_pos = Vector3(curr_pos.x, curr_pos.y -= max_velocity * Time::DeltaTime(), curr_pos.z);
				this->GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
			}
		}
	}

	void Gravity::FixedUpdate()
	{
	}
	void Gravity::Render()
	{
	}
	void Gravity::AddForce(Vector2 direction)
	{
		//0.2초만에 최대 속도 도달 마지막 위치에서 0.2

		Vector3 curr_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(curr_pos.x += direction.x * Time::DeltaTime(), curr_pos.y += (direction.y + max_velocity)*Time::DeltaTime(), curr_pos.z);
		this->GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
	}
}