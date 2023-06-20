#include "yaGameHud.h"
#include "yaObject.h"
#include "yaMaterial.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaGameObject.h"
#include "yaMaterial.h"
#include "yaInventory.h"
#include "yaPlayerScript.h"
#include "yaTime.h"

namespace ya
{
	GameHud::GameHud()
	{
	}
	GameHud::~GameHud()
	{

	}
	void GameHud::Update()
	{
		if (isButtonAppear)
		{
			Transform* button_tr = button_ui->GetComponent<Transform>();
			if (button_tr->GetScale().x < 0.4f)
			{
				Vector3 button_scale = button_tr->GetScale();
				Vector3 fixed_scale = Vector3(button_scale.x += Time::DeltaTime() * 1.0f, button_scale.y += Time::DeltaTime() * 1.0f, button_scale.z);

				button_tr->SetScale(fixed_scale);
			}
			else
			{
				isButtonAppear = false;
			}
		}

		if (isButtonDisappear)
		{
			Transform* button_tr = button_ui->GetComponent<Transform>();
			if (button_tr->GetScale().x > 0.1f)
			{
				Vector3 button_scale = button_tr->GetScale();
				Vector3 fixed_scale = Vector3(button_scale.x -= Time::DeltaTime() * 1.0f, button_scale.y -= Time::DeltaTime() * 1.0f, button_scale.z);

				button_tr->SetScale(fixed_scale);
			}
			else
			{
				button_ui->Death();
				isButtonDisappear = false;
			}
		}

		if (pScript->GetLifeAmount() != curr_life)
		{
			int array[2];

			curr_life = pScript->GetLifeAmount();

			if (curr_life > 0)
			{
				if (life_num[0]->IsDead())
				{
					life_num[0]->Alive();
				}
				if (life_num[1]->IsDead())
				{
					life_num[1]->Alive();
				}
			}
		
			if (curr_life < 10 && curr_life != 0)
			{
				array[0] = 0;
				{
					SpriteRenderer* mr = life_num[0]->GetComponent<SpriteRenderer>();
					std::shared_ptr<Material> material = Resources::Find<Material>(L"NoneIconMaterial");
					mr->SetMaterial(material);
				}
				array[1] = curr_life;
				{
					SpriteRenderer* mr = life_num[1]->GetComponent<SpriteRenderer>();
					std::shared_ptr<Material> material = GetNumberMaterial(array[1]);
					mr->SetMaterial(material);
				}
			}
			else if (curr_life >= 10)
			{
				array[0] = curr_life / 10;
				{
					SpriteRenderer* mr = life_num[0]->GetComponent<SpriteRenderer>();
					std::shared_ptr<Material> material = GetNumberMaterial(array[0]);
					mr->SetMaterial(material);
				}
				array[1] = curr_life & 10;
				{
					SpriteRenderer* mr = life_num[0]->GetComponent<SpriteRenderer>();
					std::shared_ptr<Material> material = GetNumberMaterial(array[1]);
					mr->SetMaterial(material);
				}
			}
			else if (curr_life < 1)
			{
				life_num[0]->Death();
				life_num[1]->Death();
				dead_icon->Alive();
			}
		}
	}


	void GameHud::ShowButtonUI(const wchar_t* button_name)
	{
		button_ui->Alive();
		button_ui->GetComponent<Transform>()->SetScale(Vector3(0.1f, 0.1f, 1.1f));
		isButtonDisappear = false;
		isButtonAppear = true;
	}

	void GameHud::HideButtonUI(const wchar_t* button_name)
	{
		isButtonAppear = false;
		isButtonDisappear = true;
	}

	void GameHud::ShowGameTimer()
	{

	}

	void GameHud::AddItem()
	{
		//초기화 해준뒤에 다시 채워 넣자
		for (int i = 0; i < icon_slots.size(); i++)
		{
			SpriteRenderer* mr = icon_slots[i]->GetComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"NoneIconMaterial");
			mr->SetMaterial(material);
		}

		////std::map<int ,eItemType>inventory_list = Inventory::GetList();
		//for (int i = 0; i < inventory_list.size(); i++)
		//{
		//	SpriteRenderer* mr = icon_slots[i]->GetComponent<SpriteRenderer>();
		//	std::shared_ptr<Material> material;
		//	switch (inventory_list[i])
		//	{
		//	case eItemType::ClimbingGloves:
		//		material = Resources::Find<Material>(L"ClimbingGlovesMaterial");

