#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaRenderer.h"
#include "yaRigidbody.h"
#include "yaWhipScript.h"
#include "yaShotGunScript.h"
#include "yaRopeThrowScript.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaDetector.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script(),
		camera_obj(nullptr),
		isGround(false),
		max_jump_time(0.15f),
		jump_count(1),
		pressing_timer(0.0f),
		mState(Fall),
		curr_life(3),
		isInterctWeapon(false),
		isHas_front_equip(false),
		isCtrlAble(true),
		isInivisible(false),
		touch_ground_amount(0),
		falling_limit(-9)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		animator = GetOwner()->AddComponent<Animator>();
		curr_scene = SceneManager::GetPlayScene();

#pragma region  "플레이어 머리"
		{
			head = object::Instantiate<GameObject>(eLayerType::Head, curr_scene);
			head->SetLayerType(eLayerType::Head);
			head->SetName(L"Head");
			Transform* head_tr = head->GetComponent<Transform>();
			head_tr->SetScale(Vector3::One);
			Detector* headScript = head->AddComponent<Detector>();
			headScript->SetSender(this);
			Collider2D* head_col = head->AddComponent<Collider2D>();
			head_col->SetName(L"HeadCollider");
			head_col->SetType(eColliderType::Rect);
			head_col->SetSize(Vector2(0.4f, 0.2f));
		}
#pragma endregion
		
#pragma region "플레이어 몸체"
		{
			body = object::Instantiate<GameObject>(eLayerType::Body, curr_scene);
			body->SetLayerType(eLayerType::Body);
			body->SetName(L"Body");
			Transform* body_tr = body->GetComponent<Transform>();
			body_tr->SetScale(Vector3::One);
			Detector* bodyScript = body->AddComponent<Detector>();
			bodyScript->SetSender(this);
			Collider2D* body_col = body->AddComponent<Collider2D>();
			body_col->SetName(L"BodyCollider");
			body_col->SetType(eColliderType::Rect);
			body_col->SetSize(Vector2(0.5f, 0.5f));
		}
#pragma endregion

#pragma region "플레이어 발"
		{
			feet = object::Instantiate<GameObject>(eLayerType::Feet, curr_scene);
			feet->SetLayerType(eLayerType::Feet);
			feet->SetName(L"Feet");
			Transform* feet_tr = feet->GetComponent<Transform>();
			feet_tr->SetScale(Vector3::One);
			Detector* feetScript = feet->AddComponent<Detector>();
			feetScript->SetSender(this);
			Collider2D* feet_col = feet->AddComponent<Collider2D>();
			feet_col->SetName(L"FeetCollider");
			feet_col->SetType(eColliderType::Rect);
			feet_col->SetSize(Vector2(0.55f, 0.1f));
		}
