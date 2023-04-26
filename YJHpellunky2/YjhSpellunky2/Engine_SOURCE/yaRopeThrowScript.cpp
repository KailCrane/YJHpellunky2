#include "yaRopeThrowScript.h"
#include "yaRopeScript.h"

namespace ya
{
	RopeThrowScript::RopeThrowScript()
		:Script()
	{
	}
	RopeThrowScript::~RopeThrowScript()
	{
	}
	void RopeThrowScript::Initialize()
	{
	}
	void RopeThrowScript::Update()
	{
	}
	void RopeThrowScript::FixedUpdate()
	{
	}
	void RopeThrowScript::Render()
	{
	}
	void RopeThrowScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void RopeThrowScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void RopeThrowScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void RopeThrowScript::OnTriggerEnter(Collider2D* collider)
	{
	}


	void RopeThrowScript::Throw(Vector3 pos)
	{
		//만약에 첫 배치면

		Vector3 fixed_pos = Vector3(pos.x, pos.y + 6.0f, pos.z);
		int allot_num = 0;

		for (int i = 0; i < 100; i++)
		{
			int a = 0;
			if (allot_num >= 7)
			{
				continue;
			}
			if (rope_dummy[i]->IsDead())
			{
				if (allot_num == 0)
				{
					RopeScript* rope_script = rope_dummy[i]->GetScript<RopeScript>();
					rope_script->state = rope_script->Start;
					rope_dummy[i]->Alive();
					rope_dummy[i]->GetComponent<Transform>()->SetPosition(pos);
					rope_dummy[i]->GetScript<RopeScript>()->Throw(fixed_pos);
				}
				else if (allot_num == 1)
				{
					RopeScript* rope_script = rope_dummy[i]->GetScript<RopeScript>();
					rope_script->state = rope_script->End;
					RopeScript* prev_script = prev_allot->GetScript<RopeScript>();
					prev_script->SetNext(rope_dummy[i]);
					rope_script->SetPrev(prev_allot);

				}
				else
				{
					RopeScript* rope_script = rope_dummy[i]->GetScript<RopeScript>();
					rope_script->state = rope_script->Middle;
					RopeScript* prev_script = prev_allot->GetScript<RopeScript>();
					prev_script->SetNext(rope_dummy[i]);
					rope_script->SetPrev(prev_allot);

				}
				prev_allot = rope_dummy[i];

				allot_num += 1;
				//rope_dummy[i]->GetScript<RopeScript>()->SetNext();
			}
		
		}
	}
};
