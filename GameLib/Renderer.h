#pragma once
#include "Shape.h"

class Camera;
class voidPComponent;

class Renderer
{
private:
	friend class GameObject;
	friend class RenderComponent;
	friend class Scene;

	vectorMap<__int64, voidPComponent> renderComps;

	Camera* pCamera;
	Matrix CamMatrix;
	Matrix CamMatrixInvert;

	D2D1::ColorF backgroundColor;

	void AddRenderComponent(const voidPComponent& idx);
	void deleteRenderComponent(const voidPComponent& idx);
	void SortRenderComponents();
	void CompsClear();
	Renderer();
public:
	
	unsigned int objectCount;

	~Renderer();

	static Renderer& GetInstance();
	void Initialize(HWND hWnd);
	void Uninitialize();
	size_t GetUsedVRAM();

	void SetCamera(Camera* _pCamera);

	void Render();

	void RenderBitmap(pBitmap bitmap, Matrix matrix);
	void RenderBitmap(pBitmap bitmap, Matrix matrix, D2D1_RECT_F destRect, float alpha, D2D1_RECT_F sourceRect);
	void RenderPolygon(Shape::Polygon& poly, D2D1::ColorF color, float thickness);
	void RenderText(std::wstring text, D2D1_RECT_F rect);

	D2D1_SIZE_U GetScreenSize();
	void SetBackgroundColor(D2D1::ColorF color);
	D2D1::ColorF GetBackgroundColor();

	void BeginDraw();
	void resetRenderTargetTransform();
	void clear();
	HRESULT EndDraw();
	D2D1_WINDOW_STATE CheckWindowState();

	void CalcScreenMatrix();
	const Matrix& ScreenMatrix();
	const Matrix& GlabalMatrix();
	bool IsVisible(const Matrix& matrix, Shape::AABB a);

	Vector2f ScreenToGlobal(Vector2f screenPos);

	ID2D1Factory* m_pD2DFactory;		// D2D 개체 인터페이스 포인터 변수
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pWICFactory;	// D2D비트맵 생성을 위한 이미지 처리 인터페이스
	IDWriteFactory* m_pDWriteFactory;	// TextFormat생성을 위한 팩토리
	IDWriteTextFormat* m_pDWriteTextFormat; // 기본 텍스트 출력을 위한 Format
	ID2D1SolidColorBrush* m_pBrush;	// 렌더타겟이 생성하는 리소스 역시 장치의존
	ID2D1PathGeometry* m_pGeometry;
	IDXGIFactory4* m_pDXGIFactory;		// DXGI팩토리
	IDXGIAdapter3* m_pDXGIAdapter;		// 비디오카드 정보에 접근 가능한 인터페이스
	HWND m_hWnd;						// 렌더타겟을 생성할 윈도우 핸들
	D2D1_SIZE_U	m_ClientSize;			// 렌더타겟의 크기
};

