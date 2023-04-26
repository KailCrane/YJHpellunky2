#include "yaShotGunScript.h"
#include "yaTime.h"
#include "yaGravity.h"
#include "yaBulletScript.h"

namespace ya
{
	
	ShotGunScript::ShotGunScript()
	{
	}
	ShotGunScript::~ShotGunScript()
	{
	}
	void ShotGunScript::Initialize()
	{

	}
	void ShotGunScript::Update()
	{
		if (!isReadyToShoot)
		{
			if (pump_timer > 0)
			{
				pump_timer -= Time::DeltaTime();
			}
			if (pump_timer <= 0)
			{
				isReadyToShoot = true;
			}
		}
	}
	void ShotGunScript::FixedUpdate()
	{
	}
	void ShotGunScript::Render()
	{
	}

	bool ShotGunScript::Shoot()
	{
		if (!isReadyToShoot)
		{
			return false;
		}
		else
		{
			true;
		}
		int active_mount = 0;
		for (int i = 0; i < 100; i++)
		{
			if (active_mount >= 5)
			{
				continue;
			}
			if (bullets[i]->IsDead())
			{

				bullets[i]->Alive();
				Vector3 curr_fire_pos = GetOwner()->GetComponent<Transform>()->GetPosition();

				if (direction == Left)
				{

					bullets[i]->GetScript<BulletScript>()->SetDir(Vector2(-12, 0.2f - 0.1 * active_mount));
					bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(curr_fire_pos.x - 0.4f, curr_fire_pos.y, curr_fire_pos.z));
				}
				else
				{
					bullets[i]->GetScript<BulletScript>()->SetDir(Vector2(12, 0.2f - 0.1 * active_mount));
					bullets[i]->GetComponent<Transform>()->SetPosition(Vector3(curr_fire_pos.x + 0.4f, curr_fire_pos.y, curr_fire_pos.z));
				}
				active_mount++;
			}
		}
		isReadyToShoot = false;
		pump_timer = 1.5f;
	}


	void ShotGunScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			this->GetOwner()->GetComponent<Gravity>()->GravityOff();
		}
	}
	void ShotGunScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ShotGunScript::OnCollisionExit(Collider2D* collider)
	{
		if (collider->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			this->GetOwner()->GetComponent<Gravity>()->GravityOn();
		}
	}
	void ShotGunScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ShotGunScript::TurnLeft()
	{
		direction = Left;
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"IdleL",false);
	}
	void ShotGunScript::TurnRight()
	{
		direction = Right; 
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"IdleR", false);
	}
}