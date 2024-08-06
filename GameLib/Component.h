#pragma once
#include "Typedef.h"
#include "Vector2f.h"
#include "TimeSystem.h"
#include "CreateComponent.h"

class GameObject;
class Scene;


//생성자에 매개변수 넣지마 생성자에선 아직 init이 안된상태
class Component
{
private:
	friend class GameObject;
	
	template<typename T>
	friend class CreateComponent;

protected:
	
	CompIdx compidx;
	GameObject* gameObject;

	
	Component();
	virtual void Destructor() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate();
public:
	void compInit(GameObject* _gameObject, const CompIdx& idx);
	virtual void Init();
	virtual ~Component();
	
	
};

