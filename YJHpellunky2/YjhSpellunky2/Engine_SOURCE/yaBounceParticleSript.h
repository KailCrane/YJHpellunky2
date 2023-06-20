#pragma once
#include "yaGameObject.h"
#include "yaScript.h"

namespace ya
{
	class BounceParticleSript : public Script
	{
	public:
		BounceParticleSript();
		~BounceParticleSript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render()override;

		void SetPoint(Vector3 point);
		void OnActive();

	private:
		void Active();
		
		GameObject* ring;
		std::vector<GameObject*> stars;

		Vector3 start_point;

		Vector3 init_ring_size;
		
		float ring_grow_speed;
		float ring_move_speed;

		bool isActive;
		float disapear_time;
		float curr_time;
	};
}