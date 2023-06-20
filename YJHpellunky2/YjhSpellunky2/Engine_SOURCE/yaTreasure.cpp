#include "yaTreasure.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	Treasure::Treasure()
	{
	}
	Treasure::~Treasure()
	{

	}
	
	void Treasure::Initialize()
	{
		//GetScene();
		
	}

	void Treasure::Update()
	{
	}
	void Treasure::FixedUpdate()
	{
	}
	void Treasure::Render()
	{
	}
	void Treasure::SetTreasure(eTreasureType _type)
	{
		treasure_type = _type;

		tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material;
		Collider2D* col = GetOwner()->AddComponent<Collider2D>();
		

		switch (treasure_type)
		{
		case eTreasureType::eGoldBar:
			SetName(L"GoldBar");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.5f, 0.25f));
			col->SetName(L"GoldBarCollider");
			material = Resources::Find<Material>(L"GoldBarMaterial");
			break;
		case eTreasureType::ePileOfGoldBar:
			SetName(L"PileOfGoldBar");
			col->SetType(eColliderType::Rect);
			col->SetSize(Vector2(0.5f, 0.25f));
			col->SetName(L"PileOfGoldBarCollider");
			material = Resources::Find<Material>(L"PileOfGoldBarMaterial");
			break;
		case eTreasureType::eSmallGoldNugget:
			SetName(L"SmallGoldNugget");
			material = Resources::Find<Material>(L"SmallGoldNuggetMaterial");
			break;
		case eTreasureType::eLargeGoldNugget:
			SetName(L"LargeGoldNugget");
			material = Resources::Find<Material>(L"LargeGoldNuggetMaterial");
			break;
		case eTreasureType::eSmallEmerald:
			SetName(L"SmallEmerald");
			material = Resources::Find<Material>(L"SmallEmeraldMaterial");
			break;
		case eTreasureType::eLargeEmerald:
			SetName(L"LargeEmerald");
			material = Resources::Find<Material>(L"LargeEmeraldMaterial");
			break;
		case eTreasureType::eSmallSapphire:
			SetName(L"SmallSapphire");
			material = Resources::Find<Material>(L"SmallSapphireMaterial");
			break;
		case eTreasureType::eLargeSapphire:
			SetName(L"SmallSapphire");
			material = Resources::Find<Material>(L"SmallSapphireMaterial");
			break;
		case eTreasureType::eSmallRuby:
			SetName(L"SmallRuby");
			material = Resources::Find<Material>(L"SmallRubyMaterial");
			break;
		case eTreasureType::eLargeRuby:
			SetName(L"LargeRuby");
			material = Resources::Find<Material>(L"LargeRubyMaterial");
			break;
		}

		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
	}
}