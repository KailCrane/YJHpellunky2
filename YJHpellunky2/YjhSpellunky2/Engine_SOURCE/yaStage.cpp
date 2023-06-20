#include "yaStage.h"
#include "yaGameObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include <iostream>
#include <fstream>
#include <string>
#include "yaSceneManager.h"
#include "yaResource.h"
#include "yaGameObject.h"
#include "yaObject.h"
#include "yaAnimator.h"
#include "yaBat.h"
#include "yaBlock.h"
#include "yaTime.h"
#include "yaBounceParticleSript.h"
#include "yaBloodParticle.h"
#include "yaFintParticleScript.h"
#include "yaShotGunParticle.h"
#include "yaBomb.h"
#include "yaSnake.h"
#include "yaPlayer.h"

using namespace std;

namespace ya

{
	Stage::Stage()
		:column(0),
		row(0),
		scene(nullptr)
	{
	}
	Stage::~Stage()
	{

	}

	void Stage::Update()
	{
		if (isGameStart)
		{
			timer += Time::DeltaTime();
			if (timer)
			{
				if (timer >= 1.0f)
				{
					sec += 1;
					if (sec >= 60)
					{
						min += 1;
						sec = 0;
					}
					timer = 0.0f;
				}
			}
		}
	}


	void Stage::LoadStage(int stage_num)
	{

		std::string line;
		ifstream file("example.txt"); // example.txt 파일을 연다. 없으면 생성. 
		ofstream outFile;
		ifstream inFile;

		int variable = 0;
		int num = 0;
		int num2 =0;
		{
			/*Monster* monster = object::Instantiate<Monster>(eLayerType::Door, scene);
			monster->SetName(L"Bat");
			monster->SetLayerType(eLayerType::Door);
			Transform* tr = monster->GetComponent<Transform>();

			tr->SetPosition(Vector3(2.0f, 1.5f, 1.1f));
			tr->SetScale(Vector3(3.0f, 3.0f, 1.2f));

			Collider2D* collider = monster->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(1.0f, 1.0f));

			SpriteRenderer* mr = monster->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"exit_Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			bat = monster->AddComponent<Bat>();
			bat->SetScene(scene);*/

			/*Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, scene);
			monster->SetName(L"Spider");
			monster->SetLayerType(eLayerType::Monster);
			Transform* tr = monster->GetComponent<Transform>();

			tr->SetPosition(Vector3(2.0f, 1.5f, 1.1f));
			tr->SetScale(Vector3(3.0f, 3.0f, 1.2f));

			monster = monster->AddComponent<Quillback>();*/


			



			/*test1->SetPoint(Vector3(1.0f,1.0f,1.1f));
			test1->OnActive();

			/*GameObject* test_particle = object::Instantiate<Monster>(eLayerType::Door, scene);
			BounceParticleSript* test1 = test_particle->AddComponent<BounceParticleSript>();
			*/
			/*test1->SetPoint(Vector3(1.0f,1.0f,1.1f));
			test1->OnActive();*/

			Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, scene);
			monster->SetName(L"Quilback");
			monster->SetLayerType(eLayerType::Monster);
			Transform* tr = monster->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.1f));
			quilback = monster->AddComponent<Quillback>();

			quilback->SetStartPoint(Vector2(1.0f, 3.0f));
			{
				GameObject* gold = object::Instantiate<GameObject>(eLayerType::Item, scene);
				gold->SetName(L"Gold");
				gold->SetLayerType(eLayerType::Item);
				Transform* tr = gold->GetComponent<Transform>();
				tr->SetPosition(Vector3(2.0f, 3.0f, 1.1f));
				tr->SetScale(Vector3(1.0f, 1.0f, 1.1f));
				Treasure* gold_script = gold->AddComponent<Treasure>();
				gold_script->SetTreasure(eTreasureType::eGoldBar);
			}

			

			/*GameObject* test_particle = object::Instantiate<GameObject>(eLayerType::Particle, scene);
			ShotGunParticle* test1 = test_particle->AddComponent<ShotGunParticle>();

			test_particle->Death();
			test1->SetPoint(Vector3(1.0f, 1.0f, 1.1f));
			test1->SetDirection(0);
			test1->OnActive();*/

			/*GameObject* test_particle = object::Instantiate<GameObject>(eLayerType::Particle, scene);
			FintParticleScript* test1 = test_particle->AddComponent<FintParticleScript>();

			test_particle->Death();
			test1->SetTarget(monster);
			test1->OnActive();*/

			


			

			{
				GameObject* bomb = object::Instantiate<GameObject>(eLayerType::Item, scene);
				bomb->SetName(L"Bomb");
				bomb->SetLayerType(eLayerType::Item);
				Transform* tr = bomb->GetComponent<Transform>();
				tr->SetPosition(Vector3(3.0f, 3.0f, 1.2f));
				tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
				Bomb* bomb_script = bomb->AddComponent<Bomb>();
				//gold_script->SetTreasure(TreasureType::eGoldBar);
			}

		}
		/*GameObject* exit_door = object::Instantiate<GameObject>(eLayerType::Door, scene);
		exit_door->SetName(L"ExitDoor");
		exit_door->SetLayerType(eLayerType::Door);
		Transform* tr = exit_door->GetComponent<Transform>();

		tr->SetPosition(Vector3(2.0f, 1.5f, 1.1f));
		tr->SetScale(Vector3(3.0f, 3.0f, 1.2f));

		Collider2D* collider = exit_door->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(1.0f, 1.0f));

		SpriteRenderer* mr = exit_door->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"exit_Material");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);*/

				//AddBlock(scene, 2);

		if (stage_num == 0)
		{

		}
		if (stage_num == 1)
		{
			inFile.open("../Resources/Stage2.txt");
		}

		if (stage_num == 2)
		{
			inFile.open("../Resources/Stage3.txt");
		}


		inFile.open("../Resources/Stage1.txt");
		if (inFile.is_open() == false) {

			cout << "Unable to openthe file" << endl;
		}
		else
		{
			while (inFile >> variable)
			{
				cout << "variable" << endl;

				if (row == 0)
				{
					row = variable;
					num++;
					continue;
				}
				if (column == 0)
				{
					column = variable;
					for (int i = 0; i < column; i++)
					{
						std::vector<int> rows;
						std::vector<GameObject*> rowdata;
						map_column.push_back(rows);
						map_data.push_back(rowdata);
					}
					num++;
					continue;
				}

				if (num < 2) // 0 1번은 현재 준비가 안되어 있음 row와 Column의 번호
				{
					num++;
					continue;
				}

				if (num2 < row)
				{
					map_column[0].push_back(variable);
				}
				else
				{
					map_column[num2 / row].push_back(variable);
				}
				num2++;
			}

			PlaceStage();

			{
				Monster* monster = object::Instantiate<Monster>(eLayerType::Monster, scene);
				monster->SetName(L"Snake");
				monster->SetLayerType(eLayerType::Monster);
				Transform* tr = monster->GetComponent<Transform>();
				tr->SetScale(Vector3(3.0f, 3.0f, 1.2f));

				SpriteRenderer* mr = monster->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpiderMaterial");
				mr->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->SetMesh(mesh);

				Snake* snake_script = monster->AddComponent<Snake>();
				snake_script->SetPos(Vector3(9.0f, -6.3f, 1.1f));
				snake_script->SetParticleManager(pManager);
			}


			{
				GameObject* entrance_door = object::Instantiate<GameObject>(eLayerType::ExitDoor, scene);
				entrance_door->SetName(L"EntranceDoor");
				entrance_door->SetLayerType(eLayerType::ExitDoor);

				Transform* tr = entrance_door->GetComponent<Transform>();
				tr->SetPosition(Vector3(6.0f, -2.9f, 1.3f));
				tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

				SpriteRenderer* mr = entrance_door->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> material = Resources::Find<Material>(L"EntranceDoorMaterial");
				mr->SetMaterial(material);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->SetMesh(mesh);

				stage1_objs.push_back(entrance_door);
				//player->GetComponent<Transform>()->SetPosition(Vector3(6.0f, -2.9f, 1.1f));
			}

			{
				GameObject* exit_door = object::Instantiate<GameObject>(eLayerType::ExitDoor, scene);
				exit_door->SetName(L"ExitDoor");
				exit_door->SetLayerType(eLayerType::ExitDoor);

				Transform* tr = exit_door->GetComponent<Transform>();
				tr->SetPosition(Vector3(15.0f, -14.9f, 1.3f));
				tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

				SpriteRenderer* mr = exit_door->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> material = Resources::Find<Material>(L"ExitDoorMaterial");
				mr->SetMaterial(material);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->SetMesh(mesh);
				Collider2D* col = exit_door->AddComponent<Collider2D>();
				col->SetType(eColliderType::Rect);
				col->SetSize(Vector2(0.1f, 0.4f));
				col->SetName(L"ExitDoorCollider");

				stage1_objs.push_back(exit_door);
			}
		}
	}



	void Stage::PlaceStage()
	{
		for (int i =0;i<map_column.size(); i++)
		{
			int a = i;

			for (int e = 0; e < map_column[i].size(); e++)
			{
				if (map_column[i][e] == 0)
				{
					map_data[i].push_back(nullptr);

					continue;
				}
				GameObject* spawn_block = AddBlock(scene, map_column[i][e]);
				Transform* block_tr = spawn_block->GetComponent<Transform>();
				block_tr->SetPosition(Vector3(1.0 * e, -1.0 * i, 1.2f));
				Block* block_script = spawn_block->GetScript<Block>();
				block_script->MakeBorders();
				map_data[i].push_back(spawn_block);
				stage1_objs.push_back(spawn_block);
				if (i == 17)
				{
					if(e == 39)
					int a = 0;
				}
				//spawn_block->Death();
			}
		}
		BorderSort();
	}

	void Stage::BorderSort()
	{
		for (int i = 0; i < map_data.size(); i++)
		{
			for (int e = 0; e < map_data[i].size(); e++)
			{

#pragma region "왼쪽 블록 확인"

				if (map_data[i][e] == nullptr )
				{
					continue;
				}
				else if(map_data[i][e]->IsDead())
				{
					continue;
				}

				if (e == 0)
				{
					map_data[i][e]->GetScript<Block>()->SetEdge(2); //제일 왼쪽
				}

				if (e > 0)
				{
					if (map_data[i][e - 1] == nullptr) //왼쪽 확인 
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(2); //제일 왼쪽
					}
					else if (map_data[i][e - 1] != nullptr)
					{
						if (map_data[i][e - 1]->IsDead())
						{
							map_data[i][e]->GetScript<Block>()->SetEdge(2); //제일 왼쪽
						}
						else
						{

							switch (map_data[i][e - 1]->GetScript<Block>()->GetBlockType())
							{
							case eBlockType::Dirt:
								map_data[i][e]->GetScript<Block>()->ReleaseEdge(2);
								break;
							case eBlockType::Wood:
								map_data[i][e]->GetScript<Block>()->ReleaseEdge(2);
								break;
								//제일 왼쪽
							}
						}
					}
				}
#pragma endregion

#pragma region "오른쪽 블록 확인"

				if (e == map_data[i].size() -1) //가장 오른쪽
				{
					map_data[i][e]->GetScript<Block>()->SetEdge(3);
				}

				if (e < map_data[i].size() -1)
				{
					if (map_data[i][e + 1] == nullptr)//오른쪽 확인 
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(3);
					}
					else if (map_data[i][e + 1]->IsDead())
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(3);
					}
					else if (map_data[i][e + 1] != nullptr && !map_data[i][e + 1]->IsDead())
					{
						switch (map_data[i][e + 1]->GetScript<Block>()->GetBlockType())
						{
						case eBlockType::Dirt:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(3);
							break;
						case eBlockType::Wood:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(3);
							break;
							//오른쪽
						}
					}
				}
