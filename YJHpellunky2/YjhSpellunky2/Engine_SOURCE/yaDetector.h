#pragma once
#include "yaGameObject.h"
#include "yaMonster.h"
#include "yaCollider2D.h"

namespace ya
{
	class Detector : public Script
	{
	public:

		Detector();
		~Detector();
		
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void SetMonster(Monster* _target) { monster = _target; }
		void SetSender(Script* _script) { sender = _script; }
		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);
		

		Collider2D* col;
	private:
		Monster* monster;
		Script* sender;
	};
}