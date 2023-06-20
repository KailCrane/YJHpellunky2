#pragma once
#include "yaMonster.h"
#include "yaScript.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaSceneManager.h"

namespace ya
{
	class Spider : public Script
	{
	public:
		Spider();
		~Spider();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void Drop();
		void Jump();
		void ChaseTarget();

		void ReadyToJump();
		void JumpToPlayer();

		void RenderSet();


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
			Chase,
			Die,
		};


		State state;
		Scene* scene;

		Transform* tr;
		Animator* animator;

		GameObject* detector;
		GameObject* head;
		GameObject* body;

		GameObject* target;

		State my_state;

		float speed;

		float jump_speed_x;
		float jump_speed_y;

		int jump_before_count;

		bool isJump;
		bool isDrop;
		bool isGround;
	};
}