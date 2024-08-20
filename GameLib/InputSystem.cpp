#include "pch.h"
#include "InputSystem.h"
#include "Vector2f.h"
#include "Renderer.h"

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


	/*for (int i = 0; i < 2; i++)
	{
		mouseButtonUp[i] = (mouseButtonPrev[i] ^ mouseButtonCurr[i]) & mouseButtonPrev[i];
		mouseButtonDown[i] = (mouseButtonPrev[i] ^ mouseButtonCurr[i]) & mouseButtonCurr[i];
	}
	memcpy(&mouseButtonPrev, &mouseButtonCurr, 2);*/
}

//void InputSystem::MouseButtonDown(MouseButton button)
//{
//	mouseButtonCurr[button] = 0x80;
//}
//
//void InputSystem::MouseButtonUp(MouseButton button)
//{
//	mouseButtonCurr[button] = 0x00;
//}
//
//
//bool InputSystem::IsMouseButtonPress(MouseButton button)
//{
//	if (mouseButtonCurr[button] & 0x80)
//		return true;
//	return false;
//}
//
//bool InputSystem::IsMouseButtonDown(MouseButton button)
//{
//	if (mouseButtonDown[button] & 0x80)
//		return true;
//	return false;
//}
//
//bool InputSystem::IsMouseButtonUp(MouseButton button)
//{
//	if (mouseButtonUp[button] & 0x80)
//		return true;
//	return false;
//}

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

Vector2f InputSystem::GetGlobalMousePos()
{
	return Vector2f(MousePos.x,MousePos.y) * Renderer::GetInstance().GlabalMatrix();
}

InputSystem& InputSystem::GetInstance()
{
	static InputSystem input;
	return input;
}
