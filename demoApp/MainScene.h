#pragma once
#include "GameLib.h"
#include "Object.h"

class MainScene : public Scene
{
public:
	MovePoly* player;
	Object* poly;
	Floor* floor;

	void SceneLoad() override;
	void SceneEnd() override;
	void SceneUpdate() override;
	void SceneFixedUpdate() override;
	void Render() override;

};