#pragma endregion

#pragma region "위 블럭 체크"

				if (i == 0) //가장 위쪽
				{
					map_data[i][e]->GetScript<Block>()->SetEdge(0);
				}

				if (i > 0)
				{
					if (map_data[i - 1][e] == nullptr) //위 확인
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(0);
					}
					else if (map_data[i - 1][e]->IsDead())
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(0);
					}
					else if (map_data[i - 1][e] != nullptr && !map_data[i - 1][e]->IsDead())
					{
						switch (map_data[i - 1][e]->GetScript<Block>()->GetBlockType())
						{
						case eBlockType::Dirt:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(0);
							break;
						case eBlockType::Wood:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(0);
							break;
							//오른쪽
						}
					}
				}
#pragma endregion

#pragma region  "아래 블록 체크"
				if (i == map_data.size()-1)
				{
					map_data[i][e]->GetScript<Block>()->SetEdge(1);
				}
				if (i < map_data.size()-2)
				{
					if (map_data[i + 1][e] == nullptr) //아래 확인
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(1);
					}
					else if (map_data[i + 1][e]->IsDead())
					{
						map_data[i][e]->GetScript<Block>()->SetEdge(1);
					}
					else if (map_data[i + 1][e] != nullptr && !map_data[i + 1][e]->IsDead())
					{
						switch (map_data[i + 1][e]->GetScript<Block>()->GetBlockType())
						{
						case eBlockType::Dirt:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(1);
							break;
						case eBlockType::Wood:
							map_data[i][e]->GetScript<Block>()->ReleaseEdge(1);
							break;
						}
					}
				}
