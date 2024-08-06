#include "pch.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"

void GameObject::GameObjectUpdate()
{
	Update();
}

void GameObject::GameObjectFixedUpdate()
{
	/*for (auto com : components) {
		com->FixedUpdate();
	}*/

	FixedUpdate();
}

void GameObject::LoopStart()
{
	
}

void GameObject::LoopEnd()
{
	m_transform.EndofFrame();
}

void GameObject::Initialize(Scene* _scene)
{
	Init();

	for (auto idx : renderCompIdx)
		Renderer::GetInstance().AddRenderComponent((*components)[idx]);

	RenderComponent::renderOrderChanged = true;

	scene = _scene;

	Start();
}

void GameObject::Start() {

}

void GameObject::Update()
{
}

void GameObject::FixedUpdate()
{
}

GameObject::GameObject()
{
	scene = nullptr;
	
}

void GameObject::SetName(std::string _name)
{
	if (!name.empty()) {
		std::cout << "cant change name" << std::endl;
		return;
	}
		
	name = _name;

	
}

Scene& GameObject::GetScene()
{
	return *scene;
}

GameObject::~GameObject()
{
	Destroy();
}

void GameObject::Destroy()
{

	for (const auto& idx : *components) {
		Components::GetInstance().EraseComponent(idx);
	}

	scene->RemoveGameObject(name);
}
