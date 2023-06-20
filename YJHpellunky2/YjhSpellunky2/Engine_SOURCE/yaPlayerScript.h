#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
#include "yaWhip.h"
#include "yaWhipScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaGameHud.h"
#include "yaInventory.h"
#include "yaParticleManager.h"
#include "yaStageResult.h"

using namespace std;

namespace ya
{
	class GameHud;
	class Inventory;
	class Stage;
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		virtual void ChildOnCollisionEnter(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionStay(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionExit(Collider2D* sender, Collider2D* col);

		void SetHud(GameHud * _hud) { hud =_hud; }
		void SetResult(StageResult* _result) { result = _result; }
		void SetAnimation();

		void SetInventory(Inventory* _inventory) { inventory = _inventory; }
		void SetParticleManager(ParticleManager* _manager) { particle = _manager; }
		//void SetStage(Stage* _stage) { stage = _stage; }
		void SetCamera(GameObject* obj) { camera_obj = obj; }
		void SetWhip(WhipScript* obj){ my_whip = obj; }

		void LeftGetUpEnd();
		void RightGetUpEnd();

		void AttackEnd();

		void ThrowBomb();
		//void Equip();
		//void RideCtrl ();

		void FallCheck();

		void LifeUp() {curr_life ++;}
		void LifeDown(){curr_life--; }

		void InputCtrl();

		void CameraMove();

		void EquipWeapon(GameObject* equip);
		void DropWeapon();

		int GetLifeAmount() { return curr_life; }

		Vector3 prev_pos;
		Vector3 curr_pos;

	private:

		Scene* curr_scene;

		Transform* transform;
		Animator* animator;

		GameObject* camera_obj;

		int touch_ground_amount;
		int touch_ceiling_amount;
		int touch_left_wall_amount;
		int touch_right_wall_amount;

		float falling_speed;
		float falling_limit;

		bool isExitDoor;

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
			RidingRope,
			Knockback,
			Die
		};
		CharacterState mState;
		enum CharacterDircetion
		{
			LeftAhead,
			RightAhead
		};
		CharacterDircetion direction;
		enum CharacterHealthState
		{
			Nomal,
			Addicted,
			Curse,
		};
		CharacterHealthState healthState;

		bool isCtrlAble;

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

		GameObject* feet;
		Detector* feet_detector;
		GameObject* head;
		Detector* head_detector;
		GameObject* body;
		Detector* body_detector;

		bool isHeadHit_rope;
		bool isFeetHit_rope;

		WhipScript* my_whip;

		bool isInivisible;

		GameHud* hud;
		StageResult* result;
		Inventory* inventory;
		ParticleManager* particle;
		///StatusEffect
	};
}

