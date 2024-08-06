#pragma once
#include "framework.h"
#include "d2dWinApp.h"
#include "SceneManager.h"
#include "Resources.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "Mathf.h"


class Game : public d2dWinApp
{
private:

	void Render() override;
	void Update(float deltaTime) override;
	void FixedUpdate() override;
	void StartLoop() override;
	void EndLoop() override;
protected:
	Game();
	virtual ~Game();

	virtual void GameStart() = 0;
	virtual void GameEnd() = 0;
	virtual void GameUpdate() = 0;
	virtual void GameFixedUpdate() = 0;
	virtual void GameLoopStart();
	virtual void GameLoopEnd();

	SceneManager sceneManager;
	Resources gameResource;
public:

	HRESULT Init(
		const wchar_t* windowName,
		UINT width,
		UINT height);
	void Final();


};