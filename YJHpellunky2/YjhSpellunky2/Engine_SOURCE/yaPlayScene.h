#pragma once
#include "yaScene.h"
#include "yaPlayer.h"
#include "yaPlayerScript.h"
#include "yaStage.h"

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

		void LoadStage();

		virtual void OnEnter() override;
		virtual void OnExit() override;
	

	private:
		GameObject* cameraObj;
		Player* my_player;
		PlayerScript* pScript;
		WhipScript* whip;
		bool isSceneActive;
		Stage stage;
	};
}