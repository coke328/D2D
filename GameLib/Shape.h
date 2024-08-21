#pragma once

class transform;

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
		void SetPoints(Vector2f* arr, size_t size);
		Vector2f* GetLocalPoints();
		Vector2f* GetGlobalPoints();
		const AABB& GetAABB();
		size_t Size();
		void UpdateGlobalPoints();
		void Destructor();
	};

	

}

