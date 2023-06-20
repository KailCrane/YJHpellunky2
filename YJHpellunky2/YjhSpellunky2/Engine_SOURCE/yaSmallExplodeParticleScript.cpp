#include "yaSmallExplodeParticleScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"
namespace ya
{
	SmallExplodeParticleScript::SmallExplodeParticleScript()
	{

	}
	SmallExplodeParticleScript::~SmallExplodeParticleScript()
	{

	}

	void SmallExplodeParticleScript::Initialize()
	{
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"FlintMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		animator = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> explosiveTexture = Resources::Load<Texture>(L"Explosive", L"Explosive.png");

		animator->Create(L"Boom", explosiveTexture, Vector2(0, 0.0f), Vector2(256, 256), Vector2::Zero, 16, 0.05f, true);
		animator->GetCompleteEvent(L"Boom") = std::bind(&SmallExplodeParticleScript::OffActive, this);

	}
	void SmallExplodeParticleScript::Render()
	{

	}

	void SmallExplodeParticleScript::OnActive()
	{
		GetOwner()->GetComponent<Transform>()->SetPosition(point);
		animator->Play(L"Boom", false);
		GetOwner()->Alive();
	}
	void SmallExplodeParticleScript::OffActive()
	{
		GetOwner()->Death();
	}
}