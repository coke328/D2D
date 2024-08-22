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

	auto Pos = [](float x, float y) {return Vector2f( x * 1.001f , y + (y + 380) * 0.001f ); };

	AddBlock(objectsShape::Box_10x40, Pos( 0,-380));
	AddBlock(objectsShape::Box_10x40, Pos(30,-380));
	AddBlock(objectsShape::Box_10x40, Pos(60,-380));
	AddBlock(objectsShape::Box_10x40, Pos(90,-380));

	AddBlock(objectsShape::Box_40x20, Pos(15,-350));
	AddBlock(objectsShape::Box_40x20, Pos(75,-350));

	/*AddBlock(objectsShape::Box_10x50, Pos(0,-315));
	AddBlock(objectsShape::Box_20x20, Pos(25,-330));
	AddBlock(objectsShape::Box_20x20, Pos(65,-330));
	AddBlock(objectsShape::Box_10x50, Pos(90,-315));

	AddBlock(objectsShape::Box_60x10, Pos(45,-315));

	AddBlock(objectsShape::Box_20x20, Pos(25,-300));
	AddBlock(objectsShape::Box_20x20, Pos(65,-300));

	AddBlock(objectsShape::Box_40x20, Pos( 15,-280));
	AddBlock(objectsShape::Box_40x20, Pos( 75,-280));

	AddBlock(objectsShape::Box_20x20, Pos( 25,-260));
	AddBlock(objectsShape::Box_20x20, Pos( 65,-260));

	AddBlock(objectsShape::Box_60x10, Pos( 45,-245));*/
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
