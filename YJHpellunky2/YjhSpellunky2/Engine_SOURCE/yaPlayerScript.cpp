#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaRenderer.h"
#include "yaGravity.h"
#include "yaWhipScript.h"
#include "yaShotGunScript.h"
#include "yaRopeThrowScript.h"

namespace ya
{
	PlayerScript::PlayerScript()
		: Script(),
		camera_obj(nullptr),
		isGround(false),
		max_jump_time(0.25f),
		jump_count(1),
		pressing_timer(0.0f),
		mState(Fall),
		curr_life(3),
		isInterctWeapon(false),
		isHas_front_equip(false)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"Idle");

		animator->GetCompleteEvent(L"LeftAttack") = std::bind(&PlayerScript::AttackEnd, this); // 후에 손에 든 물건에 따라 샷건 활 채찍 모션을 달리할것
		animator->GetCompleteEvent(L"LeftGetUP") = std::bind(&PlayerScript::LeftGetUpEnd, this);
		animator->GetCompleteEvent(L"RightGetUP") = std::bind(&PlayerScript::RightGetUpEnd, this);
	}

	void PlayerScript::Update()
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();

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



		if (!isDead)
		{
			if (camera_obj != nullptr)
			{
				if (mState != LookUp)
				{
					Vector3 cam_pos = camera_obj->GetComponent<Transform>()->GetPosition();
					Vector3 player_pos = this->GetOwner()->GetComponent<Transform>()->GetPosition();

					Vector3 fixed_cam_pos = Vector3(player_pos.x, player_pos.y, player_pos.z - 1.0f);

					camera_obj->GetComponent<Transform>()->SetPosition(fixed_cam_pos);
				}
			}
			if(isHas_front_equip)
			if (front_equip != nullptr)
			{
				Transform* tr = GetOwner()->GetComponent<Transform>();
				ShotGunScript* shotgun = front_equip->GetScript<ShotGunScript>();
				Gravity* gr = front_equip->GetComponent<Gravity>();
				gr->GravityOff();
				if (direction == LeftAhead)
				{
					front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x - 0.2f, tr->GetPosition().y - 0.25f, tr->GetPosition().z));
					if (mState == Crouch || mState == Crawl)
					{
						front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x - 0.2f, tr->GetPosition().y - 0.35f, tr->GetPosition().z));
					}
					if (front_equip->GetLayerType() == eLayerType::ShotGun)
					{
						shotgun->TurnLeft();
					}
				}
				else
				{
					front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 0.2f, tr->GetPosition().y - 0.25f, tr->GetPosition().z));
					if (mState == Crouch || mState == Crawl)
					{
						front_equip->GetComponent<Transform>()->SetPosition(Vector3(tr->GetPosition().x + 0.2f, tr->GetPosition().y - 0.35f, tr->GetPosition().z));
					}
					if (front_equip->GetLayerType() == eLayerType::ShotGun)
					{
						shotgun->TurnRight();
					}
				}
			}
		}
		InputCtrl();
	}

	void PlayerScript::InputCtrl()
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (isDead)
		{
			return;
		}


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

			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			pos.x += move_speed * Time::DeltaTime();
			tr->SetPosition(pos);
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
				Transform* tr = GetOwner()->GetComponent<Transform>();
				Vector3 pos = tr->GetPosition();
				pos.x += move_speed * Time::DeltaTime();
				tr->SetPosition(pos);
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
					if (!GetOwner()->GetComponent<Gravity>()->GetIsGravity())
					{
						GetOwner()->GetComponent<Gravity>()->GravityOn();
					}
				}
				else
				{
					Transform* tr = GetOwner()->GetComponent<Transform>();
					Vector3 pos = tr->GetPosition();
					Vector3 fixed_pos = Vector3(pos.x, pos.y -= 5.0f * Time::DeltaTime(), pos.z);
					tr->SetPosition(fixed_pos);
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

				Transform* tr = GetOwner()->GetComponent<Transform>();
				Vector3 pos = tr->GetPosition();
				Vector3 fixed_pos = Vector3(pos.x, pos.y += 5.0f * Time::DeltaTime(), pos.z);
				tr->SetPosition(fixed_pos);
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

		if (jump_count >= 1 || mState == RidingRope)
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
				jump_count--;
				mState = Jump;
			}
		}
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			if (mState == Jump)
			{
				jump_timer += Time::DeltaTime();
				GetOwner()->GetComponent<Gravity>()->AddForce(Vector2(0.0f, 10.0f));

				if (jump_timer >= max_jump_time)
				{
					jump_timer = 0;
					GetOwner()->GetComponent<Gravity>()->Reset();
					GetOwner()->GetComponent<Gravity>()->GravityOn();
					mState = Fall;
				}
			}
		}
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::UP)
		{
			if (mState == Jump)
			{
				jump_timer = 0;
				GetOwner()->GetComponent<Gravity>()->Reset();
				GetOwner()->GetComponent<Gravity>()->GravityOn();
				mState == Fall;
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
						front_equip->GetComponent<Gravity>()->GravityOff();
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
					Gravity* gr = front_equip->GetComponent<Gravity>();
					gr->GravityOn();
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
		Vector3 player_pos = GetOwner()->GetComponent<Transform>()->GetPosition();

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

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
 
	void PlayerScript::OnCollisionExit(Collider2D* col)
	{
		
	}

	void PlayerScript::OnTriggerEnter(Collider2D* collider)
	{

	}
	void PlayerScript::ReciveColEnter(eLayerType receive_layer, Collider2D* col)
	{
		if (receive_layer == eLayerType::Feet)
		{
			if (col->GetOwner()->GetLayerType() == eLayerType::Ground)
			{
				if (mState == Fall)
				{
					if (direction == LeftAhead)
					{
						Animator* animator = GetOwner()->GetComponent<Animator>();
						animator->Play(L"LeftIdle", false);
					}
					else
					{
						Animator* animator = GetOwner()->GetComponent<Animator>();
						animator->Play(L"RightIdle", false);
					}
				}
				jump_count = 1;
				mState = Idle;
				if (direction == LeftAhead)
				{
					GetOwner()->GetComponent<Animator>()->Play(L"LeftIdle",false);
				}
				else
				{
					GetOwner()->GetComponent<Animator>()->Play(L"RightIdle",false);
				}
				isGround = true;
				Gravity* gravity = GetOwner()->GetComponent<Gravity>();
				gravity->GravityOff();
			}
			if (col->GetOwner()->GetLayerType() == eLayerType::ShotGun)
			{
				isInterctWeapon = true;
				interact_obj = col->GetOwner();
			}
		}

		if (receive_layer == eLayerType::Head && col->GetOwner()->GetLayerType() == eLayerType::Rope)
		{
			isHeadHit_rope = true;
		}
		if (receive_layer == eLayerType::Feet)
		{
			isFeetHit_rope = true;
		}
	}

	void PlayerScript::ReciveColStay(eLayerType receive_layer, Collider2D* col)
	{
		if (col->GetOwner()->GetLayerType() == eLayerType::ShotGun)
		{
			isInterctWeapon = true;
			interact_obj = col->GetOwner();
		}

		if (col->GetOwner()->GetLayerType() == eLayerType::ShotGun)
		{
			isInterctWeapon = true;
			interact_obj = col->GetOwner();
		}


		if (mState != RidingRope && mState != Jump)
		{
			if (receive_layer == eLayerType::Head && col->GetOwner()->GetLayerType() == eLayerType::Rope)
			{
				if(mState != Jump)
				if (Input::GetKeyState(eKeyCode::UP) == eKeyState::DOWN || Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
				{
					Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
					Vector3 rope_pos = col->GetOwner()->GetComponent<Transform>()->GetPosition();
					GetOwner()->GetComponent<Transform>()->SetPosition(Vector3(rope_pos.x, curr_pos.y, curr_pos.z));
					Gravity* gravity = GetOwner()->GetComponent<Gravity>();
					gravity->GravityOff();
					mState = RidingRope;
				}
			}
		}
		if (receive_layer == eLayerType::Head && col->GetOwner()->GetLayerType() == eLayerType::Rope)
		{
			isHeadHit_rope = true;
		}
		if (receive_layer == eLayerType::Feet)
		{
			isFeetHit_rope = true;
		}
	}
	void PlayerScript::ReciveColExit(eLayerType receive_layer, Collider2D* col)
	{
			if (col->GetOwner()->GetLayerType() == eLayerType::Ground)
			{
				isGround = false;
				if (mState != RidingRope)
				{
					Gravity* gravity = GetOwner()->GetComponent<Gravity>();
					gravity->GravityOn();
				}
			}
			if (col->GetOwner()->GetLayerType() == eLayerType::ShotGun)
			{
				isInterctWeapon = false;
				interact_obj = nullptr;
			}

		if (receive_layer == eLayerType::Head && col->GetOwner()->GetLayerType() == eLayerType::Rope)
		{
			isHeadHit_rope = false;
		}
		if (receive_layer == eLayerType::Feet)
		{
			isFeetHit_rope = false;
		}
	}
}