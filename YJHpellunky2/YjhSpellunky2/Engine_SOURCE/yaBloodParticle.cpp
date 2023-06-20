#include "yaBloodParticle.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"

namespace ya
{
	BloodParticle::BloodParticle()
		:init_scale(Vector3(0.25f, 0.25f, 1.0f)),
		isActive(false),
		splash_power(Vector3::Zero),
		drop_limit(-2.0f),
		drop_speed(4.0f),
		decrease_speed(0.15f),
		decrease_limit(0.1f)
	{

	}
	BloodParticle::~BloodParticle()
	{
	}
	void BloodParticle::Initialize()
	{
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"BloodMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		GetOwner()->GetComponent<Transform>()->SetScale(init_scale);

	}
	void BloodParticle::Update()
	{
		if (isActive)
		{
			Active();
		}
	}
	void BloodParticle::Render()
	{

	}
	void BloodParticle::SetPoint(Vector3 point)
	{              
		GetOwner()->GetComponent<Transform>()->SetPosition(point);
	}  
	void BloodParticle::OnActive()
	{
		GetOwner()->GetComponent<Transform>()->SetScale(init_scale);
		GetOwner()->Alive();
		isActive = true;
	}
	void BloodParticle::Active()
	{
		Vector3 owner_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(owner_pos.x += splash_power.x * Time::DeltaTime(), owner_pos.y += splash_power.y * Time::DeltaTime(), owner_pos.z);
		GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
		if (splash_power.y > drop_limit)
		{
			splash_power.y -= drop_speed * Time::DeltaTime();
		}
		Vector3 owner_scale = GetOwner()->GetComponent<Transform>()->GetScale();
		Vector3 fixed_scale = Vector3(owner_scale.x -= decrease_speed * Time::DeltaTime(), owner_scale.y -= decrease_speed * Time::DeltaTime(), owner_scale.z);
		GetOwner()->GetComponent<Transform>()->SetScale(fixed_scale);
		if (owner_scale.x <= decrease_limit)
		{
			isActive = false;
			GetOwner()->Death();
		}
	}
}