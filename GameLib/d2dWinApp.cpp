#include "pch.h"
#include "d2dWinApp.h"
#include "TimeSystem.h"
#include "InputSystem.h"

d2dWinApp::d2dWinApp() :
	m_hwnd(nullptr)
{

}

d2dWinApp::~d2dWinApp()
{

	
}

void d2dWinApp::Render()
{
	
}

HRESULT d2dWinApp::Initialize(const wchar_t* windowName, 
	UINT width,
	UINT height
)
{
	HRESULT hr;

	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = d2dWinApp::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = windowName;

	RegisterClassEx(&wcex);

	m_hwnd = CreateWindow(
		windowName,
		windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	ShowWindow(m_hwnd, SW_SHOWNORMAL);

	UpdateWindow(m_hwnd);

	hr = CoInitialize(NULL);
	if (FAILED(hr)) return E_ABORT;

	TimeSystem::GetInstance().InitTime();
	InputSystem::GetInstance().Initialize(m_hwnd);
	Renderer::GetInstance().Initialize(m_hwnd);

	return hr;
}


void d2dWinApp::Run()
{
	MSG msg;

	float lag = 0.0f;

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			StartLoop();

			TimeSystem::GetInstance().UpdateTime();
			InputSystem::GetInstance().UpdateInput();

			float deltaTime = TimeSystem::GetInstance().GetDeltaTime();
			float fixedInteval = TimeSystem::GetInstance().GetFixedUpdateInterval();//default 60fps

			lag += deltaTime;

			if (lag >= fixedInteval) {
				TimeSystem::GetInstance().FixedUpdate(lag);
				FixedUpdate();
				lag -= fixedInteval;
			}
			//InputUpdate
			Update(deltaTime);

			Components::GetInstance().ComponentsUpdate();

			CollideManager::GetInstance().Update();

			Physics::GetInstance().ProcessCollision();

			OnRender();

			EndLoop();
		}
	}
}

void d2dWinApp::Finalize()
{
	Renderer::GetInstance().Uninitialize();
	
	CoUninitialize();
}

HRESULT d2dWinApp::OnRender()
{
	HRESULT hr = S_OK;


	if (SUCCEEDED(hr) && !(Renderer::GetInstance().CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{

		Renderer::GetInstance().BeginDraw();
		Renderer::GetInstance().resetRenderTargetTransform();
		Renderer::GetInstance().clear();

		
		Renderer::GetInstance().Render();
		Render();

		hr = Renderer::GetInstance().EndDraw();
	}

	return hr;
}

LRESULT d2dWinApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
