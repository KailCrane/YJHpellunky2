#include "yaBat.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaDetector.h"
#include "yaTime.h"

namespace ya
{
	Bat::Bat()
		:speed(2.0f)
	{

	}
	Bat::~Bat()
	{

	}

	void Bat::Initialize()
	{
		tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
		tr->SetScale(Vector3::One);
		animator = GetOwner()->AddComponent<Animator>();
		SetName(L"Bat");
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
		SetAnimation();

		detector = object::Instantiate<GameObject>(eLayerType::Detector ,scene);
		Transform* detector_tr = detector->GetComponent<Transform>();
		detector->SetName(L"Detector");
		detector_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		detector_tr->SetScale(Vector3::One);
		Detector* detectorScript = detector->AddComponent<Detector>();
		Collider2D* col = detector->AddComponent<Collider2D>();
		col->SetName(L"DetectorCollider");
		detectorScript->SetSender(this);
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(3.5, 0.3));

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
		body_tr->SetScale(Vector3::One);
		Detector* bodyScript = body->AddComponent<Detector>();
		bodyScript->SetSender(this);
		Collider2D* body_col = body->AddComponent<Collider2D>();
		body_col->SetName(L"MonsterBodyCollider");
		body_col->SetType(eColliderType::Rect);
		body_col->SetSize(Vector2(0.4, 0.4));
#pragma endregion
	}


	void Bat::Update()
	{
		switch (state)
		{
		case ya::Bat::Standby:
			break;
		case ya::Bat::Chase:
			ChaseTarget();
			break;
		case ya::Bat::Die:
			break;
		}
	}
	void Bat::FixedUpdate()
	{

	}

	void Bat::ChaseTarget()
	{
		if (target == nullptr)
		{
			std::vector<GameObject*> curr_scene_GameObject = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Player);
			target = curr_scene_GameObject[0];
		}

		Vector3 target_pos = target->GetComponent<Transform>()->GetPosition();
		Vector3 my_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		
		if (target_pos.x < my_pos.x)
		{
			Vector3 fixed_pos = Vector3(my_pos.x -= Time::DeltaTime() * speed, my_pos.y, my_pos.z);
			GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		}
		else
		{
			Vector3 fixed_pos = Vector3(my_pos.x += Time::DeltaTime() * speed, my_pos.y, my_pos.z);
			GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		}
		if (target_pos.y < my_pos.y)
		{
			Vector3 fixed_pos = Vector3(my_pos.x, my_pos.y -= Time::DeltaTime() * speed, my_pos.z);
			GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		}
		else
		{
			Vector3 fixed_pos = Vector3(my_pos.x, my_pos.y += Time::DeltaTime() * speed, my_pos.z);
			GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		}
	}

	void Bat::Render()
	{
	}
	void Bat::OnCollisionEnter(Collider2D* collider)
	{
	}
	void Bat::OnCollisionStay(Collider2D* collider)
	{
	}
	void Bat::OnCollisionExit(Collider2D* collider)
	{

	}

	void Bat::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"DetectorCollider")
		{
			if (col->GetName() ==
				L"PlayerCollider")
			{
				//플레이어 추적
				StateChange(Chase);
			}
		}
		if (sender->GetName() == L"MonsterHeadCollider")
		{
			if (col->GetName() ==
				L"PlayerFeetCollider")
			{
				//플레이어 추적
				StateChange(Chase);
			}
		}
	}

	void Bat::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{

	}

	void Bat::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
	}
	
	void Bat::SetAnimation()
	{
		std::shared_ptr<Texture> texture_L = Resources::Load<Texture>(L"LSkeleton", L"Monster//monstersbasic01L.png");
		std::shared_ptr<Texture> texture_R = Resources::Load<Texture>(L"RSkeleton", L"Monster//monstersbasic01R.png");

		animator->Create(L"LeftIdle", texture_L, Vector2(128.0f * 4, 0), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.1f, true);
		animator->Create(L"RightIdle", texture_R, Vector2(128.0f * 6, 0), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f, false);
		animator->Play(L"LeftIdle", true);
	}
	void Bat::StateChange(int change_num)
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