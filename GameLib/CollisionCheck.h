#pragma once
#include "Shape.h"



namespace CollisionCheck 
{
	bool Circle_Circle(const Shape::Circle& c1, const Shape::Circle& c2);

	bool Polygon_Point(Vector2f* points, unsigned int count, Vector2f point);

	bool AA_BB(const Shape::AABB& a, const Shape::AABB& b);

	
}