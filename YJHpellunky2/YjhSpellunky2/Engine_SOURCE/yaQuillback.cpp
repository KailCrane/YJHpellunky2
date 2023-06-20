#include "yaQuillback.h"
#include "yaSpriteRenderer.h"
#include "yaGameObject.h"
#include "yaObject.h"
#include "yaDetector.h"
#include "yaResources.h"
#include "yaTime.h"
#include "yaBlock.h"

namespace ya
{
	Quillback::Quillback()
		:animator(nullptr),
		curr_scene(nullptr),
		ground_count(0),
		walk_speed(2.0f),
		petrol_range(10.0f),
		jump_power(Vector2(2, 5)),
		jump_decrease(5.0f),
		decrease_limit(-10.0f)
	{

	}
	Quillback::~Quillback()
	{
	}
	void Quillback::Initialize()
	{
		GetScene();
		tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
		tr->SetScale(Vector3(2.0f,2.0f,1.1f));
		SetName(L"Quillback");

		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"QuillbackMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();
		SetAnimation();

		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();

#pragma region "Detector"
		detector = object::Instantiate<GameObject>(eLayerType::Detector, curr_scene);
		Transform* detector_tr = detector->GetComponent<Transform>();
		detector_tr->SetPosition(owner_pos);
		detector_tr->SetScale(Vector3::One);
		Detector* detectorScript = detector->AddComponent<Detector>();
		Collider2D* col = detector->AddComponent<Collider2D>();
		col->SetName(L"DetectorCollider");
		detectorScript->SetSender(this);
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(7.5f, 0.6f));
		col->SetCenter(Vector2(0.0f, 0.0f));
#pragma endregion

#pragma region "Head"
		head = object::Instantiate<GameObject>(eLayerType::MonsterHead, curr_scene);
		head->SetLayerType(eLayerType::MonsterHead);
		head->SetName(L"MonsterHead");
		Transform* head_tr = head->GetComponent<Transform>();
		Vector3 head_pos = Vector3(owner_pos.x, owner_pos.y + 0.5f, owner_pos.z);
		head_tr->SetPosition(head_pos);
		head_tr->SetScale(Vector3::One);
		Detector* headScript = head->AddComponent<Detector>();
		headScript->SetSender(this);
		Collider2D* head_col = head->AddComponent<Collider2D>();
		head_col->SetName(L"MonsterHeadCollider");
		head_col->SetType(eColliderType::Rect);
		head_col->SetSize(Vector2(1.3f, 0.2f));
#pragma endregion

#pragma region "Body"
		body = object::Instantiate<GameObject>(eLayerType::MonsterBody, curr_scene);
		body->SetLayerType(eLayerType::MonsterBody);
		body->SetName(L"MonsterBody");
		Transform* body_tr = body->GetComponent<Transform>();
		Vector3 body_pos = Vector3(owner_pos.x, owner_pos.y -0.2f, owner_pos.z);
		body_tr->SetPosition(body_pos);
		body_tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		Detector* bodyScript = body->AddComponent<Detector>();
		bodyScript->SetSender(this);
		Collider2D* body_col = body->AddComponent<Collider2D>();
		body_col->SetName(L"MonsterBodyCollider");
		body_col->SetType(eColliderType::Rect);
		body_col->SetSize(Vector2(1.5, 1.2));
#pragma endregion

#pragma region "Feet"
		feet = object::Instantiate<GameObject>(eLayerType::MonsterFeet, curr_scene);
		feet->SetLayerType(eLayerType::MonsterFeet);
		feet->SetName(L"MonsterFeet");
		Transform* feet_tr = feet->GetComponent<Transform>();
		feet_tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		Vector3 feet_pos = Vector3(owner_pos.x, owner_pos.y - 0.9f, owner_pos.z);
		feet_tr->SetPosition(feet_pos);
		Detector* feetScript = feet->AddComponent<Detector>();
		feetScript->SetSender(this);
		Collider2D* feet_col = feet->AddComponent<Collider2D>();
		feet_col->SetName(L"MonsterFeetCollider");
		feet_col->SetType(eColliderType::Rect);
		feet_col->SetSize(Vector2(1.4, 0.2));
#pragma endregion

