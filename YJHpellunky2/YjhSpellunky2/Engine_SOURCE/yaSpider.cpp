#include "yaSpider.h"
#include "yaTime.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaDetector.h"

namespace ya
{
	Spider::Spider()
		:jump_speed_x(0.0f),
		jump_speed_y(0.0f)
	{
	}
	Spider::~Spider()
	{
	}
	void Spider::Initialize()
	{
		GetScene();
		tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
		tr->SetScale(Vector3::One);
		SetName(L"Spider");

		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpiderMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();
		SetAnimation();

#pragma region "Detector"
		detector = object::Instantiate<GameObject>(eLayerType::Detector ,scene);
		Transform* detector_tr = detector->GetComponent<Transform>();
		detector_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		detector_tr->SetScale(Vector3::One);
		Detector* detectorScript = detector->AddComponent<Detector>();
		Collider2D* col = detector->AddComponent<Collider2D>();
		col->SetName(L"DetectorCollider");
		detectorScript->SetSender(this);
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.5f, 4.0f));
		col->SetCenter(Vector2(0.0f, -2.0f));
#pragma endregion

#pragma region "Head"
		head = object::Instantiate<GameObject>(eLayerType::MonsterHead, scene);
		head->SetLayerType(eLayerType::MonsterHead);
		head->SetName(L"MonsterHead");
		Transform* head_tr = head->GetComponent<Transform>();
		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x, owner_pos.y + 0.2f, owner_pos.z);
		head_tr->SetPosition(fixed_pos);
		head_tr->SetScale(Vector3::One);
		Detector* headScript = head->AddComponent<Detector>();
		headScript->SetSender(this);
		Collider2D* head_col = head->AddComponent<Collider2D>();
		head_col->SetName(L"MonsterHeadCollider");
		head_col->SetType(eColliderType::Rect);
		head_col->SetSize(Vector2(0.3f, 0.2f));
#pragma endregion

#pragma region "Body"
		body = object::Instantiate<GameObject>(eLayerType::MonsterBody, scene);
		body->SetLayerType(eLayerType::MonsterBody);
		body->SetName(L"MonsterBody");
		Transform* body_tr = body->GetComponent<Transform>();
		body_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		body_tr->SetScale(Vector3(1.0f,1.0f,1.0f));
		Detector* bodyScript = body->AddComponent<Detector>();
		bodyScript->SetSender(this);
		Collider2D* body_col = body->AddComponent<Collider2D>();
		body_col->SetName(L"MonsterBodyCollider");
		body_col->SetType(eColliderType::Rect);
		body_col->SetSize(Vector2(0.4, 0.4));
