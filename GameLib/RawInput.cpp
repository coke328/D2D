#include "pch.h"
#include "RawInput.h"

RawInput::~RawInput()
{
    RAWINPUTDEVICE rid[2];

    rid[0].usUsagePage = 0x01; // Generic Desktop Controls
    rid[0].usUsage = 0x02;     // Mouse
    rid[0].dwFlags = RIDEV_REMOVE;
    rid[0].hwndTarget = m_hwnd;

    rid[1].usUsagePage = 0x01; // Generic Desktop Controls
    rid[1].usUsage = 0x06;     // Keyboard
    rid[1].dwFlags = RIDEV_REMOVE;
    rid[1].hwndTarget = m_hwnd;

    RegisterRawInputDevices(rid, 2, sizeof(rid[0]));
}

void RawInput::RegisterDevices()
{
    RAWINPUTDEVICE rid[2];

    rid[0].usUsagePage = 0x01; // Generic Desktop Controls
    rid[0].usUsage = 0x02;     // Mouse
    rid[0].dwFlags = 0;
    rid[0].hwndTarget = m_hwnd;

    rid[1].usUsagePage = 0x01; // Generic Desktop Controls
    rid[1].usUsage = 0x06;     // Keyboard
    rid[1].dwFlags = 0;
    rid[1].hwndTarget = m_hwnd;

    RegisterRawInputDevices(rid, 2, sizeof(rid[0]));
}

void RawInput::HandleMouseInput(const RAWINPUT& rawInput)
{
}

RawInput::RawInput()
{
    initialized = false;
}

RawInput& RawInput::GetInstance()
{
	static RawInput input;
	return input;
}

void RawInput::Initialize(HWND hwnd)
{
	m_hwnd = hwnd;
    RegisterDevices();
    initialized = true;
}

void RawInput::ProcessInput(HRAWINPUT lParam)
{
    if (!initialized) return;

    UINT dwSize;
    GetRawInputData(lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
    LPBYTE lpb = new BYTE[dwSize];
    if (lpb == nullptr) return;
    RAWINPUT* raw = (RAWINPUT*)lpb;

    delete[] lpb;
}
