#include "yaSnake.h"
#include "yaTime.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaDetector.h"
namespace ya
{
	Snake::Snake()
		:animator(nullptr),
		body(nullptr),
		head(nullptr),
		isDrop(false),
		scene(nullptr),
		isGround(false),
		speed(2.0f),
		target(nullptr),
		tr(nullptr),
		state(State::eStandby),
		ground_count(0),
		direction(Right),
		petrol_time(2.0f),
		petrol_timer(0.0f),
		standby_time(2.0f),
		standby_timer(0.0f)
	{

	}
	Snake::~Snake()
	{

	}
	void Snake::Initialize()
	{
		GetScene();
		tr = GetOwner()->GetComponent<Transform>();
		tr->SetScale(Vector3::One);
		SetName(L"Snake");

		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();
		SetAnimation();

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
		head_col->SetSize(Vector2(0.4f, 0.2f));
#pragma endregion
#pragma region "Body"

		body = object::Instantiate<GameObject>(eLayerType::MonsterBody, scene);
		body->SetLayerType(eLayerType::MonsterBody);
		body->SetName(L"MonsterBody");
		Transform* body_tr = body->GetComponent<Transform>();
		body_tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		body_tr->SetScale(Vector3(1, 1, 1));
		Detector* bodyScript = body->AddComponent<Detector>();
		bodyScript->SetSender(this);
		Collider2D* body_col = body->AddComponent<Collider2D>();
		body_col->SetName(L"MonsterBodyCollider");
		body_col->SetType(eColliderType::Rect);
		body_col->SetSize(Vector2(0.6, 0.4));
#pragma endregion
		petrol_timer = petrol_time;
		standby_timer = standby_time;
	
	}
	void Snake::Update()
	{
		if (!GetOwner()->IsDead())
		{
			Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Transform* head_tr = head->GetComponent<Transform>();
			Vector3 fixed_head_pos = Vector3(owner_pos.x, owner_pos.y + 0.2f, owner_pos.z);
			head_tr->SetPosition(fixed_head_pos);

			Transform* body_tr = body->GetComponent<Transform>();
			Vector3 fixed_body_pos = Vector3(owner_pos.x, owner_pos.y - 0.18f, owner_pos.z);
			body_tr->SetPosition(fixed_body_pos);

			if (ground_count == 0)
			{
				isGround == false;
				Vector3 owner_pos = tr->GetPosition();

				Vector3 fixed_pos = Vector3(owner_pos.x, owner_pos.y - 4 * Time::DeltaTime(), owner_pos.z);
				tr->SetPosition(fixed_pos);
			}
			else
			{
				isGround == true;
			}
		}
		
		switch (state)
		{
		case eStandby:
			Standby();
			break;
		case ePetrol:
			Petrol();
			break;
		case eAttack:
			break;
		}
	}
	void Snake::FixedUpdate()
	{

	}
	void Snake::Render()
	{
	}
	void Snake::SetPos(Vector3 point)
	{
		tr->SetPosition(point);
		//tr->SetPosition(Vector3(9.0f, -6.3f, 1.1f));

	}
	void Snake::OnCollisionEnter(Collider2D* collider)
	{
	}
	void Snake::OnCollisionStay(Collider2D* collider)
	{
	}
	void Snake::OnCollisionExit(Collider2D* collider)
	{
	}
	void Snake::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"MonsterBodyCollider")
		{

			if (col->GetName() == L"WhipCollider")
			{
				head->Death();
				body->Death();
				GetOwner()->Death();
			}

			if (col->GetName() ==
				L"PlayerCollider" ||
				L"PlayerHeadCollider" ||
				L"PlayerBodyCollider")
			{
				/*animator->Play(L"Attack", false);
				*/
			}
			if (col->GetName() == L"GroundCollider")
			{
				ground_count++;
			}

			if (state == ePetrol)
			{
				if (col->GetName() == L"LeftSideCollider")
				{
					if (direction == Left)
					{
						Turn();
					}
				}
				if (col->GetName() == L"RightSideCollider")
				{
					if (direction == Right)
					{
						Turn();
					}
				}
				if (col->GetName() == L"BodyCollider")
				{
					if (direction == Left)
					{
						if (animator->IsComplete())
						{
							animator->Play(L"LeftAttack");
						}
					}
					else
					{
						if (animator->IsComplete())
						{
							animator->Play(L"RightAttack");
						}
					}
				}
				if (col->GetName() == L"HeadCollider")
				{
					if (direction == Left)
					{
						if (direction == Left)
						{
							if (animator->IsComplete())
							{
								animator->Play(L"LeftAttack");
							}
						}
						else
						{
							if (animator->IsComplete())
							{
								animator->Play(L"RightAttack");
							}
						}
					}
				}
				if (col->GetName() == L"FeetCollider")
				{
					if (direction == Left)
					{

					}if (direction == Left)
					{
						if (animator->IsComplete())
						{
							animator->Play(L"LeftAttack");
						}
					}
					else
					{
						if (animator->IsComplete())
						{
							animator->Play(L"RightAttack");
						}
					}
				}
			}
		}

		if (sender->GetName() == L"MonsterHeadCollider")
		{
			if (col->GetName() == L"WhipCollider")
			{
				pManager->SpawnBlood(GetOwner()->GetComponent<Transform>()->GetPosition());
				head->Death();
				body->Death();
				GetOwner()->Death();
			}
			if (col->GetName() == L"FeetCollider")
			{
				pManager->SpawnBlood(GetOwner()->GetComponent<Transform>()->GetPosition());
				head->Death();
				body->Death();
				GetOwner()->Death();
			}
		}
	}

	void Snake::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{
	}
	void Snake::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
		if (col->GetName() == L"GroundCollider")
		{
			ground_count--;
		}
	}

	void Snake::Petrol()
	{
		Transform* owner_tr = GetOwner()->GetComponent<Transform>();
		Vector3 owner_pos = owner_tr->GetPosition();
		Vector3 fixed_pos;

		petrol_timer -= Time::DeltaTime();
		if (petrol_timer <= 0);
		{
			petrol_timer = petrol_time;
			StateChange(eStandby);
		}
		if (direction == Left)
		{
			fixed_pos = Vector3(owner_pos.x -= speed * Time::DeltaTime(), owner_pos.y, owner_pos.z);
			owner_tr->SetPosition(fixed_pos);
			if (animator->IsComplete())
			{
				animator->Play(L"LeftMove");
			}
		}
		else
		{
			fixed_pos = Vector3(owner_pos.x += speed * Time::DeltaTime(), owner_pos.y, owner_pos.z);
			owner_tr->SetPosition(fixed_pos);
			if (animator->IsComplete())
			{
				animator->Play(L"RightMove");
			}
		}
	}

	void Snake::Attack()
	{

	}

	void Snake::Standby()
	{
		standby_timer -= Time::DeltaTime();
		if (standby_timer <= 0);
		{
			standby_timer = standby_time;
			StateChange(ePetrol);
		}
	}

	void Snake::Turn()
	{
		if (direction == Left)
		{
			direction = Right;
		}
		else
		{
			direction = Left;
		}
	}

	void Snake::SetAnimation()
	{
		std::shared_ptr<Texture> texture_l = Resources::Load<Texture>(L"LefetSnake", L"Monster//SnakeLeft.png");
		std::shared_ptr<Texture> texture_r = Resources::Load<Texture>(L"RightSnake", L"Monster//RightSnake.png");

		animator->Create(L"LeftIdle", texture_l, Vector2(128.0f * 5, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"RightIdle", texture_r, Vector2(0 * 8, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, false);
		animator->Create(L"LeftMove", texture_l, Vector2(0 * 8, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.1f, true);
		animator->Create(L"RightMove", texture_r, Vector2(0 * 8, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.1f, false);
		animator->Create(L"LeftAttack", texture_l, Vector2(0 * 8, 128.0f * 1), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.1f, true);
		animator->Create(L"RightAttack", texture_l, Vector2(0 * 8, 128.0f * 1), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.1f, true);

		animator->Play(L"RightIdle");
	}

	void Snake::StateChange(int change_num)
	{
		const int num = change_num;

		switch(num)
		{
		case eStandby:
			state = eStandby;
			break;
		case ePetrol:
			state = ePetrol;
			break;
		case eAttack:
			state = eAttack;
			break;
		}

	}
}