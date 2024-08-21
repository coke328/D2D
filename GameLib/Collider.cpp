#include "pch.h"
#include "Collider.h"
#include "GameObject.h"





PolygonCollider::PolygonCollider()
{
}

void PolygonCollider::Init(Vector2f* arr, size_t size)
{
	if (size < 3) {
		std::cout << "polygonCollider init fail" << std::endl;
		return;
	}

	polygon.SetPoints(arr, size);
	polygon.SetTransform(&gameObject->m_transform);
}

void PolygonCollider::Update()
{
	polygon.UpdateGlobalPoints();
	aabb = polygon.GetAABB();
}

void PolygonCollider::Destructor()
{
	polygon.Destructor();
}

Collider::Collider()
{
	ColliderOn = true;
}
