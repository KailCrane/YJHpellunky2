#pragma once
#include "yaComponent.h"
#include "yaCollider2D.h"

namespace ya
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		virtual void ChildOnCollisionEnter(Collider2D* Col1, Collider2D* col2) {};
		virtual void ChildOnCollisionStay(Collider2D* Col1, Collider2D* col2) {};
		virtual void ChildOnCollisionExit(Collider2D* Col1, Collider2D* col2) {};

	private:
		//std::vector<Script*> mScripts;
	};
}
