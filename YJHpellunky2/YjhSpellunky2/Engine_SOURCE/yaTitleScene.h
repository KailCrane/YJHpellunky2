#pragma once
#include "yaScene.h"
#include "yaUIDisk.h"
#include "yaUIStatue.h"
#include "yaTime.h"
#include "yaArrow.h"
#include  "yaCharSelectUI.h"
#include "yaTitleMenuSelect.h"

namespace ya
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void ObjsOn(std::vector<GameObject*> objs) {
			for (int i = 0; i < objs.size(); i++)
			{
				objs[i]->Alive();
			}
		}
		void ObjsOff(std::vector<GameObject*> objs) {
			for (int i = 0; i < objs.size(); i++)
			{
				objs[i]->Death();
			}
		}


		//// 메뉴 선택 애니메이션 작동
		//void MenuSelectAnim();
		//// 메뉴 선택 애니메이션 스킵
		//void MenuSelectAnimSkip();

	private:

		// 돌아가는 원판
		std::vector<GameObject*> menu_select_objs;
		std::vector<GameObject*>intro_bg_objs;

		UIDisk* uiDisk;
		UIStatue* uiStatue;

		TitleMenuSelect* menuSelect;
		CharSelectUI* charSelect;


		enum TitleIntroPhase
		{
			Standby,
			DiskActive,
			StatueActive,
			MenuSelectMode,
			CharSelectMode,
			Complete
		};
		TitleIntroPhase titleIntroPhase;

		GameObject* select_bar_L;
		GameObject* select_bar_R;

		float spear_move_speed;

		enum MenuSpearState
		{
			forward,
			backward
		};

		std::vector<GameObject*> menu_select_bars;
		std::vector<GameObject*> snake_objs;
		std::vector<GameObject*> char_select_objs;

		MenuSpearState menuSpearState;

		float spear_move_dist;

		int menu_num;
		int prev_menu_num;


		GameObject* upboard;
		GameObject* downboard;

		float board_move_dist;
		float board_move_speed;

		Vector3 init_Board_pos;


		GameObject* scroll_L;
		GameObject* scroll_R;

		GameObject* scrollMiddle;

		float scroll_move_dist;
		float scroll_move_speed;

		Vector3 init_Scroll_pos;


		Arrow* left_arrow;
		Arrow* right_arrow;

		GameObject* door_obj;
		GameObject* z_button;

		float door_move_speed;
		float door_move_dist;

		Vector3 init_door_pos;

	};
}
