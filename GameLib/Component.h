#pragma once
#include "Typedef.h"
#include "TimeSystem.h"
#include "CreateComponent.h"

class GameObject;
class Scene;


//�����ڿ� �Ű����� ������ �����ڿ��� ���� init�� �ȵȻ���
class Component
{
private:
	friend class GameObject;
	
	template<typename T>
	friend class CreateComponent;


	unsigned int* idx;

	void dest();
	void compInit(GameObject* _gameObject, const CompIdx& idx);
protected:
	
	CompIdx compidx;
	GameObject* gameObject;

	
	Component();
	
	virtual void Destructor() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate();

	virtual void Init();
public:
	virtual ~Component();
};

