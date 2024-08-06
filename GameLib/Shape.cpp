#include "pch.h"
#include "Shape.h"

Shape::Polygon::Polygon()
{
	m_ptransform = nullptr;
	globalPoints = nullptr;
	localPoints = nullptr;
	size = 0;
}
void Shape::Polygon::SetTransform(transform* _transform) {
	m_ptransform = _transform;

	if (globalPoints != nullptr)
		delete[] globalPoints;

	globalPoints = new Vector2f[size];
}

Vector2f* Shape::Polygon::GetLocalPoints()
{
	return localPoints;
}

Vector2f* Shape::Polygon::GetGlobalPoints()
{
	return globalPoints;
}

const Shape::AABB& Shape::Polygon::GetAABB()
{
	return aabb;
}

size_t Shape::Polygon::Size()
{
	return size;
}

void Shape::Polygon::UpdateGlobalPoints()
{
	if (m_ptransform->IsModified()) {
		//std::cout << "updatePoints" << std::endl;
		globalPoints[0] = localPoints[0] * m_ptransform->GetGlobalMatrix();

		aabb.Min.x = globalPoints[0].x;
		aabb.Max.x = globalPoints[0].x;
		aabb.Min.y = globalPoints[0].y;
		aabb.Max.y = globalPoints[0].y;

		for (size_t i = 1; i < size; i++)
		{
			globalPoints[i] = localPoints[i] * m_ptransform->GetGlobalMatrix();

			aabb.Min.x = min(aabb.Min.x, globalPoints[i].x);
			aabb.Max.x = max(aabb.Max.x, globalPoints[i].x);
			aabb.Min.y = min(aabb.Min.y, globalPoints[i].y);
			aabb.Max.y = max(aabb.Max.y, globalPoints[i].y);
		}

		/*std::cout << aabb.Min.x << " , " << aabb.Max.x << std::endl;
		std::cout << aabb.Min.y << " , " << aabb.Max.y << std::endl;
		std::cout << "";*/
	}
	
}

void Shape::Polygon::Destructor()
{
	if (localPoints) { 
		delete[] localPoints; 
		localPoints = nullptr;
	}

	if (globalPoints) { 
		delete[] globalPoints;
		globalPoints = nullptr;
	}
}