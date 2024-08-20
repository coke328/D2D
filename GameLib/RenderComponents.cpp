#include "pch.h"
#include "RenderComponents.h"
#include "Renderer.h"
#include "GameObject.h"

bool RenderComponent::renderOrderChanged = false;


void RenderComponent::Update()
{
}

void RenderComponent::Render()
{
}

RenderComponent::RenderComponent()
{
	renderOrder = 0;
}

RenderComponent::~RenderComponent()
{

}

void RenderComponent::Destructor()
{
	destruct();
	Renderer::GetInstance().deleteRenderComponent(compidx);
}

void RenderComponent::destruct()
{
}

int RenderComponent::GetRenderOrder() const
{
	return renderOrder;
}

void RenderComponent::SetRenderOrder(int _renderOrder)
{
	if (renderOrder != _renderOrder) {
		renderOrder = _renderOrder;
		renderOrderChanged = true;
	}
}

BitmapRender::BitmapRender() : bitmap(nullptr), center({ 0,0 })
{
	alpha = 1;

}

BitmapRender::~BitmapRender()
{
}

void BitmapRender::Update()
{
}

void BitmapRender::Init(pBitmap _bitmap)
{
	bitmap = _bitmap;

	float width = bitmap->GetPixelSize().width;
	float height = bitmap->GetPixelSize().height;
	center = { width / 2,height / 2 };
	DestRect = { 0, 0, (float)width, (float)height };
	sourceRect = DestRect;
}



void BitmapRender::Render()
{
	if (bitmap == nullptr) return;

	Matrix m = Matrix::Translation(-center.x, -center.y) * gameObject->m_transform.GetGlobalMatrix();
	Renderer::GetInstance().RenderBitmap(bitmap, m, DestRect, alpha, sourceRect);
}

void AnimationRender::Reset()
{
	currentFrame = 0;
	currTime = 0;
}

void AnimationRender::Play()
{
	play = true;
}

void AnimationRender::Stop()
{
	play = false;
}

AnimationRender::AnimationRender()
{
	currentFrame = 0;
	currTime = 0;
	animationSpeed = 1.f;
	play = true;
	frameSize = 0;
	frames = nullptr;
}

AnimationRender::~AnimationRender()
{
}


void AnimationRender::Init(pBitmap _bitmap, float _duration, unsigned int widthDivide, unsigned int HeightDivide)
{
	bitmap = _bitmap;

	float width = bitmap->GetPixelSize().width / widthDivide;
	float height = bitmap->GetPixelSize().height / HeightDivide;
	center = { width / 2, height / 2 };
	DestRect = { 0, 0, width, height };

	DeleteFrames();

	frameSize = widthDivide * HeightDivide;
	frames = new Frame[frameSize];

	for (int i = 0; i < HeightDivide; i++) {
		for (int j = 0; j < widthDivide; j++) {

			int idx = i * widthDivide + j;

			frames[idx].center = center;
			frames[idx].duration = _duration / frameSize;

			float x = j * width;
			float y = i * height;
			frames[idx].source = { x, y, x + width, y + height };
		}
	}
	ChangeFrame(0);
}

void AnimationRender::ChangeFrame(unsigned int idx)
{
	sourceRect = frames[idx].source;
	center = frames[idx].center;
}

void AnimationRender::Update()
{
	if (play) {
		currTime += TimeSystem::GetInstance().GetDeltaTime() * animationSpeed;
		if (abs(currTime) >= frames[currentFrame].duration && currTime) {
			currTime -= frames[currentFrame].duration * currTime / abs(currTime);

			if (currTime > 0) {
				currentFrame++;
				currentFrame = (currentFrame >= frameSize) ? 0 : currentFrame;
			}
			else {
				currentFrame--;
				currentFrame = (currentFrame < 0) ? (frameSize - 1) : currentFrame;
			}

			ChangeFrame(currentFrame);
		}

	}
}

void AnimationRender::destruct()
{
	DeleteFrames();
}

void AnimationRender::DeleteFrames()
{
	if (frames != nullptr) {
		delete[] frames;
	}
}

void PolygonRender::Render()
{
	if (polygon.Size() == 0) return;
	polygon.UpdateGlobalPoints();
	Renderer::GetInstance().RenderPolygon(polygon,color,lineThickness);
}

void PolygonRender::Update()
{
	
}

PolygonRender::PolygonRender() : color(0,0,0),lineColor(0,0,0)
{
	lineThickness = 1;
}

void PolygonRender::destruct()
{
	polygon.Destructor();
}
