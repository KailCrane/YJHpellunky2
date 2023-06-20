#pragma once
#include "yaMonster.h"
#include "yaScript.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaGameObject.h"

namespace ya
{
	class Quillback : public Script
	{
	public:
		Quillback();
		~Quillback();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void Petrol();
		void Jump();
		void RollAttack();
		bool CheckDistanceWithTarget();
		void TurnEnd();

		void PrepareJump();


		float GetDistance(Vector3 a, Vector3 b)
		{
			float X = a.x - b.x;
			float Y = a.y - b.y;

			float R = sqrtf(pow(X, 2) + pow(Y, 2));

			return R;
		}
#pragma region "�ݶ��̴�"
		
		virtual void ChildOnCollisionEnter(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionStay(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionExit(Collider2D* sender, Collider2D* col);

#pragma endregion
		void Land();
		void Rush();
		void SetAnimation();
		void SetStartPoint(Vector2 _start_pos) {starting_point = _start_pos;}
		
		void StateChange(int change_num);
		void GetScene() { curr_scene = SceneManager::GetPlayScene(); }
	private:

		Transform* tr;
		Animator* animator;

		GameObject* head;
		GameObject* body;
		GameObject* feet;
		GameObject* detector;

		Scene* curr_scene;
		GameObject* target;

		Vector2 jump_power;
		Vector2 curr_jump_power;

		float jump_decrease;
		float decrease_limit;

		bool isGround;
		int ground_count;

#pragma region "��Ʈ�� ���� ����"
		float walk_speed;
		float petrol_range;

		Vector2 starting_point; // �̰��� �������� �ɾ�� range���� ��ȯ �õ�
#pragma endregion

		enum Direction
		{
			Left,
			Right
		};
		Direction my_direction;
		

		enum MyState
		{
			mStandby,
			mPetrol,
			mTurn,
			mPrepareJump,
			mJump,
			mRollAttack,
			mRush,
			mLand,
			mDead,
		};
		MyState state;
	};
}