		//		break;
		//	case eItemType::SkeletonKey:
		//		material = Resources::Find<Material>(L"SkeletonKeyIconMaterial");

		//		break;
		//	}
		//	mr->SetMaterial(material);
		//}
	}

	void GameHud::ShowMoney()
	{
		int money = inventory->GetMoney();

		if (money > 10000)
		{
			vector<int> digit_num;

			for (int i = 4; i >= 0; i--)
			{
				int digit = pow(10, i);
				int num = money / digit;
				digit_num.push_back(num);
				money -= digit * num;
			}

			int y = digit_num.size() - 1;
			for (int i = 0; i < digit_num.size(); i++)
			{
				Animator* animator = money_slots[y]->GetComponent<Animator>();
				animator->Play(L"Num" + std::to_wstring(digit_num[i]));
				y--;
			}
			return;
		}
		else
		{
			Animator* animator = money_slots[4]->GetComponent<Animator>();
			animator->Play(L"Num" + std::to_wstring(0));
		}
		if (money > 1000)
		{
			vector<int> digit_num;

			for (int i = 3; i >= 0; i--)
			{
				int digit = pow(10, i);
				int num = money / digit;
				digit_num.push_back(num);
				money -= digit * num;
			}

			int y = digit_num.size() - 1;
			for (int i = 0; i < digit_num.size(); i++)
			{
				Animator* animator = money_slots[y]->GetComponent<Animator>();
				animator->Play(L"Num" + std::to_wstring(digit_num[i]));
				y--;
			}
			return;
		}
		else
		{
			Animator* animator = money_slots[3]->GetComponent<Animator>();
			animator->Play(L"Num" + std::to_wstring(0));
		}
		if (money > 100)
		{
			vector<int> digit_num;

			for (int i = 2; i >= 0; i--)
			{  
				int digit = pow(10, i);
				int num = money / digit;
				digit_num.push_back(num);
				money -= digit * num;
			}
			int y = digit_num.size()-1;
			for (int i = 0; i < digit_num.size(); i++)
			{
				Animator* animator = money_slots[y]->GetComponent<Animator>();
				animator->Play(L"Num" + std::to_wstring(digit_num[i]));
				y--;
			}
			return;
		}
		else
		{
			Animator* animator = money_slots[2]->GetComponent<Animator>();
			animator->Play(L"Num" + std::to_wstring(0));
		}
		if (money > 10)
		{
			vector<int> digit_num;

			for (int i = 1; i >= 0; i--)
			{
				int digit = pow(10, i);
				int num = money / digit;
				digit_num.push_back(num);
				money -= digit * num;
			}

			int y = digit_num.size() - 1;
			for (int i = 0; i < digit_num.size(); i++)
			{
				Animator* animator = money_slots[y]->GetComponent<Animator>();
				animator->Play(L"Num" + std::to_wstring(digit_num[i]));
				y--;
			}
			return;
		}
		else
		{
			Animator* animator = money_slots[1]->GetComponent<Animator>();
			animator->Play(L"Num" + std::to_wstring(0));
		}
		if (money > 0)
		{
			vector<int> digit_num;

			for (int i = 1; i >= 0; i--)
			{
				int digit = pow(10, i);
				int num = money / digit;
				digit_num.push_back(num);
				money -= digit * num;
			}
			int y = digit_num.size() - 1;
			for (int i = 0; i < digit_num.size(); i++)
			{
				Animator* animator = money_slots[y]->GetComponent<Animator>();
				animator->Play(L"Num" + std::to_wstring(digit_num[i]));
				y--;
			}
			return;
		}
		else
		{
			Animator* animator = money_slots[0]->GetComponent<Animator>();
			animator->Play(L"Num0");
		}
	}

	void GameHud::RefreshBomb()
	{
		int bomb = inventory->GetBomb();
		if (bomb > 10)
		{
			int digit = bomb / 10;

			Animator* animator1 = bomb_num_slot[1]->GetComponent<Animator>();
			animator1->Play(L"Num" + std::to_wstring(digit));
			bomb_num_slot[1]->Alive();

			int left = bomb - digit * 10;
			Animator* animator2 = bomb_num_slot[0]->GetComponent<Animator>();
			animator2->Play(L"Num" + std::to_wstring(left));
		}
		else
		{
			Animator* animator1 = bomb_num_slot[1]->GetComponent<Animator>();
			animator1->Play(L"Num0");
			bomb_num_slot[1]->Death();
			Animator* animator2 = bomb_num_slot[0]->GetComponent<Animator>();
			animator2->Play(L"Num" + std::to_wstring(bomb));
		}
	}

	void GameHud::RefreshRope()
	{
		int bomb = inventory->GetRope();
	}


	void GameHud::SetUp()
	{
#pragma region "ButtonUI"
		{
			button_ui = object::Instantiate<GameObject>(eLayerType::UI, scene);
			button_ui->SetName(L"ButtonUI");
			Transform* tr = button_ui->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.5f, 1.2f, 1.0f));
			tr->SetScale(Vector3(0.4f, 0.4f, 1.0f));
			SpriteRenderer* mr = button_ui->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"ButtonHudMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion
		