#pragma endregion

		SetAnimation();
	}

	void PlayerScript::Update()
	{
		if (!isDead)
		{
			InputCtrl();

			if (touch_ground_amount == 0)
			{
				isGround = false;
				if (mState == Fall)
				{
					Vector3 mPos = transform->GetPosition();
					Vector3 fixed_pos = Vector3(mPos.x, mPos.y + falling_speed * Time::DeltaTime(), mPos.z);
					if (falling_speed > falling_limit)
					{
						falling_speed -= Time::DeltaTime() * 18;
					}
					else
					{
						falling_speed = falling_limit;
					}


					transform->SetPosition(fixed_pos);
				}
			}
			else
			{
				falling_speed = 0.0f;
				isGround = true;
				if (mState == Fall)
				{
					mState = Idle;
				}
			}
		}


#pragma region "sadsa"


		//	if(isHas_front_equip)
		//	if (front_equip != nullptr)
		//	{
		//		Transform* tr = GetOwner()->GetComponent<Transform>();
		//		ShotGunScript* shotgun = front_equip->GetScript<ShotGunScript>();
		//		Rigidbody* rb = front_equip->GetComponent<Rigidbody>();
		//		rb->GravityOff();
		//		if (direction == LeftAhead)
		//		{
		//			front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x - 0.2f, tr->GetPosition().y - 0.25f, tr->GetPosition().z));
		//			if (mState == Crouch || mState == Crawl)
		//			{
		//				front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x - 0.2f, tr->GetPosition().y - 0.35f, tr->GetPosition().z));
		//			}
		//			if (front_equip->GetLayerType() == eLayerType::ShotGun)
		//			{
		//				shotgun->TurnLeft();
		//			}
		//		}
		//		else
		//		{
		//			front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 0.2f, tr->GetPosition().y - 0.25f, tr->GetPosition().z));
		//			if (mState == Crouch || mState == Crawl)
		//			{
		//				front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 0.2f, tr->GetPosition().y - 0.35f, tr->GetPosition().z));
		//			}
		//			if (front_equip->GetLayerType() == eLayerType::ShotGun)
		//			{
		//				shotgun->TurnRight();
		//			}
		//		}
		//	}
		//}
		//if (Input::GetKeyState(eKeyCode::O) == eKeyState::DOWN)
		//{
		//	LifeDown();
		//}


		//if (Input::GetKeyState(eKeyCode::P) == eKeyState::DOWN)
		//{
		//	Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();
		//	rb->KnockbackOn(Vector2(2,3));
		//	mState = Knockback;
		//	isCtrlAble = false;
		//	isInivisible = true;
		//	animator->Play(L"LeftJump", false);
		//}
		//if (isCtrlAble)
		//{
		//	InputCtrl();
		//}
		////prev_pos = transform->GetPosition();
#pragma endregion

	}

	void PlayerScript::FixedUpdate()
	{
		if (!isDead)
		{
			if (camera_obj != nullptr)
			{
				if (mState != LookUp)
				{
					Vector3 cam_pos = camera_obj->GetComponent<Transform>()->GetPosition();
					Vector3 player_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();

					Vector3 fixed_cam_pos = Vector3(player_pos.x, player_pos.y, player_pos.z - 5.0f);

					camera_obj->GetComponent<Transform>()->SetPosition(fixed_cam_pos);
				}
			}
		}


#pragma region "각 부위 콜라이더 동기화"
		Transform* head_tr = head->GetComponent<Transform>();
		Transform* body_tr = body->GetComponent<Transform>();
		Transform* feet_tr = feet->GetComponent<Transform>();
		Transform* owner_pos = GetOwner()->GetComponent<Transform>();

		head_tr->SetPosition(Vector3(owner_pos->GetPosition().x, owner_pos->GetPosition().y + 0.2f, owner_pos->GetPosition().z));
		body_tr->SetPosition(Vector3(owner_pos->GetPosition().x, owner_pos->GetPosition().y - 0.15f, owner_pos->GetPosition().z));
		feet_tr->SetPosition(Vector3(owner_pos->GetPosition().x, owner_pos->GetPosition().y-0.45f, owner_pos->GetPosition().z));


#pragma endregion
	}


	void PlayerScript::SetAnimation()
	{
		std::shared_ptr<Texture> texture_L = Resources::Load<Texture>(L"LPlayer", L"char_yellowL.png");
		std::shared_ptr<Texture> texture_R = Resources::Load<Texture>(L"RPlayer", L"char_yellowR.png");

		animator->Create(L"LeftIdle", texture_L, Vector2(1920.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, true);
		animator->Create(L"RightIdle",  texture_R, Vector2(0.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);

		animator->Create(L"LeftMove", texture_L, Vector2(896.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.05f, true);
		animator->Create(L"RightMove", texture_R, Vector2(128.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 8, 0.05f, false);

		animator->Create(L"LeftAttack", texture_L, Vector2(1280.0f, 512.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f, true);
		animator->Create(L"RightAttack", texture_R, Vector2(0.0f, 512.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f, false);

		animator->Create(L"LeftLookUp", texture_L, Vector2(1536.0f, 1024.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 4, 0.05f, true);
		animator->Create(L"RightLookUp", texture_R, Vector2(0.0f, 1024.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 4, 0.05f, false);

		animator->Create(L"LeftCrouchEnd", texture_L, Vector2(1664.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, true);
		animator->Create(L"RightCrouchEnd", texture_R, Vector2(256.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);

		animator->Create(L"LeftCrouch", texture_L, Vector2(128 * 13, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, true);
		animator->Create(L"RightCrouch", texture_R, Vector2(0.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, false);

		animator->Create(L"LeftCrawl", texture_L, Vector2(512.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 7, 0.05f, true);
		animator->Create(L"RightCrawl", texture_R, Vector2(630.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 7, 0.05f, false);

		animator->Create(L"LeftGetUP", texture_L, Vector2(128 * 13, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, false);
		animator->Create(L"RightGetUP", texture_R, Vector2(256.0f, 128.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, false);

		animator->Create(L"LeftJump", texture_L, Vector2(1408, 1152.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 5, 0.05f, true);
		animator->Create(L"RightJump", texture_R, Vector2(0.0f, 1152.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 5, 0.05f, false);

		animator->Create(L"LeftFall", texture_L, Vector2(1664.0f, 1280.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, true);
		animator->Create(L"RightFall", texture_R, Vector2(256.0f, 1280.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.05f, false);

		animator->Create(L"HangOnRope", texture_R, Vector2(0.0f, 128.0f * 7), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"GoUpRope", texture_R, Vector2(0.0f, 128.0f * 7), Vector2(128.0f, 128.0f), Vector2::Zero, 10, 0.05f, false);
		animator->Create(L"GoDownRope", texture_R, Vector2(0.0f, 128.0f * 7), Vector2(128.0f, 128.0f), Vector2::Zero, 10, 0.05f, true);

		animator->Create(L"LeftDead", texture_L, Vector2(128.0f * 14, 128.0f * 2), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, true);
		animator->Create(L"RightDead", texture_R, Vector2(128.0f * 1, 128.0f * 2), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"LeftGroundDead", texture_L, Vector2(128.0f * 6, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, true);
		animator->Create(L"RightGroundDead", texture_R, Vector2(128.0f * 9, 128.0f * 0), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Play(L"RightIdle", true);

		animator->GetStartEvent(L"Idle");
		animator->GetCompleteEvent(L"LeftAttack") = std::bind(&PlayerScript::AttackEnd, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"LeftGetUP") = std::bind(&PlayerScript::LeftGetUpEnd, this);
		animator->GetCompleteEvent(L"RightGetUP") = std::bind(&PlayerScript::RightGetUpEnd, this);
	}

	void PlayerScript::InputCtrl()
	{
#pragma region  "Input"

		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::DOWN)
		{
			if (direction == RightAhead)
			{
				direction = LeftAhead;
			}
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				animator->Play(L"LeftMove", false);
				mState = Walk;
				break;
			case ya::PlayerScript::Walk:
				break;
			case ya::PlayerScript::Crouch:
				if (animator->IsComplete())
				{
					animator->Play(L"LeftCrawl", false);
				}
				mState = Crawl;
				break;
			case ya::PlayerScript::LookUp:
				pressing_timer = 0.0f;
				mState = Walk;
				break;
			case ya::PlayerScript::Jump:
				break;

			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				animator->Play(L"LeftMove", false);
				mState = Walk;
				break;
			case ya::PlayerScript::Walk:
				if (animator->IsComplete())
				{
					animator->Play(L"LeftMove", false);
				}
				break;
			case ya::PlayerScript::Crouch:
				if (animator->IsComplete())
				{
					animator->Play(L"LeftCrawl", false);
				}
				break;
			case ya::PlayerScript::Crawl:
				if (animator->IsComplete())
				{
					animator->Play(L"LeftCrawl", false);
				}
				break;
			case ya::PlayerScript::LookUp:
				break;
			case ya::PlayerScript::Jump:
				//움직임만
				break;
			case ya::PlayerScript::Fall:
				//움직임만
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}

			if (mState != RidingRope)
			{

				if (mState == Crawl)
				{
					move_speed = -3.0f;
				}
				else
				{
					move_speed = -6.0f;
				}

				if (touch_right_wall_amount == 0)
				{
					Vector3 pos = transform->GetPosition();
					pos.x += move_speed * Time::DeltaTime();
					transform->SetPosition(pos);
				}
			}

			//움직이지 못하는 특정 ㄴㄴ이 아닐 경우

		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::UP)
		{
			switch (mState)
			{
			case ya::PlayerScript::Walk:
				animator->Play(L"LeftIdle", false);
				mState = Idle;
				break;
			case ya::PlayerScript::Crawl:
				animator->Play(L"LeftCrouchEnd", false);
				mState = Crouch;
				break;
			case ya::PlayerScript::Jump:
				//움직이만 없음
				break;
			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::DOWN)
		{
			if (direction == LeftAhead)
			{
				direction = RightAhead;
			}
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				animator->Play(L"RightMove", false);
				mState = Walk;
				break;
			case ya::PlayerScript::Walk:
				break;

			case ya::PlayerScript::Crouch:
				if (animator->IsComplete())
				{
					animator->Play(L"RightCrawl", false);
				}
				mState = Crawl;
				break;
			case ya::PlayerScript::LookUp:
				pressing_timer = 0.0f;
				mState = Walk;
				break;
			case ya::PlayerScript::Jump:
				break;
			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				animator->Play(L"RightMove", false);
				mState = Walk;
				break;
			case ya::PlayerScript::Walk:
				if (animator->IsComplete())
				{
					animator->Play(L"RightMove", false);
				}
				break;
			case ya::PlayerScript::Crouch:
				if (animator->IsComplete())
				{
					animator->Play(L"RightCrawl", false);
				}
				break;
			case ya::PlayerScript::Crawl:
				if (animator->IsComplete())
				{
					animator->Play(L"RightCrawl", false);
				}
				break;
			case ya::PlayerScript::LookUp:
				break;
			case ya::PlayerScript::Jump:
				//움직임만
				break;
			case ya::PlayerScript::Fall:
				//움직임만
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			default:
				break;
			}


			if (mState != RidingRope)
			{
				if (mState == Crawl)
				{
					move_speed = 3.0f;
				}
				else
				{
					move_speed = 6.0f;
				}
				if (touch_left_wall_amount == 0)
				{
					Vector3 pos = transform->GetPosition();
					pos.x += move_speed * Time::DeltaTime();
					transform->SetPosition(pos);
				}
			}
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::UP)
		{
			switch (mState)
			{
			case ya::PlayerScript::Walk:
				animator->Play(L"RightIdle", false);
				mState = Idle;
				break;
			case ya::PlayerScript::Crawl:
				animator->Play(L"RightCrouchEnd", false); //RightCrouchEnd
				mState = Crouch;
				break;
			case ya::PlayerScript::Jump:
				//움직이만 없음
				break;
			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::JumpAttack:
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::DOWN)
		{
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftCrouch", false);
					mState = Crouch;
				}
				else
				{
					animator->Play(L"RightCrouch", false);
					mState = Crouch;
				}
				break;
			case ya::PlayerScript::Walk:
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftCrouch", false);
					mState = Crawl;
				}
				else
				{
					animator->Play(L"RightCrouch", false);
					mState = Crawl;
				}
				break;
			case ya::PlayerScript::Crouch:
				break;
			case ya::PlayerScript::LookUp:
				pressing_timer = 0.0f;
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftCrouch", false);
					mState = Crouch;
				}
				else
				{
					animator->Play(L"RightCrouch", false);
					mState = Crouch;
				}
				break;
			case ya::PlayerScript::Jump:
				break;
			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::RidingRope:
				GetOwner()->GetComponent<Animator>()->Play(L"GoUpRope", false);
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			switch (mState)
			{
			case ya::PlayerScript::Idle:
				break;
			case ya::PlayerScript::Walk:

				break;
			case ya::PlayerScript::Crouch:
				if (animator->IsComplete())
				{
					if (direction == LeftAhead)
					{
						animator->Play(L"LeftCrouchEnd", false);
					}
					else
					{
						animator->Play(L"RightCrouchEnd", false);
					}
				}
				break;
			case ya::PlayerScript::LookUp:
				break;
			case ya::PlayerScript::Jump:
				//움직임만
				break;
			case ya::PlayerScript::Fall:
				//움직임만
				break;
			case ya::PlayerScript::RidingRope:
				if (!isHeadHit_rope && !isFeetHit_rope)
				{
					mState = Fall;
					if (!GetOwner()->GetComponent<Rigidbody>()->GetIsGravity())
					{
						//GetOwner()->GetComponent<Rigidbody>()->GravityOn();
					}
				}
				else
				{
					Vector3 pos = transform->GetPosition();
					Vector3 fixed_pos = Vector3(pos.x, pos.y -= 5.0f * Time::DeltaTime(), pos.z);
					transform->SetPosition(fixed_pos);
					if (GetOwner()->GetComponent<Animator>()->IsComplete())
					{
						GetOwner()->GetComponent<Animator>()->Play(L"GoUpRope", false);
					}
					if (isGround)
					{
						mState = Idle;
					}

				}
				break;	
			case ya::PlayerScript::StandAtack:
				break;
			default:
				break;
			}
		}
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::UP)
		{
			switch (mState)
			{
			case ya::PlayerScript::Crawl:
				//if()
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftGetUP", false);
				}
				else
				{
					animator->Play(L"RightGetUP", false);
				}
				mState = GetUp;
				break;
			case ya::PlayerScript::Crouch:
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftGetUP", false);
				}
				else
				{
					animator->Play(L"RightGetUP", false);
				}
				mState = GetUp;
				break;
			case ya::PlayerScript::Jump:
				//움직이만 없음
				break;
			case ya::PlayerScript::Fall:
				break;
			case ya::PlayerScript::RidingRope:
				GetOwner()->GetComponent<Animator>()->Play(L"HangOnRope", false);
				break;
			case ya::PlayerScript::StandAtack:
				break;
			}
		}


		if (Input::GetKeyState(eKeyCode::A) == eKeyState::DOWN)
		{
			if (isExitDoor)
			{
				stage->NextStage();
			}
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::DOWN)
		{
			//만약 로프가 있다면
			if (mState == RidingRope)
			{
				if (!isHeadHit_rope && isFeetHit_rope)
				{
					return;
				}
				GetOwner()->GetComponent<Animator>()->Play(L"GoUpRope", false);
			}
		}
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			//여기다 로프에 달려 있는지를 추가
			if (mState == Idle)
			{
				pressing_timer += Time::DeltaTime();

				if (pressing_timer >= 0.5f)
				{
					if (direction == LeftAhead)
					{
						animator->Play(L"LeftLookUp", false);
					}
					else
					{
						animator->Play(L"RightLookUp", false);
					}
					mState = LookUp;
				}
			}
			if (mState == RidingRope)
			{	
				if (!isHeadHit_rope && isFeetHit_rope)
				{
					return;
				}
				if (GetOwner()->GetComponent<Animator>()->IsComplete())
				{
					GetOwner()->GetComponent<Animator>()->Play(L"GoUpRope",false);
				}

				Vector3 pos = transform->GetPosition();
				Vector3 fixed_pos = Vector3(pos.x, pos.y += 5.0f * Time::DeltaTime(), pos.z);
				transform->SetPosition(fixed_pos);
			}
		}
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::UP)
		{
			if (mState != RidingRope)
			{
				pressing_timer = 0.0f;
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftIdle", false);
				}
				else
				{
					animator->Play(L"RightIdle", false);
				}
				mState = Idle;
			}
			else
			{
				GetOwner()->GetComponent<Animator>()->Play(L"HangOnRope", false);
			}
		}

		if (isGround )
		{
			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
			{
				if (direction == LeftAhead)
				{
					animator->Play(L"LeftJump", false);
				}
				else
				{
					animator->Play(L"RightJump", false);
				}
				mState = Jump;
			}
		}
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			if (mState == Jump)
			{
				jump_timer += Time::DeltaTime();

				Vector3 mPos = transform->GetPosition();
				Vector3 fixed_pos = Vector3(mPos.x, mPos.y + 9 * Time::DeltaTime(), mPos.z);
				transform->SetPosition(fixed_pos);
				
				if (jump_timer >= max_jump_time)
				{
					jump_timer = 0;
					mState = Fall;
				}

				if (touch_ceiling_amount > 0)
				{
					jump_timer = 0;
					mState = Fall;
				}

			}
		}
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::UP)
		{
			if (mState == Jump)
			{
				jump_timer = 0;
				GetOwner()->GetComponent<Rigidbody>()->Reset();
				//GetOwner()->GetComponent<Rigidbody>()->GravityOn();
				mState = Fall;
			}
		}
		
		if (Input::GetKeyState(eKeyCode::X) == eKeyState::DOWN)
		{
			if (isHas_front_equip == false)
			{
				if (isInterctWeapon)
				{
					if (mState == Crawl || mState == Crouch)
					{
						front_equip = interact_obj;
						front_equip->GetComponent<Rigidbody>()->GravityOff();
						isHas_front_equip = true;
					}
				}
				else if (!my_whip->CoolDown())
				{
					Animator* anim = GetOwner()->GetComponent<Animator>();
					my_whip->GetOwner()->Alive();
					if (direction == LeftAhead)
					{
						anim->Play(L"LeftAttack", false);
						my_whip->SetDirection(LeftAhead);
					}
					else
					{
						anim->Play(L"RightAttack", false);
						my_whip->SetDirection(RightAhead);
					}
					my_whip->Attack();
				}
			}
			else
			{
				if (mState == Crawl || mState == Crouch)
				{
					Rigidbody* rb = front_equip->GetComponent<Rigidbody>();
					//rb->GravityOn();
					isHas_front_equip = false;
					front_equip = nullptr;
				}
				else if (front_equip->GetLayerType() == eLayerType::ShotGun)
				{
					if (front_equip->GetScript<ShotGunScript>()->Shoot())
					{
						//반동 부여
					}
				}
			}
		}

		if (Input::GetKeyState(eKeyCode::C) == eKeyState::DOWN)
		{
			RopeThrowScript* throw_script = GetOwner()->GetScript<RopeThrowScript>();
			throw_script->Throw(GetOwner()->GetComponent<Transform>()->GetPosition());
		}
#pragma endregion

	}

	void PlayerScript::ThrowBomb()
	{

	}





	void PlayerScript::FallCheck()
	{

	}
	void PlayerScript::LeftGetUpEnd()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"LeftIdle", false);
		mState = Idle;
	}
	void PlayerScript::RightGetUpEnd()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"RightIdle", false);
		mState = Idle;
	}

	void PlayerScript::AttackEnd()
	{
		isAttack = false;
	}

	void PlayerScript::CameraMove()
	{
		Vector3 camera_pos = camera_obj->GetComponent<Transform>()->GetPosition();
		Vector3 player_pos = transform->GetPosition();

		if (camera_pos.y < player_pos.y + 3.0f)
		{
			Vector3 fixed_cam_pos = Vector3(player_pos.x, camera_pos.y + 20.0f * Time::DeltaTime(), player_pos.z - 1.0f);

			camera_obj->GetComponent<Transform>()->SetPosition(fixed_cam_pos);
		}
		else
		{
			Vector3 fixed_cam_pos = Vector3(player_pos.x, camera_pos.y + 20.0f * Time::DeltaTime(), player_pos.z - 1.0f);
		}

		/*if (camera_pos.y < player_pos.y - 3.0f)
		{
			Vector3 fixed_cam_pos = Vector3(player_pos.x, camera_pos.y + 20.0f * Time::DeltaTime(), player_pos.z - 1.0f);

			camera_obj->GetComponent<Transform>()->SetPosition(fixed_cam_pos);
		}*/
	}

	void PlayerScript::EquipWeapon(GameObject* equip)
	{
		front_equip = equip;
	}

	void PlayerScript::DropWeapon()
	{
		front_equip = nullptr;
	}

	void PlayerScript::Render()
	{

	}



	//손 끝과 발 끝이라는 콜라이더를 만들어서 위로 진행하는데 손끝이 로프 끝이거나
	//발 끝이 바닥에 닿았거나

	void PlayerScript::OnCollisionEnter(Collider2D* col)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* col)
	{
		//1. 위에서 아래로 낙하 
	}
 
	void PlayerScript::OnCollisionExit(Collider2D* col)
	{
	}

	void PlayerScript::OnTriggerEnter(Collider2D* collider)
	{

	}

	void PlayerScript::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"FeetCollider")
		{
			if (col->GetName() == L"GroundCollider")
			{
				jump_count = 1;
				touch_ground_amount++;
			}
		}

		if (sender->GetName() == L"BodyCollider")
		{
			int a = 0;
			if (col->GetName() == L"CeilingCollider")
			{
				touch_ceiling_amount++;
			}
		}

		if (sender->GetName() == L"BodyCollider")
		{
			if (col->GetName() == L"LeftSideCollider")
			{
				touch_left_wall_amount++;
			}
			if (col->GetName() == L"RightSideCollider")
			{
				touch_right_wall_amount++;
			}
			//if (isGround)
			if (col->GetName() == L"ExitDoorCollider")
			{
				isExitDoor = true;
				hud->ShowButtonUI(L"AButton");
			}
			if (col->GetName() == L"GoldBarCollider")
			{
				inventory->AddMoney(500);
				result->AddMoney(500);
				col->GetOwner()->Death();
			}
			if (col->GetName() == L"PileOfGoldBarCollider")
			{
				inventory->AddMoney(1500);
				col->GetOwner()->Death();
			}
		}

		
	}

	void PlayerScript::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{
	}

	void PlayerScript::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"FeetCollider")
		{
			if (col->GetName() == L"GroundCollider")
			{
				touch_ground_amount--;
			}
		}
		if (sender->GetName() == L"BodyCollider")
		{
			if (col->GetName() == L"LeftSideCollider")
			{
				touch_left_wall_amount--;
			}
		}
		if (sender->GetName() == L"BodyCollider")
		{
			if (col->GetName() == L"RightSideCollider")
			{
				touch_right_wall_amount--;
			}
		}
		if (sender->GetName() == L"BodyCollider")
		{
			if (col->GetName() == L"ExitDoorCollider")
			{
				isExitDoor = false;
				hud->HideButtonUI(L"AButton");
			}
		}
		if (sender->GetName() == L"BodyCollider")
		{
			if (col->GetName() == L"CeilingCollider")
			{
				touch_ceiling_amount--;
			}
		}


	}
	




}