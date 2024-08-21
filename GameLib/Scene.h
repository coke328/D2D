#pragma once
#include "GameObject.h"
#include "Resources.h"

class SceneManager;
class Camera;

class Scene
{
	friend class SceneManager;

	vectorMap<std::string, GameObject*> GameObjects;

	void Update();
	void FixedUpdate();
	void LoopStart();
	void LoopEnd();

	void Initialize(Resources* res);//set camera and resource
	void DeleteScene();


protected:

	Scene();
	virtual void SceneLoad();
	virtual void SceneEnd();
	virtual void SceneUpdate();
	virtual void SceneFixedUpdate();

	virtual void Render();

public:
	Camera* camera;
	Resources sceneResource;
	
	virtual ~Scene();

	template<typename T>
	void AddGameObject(T* gameObject);
	void RemoveGameObject(std::string _objectName);
	
	GameObject* FindGameObject(std::string _name);
};

template<typename T>
inline void Scene::AddGameObject(T* gameObject)
{
	if (gameObject == nullptr) return;

	GameObject* object = dynamic_cast<GameObject*>(gameObject);

	object->Initialize(this);

	if (object->name.empty()) {
		std::string str = std::to_string((int)object);
		GameObjects.Push(str, object);
		object->name = str;
	}
	else {
		GameObjects.Push(object->name, object);
	}
}
