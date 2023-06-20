#include "yaBomb.h"
#include "yaRigidbody.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaTime.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	Bomb::Bomb()
	{
		
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		curr_scene = SceneManager::GetPlayScene();

		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"BombMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();
		SetAnimation();
	}
	void Bomb::Update()
	{

	}
	void Bomb::FixedUpdate()
	{

	}
	void Bomb::Render()
	{

	}
	void Bomb::CountDown()
	{
		count += 1;
		animator->Play(L"Explode", false);

		if (count >= 3)
		{
			ExplodeBomb();
		}
	}

	void Bomb::SetAnimation()
	{
		std::shared_ptr<Texture> bomb_texture = Resources::Load<Texture>(L"Bomb", L"Item//Bomb.png");

		animator->Create(L"Idle", bomb_texture, Vector2(0.0, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 1.0f, false);
		animator->Create(L"Ignite", bomb_texture, Vector2(0.0, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 1.0f, false);
		animator->Create(L"Explode", bomb_texture, Vector2(0.0, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 3, 0.2f, false);
		animator->GetCompleteEvent(L"Explode") = std::bind(&Bomb::CountDown, this);
		animator->Play(L"Idle",false);
	}

	void Bomb::IgniteBomb()
	{

	}
	void Bomb::ExplodeBomb()
	{
		//particle_manager->SpawnExplosive(GetOwner()->GetComponent<Transform>()->GetPosition());
	}

	void Bomb::OnCollisionEnter(Collider2D* col)
	{

	}
	void Bomb::OnCollisionStay(Collider2D* col)
	{

	}
	void Bomb::OnCollisionExit(Collider2D* col)
	{
	
	}

	void Bomb::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"ExplodeRangeCollider")
		{
			if (col->GetName() == L"PlayerBodyCollider")
			{
			}
			if (col->GetName() == L"MonsterBodyCollider")
			{

			}
			if (col->GetName() == L"BlockCollider")
			{
				blocks.push_back(col->GetOwner()->GetComponent<Block>());
			}
		}
	}

	void Bomb::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{

	}

	void Bomb::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
		if (col->GetName() == L"BlockCollider")
		{
			for (int i = 0; i < blocks.size(); i++)
			{
				if (blocks[i]->GetID() == col->GetOwner()->GetComponent<Block>()->GetID())
				{
					blocks.erase(remove(blocks.begin(), blocks.end(), col->GetOwner()->GetComponent<Block>()), blocks.end());
				}
			}
		}
	}
}