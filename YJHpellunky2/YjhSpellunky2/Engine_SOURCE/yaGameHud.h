#pragma once
#include "yaScene.h"
#include "yaMaterial.h"
#include "yaPlayerScript.h"

namespace ya
{
	class Inventory;
	class PlayerScript;
	class GameHud
	{
	public:

		GameHud();
		~GameHud();
		void SetScene(Scene* _scene) { scene = _scene; }

		void HudOn();
		void Update();

		void LifeIconChange();
		void LifeChange(int num);

		void ShowButtonUI(const wchar_t* button_name);
		void HideButtonUI(const wchar_t* button_name);

		void ShowGameTimer();

		void AddItem();
		void ShowMoney();
		void RefreshBomb();
		void RefreshRope();
		void SetUp();
		void SetInventory(Inventory* _inventory) { inventory = _inventory; }
		void SetPscript(PlayerScript* _pScript) {pScript = _pScript; }
		std::shared_ptr<Material> GetNumberMaterial(static int num);
		
	private:
		Scene* scene;
		PlayerScript* pScript;
		Inventory* inventory;

		std::vector<GameObject*> icon_slots;

		GameObject* life_icon; //Á¤»ó »ç¸Á µ¶
		GameObject* life_num[2];
		int curr_life = 0;
		GameObject* dead_icon;


		GameObject* bomb_icon;
		std::vector<GameObject*> bomb_num_slot;

		int curr_bomb_num = 0;

		GameObject* rope_icon;
		GameObject* rope_nump[2];

		GameObject* locate_icon;
		GameObject* timer_icon;
		GameObject* money_hud;
		std::vector<GameObject*> money_slots;


		GameObject* map_icon;
		GameObject* sector_num;
		GameObject* sector_stage_num;
		GameObject* icons[10];
		
		GameObject* second_slot[2];
		GameObject* minute_slot[2];

		GameObject* button_ui;
		bool isButtonAppear;
		bool isButtonDisappear;
	};
}