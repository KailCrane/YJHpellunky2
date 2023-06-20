#include "yaShotGunParticle.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"

namespace ya
{
	ShotGunParticle::ShotGunParticle()
		:direction(-1),
		animator(nullptr),
		point(Vector3::Zero)
	{
	}
	ShotGunParticle::~ShotGunParticle()
	{
	}
	void ShotGunParticle::Initialize()
	{
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"FlintMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> shotGunFireLeft = Resources::Load<Texture>(L"ShotguneParticle", L"ShotGunFireLeft.png");
		std::shared_ptr<Texture> shotGunFireRight = Resources::Load<Texture>(L"ShotguneParticle", L"ShotGunFireRight.png");

		animator->Create(L"ShootLeft", shotGunFireLeft, Vector2(0, 0.0f), Vector2(256, 256), Vector2::Zero, 5, 0.05f, true);
		animator->Create(L"ShootRight", shotGunFireRight, Vector2(0, 0.0f), Vector2(256, 256), Vector2::Zero, 5, 0.05f, false);
		animator->GetCompleteEvent(L"ShootLeft") = std::bind(&ShotGunParticle::OffActive, this);
		animator->GetCompleteEvent(L"ShootRight") = std::bind(&ShotGunParticle::OffActive, this);

	}
	void ShotGunParticle::Render()
	{

	}
	
	void ShotGunParticle::OnActive()
	{
		if (direction == -1)
		{
			return;
		}
		else if (direction == 0)
		{
			animator->Play(L"ShootLeft", false);
		}
		else if (direction == 1)
		{
			animator->Play(L"ShootRight", false);
		}
		GetOwner()->Alive();
	}
	void ShotGunParticle::OffActive()
	{
		GetOwner()->Death();
		direction = -1;
	}
}