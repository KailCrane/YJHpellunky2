#pragma once
#include "yaScene.h"
#include "yaMonster.h"
#include "yaDetector.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"
#include "yaMonster.h"

namespace ya
{
	class Skeleton : public Script
	{
	public:
		Skeleton();
		virtual ~Skeleton();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;


		void SetScene(Scene* _scene) {scene = _scene; }
		void SetAnimation();
		void SetPlayer();
		void Camouflage();
		void JumpOut();
		void PlayerChase();
		void Dead();


		virtual void OnCollisionEnter(Collider2D col);
		virtual void OnCollisionStay(Collider2D col);
		virtual void OnCollisionExit(Collider2D col);

		virtual void ChildOnCollisionEnter(Collider2D* Col1, Collider2D* col2) override;
		virtual void ChildOnCollisionStay(Collider2D* Col1, Collider2D* col2) override;
		virtual void ChildOnCollisionExit(Collider2D* Col1, Collider2D* col2) override;

	private:
		enum State
		{
			Stanby,
			StandUp,
			Chase,
		};
		State state;
		GameObject* head_obj;
		GameObject* body;
		GameObject* detect_col;
		Scene* scene;

		Transform* tr;
		Animator* animator;

		int camouflage_sequence;
		int jumpout_sequence;
		Player* player;

		float move_speed = 0.0f;

	};
}
