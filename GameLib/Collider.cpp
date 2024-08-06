#include "pch.h"
#include "Collider.h"


PolygonCollider::PolygonCollider()
{
}



void PolygonCollider::Update()
{
	polygon.UpdateGlobalPoints();
}

void PolygonCollider::Destructor()
{
	polygon.Destructor();
}


