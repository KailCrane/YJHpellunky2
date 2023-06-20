#pragma once
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaMonster.h"
#include "yaBat.h"
#include "yaSpider.h"
#include "yaQuillback.h"
#include "yaTreasure.h"
#include "yaParticleManager.h"

namespace ya
{
	class Player;
	class Stage
	{
	public:

		Stage();
		~Stage();
		void Initialize();
		
		void SetScene(Scene* _scene) { scene = _scene; }
		void SetPlayer(Player* _player) { player = _player; }
		void SetParticleManager(ParticleManager* _pManager) { pManager = _pManager; }
		void LoadStage(int stage_num);
		void NextStage();
		Stage* GetStage() { return this; }

		void PlaceStage();
		void BorderSort();
		void Clear();
		void Update();


		GameObject* AddBlock(Scene* scene, int num);

		void Reset();

	private:
		int row;
		int column;
		Scene* scene;
		ParticleManager* pManager;

		Bat* bat;
		Spider* spider;
		Quillback* quilback;
		Treasure* small_gold;
		Treasure* Rarge_gold;

		Player* player;

		enum StageState
		{
			Load,
			Standby,
			Progress,
			End
		};

		std::vector<std::vector<int>> map_column;
		std::vector<std::vector<GameObject*>> map_data;

		std::vector<std::vector<int>> map_column_2;
		std::vector<std::vector<GameObject*>> map_data_2;

		std::vector<std::vector<int>> map_column_3;
		std::vector<std::vector<GameObject*>> map_data_3;


		std::vector<GameObject* > stage1_objs;
		std::vector<GameObject* > stage2_objs;
		std::vector<GameObject* > stage3_objs;


		bool isGameStart;

		int sec;
		int min;
		float timer;
	};
}