#pragma region "MoneySlot"
		for (int i = 0; i < 6; i++)
		{
			GameObject* money_slot = object::Instantiate<GameObject>(eLayerType::UI, scene);
			money_slot->SetName(L"MoneySlot");
			Transform* tr = money_slot->GetComponent<Transform>();
			tr->SetPosition(Vector3(5.15f - i * 0.25f, 5.0f, 1.0f));
			tr->SetScale(Vector3(0.35f, 0.35f, 1.0f));
			SpriteRenderer* mr = money_slot->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"NumberMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			Animator* animator = money_slot->AddComponent<Animator>();

			std::shared_ptr<Texture> number_texture = Resources::Load<Texture>(L"NumberTexture", L"GameHud//NumberTexture.png");

			animator->Create(L"Num0", number_texture, Vector2(0, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num1", number_texture, Vector2(128, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num2", number_texture, Vector2(128*2, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num3", number_texture, Vector2(128 * 3, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num4", number_texture, Vector2(128 * 4, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num5", number_texture, Vector2(128 * 5, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num6", number_texture, Vector2(128 * 6, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num7", number_texture, Vector2(128 * 7, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num8", number_texture, Vector2(128 * 8, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num9", number_texture, Vector2(128 * 9, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Play(L"Num0",false);
			money_slots.push_back(money_slot);
		}
#pragma endregion

#pragma region "IconSlot"


		for (int i = 0; i < 10; i++)
		{
			GameObject* icon_slot = object::Instantiate<GameObject>(eLayerType::UI, scene);
			icon_slot->SetName(L"IconSlot");
			Transform* tr = icon_slot->GetComponent<Transform>();
			tr->SetPosition(Vector3(-5.0f, 5.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			SpriteRenderer* mr = icon_slot->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"NoneIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			icon_slots.push_back(icon_slot);
		}
#pragma endregion


#pragma region "LifeIcon"
		{
			life_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
			life_icon->SetName(L"LifeIcon");
			Transform* tr = life_icon->GetComponent<Transform>();
			tr->SetPosition(Vector3(-6.3f, 4.7f, 1.0f));
			tr->SetScale(Vector3(0.8f, 0.8f, 1.0f));
			SpriteRenderer* mr = life_icon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"LifeIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}

		for (int i = 0; i < 2; i++)
		{
			life_num[i] = object::Instantiate<GameObject>(eLayerType::UI, scene);
			life_num[i]->SetName(L"LifenumSlot");
			Transform* tr = life_num[i]->GetComponent<Transform>();
			tr->SetPosition(Vector3(-6.05f, 4.5f, 1.0f));
			tr->SetScale(Vector3(0.4f, 0.4f, 1.0f));
			SpriteRenderer* mr = life_num[i]->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"NoneIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion


		dead_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
		dead_icon->SetName(L"DeadIcon");
		Transform* tr = dead_icon->GetComponent<Transform>();
		tr->SetPosition(Vector3(-6.3f, 4.7f, 1.0f));
		tr->SetScale(Vector3(0.8f, 0.8f, 1.0f));
		SpriteRenderer* mr = dead_icon->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"DeadIconMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
		dead_icon->Death();


#pragma region "BombIcon"
		{
			bomb_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
			bomb_icon->SetName(L"BombIcon");
			Transform* tr = bomb_icon->GetComponent<Transform>();
			tr->SetPosition(Vector3(-5.3f, 4.7f, 1.0f));
			tr->SetScale(Vector3(0.8f, 0.8f, 1.0f));
			SpriteRenderer* mr = bomb_icon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"BombIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion
#pragma region "BombNumSlot"

		for (int i = 0; i < 2; i++)
		{
			GameObject* bomb_num = object::Instantiate<GameObject>(eLayerType::UI, scene);
			bomb_num->SetName(L"BombSlot");
			Transform* tr = bomb_num->GetComponent<Transform>();
			tr->SetPosition(Vector3(-4.9f - 0.2f * i, 4.5f, 1.1f));
			tr->SetScale(Vector3(0.3f, 0.3f, 1.0f));
			SpriteRenderer* mr = bomb_num->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"NumberMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			Animator* animator = bomb_num->AddComponent<Animator>();

			std::shared_ptr<Texture> number_texture = Resources::Load<Texture>(L"NumberTexture", L"GameHud//NumberTexture.png");

			animator->Create(L"Num0", number_texture, Vector2(0, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num1", number_texture, Vector2(128, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num2", number_texture, Vector2(128 * 2, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num3", number_texture, Vector2(128 * 3, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num4", number_texture, Vector2(128 * 4, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num5", number_texture, Vector2(128 * 5, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num6", number_texture, Vector2(128 * 6, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num7", number_texture, Vector2(128 * 7, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num8", number_texture, Vector2(128 * 8, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Create(L"Num9", number_texture, Vector2(128 * 9, 0), Vector2(128, 129), Vector2::Zero, 1, 1.0f, false);
			animator->Play(L"Num0", false);
			bomb_num_slot.push_back(bomb_num);
		}

#pragma endregion
#pragma region "RopeIcon"


		{
			rope_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
			rope_icon->SetName(L"RopeIcon");
			Transform* tr = rope_icon->GetComponent<Transform>();
			tr->SetPosition(Vector3(-4.3f, 4.7f, 1.0f));
			tr->SetScale(Vector3(0.8f, 0.8f, 1.0f));
			SpriteRenderer* mr = rope_icon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"RopeIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion

#pragma region "LocateIcon"
		{
			locate_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
			locate_icon->SetName(L"LocateIcon");
			Transform* tr = locate_icon->GetComponent<Transform>();
			tr->SetPosition(Vector3(7.5f, 5.0f, 1.0f));
			tr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
			SpriteRenderer* mr = locate_icon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"LocateIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		} 
#pragma endregion
#pragma region "TiemrIcon"


		{
			timer_icon = object::Instantiate<GameObject>(eLayerType::UI, scene);
			timer_icon->SetName(L"TimerIcon");
			Transform* tr = timer_icon->GetComponent<Transform>();
			tr->SetPosition(Vector3(5.5f, 5.0f, 1.0f));
			tr->SetScale(Vector3(0.7f, 0.7f, 1.0f));
			SpriteRenderer* mr = timer_icon->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"TimerIconMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion
#pragma region "MoneyHud"

		{
			money_hud = object::Instantiate<GameObject>(eLayerType::UI, scene);
			money_hud->SetName(L"MoneyHud");
			Transform* tr = money_hud->GetComponent<Transform>();
			tr->SetPosition(Vector3(3.5f, 5.0f, 1.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			SpriteRenderer* mr = money_hud->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"MoneyHudMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
#pragma endregion

	}

	std::shared_ptr<Material> GameHud::GetNumberMaterial(static int num)
	{
		switch (num)
		{
		case 0:
			return Resources::Find<Material>(L"SampleNum_0_Material");
		case 1:
			return Resources::Find<Material>(L"SampleNum_1_Material");
		case 2:
			return Resources::Find<Material>(L"SampleNum_2_Material");
		case 3:
			return Resources::Find<Material>(L"SampleNum_3_Material");
		case 4:
			return Resources::Find<Material>(L"SampleNum_4_Material");
		case 5:
			return Resources::Find<Material>(L"SampleNum_5_Material");
		case 6:
			return Resources::Find<Material>(L"SampleNum_6_Material");
		case 7:
			return Resources::Find<Material>(L"SampleNum_7_Material");
		case 8:
			return Resources::Find<Material>(L"SampleNum_8_Material");
		case 9:
			return Resources::Find<Material>(L"SampleNum_9_Material");
		}

	}
}