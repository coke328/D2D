#pragma once
#include "Component.h"
#include "Shape.h"


class Renderer;

class RenderComponent : public Component
{
private:
	friend class Renderer;
	friend class GameObject;


	

	static bool renderOrderChanged;
	int renderOrder;
protected:
	RenderComponent();
	virtual void Render();
public:
	
	virtual void Update() override;
	virtual ~RenderComponent();
	void Destructor() override;
	virtual void destruct();
	int GetRenderOrder() const;
	void SetRenderOrder(int _renderOrder);
};

class PolygonRender : public RenderComponent 
{
private:
	Shape::Polygon polygon;
protected:

	
public:
	template<size_t n>
	void Init(const std::array<Vector2f, n>& arr);
	void Render() override;
	void Update() override;
	PolygonRender();
	virtual ~PolygonRender() = default;
	void destruct() override;
	
	D2D1::ColorF color;
	D2D1::ColorF lineColor;
	float lineThickness;
};

class BitmapRender : public RenderComponent
{
private:
	
public:
	

	BitmapRender();
	virtual ~BitmapRender();

	virtual void Update() override;

	Vector2f center;
	float alpha;
	D2D1_RECT_F sourceRect;
	D2D1_RECT_F DestRect;

	void Init(pBitmap bitmap);
protected:
	pBitmap bitmap;
	
	void Render() override;


};

class AnimationRender : public BitmapRender {


public:
	struct Frame {
		D2D1_RECT_F source;
		Vector2f center;
		float duration;
	};

	int currentFrame;
	Frame* frames;
	unsigned int frameSize;
	float animationSpeed;

	void Reset();
	void Play();
	void Stop();

	AnimationRender();
	virtual ~AnimationRender();

	void Init(pBitmap bitmap, float duration, unsigned int widthDivide, unsigned int HeightDivide);
	void ChangeFrame(unsigned int idx);

	void Update() override;
private:
	float currTime;

	bool play;

	void destruct() override;
	void DeleteFrames();
};