		my_direction = Left;
		StateChange(mPetrol);
	}
	void Quillback::Update()
	{
		if (!GetOwner()->IsDead())
		{
			Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			Transform* detector_tr = detector->GetComponent<Transform>();
			detector_tr->SetPosition(owner_pos);

			Transform* head_tr = head->GetComponent<Transform>();
			Vector3 head_pos = Vector3(owner_pos.x, owner_pos.y + 0.5f, owner_pos.z);
			head_tr->SetPosition(head_pos);

			Transform* feet_tr = feet->GetComponent<Transform>();
			Vector3 feet_pos = Vector3(owner_pos.x, owner_pos.y - 0.9f, owner_pos.z);
			feet_tr->SetPosition(feet_pos);

			Transform* body_tr = body->GetComponent<Transform>();
			Vector3 body_pos = Vector3(owner_pos.x, owner_pos.y - 0.2f, owner_pos.z);
			body_tr->SetPosition(body_pos);


			if (ground_count == 0)
			{
				isGround == false;
				Vector3 owner_pos = tr->GetPosition();

				/*Vector3 fixed_pos = Vector3(owner_pos.x, owner_pos.y - 9 * Time::DeltaTime(), owner_pos.z);
				tr->SetPosition(fixed_pos);*/
			}
			else
			{
				isGround == true;
			}
		}

		switch (state)
		{
		case mStandby:
			break;
		case mPetrol:
			Petrol();
			break;
		case mTurn:
			break;
		case mJump:
			Jump();
			break;
		case mRollAttack:
			RollAttack();
			break;
		case mRush:
			Rush();
			break;
		case mLand:
			Land();
			break;
		case ya::Quillback::mDead:
			break;
		default:
			break;
		}
	}
	void Quillback::FixedUpdate()
	{

	}
	void Quillback::Render()
	{

	}
	void Quillback::Petrol()
	{
		Vector3 owner_pos = tr->GetPosition();
		Vector3 fixed_pos;
		switch (my_direction)
		{
		case Left:
			fixed_pos = Vector3(owner_pos.x -= walk_speed * Time::DeltaTime(), owner_pos.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
			if (animator->IsComplete())
			{
				animator->Play(L"LeftWalk");
			}
			if (-petrol_range >= starting_point.x + tr->GetPosition().x)
			{
				my_direction = Right;
				animator->Play(L"LeftTurn");
				StateChange(mTurn);
			}
			break;
		case Right:
			 fixed_pos = Vector3 (owner_pos.x += walk_speed * Time::DeltaTime(), owner_pos.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
			if (animator->IsComplete())
			{
				animator->Play(L"RightWalk");
			}
			if (petrol_range  <= starting_point.x + tr->GetPosition().x)
			{
				animator->Play(L"RightTurn");
				my_direction = Left;
				StateChange(mTurn);
			}
			//if (petrol_range >= starting_point.x - tr->GetPosition().x)
			//{
			//	detector->Death(); //도는 동안은 감지 불가!
			//	my_direction = Left;
			//	animator->Play(L"LeftTurn");
			//	StateChange(mTurn);
			//}
			break;
		}

		

	}
	void Quillback::Jump()
	{
		Vector3 owner_pos = tr->GetPosition(); 
		Vector3 fixed_pos = Vector3(owner_pos.x += Time::DeltaTime() * jump_power.x , owner_pos.y += Time::DeltaTime() * jump_power.y, owner_pos.z);
		tr->SetPosition(fixed_pos);

		if (jump_power.y <= 0 && jump_power.y > -1.0f)
		{
			int a = 0;
			if (!CheckDistanceWithTarget())
			{
				if (my_direction == Left)
				{
					animator->Play(L"LeftRollAttack",true);
				}
				else
				{
					animator->Play(L"RightRollAttack", true);
				}
				StateChange(mRollAttack);
				return;
			}
		}
		else
		{
			StateChange(mLand);
		}
		if (jump_power.y > decrease_limit)
		{
			jump_power.y -= jump_decrease * Time::DeltaTime();
		}
	}
	void Quillback::RollAttack()
	{
		int a = 0;
		if (jump_power.y > decrease_limit)
		{
			jump_power.y -= jump_decrease * Time::DeltaTime();
		}
		if (my_direction == Left)
		{
			Vector3 owner_pos = tr->GetPosition();
			Vector3 fixed_pos = Vector3(owner_pos.x -= Time::DeltaTime() * jump_power.x /2, owner_pos.y += Time::DeltaTime() * jump_power.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
		}
		else
		{
			Vector3 owner_pos = tr->GetPosition();
			Vector3 fixed_pos = Vector3(owner_pos.x += Time::DeltaTime() * jump_power.x / 2, owner_pos.y += Time::DeltaTime() * jump_power.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
		}
	}

	bool Quillback::CheckDistanceWithTarget()
	{
		if (target == nullptr)
		{
			std::vector<GameObject*> curr_scene_GameObject = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Player);
			target = curr_scene_GameObject[0];
		}
		float distance = GetDistance(GetOwner()->GetComponent<Transform>()->GetPosition(), target->GetComponent<Transform>()->GetPosition());
		if (distance <= 4)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	void Quillback::TurnEnd()
	{
		if (my_direction == Left)
		{
			animator->Play(L"LeftWalk");
		}
		else
		{
			animator->Play(L"RightWalk");
		}
		StateChange(mPetrol);
		detector->Alive();
	}


	void Quillback::PrepareJump()
	{
		StateChange(mJump);
		if (my_direction == Left)
		{
			animator->Play(L"LeftJump",false);
		}
		else
		{
			animator->Play(L"RightJump", false);
		}
	}

	void Quillback::Land()
	{
		Vector3 owner_pos = tr->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x += Time::DeltaTime() * jump_power.x, owner_pos.y += Time::DeltaTime() * jump_power.y, owner_pos.z);
		tr->SetPosition(fixed_pos);

		if (jump_power.y > decrease_limit)
		{
			jump_power.y -= jump_decrease * Time::DeltaTime();
		}
	}

	void Quillback::Rush()
	{
		if (my_direction == Left)
		{
			Vector3 owner_pos = tr->GetPosition();
			Vector3 fixed_pos = Vector3(owner_pos.x -= Time::DeltaTime() * walk_speed * 3, owner_pos.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
		}
		else
		{
			Vector3 owner_pos = tr->GetPosition();
			Vector3 fixed_pos = Vector3(owner_pos.x += Time::DeltaTime() * walk_speed * 3, owner_pos.y, owner_pos.z);
			tr->SetPosition(fixed_pos);
		}
	}

	void Quillback::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"DetectorCollider")
		{
			if (col->GetName() == L"PlayerCollider" ||
				L"PlayerHeadCollider" ||
				L"PlayerBodyCollider")
			{

				if (state == mPetrol)
				{
					if (target == nullptr)
					{
						std::vector<GameObject*> curr_scene_GameObject = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Player);
						target = curr_scene_GameObject[0];
					}
					Vector3 target_pos = target->GetComponent<Transform>()->GetPosition();
					if (my_direction == Left)
					{
						if (target_pos.x < tr->GetPosition().x)
						{
							curr_jump_power = jump_power;
							animator->Play(L"LeftPrepareJump");
							StateChange(mPrepareJump);
						}
						else
						{
							my_direction = Right;
							animator->Play(L"LeftTurn");
							StateChange(mTurn);
						}
					}
					else
					{
						if (target_pos.x >= tr->GetPosition().x)
						{
							curr_jump_power = jump_power;
							animator->Play(L"RightPrepareJump", false);
							StateChange(mPrepareJump);
						}
						else
						{
							my_direction = Right;
							animator->Play(L"LeftTurn");
							StateChange(mTurn);
						}
					}
				}
			}
		}
		if (sender->GetName() == L"MonsterFeetCollider")
		{
			if (col->GetName() == L"GroundCollider")
			{
				ground_count++;

				if (state == mRollAttack)
				{
					StateChange(mRush);
					/*Block* block = col->GetOwner()->GetScript<Block>();
					block->Destroy();*/
				}
			}
			
			if (state == mLand)
			{
				detector->Alive();
				if (my_direction == Left)
				{
					animator->Play(L"LeftLandReady");
				}
				else
				{
					animator->Play(L"RightLandReady");
				}
				StateChange(mPetrol);
			}
		}
	}

	void Quillback::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{
	}

	void Quillback::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"MonsterFeetCollider")
		{
			if (col->GetName() == L"GroundCollider")
			{
				ground_count--;
			}
		}
	}

	void Quillback::SetAnimation()
	{

#pragma region "Texture"
		std::shared_ptr<Texture> texture_L = Resources::Load<Texture>(L"LQuillback", L"Monster//monstersbig01L.png");
		std::shared_ptr<Texture> texture_R = Resources::Load<Texture>(L"RQuillback", L"Monster//monstersbig01R.png");
#pragma endregion

#pragma region "Idle"
		animator->Create(L"LeftIdle", texture_L, Vector2(256.0f * 7, 0), Vector2(256.0f, 256.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"RightIdle", texture_R, Vector2(256.0f * 0, 0), Vector2(256.0f, 256.0f), Vector2::Zero, 1, 0.01f, false);
#pragma endregion

#pragma region "Turn"
		animator->Create(L"LeftTurn", texture_L, Vector2(256.0f * 0, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.15f, true);
		animator->Create(L"RightTurn", texture_R, Vector2(256.0f * 6, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.15f, false);
#pragma endregion

#pragma region "Walk"
		animator->Create(L"LeftWalk", texture_L, Vector2(256.0f * 2, 256.0f * 3), Vector2(256.0f, 256.0f), Vector2::Zero, 6, 0.1f, true);
		animator->Create(L"RightWalk", texture_R, Vector2(256.0f * 0, 256.0f * 3), Vector2(256.0f, 256.0f), Vector2::Zero, 6, 0.1f, false);
#pragma endregion

#pragma region  "ReadyToJump"
		animator->Create(L"LeftPrepareJump", texture_L, Vector2(256.0f * 6, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.1f, true);
		animator->Create(L"RightPrepareJump", texture_R, Vector2(256.0f * 0, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.2f, false);
#pragma endregion

#pragma region  "Jump"
		animator->Create(L"LeftJump", texture_L, Vector2(256.0f * 4, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.1f, true);
		animator->Create(L"RightJump", texture_R, Vector2(256.0f * 2, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.1f, false);
#pragma endregion

#pragma region  "Land"
		animator->Create(L"LeftLandReady", texture_L, Vector2(256.0f * 6, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.1f, true);
		animator->Create(L"RightLandReady", texture_R, Vector2(256.0f * 0, 256.0f * 1), Vector2(256.0f, 256.0f), Vector2::Zero, 2, 0.1f, false);
#pragma endregion

#pragma region "RollAttack"
		animator->Create(L"LeftRollAttack", texture_L, Vector2(256.0f * 4, 256.0f * 2), Vector2(256.0f, 256.0f), Vector2::Zero, 4, 0.05f, true);
		animator->Create(L"RightRollAttack", texture_R, Vector2(256.0f * 0, 256.0f * 2), Vector2(256.0f, 256.0f), Vector2::Zero, 4, 0.05f, false);
#pragma endregion

		animator->GetCompleteEvent(L"LeftPrepareJump") = std::bind(&Quillback::PrepareJump, this);
		animator->GetCompleteEvent(L"RightPrepareJump") = std::bind(&Quillback::PrepareJump, this);
		
		animator->Play(L"LeftIdle", true);
		//animator->GetCompleteEvent(L"LeftWhipFirstAnim") = std::bind(&WhipScript::WhipSecond, this); // 후에 손에 든
		//animator->GetCompleteEvent(L"LeftWhipFirstAnim") = std::bind(&WhipScript::WhipSecond, this); // 후에 손에 든
	}

	void Quillback::StateChange(int change_num)
	{
		const int num = change_num;

		switch (num)
		{
		case MyState::mStandby:
			state = MyState::mStandby;
			break;
		case MyState::mPetrol:
			state = MyState::mPetrol;
			break;
		case MyState::mPrepareJump:
			state = MyState::mPrepareJump;
			break;
		case MyState::mJump:
			state = MyState::mJump;
			break;
		case MyState::mLand:
			state = MyState::mLand;
			break;
		case MyState::mRollAttack:
			state = MyState::mRollAttack;
			break;
		case MyState::mRush:
			state = MyState::mRush;
			break;
		case MyState::mDead:
			state = MyState::mDead;
			break;
		};
	}
}