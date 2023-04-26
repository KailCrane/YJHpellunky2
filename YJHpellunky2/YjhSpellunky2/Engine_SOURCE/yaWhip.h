#pragma once
#include "yaScript.h"
#include "yaCollider2D.h"
#include "yaGameObject.h"
namespace ya
{
	class Whip : public GameObject
	{
	public:

		Whip();
		virtual ~Whip();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
	private:
		
	};
}

