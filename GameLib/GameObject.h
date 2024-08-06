#pragma once
#include "RenderComponents.h"
#include "Collider.h"
#include "Transform.h"
#include "vectorMap.h"

class Scene;

//addcomponent´Â init¿¡¼­
class GameObject
{
	friend class Scene;

	void GameObjectUpdate();
	void GameObjectFixedUpdate();//not use?
	void LoopStart();
	void LoopEnd();
	void Initialize(Scene* _scene);

	vectorMap<std::string, CompIdx> components;
	std::vector<unsigned int> renderCompIdx;

	std::string name;
	Scene* scene;

	void Destroy();
protected:
	

	template<class C>
	pComponent<C*> AddComponent();
	template<class C>
	pComponent<C*> FindComponent();
	template<class C>
	void DestroyComponent();

	void SetName(std::string _name);
	Scene& GetScene();

	virtual void Init() = 0;
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();

	
public:
	GameObject();
	
	virtual ~GameObject();

	transform m_transform;

};

template<size_t n>
void PolygonCollider::Init(const std::array<Vector2f, n>& arr)
{
	if (n < 3) {
		std::cout << "polygonCollider init fail" << std::endl;
		return;
	}

	polygon.SetPoints(arr);
	polygon.SetTransform(&gameObject->m_transform);
}

template<size_t n>
inline void PolygonRender::Init(const std::array<Vector2f, n>& arr)
{
	if (n < 3) {
		std::cout << "polygonCollider init fail" << std::endl;
		return;
	}

	polygon.SetPoints(arr);
	polygon.SetTransform(&gameObject->m_transform);
}

template<class C>
inline pComponent<C*> GameObject::AddComponent()
{
	pComponent<C*> pCom = CreateComponent<C>::Get().Create();
	pCom.Get()->compInit(this, pCom.Idx());
	components.Push(typeid(C).raw_name(), pCom.Idx());
	if (std::is_base_of<RenderComponent, C>::value) {
		renderCompIdx.push_back(components.Size()-1);
		//std::cout << typeid(C).name() << components.Size() - 1 << std::endl;
	}
	
	return pCom;
}

template<class C>
inline pComponent<C*> GameObject::FindComponent()
{
	return components.FindObject(typeid(C).raw_name());
	
}

template<class C>
inline void GameObject::DestroyComponent()
{
	Components::GetInstance().EraseComponent(FindComponent<C>());
}
