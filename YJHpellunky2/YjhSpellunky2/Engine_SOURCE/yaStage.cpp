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

	void Stage::LoadStage(int stage_num)
	{
		std::string line;
		ifstream file("example.txt"); // example.txt 파일을 연다. 없으면 생성. 
		ofstream outFile;
		ifstream inFile;

		int variable = 0;
		int num = 0;

		std::shared_ptr<Texture> floor_cave = Resources::Load<Texture>(L"floor_cave", L"floor_cave.png");

		GameObject* exit_door = object::Instantiate<GameObject>(eLayerType::Door, scene);
		exit_door->SetName(L"ExitDoor");
		exit_door->SetLayerType(eLayerType::Door);
		Transform* tr = exit_door->GetComponent<Transform>();

		tr->SetPosition(Vector3(2.0f, 1.5f, 1.1f));
		tr->SetScale(Vector3(3.0f, 3.0f, 1.2f));

		Collider2D* collider = exit_door->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(1.1f, 1.1f));

		SpriteRenderer* mr = exit_door->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"exit_Material");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

				//AddBlock(scene, 2);
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
					continue;
				}
				if (column == 0)
				{
					column = variable;
					continue;
				}

				if (variable < 2) // 0 1번은 현재 준비가 안되어 있음
				{
					num++;
					continue;
				}

				GameObject* spawn_block = AddBlock(scene, variable);
				Transform* block_tr = spawn_block->GetComponent<Transform>();
				if (row > num)
				{
					block_tr->SetPosition(Vector3(1.0f * num, 0.0f, 1.1f));
				}
				else
				{
					block_tr->SetPosition(Vector3(1.0f * (num % row),  1.0f * (-(num / row)), 1.1f));
				}
				num++;
			}
		}
	}

	GameObject* Stage::AddBlock(Scene* scene, int num)
	{
		if (num < 2)
		{
			return nullptr;
		}
		else
		{

			GameObject* block = object::Instantiate<GameObject>(eLayerType::Ground, scene);
			block->SetLayerType(eLayerType::Ground);
			Transform* tr = block->GetComponent<Transform>();
			tr->SetScale(Vector3(1, 1, 1));

			Collider2D* collider = block->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(1.0f, 1.0f));

			SpriteRenderer* mr = block->AddComponent<SpriteRenderer>();

			std::shared_ptr<Material> mateiral;
			if (num >= 0 && num <= 30)
			{
				mateiral = Resources::Find<Material>(L"DirtMaterial"+ std::to_wstring(num - 1));
				block->SetName(L"Dirt"+ std::to_wstring(num - 1));
			}

			if (num >= 31 && num <= 78)
			{
				mateiral = Resources::Find<Material>(L"WoodTileMaterial" + std::to_wstring(num - 30));
				block->SetName(L"WoodTileMaterial" + std::to_wstring(num - 30));
			}
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			return block;
		}
	}
}
	
