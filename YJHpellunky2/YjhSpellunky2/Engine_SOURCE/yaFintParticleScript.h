#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaGameObject.h"

namespace ya
{
	class FintParticleScript : public Script
	{
	public:

		FintParticleScript();
		~FintParticleScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render()override;

		void SetTarget(GameObject* _target);

		void OnActive();
		void Active();

	private:
		Animator* animator;
		GameObject* target;

		float fint_timer;
		float fint_time;

		bool isActive;
	};
}
