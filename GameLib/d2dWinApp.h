#pragma once
#include "Renderer.h"
#include "CollideManager.h"

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


class d2dWinApp
{

public:

	void Run();

private:

	HRESULT OnRender();
	
	static LRESULT CALLBACK WndProc(
		HWND hwnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	HWND m_hwnd;

protected:
	d2dWinApp();
	virtual ~d2dWinApp();

	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate() = 0;
	virtual void StartLoop() = 0;
	virtual void EndLoop() = 0;

	HRESULT Initialize(
		const wchar_t* windowName,
		UINT width,
		UINT height
	);

	void Finalize();
};

