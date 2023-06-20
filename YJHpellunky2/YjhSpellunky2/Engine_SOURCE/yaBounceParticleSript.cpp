#include "yaBounceParticleSript.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	BounceParticleSript::BounceParticleSript()
		:isActive(false),
		curr_time(0.0f),
		disapear_time(0.5f),
		ring(nullptr),
		ring_grow_speed(2.0f),
		ring_move_speed(1.0f),
		init_ring_size(Vector3(0.1f, 0.1f, 1.1f))
	{

	}

	BounceParticleSript::~BounceParticleSript()
	{
	}

	void BounceParticleSript::Initialize()
	{
		Scene* curr_scene = SceneManager::GetPlayScene();
		{
			ring = object::Instantiate<GameObject>(eLayerType::Particle, curr_scene);
			Transform* ring_tr = ring->GetComponent<Transform>();
			ring_tr->SetScale(Vector3(0.1f, 0.1f, 1.2f));

			SpriteRenderer* mr = ring->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"BounceRingMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			ring->Death();
		}

		for (int i = 0; i < 3; i++)
		{
			GameObject* star = object::Instantiate<GameObject>(eLayerType::Detector, curr_scene);
			Transform* star_tr = star->GetComponent<Transform>();
			star_tr->SetScale(Vector3(0.3f, 0.3f, 1.1f));

			SpriteRenderer* mr = star->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"BounceStarMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			stars.push_back(star);
			star->Death();
		}
	}

	void BounceParticleSript::Update()
	{
		if (isActive)
		{
			Active();
		}
	}

	void BounceParticleSript::Render()
	{

	}

	void BounceParticleSript::SetPoint(Vector3 point)
	{
		start_point = point;
		ring->GetComponent<Transform>()->SetPosition(point);
		for (int i = 0; i < 3; i++)
		{
			stars[i]->GetComponent<Transform>()->SetPosition(Vector3(point.x, point.y + 0.2f, point.z));
		}
	}

	void BounceParticleSript::OnActive()
	{
		ring->Alive();
		for (int i = 0; i < 3; i++)
		{
			stars[i]->Alive();
		}
		ring->GetComponent<Transform>()->SetScale(init_ring_size);
		curr_time = 0.0f;
		isActive = true;
	}

	void BounceParticleSript::Active()
	{
		curr_time += Time::DeltaTime();

		Transform* ring_tr = ring->GetComponent<Transform>();
		//링이 커지는것
		Vector3 ring_scale = ring_tr->GetScale();
		Vector3 fixed_ring_scale = Vector3(ring_scale.x + ring_grow_speed * Time::DeltaTime(), ring_scale.y + ring_grow_speed * Time::DeltaTime(), ring_scale.z);
		ring_tr->SetScale(fixed_ring_scale);
		//링이 올라가는것
		Vector3 ring_pos = ring_tr->GetPosition();
		Vector3 fixed_ring_pos = Vector3(ring_pos.x, ring_pos.y += ring_move_speed * Time::DeltaTime(), ring_pos.z);

		for (int i = 0; i < 3; i++)
		{
			const int num = i;

			Transform* star_tr = stars[i]->GetComponent<Transform>();
			Vector3 star_pos = star_tr->GetPosition();
			Vector3 fixed_star_pos;

			switch (num)
			{
			case 0:
				fixed_star_pos= Vector3(star_pos.x, star_pos.y += ring_move_speed * Time::DeltaTime(), ring_pos.z);
				break;
			case 1:
				fixed_star_pos = Vector3(star_pos.x -= Time::DeltaTime(), star_pos.y += ring_move_speed/2 * Time::DeltaTime(), ring_pos.z);
				break;
			case 2:
				fixed_star_pos = Vector3(star_pos.x += Time::DeltaTime(), star_pos.y += ring_move_speed/2 * Time::DeltaTime(), ring_pos.z);
				break;
			}
			star_tr->SetPosition(fixed_star_pos);
		}

		if (curr_time >= disapear_time)
		{
			ring->Death();

			for (int i = 0; i < 3; i++)
			{
				stars[i]->Death();
			}

			isActive = false;
		}
	}
}