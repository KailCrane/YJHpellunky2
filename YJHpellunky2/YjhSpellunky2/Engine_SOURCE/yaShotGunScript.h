#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
namespace ya
{

	class ShotGunScript : public Script
	{
	public:
		ShotGunScript();
		~ShotGunScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;
		
		void TurnLeft();
		void TurnRight();

		void SetBullet(GameObject* bullet, int num) { bullets[num] = bullet; }
		bool Shoot();

	private:
		bool isGround;

		enum Direction
		{
			Left,
			Right
		};
		Direction direction;

		float pump_delay;
		float pump_timer;
		bool isReadyToShoot;

		GameObject* bullets[100];
	};
}