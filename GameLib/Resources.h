#pragma once
#include "Typedef.h"
#include "Renderer.h"
#include "vectorMap.h"

class Resources
{
	Resources* upperResource;

	vectorMap<std::wstring, pBitmap> bitmapMap;

public:
	Resources();
	~Resources();

	void Initialize(Resources* _upper = nullptr);
	
	pBitmap LoadBitmapFromFile(const WCHAR* filePath);//TODO ��Ʈ�� �Ϻθ� �������� ���
};

