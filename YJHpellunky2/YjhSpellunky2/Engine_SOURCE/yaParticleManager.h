#pragma once
#include "yaGameObject.h"
#include "yaBloodParticle.h"
#include "yaBulletScript.h"
#include "yaSmallExplodeParticleScript.h"
#include "yaFintParticleScript.h"
#include "yaShotGunParticle.h"
#include "yaBounceParticleSript.h"

namespace ya
{
	class ParticleManager : public Script
	{
	public:
		ParticleManager();
		~ParticleManager();

		void Initialize();

		void SpawnBlood(Vector3 point);
		void SpawnBounce(Vector3 point);
		void SpawnFlint(GameObject* _target);
		void SpawnShotGun(Vector3 _point, int _direction);
		void SpawnExplosive(Vector3 _point);

		void SpawnDestroy(Vector3 Point, eBlockType type);
		void SpawnGetLife(Transform* target);

		void SpawnBurn();
		void SpawnLand();
		void SpawnGetTreasure();
		void SpawnHit();
		void SpawnFire(int direction);


	private:
		std::vector<GameObject*> bloods;
		std::vector<GameObject*> explosives;
		std::vector<GameObject*> flints;
		std::vector<GameObject*> shotguns;
		std::vector<GameObject*> bounces;

	};
}