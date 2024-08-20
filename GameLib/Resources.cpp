#include "pch.h"
#include "Resources.h"


Resources::Resources()
{
}

Resources::~Resources()
{
    for (auto i : *bitmapMap) {
		i->Release();
    }
	bitmapMap.Clear();
}

void Resources::Initialize(Resources* _upper)
{
	upperResource = _upper;
}


pBitmap Resources::LoadBitmapFromFile(const WCHAR* filePath)
{
	pBitmap bitmap = nullptr;

	if (upperResource != nullptr) {
		bitmap = *upperResource->bitmapMap.FindObject(std::wstring(filePath));
		if (bitmap != nullptr) {
			return bitmap;
		}
	}

	bitmap = *bitmapMap.FindObject(std::wstring(filePath));

	if (bitmap != nullptr) {
		return bitmap;
	}

    HRESULT hr;

    IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

	hr = Renderer::GetInstance().m_pWICFactory->CreateDecoderFromFilename(
		filePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = Renderer::GetInstance().m_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}


	if (SUCCEEDED(hr))
	{
		hr = Renderer::GetInstance().m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &bitmap);
	}

	// 파일을 사용할때마다 다시 만든다.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	if (bitmap != nullptr) {
		bitmapMap.Push(filePath, bitmap);
	}

    return bitmap;
}


