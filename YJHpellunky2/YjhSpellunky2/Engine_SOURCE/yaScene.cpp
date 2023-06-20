#include "yaScene.h"


namespace ya
{
	Scene::Scene(eSceneType type)
		: mType(type)
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initalize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initalize();
		}
	}
	void Scene::Update()
	{
		if (mType == eSceneType::Play)
		{
			int a = 0;

			for (Layer& layer : mLayers)
			{
				if (layer.GetName() == L"Camera")
				{
					int a = 0;
				}

			}
		}

		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		//씬이 플레이 씬일때
		//아니라면 그냥 다 렌더
		//
		


		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{

	}
	void Scene::OnExit()
	{

	}
	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);
	}
	
	std::vector<GameObject*> Scene::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> gameObjects;
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*> dontGameObjs
				= layer.GetDontDestroyGameObjects();

			gameObjects.insert(gameObjects.end()
			, dontGameObjs.begin()
			, dontGameObjs.end());
		}

		return gameObjects;
	}
	const std::vector<GameObject*>& Scene::GetGameObjects(const eLayerType type)
	{
		return mLayers[(UINT)type].GetGameObjects();
	}
}
