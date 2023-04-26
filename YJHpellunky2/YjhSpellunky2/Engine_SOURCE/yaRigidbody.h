#pragma once

#pragma once
#include "yaComponent.h"
#include "yaGameObject.h"

using namespace ya::math;
namespace ya
{

	class Rigidbody : public Component
	{

	public:

		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


		void GravityOn() { isGravity = true; }
		void GravityOff() { isGravity = false; }
		void Gravity();
		bool GetIsGravity() { return isGravity; }
		void Reset() { velocity = 0.0f; force_power = 0.0f; }

		void AddForce(Vector2 direction);

		void KnockbackOff();
		void KnockbackOn(Vector2 _power);
		bool GetIsKnockback() { return isKnockback; }


	private:

		void Knockback();
		//�������� �ִ� �ӵ�
		//���� �پ��ִ°� �ƴѰ��� �޾ƿ;߰ڳ�
		// bool�� �̿��Ͽ� on off
		float velocity;
		float max_velocity;
		float acc;
		bool isGravity;
		float force_power;
		float max_power;

		bool isKnockback;
		Vector2 knockback_power;
	};
}