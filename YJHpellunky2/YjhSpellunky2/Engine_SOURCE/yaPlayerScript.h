#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
#include "yaWhip.h"
#include "yaWhipScript.h"

namespace ya
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		void ReciveColEnter(eLayerType receive_layer, Collider2D* col);
		void ReciveColStay(eLayerType receive_layer, Collider2D* col);
		void ReciveColExit(eLayerType receive_layer, Collider2D* col);

		void SetCamera(GameObject* obj) { camera_obj = obj; }
		void SetFeet(GameObject* obj) { feet = obj; }
		void SetHead(GameObject* obj) { head = obj; }
		void SetLeftBody(GameObject* obj) { left_body = obj; }
		void SetRightBody(GameObject* obj) { right_body = obj; }
		void SetWhip(WhipScript* obj){ my_whip = obj; }


		void LeftGetUpEnd();
		void RightGetUpEnd();

		void AttackEnd();

		void ThrowBomb();
		//void Equip();
		//void RideCtrl ();

		void FallCheck();

		void SetBombs(GameObject* _bombs[]) {
			for (int i = 0; i > 100; i++)
			{
				_bombs[i] = bombs[i];
			};
		}

		void LifeUp() {curr_life ++;}
		void LifeDown(){curr_life--; }

		void InputCtrl();

		void CameraMove();

		void EquipWeapon(GameObject* equip);
		void DropWeapon();
		

	private:

			
		GameObject* camera_obj;


		enum CharacterState
		{
			Idle,
			Walk,
			Crouch,
			Crawl,
			LookUp,
			Jump,
			Fall,
			JumpAttack,
			StandAtack,
			GetUp,
			RidingRope
		};

		enum CharacterDircetion
		{
			LeftAhead,
			RightAhead
		};

		CharacterDircetion direction;
		CharacterState mState;

		enum CharacterHealthState
		{
			Nomal,
			Addicted,
			Curse,
		};
		CharacterHealthState healthState;



		bool ControllAble;
		int curr_life;

		float move_speed;

		int jump_count;
		float pressing_timer;


		bool isAttack;
		bool isMove;
		bool isDead;

		bool isGround;
		bool isFall;
		float jump_timer;
		float max_jump_time;


		GameObject* front_equip;
		GameObject* back_equip;
		GameObject* interact_obj;
		bool isHas_front_equip;
		bool isInterctWeapon;

		GameObject* bombs[100];

		GameObject* feet;
		GameObject* head;

		bool isHeadHit_rope;
		bool isFeetHit_rope;


		GameObject* left_body;
		GameObject* right_body;
		
		WhipScript* my_whip;


		///KnockBack
		float knoback_recover_time;
		float knoback_timer;

		///StatusEffect
	};
}
