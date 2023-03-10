#include "yaTitleScene.h"
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
#include "yaCollider2D.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"


namespace ya
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera,this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
		
		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);

		//MainBG
		GameObject* bgObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		bgObj->SetName(L"MenuTitle");
		Transform* bg_tr = bgObj->GetComponent<Transform>();
		bg_tr->SetPosition(Vector3(1.0f, 1.0f, 7.0f));
		bg_tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

		SpriteRenderer* mr = bgObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MenuTitleMaterial");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);


		{
		GameObject* bggalObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		bggalObj->SetName(L"MenuBgGal");
		Transform* bggal_tr = bggalObj->GetComponent<Transform>();
		bggal_tr->SetPosition(Vector3(-2.5f, 0.8f, 6.0f));
		bggal_tr->SetScale(Vector3(9.0f, 9.0f, 1.0f));

		SpriteRenderer* mr = bggalObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"MenuTitlegalMaterial");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);
		}

		

		{
			//Player* monster = object::Instantiate<Player>(eLayerType::Monster);
			//monster->SetName(L"MONSTER");
			//Transform* mtr = monster->GetComponent<Transform>();
			//mtr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
			////tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			//mtr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			//Collider2D* collider = monster->AddComponent<Collider2D>();
			//collider->SetType(eColliderType::Circle);
			////collider->SetSize(Vector2(1.5f, 1.5f));

		/*	SpriteRenderer* mr = monster->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);*/
			//object::DontDestroyOnLoad(monster);
		}

		////SMILE RECT CHild
		//GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
		//child->SetName(L"SMILE");
		//Transform* childTr = child->GetComponent<Transform>();
		//childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		//childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//childTr->SetParent(tr);

		//MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		//std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		//childMr->SetMaterial(childmateiral);
		//childMr->SetMesh(mesh);

		//// HPBAR
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Player);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTR = hpBar->GetComponent<Transform>();
		//hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		//hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		//SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		//hpBar->AddComponent(hpsr);
		//std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//hpsr->SetMesh(hpmesh);
		//hpsr->SetMaterial(hpspriteMaterial);

		//CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::CharacterSelect);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}
