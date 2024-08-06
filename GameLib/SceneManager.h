#pragma once
#include "Scene.h"
#include "Renderer.h"

class Game;

class SceneManager
{
	friend class Game;

	Scene* currentScene;

	void Update();
	void FixedUpdate();
	void LoopStart();
	void LoopEnd();

	Resources* pResources;

	SceneManager(Resources* res);
	void Render();

public:

	template<typename T>
	bool StartScene();
	Scene* GetCurrentScene();

};

template<typename T>
inline bool SceneManager::StartScene()
{
	if (!std::is_base_of_v<Scene, T>) {
		std::cout << "Create Scene Fail" << std::endl;
		return false;
	}
	if (currentScene != nullptr) {
		delete currentScene;
		currentScene = nullptr;
	}
	currentScene = dynamic_cast<Scene*>(new T());
	currentScene->Initialize(pResources);
	return true;
}
