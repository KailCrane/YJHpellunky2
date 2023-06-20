#include "yaWhipScript.h"
#include "yaAnimator.h"
#include "yaResources.h"


namespace ya
{
	WhipScript::WhipScript()
		:Script(),
		isCooldown(false)
	{
	}
	WhipScript::~WhipScript()
	{

	}
	void WhipScript::Initialize()
	{
		animator = GetOwner()->GetComponent<Animator>();
		SetAnimation();
	}

	void WhipScript::Update()
	{
	
		if (!this->GetOwner()->IsDead())
		{
			Vector3 player_pos = player_obj->GetComponent<Transform>()->GetPosition();
			Vector3 my_pos = Vector3(0, 0, 0);
			switch (sequence)
			{
			case First:
				if (direction == Left)
				{
					my_pos = Vector3(player_pos.x + 0.55f, player_pos.y + 0.4f, player_pos.z);
				}
				else
				{
					my_pos = Vector3(player_pos.x - 0.55f, player_pos.y + 0.4f, player_pos.z);
				}
				break;
			case Second:
				if (direction == Left)
				{
					my_pos = Vector3(player_pos.x - 0.5f, player_pos.y, player_pos.z);
				}
				else 
				{
					 my_pos = Vector3(player_pos.x + 0.5f, player_pos.y, player_pos.z);
				}
				break;
			case Third:
				if (direction == Left)
				{
					my_pos = Vector3(player_pos.x - 0.75f, player_pos.y - 0.25f, player_pos.z);
				}
				else
				{
					my_pos = Vector3(player_pos.x + 0.75f, player_pos.y - 0.25f, player_pos.z);
				}
				break;
			}
			
			this->GetOwner()->GetComponent<Transform>()->SetPosition(my_pos);
		}
	}
	void WhipScript::FixedUpdate()
	{

	}
	void WhipScript::Render()

	{
	}
	void WhipScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{         
		}
	}
	void WhipScript::OnCollisionStay(Collider2D* collider)
	{
		int a = 0;
	}
	void WhipScript::OnCollisionExit(Collider2D* collider)
	{
		int a = 0;

	}
	void WhipScript::OnTriggerEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Monster)
		{
			//collider->GetOwner()->GetComponent<Monster>()->GetBluntDamage();
		}
	}
	void WhipScript::SetAnimation()
	{
		animator = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> whip_texture_L = Resources::Load<Texture>(L"WhipL", L"char_yellowL.png");
		std::shared_ptr<Texture> whip_texture_R = Resources::Load<Texture>(L"WhipR", L"char_yellowR.png");

		//13번쨰줄 11번째 부터 6개인데  3 1 2
		

		animator->Create(L"WhipIdle", whip_texture_R, Vector2(1280.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false); animator->Create(L"WhipIdle", whip_texture_R, Vector2(1280.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"RightWhipFirstAnim", whip_texture_R, Vector2(1280.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, false);
		animator->Create(L"RightWhipSecondAnim", whip_texture_R, Vector2(1664.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"RightWhipThirdAnim", whip_texture_R, Vector2(1792.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 2, 0.05f, false);

		animator->Create(L"LeftWhipFirstAnim", whip_texture_L, Vector2(384, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, true);
		animator->Create(L"LeftWhipSecondAnim", whip_texture_L, Vector2(256.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, true);
		animator->Create(L"LeftWhipThirdAnim", whip_texture_L, Vector2(0.0f, 1526.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 2, 0.05f, true);

		animator->Play(L"WhipIdle", false);


		animator->GetCompleteEvent(L"LeftWhipFirstAnim") = std::bind(&WhipScript::WhipSecond, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"RightWhipFirstAnim") = std::bind(&WhipScript::WhipSecond, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"LeftWhipSecondAnim") = std::bind(&WhipScript::WhipThird, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"RightWhipSecondAnim") = std::bind(&WhipScript::WhipThird, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"LeftWhipThirdAnim") = std::bind(&WhipScript::WhipEnd, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"RightWhipThirdAnim") = std::bind(&WhipScript::WhipEnd, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
	}
	void WhipScript::Attack()
	{
		WhipFirst();
		isCooldown = true;
		//this->GetOwner()->GetComponent<Transform>()->SetPosition();
	}
	void WhipScript::WhipFirst()
	{
		Animator* anim = GetOwner()->GetComponent<Animator>();
		if(direction == Left)
		{
			anim->Play(L"LeftWhipFirstAnim", false);
		}
		else
		{
			anim->Play(L"RightWhipFirstAnim", false);
		}
		sequence = First;
		
		//this->GetOwner()->GetComponent<Transform>()->SetPosition();
	}
	void WhipScript::WhipSecond()
	{
		Animator* anim = GetOwner()->GetComponent<Animator>();
		if (direction == Left)
		{
			anim->Play(L"LeftWhipSecondAnim", false);
		}
		else
		{
			anim->Play(L"RightWhipSecondAnim", false);
		}
		sequence = Second;
		//this->GetOwner()->GetComponent<Transform>()->SetPosition();
	}
	void WhipScript::WhipThird()
	{
		Animator* anim = GetOwner()->GetComponent<Animator>();
		if (direction == Left)
		{
			anim->Play(L"LeftWhipThirdAnim", false);
		}
		else
		{
			anim->Play(L"RightWhipThirdAnim", false);
		}
		sequence = Third;
		//this->GetOwner()->GetComponent<Transform>()->SetPosition();
	}
	void WhipScript::WhipEnd()
	{
		isCooldown = false;
		sequence = Standby;
		this->GetOwner()->Death();
	}
}