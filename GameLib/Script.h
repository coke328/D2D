#pragma once
#include "GameObject.h"

class Script //���� ���� �����غ���
{
protected:

	GameObject& GetGameObject();

public:
	Script();

	virtual void Update(float deltaTime);
	virtual void FixedUpdate();

	
};

