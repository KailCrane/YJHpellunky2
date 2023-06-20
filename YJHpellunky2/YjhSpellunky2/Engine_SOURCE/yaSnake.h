#pragma once
#include "yaMonster.h"
#include "yaScript.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaSceneManager.h"
#include "yaParticleManager.h"

namespace ya
{

	class Snake : public Script
	{
	public:
		Snake();
		~Snake();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void SetPos(Vector3 point);
		void SetAnimation();
		void SetParticleManager(ParticleManager* _pManager) { pManager = _pManager; }

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void ChildOnCollisionEnter(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionStay(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionExit(Collider2D* sender, Collider2D* col);

		void Petrol();
		void Attack();
		void Standby();
		void Turn();

		void StateChange(int change_num);
		void GetScene() { scene = SceneManager::GetPlayScene(); }

	private:

		enum State
		{
			eStandby,
			ePetrol,
			eAttack,
			eDie,
		};

		State state;

		enum Direction
		{
			Left,
			Right,
		};
		Direction direction;

		Scene* scene;
		ParticleManager* pManager;


		Animator* animator;
		Transform* tr;

		int ground_count;

		float petrol_time;
		float petrol_timer;

		float standby_time;
		float standby_timer;

		GameObject* head;
		GameObject* body;

		GameObject* target;

		State my_state;

		float speed;

		bool isDrop;
		bool isGround;
	};
}