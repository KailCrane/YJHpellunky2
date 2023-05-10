#pragma once
#include "yaGameObject.h"
#include "yaScene.h"

namespace ya
{
	class Stage
	{
	public:

		Stage();
		~Stage();
		void Initiailze();
		void SetScene(Scene* _scene) { scene = _scene; }
		void LoadStage(int stage_num);
		void Clear();
		GameObject* AddBlock(Scene* scene, int num);


	private:
		int row;
		int column;
		Scene* scene;
	};

	enum class  eBlockType
	{
		Dirt,
		Wood,
	};

}