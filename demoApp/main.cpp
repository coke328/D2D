#include "pch.h"
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "GameLib.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


class PolygonShape : public GameObject {
public:
	pComponent<PolygonRender*> polyRender;
	pComponent<PolygonCollider*> polyColl;

	PolygonShape() = default;

	void Init() override {
		std::array<Vector2f, 4> tmp;
		tmp[0] = { 50,50 };
		tmp[1] = { -50,50 };
		tmp[2] = { -50,-50 };
		tmp[3] = { 50,-50 };

		polyRender = AddComponent<PolygonRender>();
		polyColl = AddComponent<PolygonCollider>();

		polyRender.Get()->Init(tmp);
		polyColl.Get()->Init(tmp);

		polyRender.Get()->color = D2D1::ColorF(0, 0, 0);
		polyRender.Get()->lineThickness = 2;

		

		
	}

	void FixedUpdate() override {

		

	}
};

class Test : public Scene {
	float speed;
public:
	PolygonShape* poly1;
	PolygonShape* poly2;

	void SceneLoad() override {
		Renderer::GetInstance().SetBackgroundColor({ 255, 255, 255 });

		poly1 = new PolygonShape;
		AddGameObject(poly1);
		poly2 = new PolygonShape;
		AddGameObject(poly2);
		poly1->m_transform.SetGlobalPosition({ 300, 0 });
		speed = 3;
	}
	void SceneEnd() override {

	}
	void SceneUpdate() override {

		
	}
	void SceneFixedUpdate() override {
		if (InputSystem::GetInstance().IsKeyPress('W')) {
			poly1->m_transform.AddLocalPosition({ 0, speed });
		}
		if (InputSystem::GetInstance().IsKeyPress('S')) {
			poly1->m_transform.AddLocalPosition({ 0, -speed });
		}
		if (InputSystem::GetInstance().IsKeyPress('A')) {
			poly1->m_transform.AddLocalPosition({ -speed, 0 });
		}
		if (InputSystem::GetInstance().IsKeyPress('D')) {
			poly1->m_transform.AddLocalPosition({ speed, 0 });
		}
	}

	void Render() override {
		
	
	}
};

class DemoApp : public Game {
public:
	DemoApp() {
		
	}
	void GameStart() override {
		Renderer::GetInstance().SetBackgroundColor({0,0,0,255});

		sceneManager.StartScene<Test>();

	}
	void GameEnd() override {

	}
	void GameUpdate() override {
		//std::cout << TimeSystem::GetInstance().GetDeltaTime() << std::endl;
	}
	void GameFixedUpdate() override {
		//std::cout << "GameUpdate" << std::endl;
	}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	DemoApp app;

	HRESULT hr = app.Init(L"helloWorld", 1200, 900);

	//if (!SUCCEEDED(hr)) return hr;
	app.Run();
	app.Final();


	return 0;
}
