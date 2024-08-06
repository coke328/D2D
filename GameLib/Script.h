#pragma once
#include "GameObject.h"

class Script //구조 좀더 생각해보죠
{
protected:

	GameObject& GetGameObject();

public:
	Script();

	virtual void Update(float deltaTime);
	virtual void FixedUpdate();

	
};

