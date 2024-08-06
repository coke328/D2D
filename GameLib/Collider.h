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

class GameObject;

class PolygonCollider : public Collider{
	friend inline void CreateComponent<PolygonCollider>::Update();
private:
	Shape::Polygon polygon;
public:

	PolygonCollider();
	~PolygonCollider() = default;
	template<size_t n>
	void Init(const std::array<Vector2f, n>& arr);
	void Update() override;
	void Destructor() override;
};

template<>
inline CreateComponent<PolygonCollider>::CreateComponent() : Base(2)
{
	compsIdx = Components::GetInstance().Bases.size();
	Components::GetInstance().Bases.push_back(dynamic_cast<Base*>(this));
	Components::GetInstance().Sort();
}

template<>
inline void CreateComponent<PolygonCollider>::Update()
{
	size_t size = vector.size();
	for (size_t i = 0; i < size; i++)
	{
		vector[i].Update();
	}
	
	for (size_t i = 0; i < size - 1; i++) {
		for (size_t j = i + 1; j < size; j++)
		{
			if (CollisionCheck::AA_BB(vector[i].polygon.GetAABB(), vector[j].polygon.GetAABB())) {
				std::cout << "collide" << std::endl;
			}
		}
	}
}

