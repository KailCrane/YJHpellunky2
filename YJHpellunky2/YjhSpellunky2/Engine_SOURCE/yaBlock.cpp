#include "yaBlock.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaSceneManager.h"

namespace ya
{
	Block::Block()
		:block_type(eBlockType::Dirt),
		curr_scene(nullptr)
	{
	}
	Block::~Block()
	{
	}
	void Block::Initialize()
	{
		curr_scene = SceneManager::GetPlayScene();
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		col->SetType(eColliderType::Rect);
		col->SetSize(Vector2(0.8f,0.8f));
		col->SetName(L"BlockCollider");
	}
	void Block::Render()
	{

	}
	void Block::MakeBorders()
	{
		for (int i = 0; i < 4; i++)
		{
			const int num = i;
			GameObject* border = object::Instantiate<GameObject>(eLayerType::Ground, curr_scene);
			Collider2D* col = border->AddComponent<Collider2D>();
			Transform* tr = border->GetComponent<Transform>();
			Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			switch (num)
			{
			case 0:
				border->SetLayerType(eLayerType::Ground);
				border->SetName(L"Ground");
				col->SetSize(Vector2(1.0f, 0.2f));
				col->SetCenter(Vector2(0, -0.1f));
				col->SetName(L"GroundCollider");
				tr->SetPosition(Vector3(owner_pos.x, owner_pos.y + 0.5f, owner_pos.z));
				break;
			case 1:
				border->SetLayerType(eLayerType::Ceiling);
				border->SetName(L"Ceiling");
				col->SetName(L"CeilingCollider");
				col->SetSize(Vector2(1.0f, 0.2f));
				col->SetCenter(Vector2(0, 0.1f));
				tr->SetPosition(Vector3(owner_pos.x, owner_pos.y - 0.5f, owner_pos.z));
			break;
			case 2:
				border->SetLayerType(eLayerType::LeftSide);
				border->SetName(L"LeftSide");
				col->SetSize(Vector2(0.2f, 1.0f));
				col->SetName(L"LeftSideCollider");
				col->SetCenter(Vector2(0.1f, 0.0f));
				tr->SetPosition(Vector3(owner_pos.x - 0.5f, owner_pos.y, owner_pos.z));
				break;
			case 3:
				border->SetLayerType(eLayerType::RightSide);
				border->SetName(L"RightSide");
				col->SetName(L"RightSideCollider");
				col->SetSize(Vector2(0.2f, 1.0f));
				col->SetCenter(Vector2(-0.1f, 0.0f));
				tr->SetPosition(Vector3(owner_pos.x + 0.5f, owner_pos.y, owner_pos.z));
			break;
			}
			
			col->SetType(eColliderType::Rect);
			borders.push_back(border);
		}
		SetBordersTexture();
	}	
	void Block::SetBordersTexture()
	{
		for (int i = 0; i < 4; i++)
		{
			if(block_type == eBlockType::Dirt)
			{
				const int num = i;

				SpriteRenderer* mr = borders[num]->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> material;
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				switch (num)
				{
				case 0:
					material = Resources::Find<Material>(L"DirtUpperMaterial");
					borders[num]->SetName(L"DirtUpper");
					break;
				case 1:
					material = Resources::Find<Material>(L"DirtBelowMaterial");
					borders[num]->SetName(L"DirtBelow");
					break; 
				case 2:
					material = Resources::Find<Material>(L"DirtLeftSideMaterial");
					borders[num]->SetName(L"DirtLeftSide");
					break;
				case 3:
					material = Resources::Find<Material>(L"DirtRightSideMaterial");
					borders[num]->SetName(L"DirtRightSide");
					break;
				}
				mr->SetMaterial(material);
				mr->SetMesh(mesh);
			}
			//만약 i번쨰의 타입이 특정 타입이면
			//보더에 메테리얼 입히기
			//아니면 넘어가기
		}
	}
	void Block::SetEdge(int num)
	{
		borders[num]->Alive();
	}
	void Block::ReleaseEdge(int num)
	{
		borders[num]->Death();
	}
	void Block::Destroy()
	{
		for (int i = 0; i < 4; i++)
		{
			borders[i]->Death();
		}
		GetOwner()->Death();
	}
}