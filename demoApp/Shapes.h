#pragma once
#include <array>
#include "GameLib.h"


enum objectsShape
{
	Box_10x40,
	Box_40x10,
	Box_20x20,
	Box_40x40,
	Box_10x50,
	Box_50x10,
	Box_10x60,
	Box_60x10,
	Box_20x40,
	Box_40x20,
	Horn_20x20,
	Horn_40x40,
	SlopeLeft_20x20,
	SlopeRight_20x20,
	SlopeLeft_40x20,
	SlopeRight_40x20,
	Octagon_20x20,
	Octagon_40x40,
	Triangle_20,
	Triangle_40,
};

class Shapes
{
	static std::array<std::pair<Vector2f*, unsigned int>,20> shapes;
	
public:

	static void Initialize();
	static const std::pair<Vector2f*, unsigned int>& GetShape(objectsShape _shape);
};

