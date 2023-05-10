#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaCollider2D.h"
#include "yaPlayScene.h"

namespace ya
{
	class Bomb : public GameObject
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

		void SetScene(PlayScene* _scene) { pScene = _scene; }

		void IgniteBomb();
		void ExplodeBomb();

	private:

		Animator* animator;
		Collider2D* box_collider;
		
		enum Direction
		{
			Left,
			Right
		};
		Direction direction;

		int bomb_damage = 10;
		int fire_damage = 1;

		float fuse_burst_time = 2.8f;
		float fuse_timer;
		float explode_range = 2.0;
		
		enum State
		{
			Stanby,
			Ignite,
			Exlode
		};
		State state;
		const std::wstring& Blink = L"";

		PlayScene* pScene;
	};
}
	