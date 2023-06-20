#include "yaHornedLizard.h"
#include "yaInventory.h"
#include "yaResources.h"
namespace ya
{
	HornedLizard::HornedLizard()
	{
	}
	HornedLizard::~HornedLizard()
	{
	}
	void HornedLizard::Initialize()
	{
	}
	void HornedLizard::Update()
	{
	}
	void HornedLizard::FixedUpdate()
	{
	}
	void HornedLizard::Render()
	{
	}
	void HornedLizard::OnCollisionEnter(Collider2D* collider)
	{
	}
	void HornedLizard::OnCollisionStay(Collider2D* collider)
	{
	}
	void HornedLizard::OnCollisionExit(Collider2D* collider)
	{
	}
	void HornedLizard::ChildOnCollisionEnter(Collider2D* sender, Collider2D* col)
	{
		if (sender->GetName() == L"MonsterHead")
		{
			if (col->GetName() == L"PlayerFeet")
			{
				if (target->GetComponent<Inventory>()->FindItem(eItemType::SpikesShoes))
				{
					//���� ������ �Դ� �Ҹ�
					//������ 2 + �������� ���߿��� ������ ��
				}
				else
				{
					//������ ���� �÷��̾�� ƨ�ܳ����� ����Ʈ,
				}
			}
		}
	}
	void HornedLizard::ChildOnCollisionStay(Collider2D* sender, Collider2D* col)
	{
	}
	void HornedLizard::ChildOnCollisionExit(Collider2D* sender, Collider2D* col)
	{
	}
	void HornedLizard::SetAnimation()
	{
		std::shared_ptr<Texture> texture_l = Resources::Load<Texture>(L"HornedLizard", L"Monster//monstersbasic01L.png");
		std::shared_ptr<Texture> texture_r = Resources::Load<Texture>(L"HornedLizard", L"Monster//monstersbasic01R.png");

		animator->Create(L"LeftMove", texture_l, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"RightMove", texture_r, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, false);
		animator->Create(L"LeftRoll", texture_l, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"RightRoll", texture_l, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"Finch", texture_l, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Create(L"Dead", texture_l, Vector2(128.0f * 8, 128.0f * 3), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.1f, true);
		animator->Play(L"Idle", false);


	}
	void HornedLizard::StateChange(int change_num)
	{
	}
}