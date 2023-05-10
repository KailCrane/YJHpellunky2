#pragma once
#include "yaItem.h"
#include "yaScript.h"
#include "yaGameObject.h"

namespace ya
{
	class Arrows : public Script
	{
	public:
		Arrows();
		~Arrows();
		
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* col);
		virtual void OnCollisionStay(Collider2D* col);
		virtual void OnCollisionExit(Collider2D* col);

		void Broke();
		void Flying();
		void Throw();
		void Bound();
		void Stuck();

	private:

		int damage;

		enum Variant
		{
			Stone,
			Metal
		};

		float stuck_time = 3.0f;
		float stuck_timer;
	};
}