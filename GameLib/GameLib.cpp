// GameLib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "GameLib.h"

void Game::Render()
{
	sceneManager.Render();
}

Game::Game() : sceneManager(&gameResource)
{

}

Game::~Game()
{

}

void Game::GameLoopStart()
{
}

void Game::GameLoopEnd()
{
}

void Game::Update(float deltaTime)
{
	sceneManager.Update();
	GameUpdate();
}

void Game::FixedUpdate()
{
	sceneManager.FixedUpdate();
	GameFixedUpdate();
}

void Game::StartLoop()
{
	sceneManager.LoopStart();
	GameLoopStart();
}

void Game::EndLoop()
{
	sceneManager.LoopEnd();
	GameLoopEnd();
}

HRESULT Game::Init(const wchar_t* windowName, UINT width, UINT height)
{
	HRESULT hr = Initialize(windowName, width, height);

	if (!SUCCEEDED(hr)) return hr;
	gameResource.Initialize();
	GameStart();
}

void Game::Final()
{
	Finalize();

	GameEnd();
}

