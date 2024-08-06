#pragma once
#include "Vector2f.h"
#include "Transform.h"

namespace Shape {
	struct AABB {
		Vector2f Min;
		Vector2f Max;
	};

	struct Circle
	{
		Vector2f center;
		float radius;
	};

	class PolygonRender;
	class PolygonCollider;

	class Polygon {
		friend class PolygonRender;
		friend class PolygonCollider;

		transform* m_ptransform;
		Vector2f* localPoints;
		Vector2f* globalPoints;
		unsigned int size;

		AABB aabb;

	public:
		Polygon();
		void SetTransform(transform* _transform);//이걸 호출하면 글로벌포인트도 쓴다는 뜻
		template<size_t n>
		void SetPoints(const std::array<Vector2f, n>& arr);
		Vector2f* GetLocalPoints();
		Vector2f* GetGlobalPoints();
		const AABB& GetAABB();
		size_t Size();
		void UpdateGlobalPoints();
		void Destructor();
	};

	template<size_t n>
	inline void Polygon::SetPoints(const std::array<Vector2f, n>& arr)
	{
		if (localPoints != nullptr)
			delete[] localPoints;

		size = n;
		localPoints = new Vector2f[size];

		aabb.Min.x = localPoints[0].x;
		aabb.Max.x = localPoints[0].x;
		aabb.Min.y = localPoints[0].y;
		aabb.Max.y = localPoints[0].y;

		for (size_t i = 0; i < size; i++) {
			localPoints[i] = arr[i];

			aabb.Min.x = min(aabb.Min.x, localPoints[i].x);
			aabb.Max.x = max(aabb.Max.x, localPoints[i].x);
			aabb.Min.y = min(aabb.Min.y, localPoints[i].y);
			aabb.Max.y = max(aabb.Max.y, localPoints[i].y);
				
		}
	}

}

