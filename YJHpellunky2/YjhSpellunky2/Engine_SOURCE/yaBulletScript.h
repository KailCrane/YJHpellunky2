#pragma once
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		~BulletScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		void SetDir(Vector2 dir) {flow_dir = dir ; }
		void Flow();

	private:
		Vector2 flow_dir;
		float power;

	};
}



	

	

	

		

