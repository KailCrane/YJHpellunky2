#include "yaMonsterManager.h"
#include "yaObject.h"

namespace ya
{
	MonsterManager::MonsterManager()
	{

	}
	MonsterManager::~MonsterManager()
	{

	}
	void MonsterManager::Initialize()
	{
		play_scene = SceneManager::GetPlayScene();

		for (int i = 0; i < 10; i++)
		{
			GameObject* bat = object::Instantiate<GameObject>(eLayerType::Monster, play_scene);
			bat->AddComponent<Bat>();
			bat->Death();
			bats.push_back(bat);
		}

		for (int i = 0; i < 10; i++)
		{
			GameObject* spider = object::Instantiate<GameObject>(eLayerType::Monster, play_scene);
			spider->AddComponent<Spider>();
			spider->Death();
			spiders.push_back(spider);
		}

		for (int i = 0; i < 10; i++)
		{
			GameObject* skeleton = object::Instantiate<GameObject>(eLayerType::Monster, play_scene);
			skeleton->AddComponent<Skeleton>();
			skeleton->Death();
			skeletons.push_back(skeleton);
		}
		for (int i = 0; i < 10; i++)
		{
			GameObject* caveman = object::Instantiate<GameObject>(eLayerType::Monster, play_scene);
			caveman->AddComponent<Caveman>();
			caveman->Death();
			cavemans.push_back(caveman);
		}
		quillback = object::Instantiate<GameObject>(eLayerType::Monster, play_scene);
		quillback->AddComponent<Quillback>();
		quillback->Death();

	}
	void MonsterManager::SpawnMonster(Vector3 spawn_pos, eMonsterType monsterType)
	{
		switch (monsterType)
		{
		case eMonsterType::eSkeleton:
			for (int i = 0; i < skeletons.size(); i++)
			{
				if (skeletons[i]->IsDead())
				{
					skeletons[i]->Alive();
					skeletons[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eBat:
			for (int i = 0; i < bats.size(); i++)
			{
				if (bats[i]->IsDead())
				{
					bats[i]->Alive();
					bats[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eCaveman:
			for (int i = 0; i < cavemans.size(); i++)
			{
				if (cavemans[i]->IsDead())
				{
					cavemans[i]->Alive();
					cavemans[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eSpider:
			for (int i = 0; i < spiders.size(); i++)
			{
				if (spiders[i]->IsDead())
				{
					spiders[i]->Alive();
					spiders[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eSnake:
			for (int i = 0; i < snakes.size(); i++)
			{
				if (snakes[i]->IsDead())
				{
					snakes[i]->Alive();
					snakes[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eHornlizard:
			for (int i = 0; i < hornlizards.size(); i++)
			{
				if (hornlizards[i]->IsDead())
				{
					hornlizards[i]->Alive();
					hornlizards[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eMerchant:
			for (int i = 0; i < merchants.size(); i++)
			{
				if (merchants[i]->IsDead())
				{
					merchants[i]->Alive();
					merchants[i]->GetComponent<Transform>()->SetPosition(spawn_pos);
					return;
				}
			}
			break;
		case eMonsterType::eQuillback:
			quillback->Alive();
			quillback->GetComponent<Transform>()->SetPosition(spawn_pos);
			return;
		}
	}
}