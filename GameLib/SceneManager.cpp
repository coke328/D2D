#include "pch.h"
#include "SceneManager.h"


SceneManager::SceneManager(Resources* res) :
	pResources(res),
	currentScene(nullptr)
{
	//StartScene<Scene>();
	//currentScene->Initialize(pRenderer);
}

void SceneManager::Render()
{
	currentScene->Render();
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::Update()
{
	currentScene->Update();
}

void SceneManager::FixedUpdate()
{
	currentScene->FixedUpdate();
}

void SceneManager::LoopStart()
{
	currentScene->LoopStart();
}

void SceneManager::LoopEnd()
{
	currentScene->LoopEnd();
}
