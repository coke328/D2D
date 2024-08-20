#pragma once

enum MouseButton {
	LEFT,
	RIGHT
};

class Vector2f;

class InputSystem
{
public:
	

	void Initialize(HWND hWindow);
	void UpdateInput();
	bool IsKeyUp(BYTE vk);
	bool IsKeyDown(BYTE vk);
	bool IsKeyPress(BYTE vk);
	POINT GetMousePos();
	Vector2f GetGlobalMousePos();

	static InputSystem& GetInstance();
private:
	POINT MousePos;
	HWND hWnd;


	#define KEYBOARD_MAX 256		// 전체 가상 키의 수 
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// 이전 키의 정보
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// 현재 키의 정보
	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down된 키의 정보
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up 된 키의 정보
	BYTE mouseButtonCurr[2];
	BYTE mouseButtonPrev[2];
	BYTE mouseButtonUp[2];
	BYTE mouseButtonDown[2];
};

