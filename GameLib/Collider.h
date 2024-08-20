#pragma once
#include "Component.h"
#include "CollisionCheck.h"
#include "Shape.h"


class Collider : public Component
{
protected:
	Shape::AABB aabb;

	virtual void Update() override = 0;
	virtual void Destructor() override = 0;
public:
	Collider() = default;
	virtual ~Collider() = default;
};

class CollideManager;
class Physics;

class PolygonCollider : public Collider{
	friend class CollideManager;
	friend class Physics;
private:
	
public:
	Shape::Polygon polygon;
	PolygonCollider();
	~PolygonCollider() = default;
	template<size_t n>
	void Init(const std::array<Vector2f, n>& arr);
	void Update() override;
	void Destructor() override;
};

//template<>
//inline CreateComponent<PolygonCollider>::CreateComponent() : Base(2)
//{
//	compsIdx = Components::GetInstance().Bases.size();
//	Components::GetInstance().Bases.push_back(dynamic_cast<Base*>(this));
//	Components::GetInstance().Sort();
//}
