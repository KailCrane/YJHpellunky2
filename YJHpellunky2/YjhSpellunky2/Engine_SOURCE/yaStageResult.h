#pragma once
#include "yaGameObject.h"

namespace ya
{

	class StageResult : public Script
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render();
		void SetInfo(float time ,float earn_money);
		void AddMoney(int money);

	private:

		GameObject* AddUI(eLayerType layer, const std::wstring& object_name, Vector3 point, const std::wstring& material_name);
		
		GameObject*	timer_icon;
		GameObject* timer_icon2;

		GameObject* money_icon;
		GameObject* money_icon2;

		GameObject* darkboard_ui;
		GameObject* darkboard_ui2;
		GameObject* darkboard_ui3;
		GameObject* darkboard_ui4;
		GameObject* darkboard_ui5;
		GameObject* levelboard_ui;
		GameObject* papyrus_ui;
		GameObject* plank_ui;
		GameObject* roll_ui;
		GameObject* roll_ui2;
		GameObject* woodboard_ui;

		std::vector<GameObject*> ui_list;

		int life;
		
		float curr_level_time;
		float total_level_time;
		float curr_earn_money;
		float total_earn_money;

		std::map<eMonsterType, int> defeated_monster;
		std::map<eTreasureType, int> earn_treasure;
	};
}