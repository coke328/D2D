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


	#define KEYBOARD_MAX 256		// ��ü ���� Ű�� �� 
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down�� Ű�� ����
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up �� Ű�� ����
	BYTE mouseButtonCurr[2];
	BYTE mouseButtonPrev[2];
	BYTE mouseButtonUp[2];
	BYTE mouseButtonDown[2];
};

