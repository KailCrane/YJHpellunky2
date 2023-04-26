#include "yaCharacterSelectScene.h"
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
#include "yaCollisionManager.h"


namespace ya
{
	CharacterSelectScene::CharacterSelectScene()
		: Scene(eSceneType::CharacterSelect)
	{
	
	}
	CharacterSelectScene::~CharacterSelectScene()
	{
		

	}
	void CharacterSelectScene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		GameObject* chrselBgObj = object::Instantiate<GameObject>(eLayerType::Bg, this);
		chrselBgObj->SetName(L"ChrSelBg");
		Transform* chrselBg_tr = chrselBgObj->GetComponent<Transform>();
		chrselBg_tr->SetPosition(Vector3(1.2f, 1.0f, 6.0f));
		chrselBg_tr->SetScale(Vector3(11.0f, 7.0f, 1.0f));

		SpriteRenderer* mr = chrselBgObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"ChrSelMaterial");
		mr->SetMaterial(mateiral);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		// 후에 전체대신 캐릭터를 분리 셀렉이 확인될시 정해진 행동 재생
		// 다시한번 fade in out 넣을것
		// 공동 마을 씬을 스킵 할지 고민할것
		// 텍스트박스 기능이 필요


		Scene::Initalize();
	}
	void CharacterSelectScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void CharacterSelectScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void CharacterSelectScene::Render()
	{
		Scene::Render();
	}
	void CharacterSelectScene::OnEnter()
	{
	}
	void CharacterSelectScene::OnExit()
	{
	}
}