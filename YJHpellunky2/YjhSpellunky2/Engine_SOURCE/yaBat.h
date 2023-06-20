#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaDetector.h"
#include "yaScene.h"
#include "yaMonster.h"
#include "yaGameObject.h"

namespace ya
{
	class Bat : public Script
	{
	public:
		Bat();
		~Bat();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void ChaseTarget();



		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void ChildOnCollisionEnter(Collider2D* sender,Collider2D* col) ;
		virtual void ChildOnCollisionStay(Collider2D* sender,Collider2D* col) ;
		virtual void ChildOnCollisionExit(Collider2D* sender,Collider2D* col) ;

		void SetScene(Scene* _scene) { scene = _scene; }
		void SetAnimation();
		void SetPlayer(GameObject* _target) { target = _target; }
		void StateChange(int change_num);

		
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
	};
}
