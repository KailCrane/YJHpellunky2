#include "yaRigidbody.h"
#include "yaTime.h"


namespace ya
{
	Rigidbody::Rigidbody()
		:Component(eComponentType::Gravity),
		velocity(0.0f),
		max_velocity(10.0f),
		acc(0.0f),
		isGravity(true)
	{

	}
	Rigidbody::~Rigidbody()
	{

	}
	void Rigidbody::Initialize()
	{

	}

	void Rigidbody::Update()
	{
		if (isGravity)
		{
			if (!isKnockback)
			{
				Gravity();
			}
		}

		if (isKnockback)
		{
			Knockback();
		}
	}

	void Rigidbody::FixedUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
	void Rigidbody::Gravity()
	{
		if (!this->GetOwner()->IsDead())
		{
			acc = max_velocity / 0.3;

			if (velocity <= max_velocity)
			{
				velocity += acc * Time::DeltaTime();
			}

			Vector3 curr_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();
			Vector3 fixed_pos = Vector3(curr_pos.x, curr_pos.y -= max_velocity * Time::DeltaTime(), curr_pos.z);
			this->GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		}
	}
	void Rigidbody::AddForce(Vector2 direction)
	{
		//0.2초만에 최대 속도 도달 마지막 위치에서 0.2

		Vector3 curr_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(curr_pos.x += direction.x * Time::DeltaTime(), curr_pos.y += (direction.y + max_velocity) * Time::DeltaTime(), curr_pos.z);
		this->GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
	}
	void Rigidbody::KnockbackOff()
	{
		isKnockback = false;
	}
	void Rigidbody::KnockbackOn(Vector2 _power)
	{
		knockback_power = _power;
		isKnockback = true;
	}
	void Rigidbody::Knockback()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 curr_pos = tr->GetPosition();
		Vector3 fixed_pos = Vector3(curr_pos.x + knockback_power.x * Time::DeltaTime(),
			curr_pos.y + knockback_power.y * Time::DeltaTime(),
			curr_pos.z);
		tr->SetPosition(fixed_pos);
		knockback_power.y -= 9 * Time::DeltaTime(); //후에 처음 받은 y로 나워줄것
		if (knockback_power.y <= 0)
		{
			KnockbackOff();
		}
	}
}