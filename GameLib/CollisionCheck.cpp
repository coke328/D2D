#include "pch.h"
#include "CollisionCheck.h"

bool CollisionCheck::Circle_Circle(const Shape::Circle& c1, const Shape::Circle& c2)
{
    float x = c1.center.x - c2.center.x;
    float y = c1.center.y - c2.center.y;
    return x * x + y * y <= (c1.radius + c2.radius) * (c1.radius + c2.radius);
}

bool CollisionCheck::Polygon_Point(Vector2f* points, unsigned int count, Vector2f point)
{
    for (int i = 0; i < count; i++) {
        int j = (i + 1) % count;

    }


    return false;
}

bool CollisionCheck::AA_BB(const Shape::AABB& a, const Shape::AABB& b)
{
    return !(a.Max.x < b.Min.x || a.Min.x > b.Max.x || a.Max.y < b.Min.y || a.Min.y > b.Max.y);
}
