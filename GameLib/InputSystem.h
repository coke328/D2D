#pragma once

class InputSystem
{
public:
	void Initialize(HWND hWindow);
	void UpdateInput();

	bool IsKeyUp(BYTE vk);
	bool IsKeyDown(BYTE vk);
	bool IsKeyPress(BYTE vk);
	POINT GetMousePos();

	static InputSystem& GetInstance();
private:
	POINT MousePos;
	HWND hWnd;


	#define KEYBOARD_MAX 256		// ��ü ���� Ű�� �� 
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down�� Ű�� ����
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up �� Ű�� ����
};

