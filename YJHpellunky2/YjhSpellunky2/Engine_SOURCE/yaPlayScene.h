#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaStage.h"
#include "yaGameHud.h"
#include "yaInventory.h"
#include "yaBat.h"
#include "yaMonster.h"
#include "yaStageResult.h"

namespace ya
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		
		GameHud* GetGameHud() { return gamehud; }

		virtual void OnEnter() override;
		virtual void OnExit() override;
	

	private:

		GameObject* cameraObj;
		Player* my_player;
		PlayerScript* pScript;
		Bat* bat;
		Monster* monster;
		WhipScript* whip;
		bool isSceneActive;
		Stage stage;
		GameHud* gamehud;
		Inventory* inventory;
		StageResult* result;
	};
}