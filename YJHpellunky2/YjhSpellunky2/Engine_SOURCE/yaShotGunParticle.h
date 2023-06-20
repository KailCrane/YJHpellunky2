#pragma once
#include "yaGameObject.h"
#include "yaScript.h"
#include "yaAnimator.h"

namespace ya
{
	class ShotGunParticle : public Script
	{
	public:
		ShotGunParticle();
		~ShotGunParticle();

		virtual void Initialize()override;
		virtual void Render()override;

		void SetPoint(Vector3 _point) { point = _point; }
		void SetDirection(int _direction) { direction = _direction; }
		void OnActive();
		void OffActive();

	private:

		Vector3 point;
		int direction;
		Animator* animator;
	};
}
