#pragma once
#include "yaSkeleton.h"
#include "yaBat.h"
#include "yaCaveman.h"
#include "yaQuillback.h"
#include "yaSpider.h"
#include "yaMerchant.h"
#include "yaGameObject.h"
#include "yaScene.h"

namespace ya
{
	class MonsterManager : Script
	{
	public:
		MonsterManager();
		~MonsterManager();
		virtual void Initialize() override;
		void SpawnMonster(Vector3 spawn_pos, eMonsterType monsterType);


	private:

		Scene* play_scene;

		std::vector<GameObject*> skeletons;
		std::vector<GameObject*> bats;
		std::vector<GameObject*> spiders;
		std::vector<GameObject*> cavemans;
		std::vector<GameObject*> snakes;
		std::vector<GameObject*> hornlizards;
		std::vector<GameObject*> merchants; //�ִ� 3����� �����
		GameObject* quillback; //������ �ϳ� �ۿ� �ȳ���

	};
}