#include "MainScene.h"

MainScene::MainScene()
{
	ShootingPoint = { -700,-350 };
	clickRadius = 20;
	clicked = false;
	MaxPull = 100;
	ShootPower = 40;
	reloadTime = 1.5f;
	reloadT = 0;
}

void MainScene::Shoot(Vector2f deltaPos)
{
	float length = deltaPos.Length();
	if (length > MaxPull) {
		deltaPos = deltaPos * (MaxPull / length);
	}
	deltaPos = deltaPos * ShootPower;

	stones.front().Shoot(deltaPos);
	reloadT = reloadTime;
}

Stone* MainScene::AddStone()
{
	stones.emplace_front();

	return &stones.front();
}

void MainScene::AddBlock(objectsShape shape, Vector2f pos)
{
	blocks.emplace_front(shape, pos);
	AddGameObject(&blocks.front());
}

void MainScene::SceneLoad()
{

	Renderer::GetInstance().SetBackgroundColor({ 255, 255, 255 });
	Shapes::Initialize();

	player = new MovePoly;
	AddGameObject(player);
	floor = new Floor;
	AddGameObject(floor);

	AddGameObject(AddStone());

	//map | floor y -400 | stonePos -700,-350

	

}

void MainScene::SceneEnd()
{
}

void MainScene::SceneUpdate()
{
	InputSystem& input = InputSystem::GetInstance();
	Vector2f mPos = input.GetGlobalMousePos();
	if (input.IsKeyDown(VK_LBUTTON) &&
		(mPos - ShootingPoint).Length() < clickRadius &&
		reloadT <= 0) 
	{
		clicked = true;
	}

	if (input.IsKeyUp(VK_LBUTTON) && clicked) 
	{

		Shoot(ShootingPoint - mPos);

		clicked = false;
	}

	if (reloadT > 0) { 
		reloadT -= TimeSystem::GetInstance().GetDeltaTime(); 
		reloadEnd = true;
	}
	else if (reloadEnd) {
		AddGameObject(AddStone());
		reloadEnd = false;
	}
}

void MainScene::SceneFixedUpdate()
{
}

void MainScene::Render()
{
	if (clicked) {
		Vector2f mPos = InputSystem::GetInstance().GetGlobalMousePos();
		Vector2f deltaP = ShootingPoint - mPos;
		float length = deltaP.Length();
		if (length > MaxPull) deltaP = deltaP * (MaxPull / length);

		Renderer::GetInstance().RenderLine(ShootingPoint - deltaP, ShootingPoint, D2D1::ColorF(200, 0, 0), 2);
	}
}
