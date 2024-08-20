#include "pch.h"
#include "Collider.h"






PolygonCollider::PolygonCollider()
{
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

