#pragma once
#include "yaGameObject.h"
#include "yaScript.h"
#include "yaAnimator.h"

namespace ya
{
	class SmallExplodeParticleScript : public Script
	{
	public:
		SmallExplodeParticleScript();
		~SmallExplodeParticleScript();

		virtual void Initialize()override;
		virtual void Render()override;

		void SetPoint(Vector3 _point) { point = _point; }
		void OnActive();
		void OffActive();

	private:

		Animator* animator;
		Vector3 point;
	};
}

