#pragma once
#include "yaScript.h"
#include "yaRope.h"

namespace ya
{
	class RopeThrowScript : public Script 
	{

	public:
		RopeThrowScript();
		~RopeThrowScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;


		void SetRopeDummy(Rope* rope, int num) { rope_dummy[num] = rope; }

		void Throw(Vector3 pos);

	private:

		Rope* rope_dummy[100];
		Rope* prev_allot;
	};
}

