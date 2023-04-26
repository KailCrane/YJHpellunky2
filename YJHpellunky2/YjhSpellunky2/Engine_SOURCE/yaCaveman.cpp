#include "yaCaveman.h"
#include "yaGravity.h"
#include "yaTime.h"

namespace ya
{
	Caveman::Caveman()
		:Script(),
		hp(3)
	{
	}

	Caveman::~Caveman()
	{

	}

	void Caveman::Initialize()
	{
	}

	void Caveman::Update()
	{
		if (feet != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			feet->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x, curr_pos.y - 0.4f, curr_pos.z));
		}
		if (head != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			head->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x, curr_pos.y + 0.4f, curr_pos.z));
		}
		if (left_body != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			left_body->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x - 0.2, curr_pos.y, curr_pos.z));
		}
		if (right_body != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			right_body->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x + 0.2, curr_pos.y, curr_pos.z));
		}
		if (left_detect_col != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			left_detect_col->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x + 0.2, curr_pos.y, curr_pos.z));
		}
		if (right_detect_col != nullptr)
		{
			Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			right_detect_col->GetComponent<Transform>()->SetPosition(Vector3(curr_pos.x + 0.2, curr_pos.y, curr_pos.z));
		}

	}

	void Caveman::FixedUpdate()
	{
	}

	void Caveman::Render()
	{
	}

	void Caveman::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Whip)
		{
			my_state = FlintState;
			GetBluntDamage();
			//if (collider->GetPosition().x > GetOwner()->GetComponent<Collider2D>()->GetPosition().x)
			//{
			//}
			//else
			//{
			//}
		}
		if (collider->GetOwner()->GetLayerType() == eLayerType::Bullet)
		{
			my_state = FlintState;
			GetBluntDamage();
		}
	}

	void Caveman::OnCollisionStay(Collider2D* collider)
	{
	}

	void Caveman::OnCollisionExit(Collider2D* collider)
	{
	}

	void Caveman::OnTriggerEnter(Collider2D* collider)
	{
	}

	void Caveman::Petrol()
	{

	}

	void Caveman::Chase()
	{
	}

	void Caveman::Stumble()
	{
	}

	void Caveman::Die()
	{

	}

	void Caveman::GetBluntDamage()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"CavemanDead", false); //나중에 FLint로 바꿔줄것

		hp-=1;
		{
			if (hp <= 0)
			{
				my_state = DieState;
				animator->Play(L"CavemanDead",false);
			}
		}
	}

	void Caveman::RecoverFlint()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		flint_recover_timer += Time::DeltaTime();
		if (flint_recover_timer >= flint_recover_time)
		{
			my_state = IdleState;
			animator->Play(L"CavemanIdle",false);
		}
	}

	void Caveman::ReciveColEnter(eLayerType receive_layer, Collider2D* col)
	{
		if (receive_layer == eLayerType::MonsterFeet && col->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			Gravity* gravity = GetOwner()->GetComponent<Gravity>();
			gravity->GravityOff();
		}
		if (receive_layer == eLayerType::MonsterHead && col->GetOwner()->GetLayerType() == eLayerType::Feet)
		{
			//my_state = FlintState;
			//GetBluntDamage();
		}
	}

	void Caveman::ReciveColStay(eLayerType receive_layer, Collider2D* col)
	{
		
	}
	void Caveman::ReciveColExit(eLayerType receive_layer, Collider2D* col)
	{
		if (receive_layer == eLayerType::MonsterFeet && col->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			Gravity* gravity = GetOwner()->GetComponent<Gravity>();
			gravity->GravityOn();
		}
	}


}