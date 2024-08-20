#include "pch.h"
#include "Renderer.h"
#include "Helper.h"
#include "Transform.h"
#include "CollisionCheck.h"
#include "RenderComponents.h"

#undef min

void Renderer::AddRenderComponent(const voidPComponent& idx)
{
	renderComps.Push(CompIdxToInt(idx.idx), idx);
}

void Renderer::deleteRenderComponent(const voidPComponent& idx)
{
	renderComps.Erase(CompIdxToInt(idx.idx));
}

Renderer::Renderer() :
	backgroundColor(0,0,0)
{
	m_pWICFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pDXGIFactory = nullptr;
	m_pDXGIAdapter = nullptr;
	m_pDWriteFactory = nullptr;
	m_pD2DFactory = nullptr;
	m_pDWriteFactory = nullptr;
	m_pDWriteTextFormat = nullptr;
	m_pBrush = nullptr;

	m_ClientSize = { 0,0 };
	
	CamMatrix = Matrix::Identity();
	CamMatrixInvert = Matrix::Identity();
}

void Renderer::CompsClear()
{
	renderComps.Clear();
}

Renderer::~Renderer()
{
	
}

Renderer& Renderer::GetInstance()
{
	static Renderer render;
	return render;
}

void Renderer::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
			이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
			DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
		*/
		// Create a Direct2D render target.
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		m_ClientSize = D2D1::SizeU(rc.right - rc.left,rc.bottom - rc.top );

		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, m_ClientSize),
			&m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	}

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}
	// VRAM 정보얻기 위한 개체 생성
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
	}
	if (SUCCEEDED(hr))
	{
		m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
	}
}

void Renderer::Uninitialize()
{
	SAFE_RELEASE(m_pBrush);
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pWICFactory);
	SAFE_RELEASE(m_pDWriteFactory);
	SAFE_RELEASE(m_pDWriteTextFormat);
	SAFE_RELEASE(m_pDXGIFactory);
	SAFE_RELEASE(m_pDXGIAdapter);
	
}

size_t Renderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

void Renderer::SetCamera(Camera* _pCamera)
{
	pCamera = _pCamera;
}


void Renderer::SortRenderComponents()
{
	if (RenderComponent::renderOrderChanged) 
	{
		std::sort((*renderComps).begin(), (*renderComps).end(), [](voidPComponent& idx1, voidPComponent& idx2) {
			int order1 = idx1.Get<RenderComponent>()->GetRenderOrder();
			int order2 = idx2.Get<RenderComponent>()->GetRenderOrder();
			return order1 < order2;
			});

		RenderComponent::renderOrderChanged = false;
	}
}

void Renderer::Render()
{
	CalcScreenMatrix();
	SortRenderComponents();

	for (auto& i : *renderComps) {
		//static_cast<RenderComponent*>(Components::GetInstance().GetComponent(i))->Render();
		//std::cout << typeid(*(i.Get<RenderComponent>())).name() << std::endl;
		i.Get<RenderComponent>()->Render();
	}
}

void Renderer::RenderBitmap(pBitmap bitmap, Matrix _matrix)//TODO object culling
{
	if (bitmap) {

		m_pRenderTarget->SetTransform(_matrix * ScreenMatrix());

		m_pRenderTarget->DrawBitmap(bitmap);
	}
}

void Renderer::RenderBitmap(pBitmap bitmap, Matrix matrix, D2D1_RECT_F destRect, float alpha, D2D1_RECT_F sourceRect)
{
	if (!bitmap) return; 
	matrix = matrix * ScreenMatrix();
	if (!IsVisible(matrix, {{destRect.left,destRect.bottom},{destRect.right,destRect.top}})) return;

	m_pRenderTarget->SetTransform(matrix);

	m_pRenderTarget->DrawBitmap(bitmap, destRect,alpha,D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,sourceRect);

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	
	objectCount++;
}

void Renderer::RenderPolygon(Shape::Polygon& poly, D2D1::ColorF color, float thickness)
{

	if (!IsVisible(ScreenMatrix(), poly.GetAABB())) return;

	m_pRenderTarget->SetTransform(ScreenMatrix());
	m_pBrush->SetColor(color);

	Vector2f* vec = poly.GetGlobalPoints();


	for (int i = 0; i < poly.Size() - 1; i++) {

		m_pRenderTarget->DrawLine(vec[i], vec[i + 1], m_pBrush, thickness);
	}

	m_pRenderTarget->DrawLine(vec[0], vec[poly.Size()-1], m_pBrush, thickness);

	

}

void Renderer::RenderText(std::wstring text, D2D1_RECT_F rect)
{
	m_pRenderTarget->DrawTextW(text.c_str(), text.length(), m_pDWriteTextFormat, rect, m_pBrush);
}

D2D1_SIZE_U Renderer::GetScreenSize()
{
	return m_ClientSize;
}

void Renderer::SetBackgroundColor(D2D1::ColorF color)
{
	backgroundColor = color;
}

D2D1::ColorF Renderer::GetBackgroundColor()
{
	return backgroundColor;
}

void Renderer::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}

void Renderer::resetRenderTargetTransform()
{
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Renderer::clear()
{
	m_pRenderTarget->Clear(backgroundColor);
}

HRESULT Renderer::EndDraw()
{
	objectCount = 0;
	return m_pRenderTarget->EndDraw();
}

D2D1_WINDOW_STATE Renderer::CheckWindowState()
{
	return m_pRenderTarget->CheckWindowState();
}

void Renderer::CalcScreenMatrix()
{
	if (pCamera->m_transform.IsModified()) {
		CamMatrix = pCamera->m_transform.GetGlobalMatrix()
			* Matrix::Scale(1, -1)
			* Matrix::Translation(-float(m_ClientSize.width) / 2, float(m_ClientSize.height) / 2);
		CamMatrixInvert = CamMatrix;
		CamMatrixInvert.Invert();
	}
}

const Matrix& Renderer::ScreenMatrix()
{
	return CamMatrixInvert;
}

const Matrix& Renderer::GlabalMatrix()
{
	return CamMatrix;
}


bool Renderer::IsVisible(const Matrix& matrix, Shape::AABB a)
{

	Vector2f b = Vector2f( a.Max.x,a.Min.y ) * matrix;
	Vector2f c = Vector2f( a.Min.x,a.Max.y ) * matrix;
	a.Max = a.Max * matrix;
	a.Min = a.Min * matrix;

	auto X = std::minmax({ b.x,c.x,a.Max.x,a.Min.x });
	auto Y = std::minmax({ b.y,c.y,a.Max.y,a.Min.y });

	a.Max.x = X.second; a.Max.y = Y.second;
	a.Min.x = X.first; a.Min.y = Y.first;

	Shape::AABB B = { {0,0}, {(float)m_ClientSize.width,(float)m_ClientSize.height} };
	return CollisionCheck::AA_BB(a,B);
}

Vector2f Renderer::ScreenToGlobal(Vector2f screenPos)
{
	return Vector2f();
}
