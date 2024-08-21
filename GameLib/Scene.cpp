#include "pch.h"
#include "Scene.h"
#include "Camera.h"

void Scene::RemoveGameObject(std::string _objectName)
{
	GameObjects.Erase(_objectName);
}

void Scene::DeleteScene()
{
	SceneEnd();

	Renderer::GetInstance().CompsClear();
	GameObjects.ClearDelete();
}

GameObject* Scene::FindGameObject(std::string _name)
{

	return *GameObjects.FindObject(_name);
}

void Scene::Update()
{
	

	for (auto gameObject : *GameObjects)
	{
		gameObject->GameObjectUpdate();
	}
	SceneUpdate();
}

void Scene::FixedUpdate()
{
	for (auto gameObject : *GameObjects)
	{
		gameObject->GameObjectFixedUpdate();
	}
	SceneFixedUpdate();
}

void Scene::LoopStart()
{
	for (auto gameObject : *GameObjects)
	{
		gameObject->LoopStart();
	}
}

void Scene::LoopEnd()
{
	for (auto gameObject : *GameObjects)
	{
		gameObject->LoopEnd();
	}
}

Scene::Scene()
{
	
}

Scene::~Scene()
{

	DeleteScene();
}

void Scene::SceneLoad()
{
}

void Scene::SceneEnd()
{
	
}

void Scene::SceneUpdate()
{
}

void Scene::SceneFixedUpdate()
{
}

void Scene::Render()
{
}

void Scene::Initialize(Resources* res)
{
	sceneResource.Initialize(res);

	camera = new Camera();
	AddGameObject(camera);
	Renderer::GetInstance().SetCamera(camera);

	SceneLoad();
}
