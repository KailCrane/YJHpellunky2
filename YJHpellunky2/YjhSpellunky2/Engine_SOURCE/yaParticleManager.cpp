#include "yaParticleManager.h"
#include "yaObject.h"

namespace ya
{

	ParticleManager::ParticleManager()
	{

	}

	ParticleManager::~ParticleManager()
	{

	}

	void ParticleManager::Initialize()
	{
		Scene* add_Scene = SceneManager::GetPlayScene();

		for (int i = 0; i < 50; i++)
		{
			GameObject* blood_particle = object::Instantiate<GameObject>(eLayerType::Particle, add_Scene);
			BloodParticle* blood_script = blood_particle->AddComponent<BloodParticle>();
			bloods.push_back(blood_particle);
			blood_particle->Death();
		}

		for (int i = 0; i < 30; i++)
		{
			GameObject* explosive_particle = object::Instantiate<GameObject>(eLayerType::Particle, add_Scene);
			SmallExplodeParticleScript* explosive_script = explosive_particle->AddComponent<SmallExplodeParticleScript>();
			explosive_particle->Death();
			explosives.push_back(explosive_particle);
		}

		for (int i = 0; i < 50; i++)
		{
			GameObject* flint = object::Instantiate<GameObject>(eLayerType::Particle, add_Scene);
			FintParticleScript* flint_script = flint->AddComponent<FintParticleScript>();
			flint->Death();
			flints.push_back(flint);
		}

		for (int i = 0; i < 30; i++)
		{
			GameObject* shotgun_fire = object::Instantiate<GameObject>(eLayerType::Particle, add_Scene);
			ShotGunParticle* shotgun_script = shotgun_fire->AddComponent<ShotGunParticle>();
			shotgun_fire->Death();
			shotguns.push_back(shotgun_fire);
		}

		for (int i = 0; i < 30; i++)
		{
			GameObject* bounce = object::Instantiate<GameObject>(eLayerType::Particle, add_Scene);
			BounceParticleSript* bounce_script = bounce->AddComponent<BounceParticleSript>();
			bounce->Death();
			bounces.push_back(bounce);
		}
	}
	void ParticleManager::SpawnBlood(Vector3 point)
	{
		int a = 0;
		for (int i = 0; i < bloods.size(); i++)
		{
			if (bloods[i]->IsDead())
			{
				bloods[i]->GetScript<BloodParticle>()->SetPoint(point);

				switch (a)
				{
				case 0:
					bloods[i]->GetScript<BloodParticle>()->SetPower(Vector3(2, 3, 0));
					a++;
					break;
				case 1:
					bloods[i]->GetScript<BloodParticle>()->SetPower(Vector3(1, 4, 0));
					a++;
					break;
				case 2:
					bloods[i]->GetScript<BloodParticle>()->SetPower(Vector3(0, 5, 0));
					a++;
					break;
				case 3:
					bloods[i]->GetScript<BloodParticle>()->SetPower(Vector3(-1, 4, 0));
					a++;
					break;
				case 4:
					bloods[i]->GetScript<BloodParticle>()->SetPower(Vector3(-2, 3, 0));
				}
				
				bloods[i]->Alive();
				bloods[i]->GetScript<BloodParticle>()->OnActive();
				if (a == 4)
				{
					return;
				}
			}
		}
	}
	void ParticleManager::SpawnBounce(Vector3 point)
	{
		for (int i = 0; i < bounces.size(); i++)
		{
			if (bounces[i]->IsDead())
			{
				bounces[i]->GetComponent<BounceParticleSript>()->SetPoint(point);
				bounces[i]->Alive();
				bounces[i]->GetComponent<BounceParticleSript>()->OnActive();
				return;
			}
		}
	}

	void ParticleManager::SpawnFlint(GameObject* _target)
	{
		for (int i = 0; i < flints.size(); i++)
		{
			if (flints[i]->IsDead())
			{
				flints[i]->GetComponent<FintParticleScript>()->SetTarget(_target);
				flints[i]->Alive();
				flints[i]->GetComponent<FintParticleScript>()->OnActive();
				return;
			}	
		}
	}

	void ParticleManager::SpawnShotGun(Vector3 _point, int _direction)
	{
		for (int i = 0; i < shotguns.size(); i++)
		{
			if (flints[i]->IsDead())
			{
				shotguns[i]->GetComponent<ShotGunParticle>()->SetPoint(_point);
				shotguns[i]->GetComponent<ShotGunParticle>()->SetDirection(_direction);
				shotguns[i]->Alive();
				shotguns[i]->GetComponent<ShotGunParticle>()->OnActive();
				return;
			}
		}
	}
	
	void ParticleManager::SpawnExplosive(Vector3 _point)
	{
		for (int i = 0; i < explosives.size(); i++)
		{
			if (explosives[i]->IsDead())
			{
				explosives[i]->GetComponent<SmallExplodeParticleScript>()->SetPoint(_point);
				explosives[i]->Alive();
				explosives[i]->GetComponent<SmallExplodeParticleScript>()->OnActive();
				return;
			}
		}
	}

	void ParticleManager::SpawnDestroy(Vector3 Point, eBlockType type)
	{

	}
	void ParticleManager::SpawnGetLife(Transform* target)
	{
	}
	void ParticleManager::SpawnBurn()
	{
	}
	void ParticleManager::SpawnLand()
	{
	}
	void ParticleManager::SpawnGetTreasure()
	{
	}
	void ParticleManager::SpawnHit()
	{
	}
	void ParticleManager::SpawnFire(int direction)
	{
	}
}