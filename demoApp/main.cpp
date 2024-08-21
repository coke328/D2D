#pragma once
#include "pch.h"
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "GameLib.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Shapes.h"
#include "MainScene.h"




class DemoApp : public Game {
public:
	DemoApp() {
		
	}
	void GameStart() override {
		Renderer::GetInstance().SetBackgroundColor({0,0,0,255});

		sceneManager.StartScene<MainScene>();

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

	HRESULT hr = app.Init(L"helloWorld", 1920, 1080);

	//if (!SUCCEEDED(hr)) return hr;
	app.Run();
	app.Final();

	return 0;
}