#pragma endregion

	}
	void Spider::Update()
	{
		Transform* detector_tr = detector->GetComponent<Transform>();
		detector_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		if (isDrop)
		{
			Drop();
		}
		if (isJump)
		{
			JumpToPlayer();
		}
	}
	void Spider::FixedUpdate()
	{
		Transform* head_tr = head->GetComponent<Transform>();
		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x, owner_pos.y + 0.2f, owner_pos.z);
		head_tr->SetPosition(fixed_pos);


		Transform* body_tr = body->GetComponent<Transform>();
		body_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

	}
	void Spider::Render()
	{

	}

	void Spider::Drop()
	{
		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x, owner_pos.y -= Time::DeltaTime() * 4, owner_pos.z);
		GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
	}

	void Spider::Jump()
	{
		isJump = true;

		if (target == nullptr)
		{
			std::vector<GameObject*> curr_scene_GameObject = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Player);
			target = curr_scene_GameObject[0];
		}

		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 target_pos = target->GetComponent<Transform>()->GetPosition();
		
		
		jump_speed_y = 4.0f;

		if (target_pos.x <= owner_pos.x)
		{
			jump_speed_x = -2.0f;
		}
		else
		{
			jump_speed_x = 2.0f;
		}
		animator->Play(L"JumpComplete");
	}

	void Spider::ChaseTarget()
	{
		
	}
	void Spider::ReadyToJump()
	{
		if (jump_before_count == 0)
		{
			animator->Play(L"Flinch1",false);
			//첫번쨰 애니메이션재생
		}
		if (jump_before_count == 1)
		{
			animator->Play(L"Flinch2", false);
			//첫번쨰 애니메이션재생
		}
		if (jump_before_count == 2)
		{
			animator->Play(L"Flinch1", false);
			//첫번쨰 애니메이션재생
		}
		if (jump_before_count == 3)
		{
			animator->Play(L"Jump", false);
			//첫번쨰 애니메이션재생
		}
		jump_before_count++;
	}
	void Spider::JumpToPlayer()
	{
		if (jump_speed_y <= -4)
		{
			jump_speed_y = -4;
		}
		else
		{
			jump_speed_y -= Time::DeltaTime() * 4;
		}

		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x += jump_speed_x * Time::DeltaTime()
									, owner_pos.y += jump_speed_y * Time::DeltaTime()
									, owner_pos.z);

		GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
	}

	void Spider::RenderSet()
	{
		
	}


	void Spider::OnCollisionEnter(Collider2D* collider)
	{

	}
	void Spider::OnCollisionStay(Collider2D* collider)
	{

	}
	void Spider::OnCollisionExit(Collider2D* collider)
	{
		
	}

	void Spider::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"DetectorCollider")
		{
			if (col->GetName() ==
				L"PlayerCollider" ||
				L"PlayerHeadCollider" ||
				L"PlayerBodyCollider")
			{
				detector->Death();
				isDrop = true;
				animator->Play(L"Drop", false);
				StateChange(Chase);
				//드랍
				//상태를 쫓음으로 바꿔준다
			}
		}

		if (sender->GetName() == L"MonsterBodyCollider")
		{
			int a = 0;
			if (col->GetName() == L"GroundCollider")
			{
				if (isDrop)
				{
					isDrop = false;
					ReadyToJump();
					//점프 이전 대기 애니메이션 출력
				}

				if (isJump)
				{
					jump_before_count = 0;
					ReadyToJump();
					isJump = false;
				}
			}
		}

		if (sender->GetName() == L"MonsterHeadCollider")
		{
			if (col->GetName() == L"FeetCollider")
			{
				//플레이어가 거미를 잡았음 추가
				//이펙트 피 재생
				//찰팍 사운드 재생
				head->Death();
				body->Death();
				GetOwner()->Death();
			}
		}
	}
	void Spider::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{
		
	}
	void Spider::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
		//if (my_state == Standby)
		//{
		//	if (sender->GetName() == L"MonsterHeadCollider")
		//	{
		//		if (col->GetName() == L"CeilingCollider")
		//		{
		//			
		//			//추락
		//		}
		//	}
		//}
	}
	void Spider::SetAnimation()
	{

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Spider", L"Monster//monstersbasic01R.png");

		animator->Create(L"Idle", texture, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, false);
		animator->Create(L"Drop", texture, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 5, 0.1f, false);
		animator->Create(L"Flinch1", texture, Vector2(128.0f * 3, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.1f, true);
		animator->Create(L"Flinch2", texture, Vector2(128.0f * 0, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.1f, false);
		animator->Create(L"Jump", texture, Vector2(128.0f * 0, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.1f, false);
		animator->Create(L"JumpComplete", texture, Vector2(128.0f * 7, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, false);
		animator->GetCompleteEvent(L"Flinch1") = std::bind(&Spider::ReadyToJump, this);
		animator->GetCompleteEvent(L"Flinch2") = std::bind(&Spider::ReadyToJump, this);
		animator->GetCompleteEvent(L"Jump") = std::bind(&Spider::Jump, this);

		animator->Play(L"Idle", false);
	}

	void Spider::StateChange(int change_num)
	{
		const int num = change_num;

		switch (num)
		{
		case State::Standby:
			state = State::Standby;
			break;
		case State::Chase:
			state = State::Chase;
			break;
		case State::Die:
			state = State::Die;
			break;
		};
	}
}