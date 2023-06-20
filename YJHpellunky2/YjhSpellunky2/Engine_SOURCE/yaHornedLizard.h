#pragma once
#pragma once
#include "yaMonster.h"
#include "yaScript.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaSceneManager.h"

namespace ya
{
	class HornedLizard : public Script
	{
		HornedLizard();
		~HornedLizard();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;


		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void ChildOnCollisionEnter(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionStay(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionExit(Collider2D* sender, Collider2D* col);

		void SetScene(Scene* _scene) { scene = _scene; }
		void SetAnimation();
		void StateChange(int change_num);
		void GetScene() { scene = SceneManager::GetPlayScene(); }

	private:

		enum State
		{
			Standby,
			Move,
			RollAttack,
			Die,
		};


		State state = State::Standby;
		Scene* scene;

		Transform* tr;
		Animator* animator;

		GameObject* head;
		GameObject* body;

		GameObject* target;

		State my_state;

		float speed;

		bool isDrop;
		bool isGround;
	};
}