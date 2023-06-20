#pragma once
#include "yaGameObject.h"

namespace ya
{
	class BloodParticle : public Script
	{
	public:
		BloodParticle();
		~BloodParticle();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render()override;

		void SetPoint(Vector3 point);
		void SetPower(Vector3 power) { splash_power = power; }
		void OnActive();
		void Active();

	private:
		Vector3 init_scale;
		Vector3 splash_power;
		bool isActive;
		float drop_limit;
		float drop_speed;
		float decrease_speed;
		float decrease_limit;
	};

}