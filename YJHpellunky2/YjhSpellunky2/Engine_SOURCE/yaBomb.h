#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"
#include "yaPlayScene.h"
#include "yaParticleManager.h"
#include "yaDetector.h"
#include "yaBlock.h"

namespace ya
{
	class Bomb : public Script
	{
	public:

		Bomb();
		virtual ~Bomb();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		
		virtual void OnCollisionEnter(Collider2D* col);
		virtual void OnCollisionStay(Collider2D* col);
		virtual void OnCollisionExit(Collider2D* col);

		void SetParticleManager(ParticleManager* manager) { particle_manager = manager; }

		virtual void ChildOnCollisionEnter(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionStay(Collider2D* sender, Collider2D* col);
		virtual void ChildOnCollisionExit(Collider2D* sender, Collider2D* col);



		void SetAnimation();

		void CountDown();

		void IgniteBomb();
		void ExplodeBomb();

	private:

		Animator* animator;
		Collider2D* box_collider;

		int bomb_damage = 10;
		int fire_damage = 1;

		float fuse_burst_time = 2.8f;
		float fuse_timer;
		float explode_range = 2.0;
		
		int count;
		
		std::vector<Block*> blocks;
		
		enum State
		{
			Stanby,
			Ignite,
			Exlode
		};
		State state;
		Scene* curr_scene;
		ParticleManager* particle_manager;
	};
}
	