#pragma once
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaScript.h"
namespace ya
{
	class Block : public Script
	{
	public:
		Block();
		~Block();
		
		virtual void Initialize();
		virtual void Render();
		
		void SetBordersTexture();
		
		void MakeBorders();
		void SetBorderBlockType(eBlockType _block_type) { block_type = _block_type; }
		void SetEdge(int num);
		void ReleaseEdge(int num);
		void SetType(eBlockType _type) { block_type = _type;}
		void Destroy(); //파티클 시스템 필요 
		eBlockType GetBlockType() { return block_type; }

	private:
		Scene* curr_scene;
		std::vector<GameObject*> borders;
		eBlockType block_type;
	};
}