#pragma endregion
			}
		}
	}

	GameObject* Stage::AddBlock(Scene* scene, int block_num)
	{
		if (block_num == 0)
		{
			return nullptr;
		}

		GameObject* block = object::Instantiate<GameObject>(eLayerType::Tile, scene);
		block->SetLayerType(eLayerType::Tile);
		Transform* tr = block->GetComponent<Transform>();
		tr->SetScale(Vector3(1, 1, 1));

		SpriteRenderer* mr = block->AddComponent<SpriteRenderer>();

		std::shared_ptr<Material> mateiral;

		Block* block_script = block->AddComponent<Block>();

		if (block_num >= 0 && block_num <= 28)
		{
			mateiral = Resources::Find<Material>(L"DirtMaterial" + std::to_wstring(block_num));
			block->SetName(L"Dirt" + std::to_wstring(block_num));
			
			if (mateiral == nullptr)
			{
				int a = 2;
			}
			block_script->SetType(eBlockType::Dirt);
		}

		if (block_num >= 29 && block_num <= 75)
		{
			mateiral = Resources::Find<Material>(L"WoodTileMaterial" + std::to_wstring(block_num - 28));
			block->SetName(L"WoodTileMaterial" + std::to_wstring(block_num - 31));
			if (mateiral == nullptr)
			{
				int a = 2;
			}
			block_script->SetType(eBlockType::Wood);
		}

		if (block_num == 76)
		{
			mateiral = Resources::Find<Material>(L"ObsidianMaterial");
			block->SetName(L"Obsidian");
			if (mateiral == nullptr)
			{
				int a = 2;
			}
			block_script->SetType(eBlockType::Stone);
		}


		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		return block;
	}
	
	void Stage::Reset()
	{
		min = 0;
		sec = 0;
		timer = 0.0f;
	}
}
	
