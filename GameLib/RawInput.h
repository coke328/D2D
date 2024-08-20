#pragma once
class RawInput
{
	RawInput();
	~RawInput();
	void RegisterDevices();
	void HandleMouseInput(const RAWINPUT& rawInput);

	HWND m_hwnd;
	bool initialized;
public:
	
	static RawInput& GetInstance();
	void Initialize(HWND hwnd);
	void ProcessInput(HRAWINPUT lParam);
};

