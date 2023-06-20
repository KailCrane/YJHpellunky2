#include "yaStageResult.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	void StageResult::Initialize()
	{
		Scene* scene = SceneManager::GetPlayScene();
	
			woodboard_ui = AddUI(eLayerType::UI, L"WoodboardUI", Vector3(1.0f, 2.0f , 1.0f), L"WoodBoardUIMaterial");
			woodboard_ui->GetComponent<Transform>()->SetScale(Vector3(15, 5, 1));
			ui_list.push_back(woodboard_ui);;
			darkboard_ui = AddUI(eLayerType::UI, L"DarkBoardUI", Vector3(-2.0f, 1.0f, 1.0f), L"DarkBoardUIMaterial");
			darkboard_ui->GetComponent<Transform>()->SetScale(Vector3(6, 1.2f, 1));
			ui_list.push_back(darkboard_ui);;

			darkboard_ui2 = AddUI(eLayerType::UI, L"DarkBoardUI", Vector3(-3.6f, 2.5f, 1.0f), L"DarkBoardUIMaterial");
			darkboard_ui2->GetComponent<Transform>()->SetScale(Vector3(2.0f, 0.6f, 1));
			ui_list.push_back(darkboard_ui2);;

			darkboard_ui3 = AddUI(eLayerType::UI, L"DarkBoardUI", Vector3(-3.6f, 2.0f, 1.0f), L"DarkBoardUIMaterial");
			darkboard_ui3->GetComponent<Transform>()->SetScale(Vector3(2.0f, 0.6f, 1));
			ui_list.push_back(darkboard_ui3);;

			darkboard_ui4 = AddUI(eLayerType::UI, L"DarkBoardUI", Vector3(-0.4f, 2.5f, 1.0f), L"DarkBoardUIMaterial");
			darkboard_ui4->GetComponent<Transform>()->SetScale(Vector3(2.0f, 0.6f, 1));
			ui_list.push_back(darkboard_ui4);;

			darkboard_ui5 = AddUI(eLayerType::UI, L"DarkBoardUI", Vector3(-0.4f, 2.0f, 1.0f), L"DarkBoardUIMaterial");
			darkboard_ui5->GetComponent<Transform>()->SetScale(Vector3(2.0f, 0.6f, 1));
			ui_list.push_back(darkboard_ui5);;


			levelboard_ui = AddUI(eLayerType::UI, L"LevelBoasrdUI", Vector3(-2.0f, 4.4f, 1.0f), L"LevelBoardUIMaterial");
			levelboard_ui->GetComponent<Transform>()->SetScale(Vector3(8, 2.2f, 1));
			ui_list.push_back(levelboard_ui);;

			papyrus_ui = AddUI(eLayerType::UI, L"PapyrusUI", Vector3(4.4f, 1.9f, 1.0f), L"PapyrusUIMaterial");
			papyrus_ui->GetComponent<Transform>()->SetScale(Vector3(5, 3.5f, 1));
			ui_list.push_back(papyrus_ui);;
			
			roll_ui = AddUI(eLayerType::UI, L"RollUI", Vector3(4.4f, 4.0f, 1.0f), L"RollUIMaterial");
			roll_ui->GetComponent<Transform>()->SetScale(Vector3(5, 1.5f, 1));
			ui_list.push_back(roll_ui);;
			
			roll_ui2 = AddUI(eLayerType::UI, L"RollUI2", Vector3(4.4f, 0.0f, 1.0f), L"RollUIMaterial");
			roll_ui2->GetComponent<Transform>()->SetScale(Vector3(5, 1.5f, 1));
			ui_list.push_back(roll_ui2);;

			plank_ui = AddUI(eLayerType::UI, L"PlankUI", Vector3(-2.0f, 2.1f, 1.0f), L"PlankBardUIMaterial");
			plank_ui->GetComponent<Transform>()->SetScale(Vector3(1.3, 1.3, 1));
			ui_list.push_back(plank_ui);;

			timer_icon = AddUI(eLayerType::UI, L"TimerUI", Vector3(-4.6f, 2.0f, 1.0f), L"TimerIconMaterial");
			timer_icon->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.8f, 1));
			ui_list.push_back(timer_icon);;

			timer_icon2 = AddUI(eLayerType::UI, L"TimerUI", Vector3(-4.6f, 2.5f, 1.0f), L"TimerIconMaterial");
			timer_icon2->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.8f, 1));;
			ui_list.push_back(timer_icon2);;

			money_icon = AddUI(eLayerType::UI, L"MoneyUI", Vector3(-1.3f, 2.0f, 1.0f), L"MoneyHudMaterial");
			money_icon->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.8f, 1));
			ui_list.push_back(money_icon);;

			money_icon2 = AddUI(eLayerType::UI, L"MoneyUI", Vector3(-1.3f, 2.5f, 1.0f), L"MoneyHudMaterial");
			money_icon2->GetComponent<Transform>()->SetScale(Vector3(0.8f, 0.8f, 1));
			ui_list.push_back(money_icon2);;


			for (int i = 0; i < ui_list.size(); i++)
			{
				ui_list[i]->Death();
			}

	}

	void StageResult::Update()
	{
	}

	void StageResult::Render()
	{
	}

	void StageResult::SetInfo(float time, float earn_money)
	{

	}
	void StageResult::AddMoney(int money)
	{
	}

	GameObject* StageResult::AddUI(eLayerType layer, const std::wstring& object_name, Vector3 point, const std::wstring& material_name)
	{
		Scene* scene = SceneManager::GetPlayScene();
		GameObject* obj = object::Instantiate<GameObject>(layer, scene);
		obj->SetName(object_name);
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(point);
		tr->SetScale(Vector3::One);
		SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(material_name);
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
		return obj;
	}
}
