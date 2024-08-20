#include "pch.h"
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "GameLib.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

class Wall : public GameObject {
public:
	pComponent<PolygonRender*> polyRender;
	pComponent<PolygonCollider*> polyColl;
	virtual ~Wall() {}

	void Init() override {
		std::array<Vector2f, 4> tmp;
		tmp[0] = { 1200,-400 };
		tmp[1] = { -1200,-450 };
		tmp[2] = { -1200,-600 };
		tmp[3] = { 1200,-600 };
		polyRender = AddComponent<PolygonRender>();
		polyColl = AddComponent<PolygonCollider>();

		polyRender.Get()->Init(tmp);
		polyColl.Get()->Init(tmp);

		polyRender.Get()->color = D2D1::ColorF(255, 0, 0);
		polyRender.Get()->lineThickness = 2;
	}
};

class PolygonShape : public GameObject {
public:
	pComponent<PolygonRender*> polyRender;
	pComponent<PolygonCollider*> polyColl;
	pComponent<RigidBody*> rigidbody;
	virtual ~PolygonShape() {

	}

	void Init() override {
		std::array<Vector2f, 4> tmp;
		tmp[0] = { 50,50 };
		tmp[1] = { -50,50 };
		tmp[2] = { -50,-50 };
		tmp[3] = { 50,-50 };

		polyRender = AddComponent<PolygonRender>();
		polyColl = AddComponent<PolygonCollider>();
		rigidbody = AddComponent<RigidBody>();

		polyRender.Get()->Init(tmp);
		polyColl.Get()->Init(tmp);

		polyRender.Get()->color = D2D1::ColorF(0, 0, 0);
		polyRender.Get()->lineThickness = 2;

		rigidbody.Get()->CalcMoment();
	}

	void PolyInit(float mass, float inertia, float bounce, float staticFriction, float kineticFriction) {
		rigidbody.Get()->mass = mass;
		rigidbody.Get()->angularInertia = inertia;
		rigidbody.Get()->kineticFriction = kineticFriction;
		rigidbody.Get()->staticFriction = staticFriction;

		rigidbody.Get()->CalcMoment();
	}
	void ShapeChange(std::array<Vector2f, 4> points) {
		polyRender.Get()->Init(points);
		polyColl.Get()->Init(points);
	}

	void FixedUpdate() override {}
};

class MovePoly : public PolygonShape {
	float speed;
	float rotspeed;
	Vector2f mouseStart;
public:
	MovePoly(){
		speed = 50;
		rotspeed = 300;
	}

	void Update() override {
		//if (InputSystem::GetInstance().IsKeyDown(VK_LBUTTON)) {
		//	mouseStart = InputSystem::GetInstance().GetGlobalMousePos();

		//	
		//}
		//if (InputSystem::GetInstance().IsKeyUp(VK_LBUTTON)) {
		//	Vector2f force = (InputSystem::GetInstance().GetGlobalMousePos() - mouseStart);
		//	rigidbody.Get()->AddForceByPoint(mouseStart, force);
		//	//std::cout << force.x << "," << force.y << std::endl;
		//}

		//std::cout << m_transform.GetGlobalPosition().x << std::endl;
	}

	void FixedUpdate() override{
		//std::cout << rigidbody.Get()->velocity.x << std::endl;
		//std::cout << m_transform.GetLocalPosition().x << std::endl;

		if (InputSystem::GetInstance().IsKeyPress('W')) {
			rigidbody.Get()->AddForce({ 0,speed });
			//m_transform.AddGlobalPosition({ 0,speed });
			//rigidbody.Get()->velocity = { 0,speed };
		}
		if (InputSystem::GetInstance().IsKeyPress('S')) {
			rigidbody.Get()->AddForce({ 0,-speed });
			//m_transform.AddGlobalPosition({ 0,-speed });
			//rigidbody.Get()->velocity = { 0,-speed };
		}
		if (InputSystem::GetInstance().IsKeyPress('A')) {
			rigidbody.Get()->AddForce({ -speed,0 });
			//m_transform.AddGlobalPosition({ -speed,0 });
			//rigidbody.Get()->velocity = { -speed,0 };
		}
		if (InputSystem::GetInstance().IsKeyPress('D')) {
			rigidbody.Get()->AddForce({ speed,0 });
			//m_transform.AddGlobalPosition({ speed,0 });
			//rigidbody.Get()->velocity = { speed,0 };
		}
		if (InputSystem::GetInstance().IsKeyPress('Q')) {
			rigidbody.Get()->AddRotForce(rotspeed);
		}
		if (InputSystem::GetInstance().IsKeyPress('E')) {
			rigidbody.Get()->AddRotForce(-rotspeed);
		}

		
	}
};

class Test : public Scene {
public:
	MovePoly* player;
	PolygonShape* poly;
	Wall* wall;

	void SceneLoad() override {
		Renderer::GetInstance().SetBackgroundColor({ 255, 255, 255 });

		player = new MovePoly;
		AddGameObject(player);
		poly = new PolygonShape;
		AddGameObject(poly);
		wall = new Wall;
		AddGameObject(wall);

		poly->PolyInit(1000, 100, 0.1, 0.9, 0.8);
		std::array<Vector2f, 4> tmp;
		tmp[0] = { 200, 200 };
		tmp[1] = { -200, 200 };
		tmp[2] = { -200, -200 };
		tmp[3] = { 200, -200 };
		poly->ShapeChange(tmp);

		player->m_transform.SetLocalPosition({ 300, 0 });

		player->PolyInit(10, 1, 0.5, 0.8, 0.8);
	}
	void SceneEnd() override {

	}
	void SceneUpdate() override {

		
	}
	void SceneFixedUpdate() override {
		
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
