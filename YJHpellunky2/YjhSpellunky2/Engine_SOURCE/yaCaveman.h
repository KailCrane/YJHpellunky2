#pragma once
#include "yaGameObject.h"
#include "yaScript.h"
#include "yaAnimator.h"

namespace ya
{
	class Caveman : public Script
	{
	public:
		Caveman();
		virtual ~Caveman();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		void ReciveColEnter(eLayerType receive_layer, Collider2D* col);
		void ReciveColStay(eLayerType receive_layer, Collider2D* col);
		void ReciveColExit(eLayerType receive_layer, Collider2D* col);

		void SetFeet(GameObject* obj) { feet = obj; }
		void SetHead(GameObject* obj) { head = obj; }
		void SetLeftBody(GameObject* obj) { left_body = obj; }
		void SetRightBody(GameObject* obj) { right_body = obj; }
		void SetLeftDetectObj(GameObject* obj) { left_detect_col = obj; }
		void SetRightDetectObj(GameObject* obj) { right_detect_col = obj; }

		void Petrol();
		void Chase();
		void Stumble();
		void Die();
		void GetBluntDamage();

		void RecoverFlint();

		enum Direction
		{
			Left,
			Right
		};
		Direction direcion;
	
	private:

		int hp;

		float walk_speed;
		float run_speed;

		float flint_recover_time;
		float flint_recover_timer;

		enum State
		{
			NoneState,
			IdleState,
			PatrolState,
			ChaseState,
			GetBluntState,
			LeftRun,
			RightRun,
			DieState,
			FlintState
		};
		State my_state;
		

		GameObject* feet;
		GameObject* head;
		GameObject* left_body;
		GameObject* right_body;
		GameObject* left_detect_col;
		GameObject* right_detect_col;
	};
};