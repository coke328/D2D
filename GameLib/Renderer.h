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

	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����
	ID2D1PathGeometry* m_pGeometry;
	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�
	HWND m_hWnd;						// ����Ÿ���� ������ ������ �ڵ�
	D2D1_SIZE_U	m_ClientSize;			// ����Ÿ���� ũ��
};

