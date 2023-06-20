#include "yaFintParticleScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"

namespace ya
{
	FintParticleScript::FintParticleScript()
		:animator(nullptr),
		fint_time(2.0f),
		fint_timer(0.0f),
		target(nullptr),
		isActive(false)
	{

	}
	FintParticleScript::~FintParticleScript()
	{

	}
	void FintParticleScript::Initialize()
	{
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"FlintMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> fintTexture = Resources::Load<Texture>(L"FintTexture", L"FlintTexture.png");

		animator->Create(L"Flint", fintTexture, Vector2(0 , 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 12, 0.05f, false);
		animator->Play(L"Flint", true);
	}
	void FintParticleScript::Update()
	{
		if (isActive)
		{
			Active();
		}
	}
	void FintParticleScript::Render()
	{
		
	}

	void FintParticleScript::SetTarget(GameObject* _target)
	{
		target = _target;
	}

	void FintParticleScript::OnActive()
	{
		if (target == nullptr)
		{
			return;
		}
		else
		{
			isActive = true;
			GetOwner()->Alive();
			animator->Play(L"Flint", true);
		}
	}
	void FintParticleScript::Active()
	{
		fint_timer += Time::DeltaTime();
	
		Vector3 target_pos = target->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(target_pos.x, target_pos.y + 0.2f, target_pos.z);
		GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);

		if (fint_timer >= fint_time)
		{
			GetOwner()->Death();
			fint_timer = 0.0f;
		}
	}
}