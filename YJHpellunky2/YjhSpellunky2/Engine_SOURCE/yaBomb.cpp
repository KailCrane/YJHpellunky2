#include "yaBomb.h"
#include "yaRigidbody.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaTime.h"

namespace ya
{
	Bomb::Bomb()
		:direction(Left)
	{
		this->AddComponent<Rigidbody>();
	    animator = this->AddComponent<Animator>();
		std::shared_ptr<Texture> texture_L = Resources::Load<Texture>(L"Bomb", L"itemsL.png");

		animator->Create(L"LeftIdle", texture_L, Vector2(1920.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);

		box_collider = this->AddComponent<Collider2D>();
		box_collider->SetType(eColliderType::Rect);
		box_collider->SetSize(Vector2(1,1));
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
		GameObject::Initialize();
	}
	void Bomb::Update()
	{
		GameObject::Update();
	}
	void Bomb::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bomb::Render()
	{
		GameObject::Render();
	}


	void Bomb::OnCollisionEnter(Collider2D* col)
	{
		if (col->GetOwner()->GetLayerType() == eLayerType::Ground)
		{
			if (GetComponent<Transform>()->GetScale().x 
				== col->GetOwner()->GetComponent<Transform>()->GetScale().x &&
				GetComponent<Transform>()->GetScale().y
				== col->GetOwner()->GetComponent<Transform>()->GetScale().y)
			{
				float Ax1 = box_collider->GetPosition().x;
				float Ax2 = box_collider->GetPosition().x + box_collider->GetSize().x;

				float Ay1 = box_collider->GetPosition().y;
				float Ay2 = box_collider->GetPosition().x - box_collider->GetSize().y;

				float Bx1 = col->GetPosition().x;
				float Bx2 = col->GetPosition().x + col->GetSize().x;

				float By1 = col->GetPosition().y;
				float By2 = col->GetPosition().y - box_collider->GetSize().y;
			}
			else
			{

			}
		}

	}
	void Bomb::OnCollisionStay(Collider2D* col)
	{
	}
	void Bomb::OnCollisionExit(Collider2D* col)
	{
	}
	void Bomb::IgniteBomb()
	{
		fuse_timer += Time::DeltaTime();
		if (fuse_timer >= fuse_burst_time)
		{
			ExplodeBomb();
		}
	}
	void Bomb::ExplodeBomb()
	{
		GameObjects A = pScene->GetGameObjects(eLayerType::Ground);

		for (int i = 0; i < A.size(); i++)
		{
			//if (A[i]->GetLayerType() == eLayerType::Ground &&)
			{

			}
		}

	}
}