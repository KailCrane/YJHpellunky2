#pragma once
#include "yaMonster.h"
#include "yaScript.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaGameObject.h"



namespace ya
{
	class Treasure : public Script
	{
	public:
		Treasure();
		~Treasure();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		void SetTreasure(eTreasureType _type);
	private:
		eTreasureType treasure_type;
		Transform* tr;
	};
}