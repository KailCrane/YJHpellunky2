#include "yaPlayScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaAnimator.h"
#include "yaAnimation.h"
#include "yaRigidbody.h"
#include "yaCollisionManager.h"
#include "yaWhip.h"
#include "yaWhipScript.h"
#include "yaShotgun.h"
#include "yaShotGunScript.h"
#include "yaBullet.h"
#include "yaBulletScript.h"
#include "yaRopeThrowScript.h"
#include "yaRope.h"
#include "yaRopeScript.h"
#include "yaCaveman.h"
#include "yaMonster.h"
#include "yaSkeleton.h"
#include "yaStageResult.h"
#include "yaParticleManager.h"

namespace ya
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{
		
	}

	PlayScene::~PlayScene()
	{
		delete gamehud;
	}

	void PlayScene::Initalize()
	{
		cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(cameraComp->Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

#pragma region  "UI Camera"


		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
#pragma endregion

		gamehud = new GameHud();
		gamehud->SetScene(this);
		gamehud->SetUp();

		GameObject* particle_manager = object::Instantiate<GameObject>(eLayerType::None, this);
		ParticleManager* pManager = particle_manager->AddComponent<ParticleManager>();

		//Player RECT
		{
			my_player = object::Instantiate<Player>(eLayerType::Player, this);
			my_player->SetName(L"Player");
			Transform* player_tr = my_player->GetComponent<Transform>();
			my_player->SetLayerType(eLayerType::Player);

			player_tr->SetPosition(Vector3(3.0f, -2.0f, 1.1f));
			player_tr->SetScale(Vector3(1.0f, 1.0f, 1.1f));

			//animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
			//좌측상단좌표,좌측상단으로부터 잘라낼 범위, 발끝, 잘라낸 크기 , 프레임당 지속
			{
			SpriteRenderer* mr = my_player->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}
			pScript = my_player->AddComponent<PlayerScript>();
			pScript->SetCamera(cameraObj);
			pScript->SetHud(gamehud);
			inventory = my_player->AddComponent<Inventory>();
			pScript->SetInventory(inventory);
			pScript->SetStage(stage.GetStage());
			gamehud->SetPscript(pScript);
			inventory->SetUp(gamehud);

			Rigidbody* pRb = my_player->AddComponent<Rigidbody>();

			RopeThrowScript* rope_throw = my_player->AddComponent<RopeThrowScript>();

			for (int i = 0; i < 100; i++)
			{
				Rope* rope_obj = object::Instantiate<Rope>(eLayerType::Rope, this);
				rope_obj->SetName(L"Rope" + i);
				Transform* rope_tr = rope_obj->GetComponent<Transform>();
				rope_obj->SetLayerType(eLayerType::Rope);

				rope_tr->SetPosition(Vector3(0.0f, 1.0f, 1.1f));
				//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
				rope_tr->SetScale(Vector3(1.0f, 1.0f, 1.1f));
				Collider2D* collider = rope_obj->AddComponent<Collider2D>();
				collider->SetType(eColliderType::Rect);
				collider->SetSize(Vector2(0.5f, 1.2f));

				Animator* rope_animator = rope_obj->AddComponent<Animator>();
				std::shared_ptr<Texture> Rope_texture = Resources::Load<Texture>(L"RopeR", L"char_yellowR.png");

				RopeScript* rope_script = rope_obj->AddComponent<RopeScript>();

				rope_animator->Create(L"RopeTop", Rope_texture, Vector2(128.0f * 12, 128.0f * 9), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
				rope_animator->Create(L"RopeTopUnfold", Rope_texture, Vector2(128.0f * 13, 128.0f * 9), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
				rope_animator->Create(L"RopeRoll", Rope_texture, Vector2(128.0f * 4, 128.0f * 12), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
				rope_animator->Create(L"RopeEnd", Rope_texture, Vector2(128.0f * 5, 128.0f * 12), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
				rope_animator->Create(L"RopeMiddle", Rope_texture, Vector2(128.0f * 0, 128.0f * 12), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);


				//rope_animator->Play(L"RopeTop", false);

				rope_animator->Play(L"RopeMiddle", false);
				//whip_animator->Play(L"WhipIdle", false);

				SpriteRenderer* mr = rope_obj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
				mr->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->SetMesh(mesh);

				rope_throw->SetRopeDummy(rope_obj, i);
				rope_obj->Death();
			};
		}


		stage.SetScene(this);
		stage.SetPlayer(my_player);
		stage.SetParticleManager(pManager);
		stage.LoadStage(0);

		{
			GameObject* result_obj = object::Instantiate<GameObject>(eLayerType::UI, this);
			result_obj->SetName(L"Result");
			result =  result_obj->AddComponent<StageResult>();
			pScript->SetResult(result);
		}


		{
			Whip* whip_obj = object::Instantiate<Whip>(eLayerType::Whip, this);
			whip_obj->SetName(L"Whip");
			Transform* whip_tr = whip_obj->GetComponent<Transform>();
			whip_obj->SetLayerType(eLayerType::Whip);

			whip_tr->SetPosition(Vector3(0.0f, 1.0f, 1.1f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			whip_tr->SetScale(Vector3(0.65f, 0.65f, 0.0f));
			//whip_tr->SetParent(mPlayer->GetComponent<Transform>());
			Collider2D* collider = whip_obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(1.1f, 1.1f));
			collider->SetName(L"WhipCollider");

			whip = whip_obj->AddComponent<WhipScript>();
			whip->SetPlayer(my_player);
			

			SpriteRenderer* mr = whip_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);

			pScript->SetWhip(whip);
			whip_obj->Death();
		}


		/*Skeleton* testSkull = object::Instantiate<Skeleton>(eLayerType::Monster,this);
		testSkull->SetScene(this);*/
		{
			/*Monster* caveman_obj = object::Instantiate<Monster>(eLayerType::Monster, this);
			caveman_obj->SetLayerType(eLayerType::Monster);
			caveman_obj->SetName(L"CaveMan1");
			Transform* tr = caveman_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(-1.0f,1.0f,1.1f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.1f));

			Collider2D* collider = caveman_obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.5f, 0.5f));

			Animator* caveman_animator = caveman_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> caveman_texture_L = Resources::Load<Texture>(L"CavemanL", L"monstersbasic02L.png");
			std::shared_ptr<Texture> caveman_texture_R = Resources::Load<Texture>(L"CavemanR", L"monstersbasic02R.png");

			caveman_animator->Create(L"CavemanIdle", caveman_texture_R, Vector2(0.0f, 640.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
			caveman_animator->Create(L"CavemanDead", caveman_texture_R, Vector2(128.0 * 11, 640.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
			caveman_animator->Play(L"CavemanIdle", false);

			Caveman* caveman_script = caveman_obj->AddComponent<Caveman>();
			Rigidbody* caveman_Rb = caveman_obj->AddComponent<Rigidbody>();

			SpriteRenderer* mr = caveman_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);


			ColTransfer* mHead_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterHead, this);;
			mHead_obj->SetName(L"MonsterHead");
			mHead_obj->SetLayerType(eLayerType::MonsterHead);
			Transform* mHead_tr = mHead_obj->GetComponent<Transform>();
			mHead_tr->SetPosition(Vector3(0, 0, 0));
			mHead_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mHead_collider = mHead_obj->AddComponent<Collider2D>();
			mHead_collider->SetType(eColliderType::Rect);
			mHead_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetHead(mHead_obj);

			ColTransferScript* mHead_colTransfer = mHead_obj->AddComponent<ColTransferScript>();
			mHead_colTransfer->SetReceiver(caveman_script);

			ColTransfer* mFeet_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterFeet, this);;
			mFeet_obj->SetName(L"MonsterFeet");
			mFeet_obj->SetLayerType(eLayerType::MonsterFeet);
			Transform* mFeet_tr = mFeet_obj->GetComponent<Transform>();
			mFeet_tr->SetPosition(Vector3(0, 0, 0));
			mFeet_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mFeet_collider = mFeet_obj->AddComponent<Collider2D>();
			mFeet_collider->SetType(eColliderType::Rect);
			mFeet_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetFeet(mFeet_obj);

			ColTransferScript* mFeet_colTransfer = mFeet_obj->AddComponent<ColTransferScript>();
			mFeet_colTransfer->SetReceiver(caveman_script);

			ColTransfer* mL_body_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterLeftbody, this);;
			mL_body_obj->SetName(L"MonsterLeftBody");
			mL_body_obj->SetLayerType(eLayerType::MonsterLeftbody);
			Transform* mL_body_tr = mL_body_obj->GetComponent<Transform>();
			mL_body_tr->SetPosition(Vector3(0, 0, 0));
			mL_body_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mL_body_collider = mL_body_obj->AddComponent<Collider2D>();
			mL_body_collider->SetType(eColliderType::Rect);
			mL_body_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetLeftBody(mL_body_obj);

			ColTransferScript* mL_body_colTransfer = mL_body_obj->AddComponent<ColTransferScript>();
			mL_body_colTransfer->SetReceiver(caveman_script);

			ColTransfer* mR_body_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterRightBody, this);;
			mR_body_obj->SetName(L"MonsterRightBody");
			mR_body_obj->SetLayerType(eLayerType::MonsterRightBody);
			Transform* mR_body_tr = mR_body_obj->GetComponent<Transform>();
			mR_body_tr->SetPosition(Vector3(0, 0, 0));
			mR_body_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mR_body_collider = mR_body_obj->AddComponent<Collider2D>();
			mR_body_collider->SetType(eColliderType::Rect);
			mR_body_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetRightBody(mR_body_obj);

			ColTransferScript* mR_body_colTransfer = mR_body_obj->AddComponent<ColTransferScript>();
			mR_body_colTransfer->SetReceiver(caveman_script);

			ColTransfer* mL_Detect_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterLeftDetect, this);;
			mL_Detect_obj->SetName(L"MonsterLeftDetect");
			mL_Detect_obj->SetLayerType(eLayerType::MonsterLeftDetect);
			Transform* mL_Detect_tr = mL_Detect_obj->GetComponent<Transform>();
			mL_Detect_tr->SetPosition(Vector3(0, 0, 0));
			mL_Detect_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mL_Detect_collider = mL_Detect_obj->AddComponent<Collider2D>();
			mL_Detect_collider->SetType(eColliderType::Rect);
			mL_Detect_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetLeftDetectObj(mL_Detect_obj);

			ColTransferScript* mL_Detect_colTransfer = mL_Detect_obj->AddComponent<ColTransferScript>();
			mL_Detect_colTransfer->SetReceiver(caveman_script);

			ColTransfer* mR_Detect_obj = object::Instantiate<ColTransfer>(eLayerType::MonsterRightBody, this);;
			mR_Detect_obj->SetName(L"MonsterLeftDetect");
			mR_Detect_obj->SetLayerType(eLayerType::MonsterRightBody);
			Transform* mR_Detect_tr = mR_Detect_obj->GetComponent<Transform>();
			mR_Detect_tr->SetPosition(Vector3(0, 0, 0));
			mR_Detect_tr->SetScale(Vector3(0.2f, 1, 1));
			Collider2D* mR_Detect_collider = mR_Detect_obj->AddComponent<Collider2D>();
			mR_Detect_collider->SetType(eColliderType::Rect);
			mR_Detect_collider->SetSize(Vector2(1.5f, 0.4f));

			caveman_script->SetLeftDetectObj(mR_Detect_obj);

			ColTransferScript* mR_Detect_colTransfer = mR_Detect_obj->AddComponent<ColTransferScript>();
			mR_Detect_colTransfer->SetReceiver(caveman_script);*/
		}



			/*Shotgun* shotgun_obj = object::Instantiate<Shotgun>(eLayerType::ShotGun, this);
			shotgun_obj->SetLayerType(eLayerType::ShotGun);
			shotgun_obj->SetName(L"Shotgun");

			Transform* tr = shotgun_obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 3.0f, 0.8f));
			tr->SetScale(Vector3(0.7f, 0.7f, 1.0f));

			Collider2D* collider = shotgun_obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.8f, 0.5f));

			Animator* shotgun_animator = shotgun_obj->AddComponent<Animator>();
			std::shared_ptr<Texture> shotgun_texture_L = Resources::Load<Texture>(L"ShotgunL", L"itemsL.png");
			std::shared_ptr<Texture> shotgun_texture_R = Resources::Load<Texture>(L"ShotgunR", L"itemsR.png");

			shotgun_animator->Create(L"IdleL", shotgun_texture_L, Vector2(128.0f * 15.0f, 384.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
			shotgun_animator->Create(L"IdleR", shotgun_texture_R, Vector2(0.0f, 384.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);

			shotgun_animator->Play(L"IdleR", false);
			shotgun_obj->AddComponent<Rigidbody>();
			ShotGunScript* shogun_Script = shotgun_obj->AddComponent<ShotGunScript>();

			SpriteRenderer* mr = shotgun_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);*/


			/*for (int i = 0; i < 100; i++)
			{
				Bullet* bullet_obj = object::Instantiate<Bullet>(eLayerType::Bullet, this);
				bullet_obj->SetLayerType(eLayerType::Bullet);
				bullet_obj->SetName(L"Bullet");
				Transform* tr = bullet_obj->GetComponent<Transform>();
				tr->SetPosition(Vector3(0.0f, 3.0f, 1.1f));
				tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

				Collider2D* bullet_collider = bullet_obj->AddComponent<Collider2D>();
				bullet_collider->SetType(eColliderType::Rect);
				bullet_collider->SetSize(Vector2(0.2f, 0.2f));

				Animator* animator = bullet_obj->AddComponent<Animator>();
				std::shared_ptr<Texture> bullet_texture = Resources::Load<Texture>(L"BulletR", L"itemsR.png");

				animator->Create(L"Idle", bullet_texture, Vector2(0.0f, 128.0f * 14.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
				animator->Play(L"Idle", false);

				bullet_obj->AddComponent<BulletScript>();

				SpriteRenderer* mr = bullet_obj->AddComponent<SpriteRenderer>();
				std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
				mr->SetMaterial(mateiral);
				std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
				mr->SetMesh(mesh);

				shogun_Script->SetBullet(bullet_obj, i);
				bullet_obj->Death();
			}*/

#pragma region BG


		GameObject* caveBgObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		caveBgObj->SetName(L"CaveBg");
		Transform* caveBg_tr = caveBgObj->GetComponent<Transform>();
		caveBg_tr->SetPosition(Vector3(0.0f, 1.0f, 6.0f));
		caveBg_tr->SetScale(Vector3(100.0f, 100.0f, 1.0f));

		SpriteRenderer* caveBgmr = caveBgObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CaveBgMaterial");
		caveBgmr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> caveBgmesh = Resources::Find<Mesh>(L"RectMesh");
		caveBgmr->SetMesh(caveBgmesh);

		/*GameObject* floorObj = object::Instantiate<GameObject>(eLayerType::Ground, this);
		floorObj->SetName(L"FloorBg");
		floorObj->SetLayerType(eLayerType::Ground);
		Transform* floor_tr = floorObj->GetComponent<Transform>();
		floor_tr->SetPosition(Vector3(0.0f, -1.0f, 1.2f));
		floor_tr->SetScale(Vector3(15.0f, 5.0f, 1.0f));
		Collider2D* collider = floorObj->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);
		collider->SetSize(Vector2(1.1f, 0.3f));
		collider->SetCenter(Vector2(0.0f,0.0f));
		floorObj->GetLayerType();

		SpriteRenderer* floormr = floorObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> floor_mateiral = Resources::Find<Material>(L"level1_floorMaterial");
		floormr->SetMaterial(floor_mateiral);
		std::shared_ptr<Mesh> floor_mesh = Resources::Find<Mesh>(L"RectMesh");
		floormr->SetMesh(floor_mesh);*/

		/*GameObject* entranceObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		entranceObj->SetName(L"EntranceBg");
		Transform* entrance_tr = entranceObj->GetComponent<Transform>();
		entrance_tr->SetPosition(Vector3(0.0f,-0.31f, 1.1f));
		entrance_tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

		SpriteRenderer* entrance_mr = entranceObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> entrance_mateiral = Resources::Find<Material>(L"deco_basecamp_entranceMaterial");
		entrance_mr->SetMaterial(entrance_mateiral);
		std::shared_ptr<Mesh> entrance_mesh = Resources::Find<Mesh>(L"RectMesh");
		entrance_mr->SetMesh(entrance_mesh);

		GameObject* uroborosObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		uroborosObj->SetName(L"EntranceBg");
		Transform* uroboros_tr = uroborosObj->GetComponent<Transform>();
		uroboros_tr->SetPosition(Vector3(0.0f, 1.0f, 6.0f));
		uroboros_tr->SetScale(Vector3(1.0f, 0.7f, 1.0f));

		SpriteRenderer* uroboros_mr = uroborosObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> uroboros_mateiral = Resources::Find<Material>(L"deco_basecamp_uroborosMaterial");
		uroboros_mr->SetMaterial(uroboros_mateiral);
		std::shared_ptr<Mesh> uroboros_mesh = Resources::Find<Mesh>(L"RectMesh");
		uroboros_mr->SetMesh(uroboros_mesh);*/
		

#pragma endregion
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Ground,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::ShotGun,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Ground,true);

		CollisionManager::CollisionLayerCheck(eLayerType::MonsterFeet, eLayerType::Ground,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterHead,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Feet, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Head, eLayerType::Ceiling, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::Ceiling, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::LeftSide, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::RightSide, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::Item, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Feet, eLayerType::MonsterHead, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Feet, eLayerType::ExitDoor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Head, eLayerType::ExitDoor, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::ExitDoor, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Detector, eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Detector, eLayerType::Feet, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Detector, eLayerType::Head, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Detector, eLayerType::Body, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Whip, eLayerType::Monster,true);

		CollisionManager::CollisionLayerCheck(eLayerType::Whip, eLayerType::MonsterBody,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Whip, eLayerType::MonsterHead,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Whip, eLayerType::MonsterFeet,true);


		CollisionManager::CollisionLayerCheck(eLayerType::ShotGun, eLayerType::Ground,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Rope, eLayerType::Feet,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Rope, eLayerType::Head,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Whip, eLayerType::Monster,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster,true);
		CollisionManager::CollisionLayerCheck(eLayerType::Detector, eLayerType::Player,true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterBody, eLayerType::Ground,true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterBody, eLayerType::Player,true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterFeet, eLayerType::Ground, true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterFeet, eLayerType::Player, true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterHead, eLayerType::Ground,true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterHead, eLayerType::Player,true);

		//Scene::Initalize();
	}

	void PlayScene::Update()
	{
		
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		//stage.Update();
		if (Input::GetKeyDown(eKeyCode::O))
		{
			stage.Reset();
		}
		/*if (Input::GetKeyDown(eKeyCode::O))
		{
			std::vector<GameObject*> gs = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Tile);
			for (int i = 0; i < gs.size(); i++)
			{
				gs[i]->Death();
			}
			std::vector<GameObject*> Ds = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Ground);
			for (int i = 0; i < gs.size(); i++)
			{
				Ds[i]->Death();
			}

		}*/
	
		//만약에 게임이 진행 중이라면

		gamehud->Update();
		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		isSceneActive = true;
	}

	void PlayScene::OnExit()
	{
		isSceneActive = false;
	}

}
