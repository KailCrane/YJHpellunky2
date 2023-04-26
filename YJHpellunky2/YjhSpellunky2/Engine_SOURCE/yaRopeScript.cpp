#include "yaRopeScript.h"
#include "yaTime.h"
#include "yaAnimator.h"

namespace ya
{
	RopeScript::RopeScript()
		:Script()
	{
	}

	RopeScript::~RopeScript()
	{
	}

	void RopeScript::Initialize()
	{

	}

	void RopeScript::Update()
	{
		if (isThrow)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			
			if (state == Start)
			{
				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				Vector3 curr_pos = tr->GetPosition();
				Vector3 fixed_pos = Vector3(curr_pos.x, curr_pos.y += 10 * Time::DeltaTime(), curr_pos.z);
				tr->SetPosition(fixed_pos);

				animator->Play(L"RopeTop",false);

				float a = fixed_pos.y;
				float b = start_pos.y;

				if (a - b > 0)
				{
					animator->Play(L"RopeTopUnfold", false);
					next_chain->Alive();
					next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					next_chain->GetScript<RopeScript>()->isThrow = true;
					isThrow = false;
				}
			}
			if (state == End)
			{
				Transform* tr = this->GetOwner()->GetComponent<Transform>();
				Vector3 curr_pos = tr->GetPosition();
				Vector3 fixed_pos = Vector3(curr_pos.x, curr_pos.y -= 10 * Time::DeltaTime(), curr_pos.z);
				tr->SetPosition(fixed_pos);

				float prev_pos = prev_chain->GetScript<RopeScript>()->start_pos.y;
				float distance = curr_pos.y -prev_pos;
				animator->Play(L"RopeRoll", false);

				if (distance <= -1.0f)
				{
					if (next_chain->IsDead())
					{
						next_chain->Alive();
						next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					}
				}
				if (distance <= -2.0f)
				{
					if (next_chain->GetScript<RopeScript>()->next_chain->IsDead())
					{
						next_chain->GetScript<RopeScript>()->next_chain->Alive();
						next_chain->GetScript<RopeScript>()->next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					}
				}if (distance <= -3.0f)
				{
					if (next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->IsDead())
					{
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->Alive();
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					}
				}
				if (distance <= -4.0f)
				{
					if (next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->IsDead())
					{
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->Alive();
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					}
				}
				if (distance <= -5.0f)
				{
					if (next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->IsDead())
					{
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->Alive();
						next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetScript<RopeScript>()->next_chain->GetComponent<Transform>()->SetPosition(fixed_pos);
					}
				}
				if (distance <=  -6.0f)
				{
					animator->Play(L"RopeEnd", false);
					isThrow = false;
				}
			}
		}
	}

	void RopeScript::FixedUpdate()
	{
	}

	void RopeScript::Render()
	{
	}

	void RopeScript::OnCollisionEnter(Collider2D* collider)
	{

	}

	void RopeScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void RopeScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void RopeScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void RopeScript::Throw(Vector3 pos)
	{
		start_pos = pos;
		isThrow = true;
	}
}