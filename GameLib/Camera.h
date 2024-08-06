#pragma once
#include "Typedef.h"
#include "Transform.h"
#include "GameObject.h"

class Scene;

class Camera : public GameObject
{
	friend class Scene;

	Camera();
public:
	void Init() override;


};

