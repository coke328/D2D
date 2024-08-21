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
	bool ColliderOn;

	Collider();
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
	void Init(Vector2f* arr, size_t size);
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
