#include "pch.h"
#include "InputSystem.h"

void InputSystem::Initialize(HWND hWindow)
{
	hWnd = hWindow;
}

void InputSystem::UpdateInput()
{
	GetCursorPos(&MousePos);
	ScreenToClient(hWnd, &MousePos);

	bool ret = GetKeyboardState((PBYTE)&g_byKeyCurr);	// 0x80 : 눌림, 0x00 : 눌리지 않음

	for (int i = 0; i < KEYBOARD_MAX; i++)
	{
		g_byKeyTurnUp[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyPrev[i];
		g_byKeyTurnDn[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyCurr[i];
	}
	memcpy(&g_byKeyPrev, &g_byKeyCurr, KEYBOARD_MAX);
}

bool InputSystem::IsKeyUp(BYTE vk)
{
	if (g_byKeyTurnUp[vk] & 0x80)
		return true;

	return false;
}

bool InputSystem::IsKeyDown(BYTE vk)
{
	if (g_byKeyTurnDn[vk] & 0x80)
		return true;

	return false;
}

bool InputSystem::IsKeyPress(BYTE vk)
{
	if (g_byKeyCurr[vk] & 0x80)
		return true;

	return false;
}

POINT InputSystem::GetMousePos()
{
	return MousePos;
}

InputSystem& InputSystem::GetInstance()
{
	static InputSystem input;
	return input;
}
