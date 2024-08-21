#include "MainScene.h"

void MainScene::SceneLoad()
{

	Renderer::GetInstance().SetBackgroundColor({ 255, 255, 255 });
	Shapes::Initialize();

	player = new MovePoly;
	AddGameObject(player);
	//poly = new Object(objectsShape::Box_40x20);
	//AddGameObject(poly);
	floor = new Floor;
	AddGameObject(floor);
}

void MainScene::SceneEnd()
{
}

void MainScene::SceneUpdate()
{
}

void MainScene::SceneFixedUpdate()
{
}

void MainScene::Render()
{
}
