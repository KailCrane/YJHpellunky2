#pragma once
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class WhipScript : public Script
	{
	public:
		WhipScript();
		virtual ~WhipScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		void SetPlayer(GameObject* obj) { player_obj = obj; }


		void Attack();
		void WhipFirst();
		void WhipSecond();
		void WhipThird();
		void WhipEnd();
		bool CoolDown() { return isCooldown; }

		void SetDirection(int a) {
			if (a == 0)
			{
				direction = Left;
			}
			else
			{
				direction = RIght;
			}
		};

		enum Sequence
		{
			Standby,
			First,
			Second,
			Third
		};
		Sequence sequence;

	private:
		bool isCooldown;
		Vector2 curr_whip_pos;
		Vector2 whip_pos_array[3];
		GameObject* player_obj;

		enum Direction
		{
			Left,
			RIght
		};
		Direction direction;
	};

}