#pragma once
#include "yaGameObject.h"
#include "yaCollider2D.h"

namespace ya
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void RemoveLife(int amount);

		virtual void OnCollisionEnter(Collider2D col);
		virtual void OnCollisionStay(Collider2D col);
		virtual void OnCollisionExit(Collider2D col);

		virtual void ChildOnCollisionEnter(Collider2D* Col1, Collider2D* col2);
		virtual void ChildOnCollisionStay(Collider2D* Col1, Collider2D* col2);
		virtual void ChildOnCollisionExit(Collider2D* Col1, Collider2D* col2);
	private:

		int life;
		void SetLife(int _life) { life = _life; }
	};
}

