#pragma once
#include "GameLib.h"
#include "Object.h"

class MainScene : public Scene
{
	MovePoly* player;
	Object* poly;
	Floor* floor;

	std::list<Stone> stones;
	std::list<Object> blocks;
	Vector2f ShootingPoint;
	float clickRadius;
	float MaxPull;
	float ShootPower;
	bool clicked;
	float reloadTime;
	float reloadT;
	bool reloadEnd;
public:
	MainScene();

	void Shoot(Vector2f deltaPos);
	Stone* AddStone();
	void AddBlock(objectsShape shape,Vector2f pos);

	void SceneLoad() override;
	void SceneEnd() override;
	void SceneUpdate() override;
	void SceneFixedUpdate() override;
	void Render() override;

};

