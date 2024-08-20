#pragma once
#include "Collider.h"

struct Contact {
	bool pointObject;//0 : object1 -> point ,  1 : object2 -> point
	size_t pointIdx;
	size_t cornerIdx;
	Vector2f CollisionPoint;

	Contact() = default;
	void Init(bool pointObject, int pointidx, int corner, Vector2f collPoint);
};

class Collision 
{
	static std::list<Collision> Collisions;

public:
	PolygonCollider* polys[2];
	Contact* contacts;
	size_t size;
	static const unsigned int maxContacts = 2;
	Collision(PolygonCollider* poly1, PolygonCollider* poly2, Contact* _contacts, size_t _size);
	static void CreateCollision(PolygonCollider* poly1, PolygonCollider* poly2, Contact* _contacts, size_t _size);
	static Collision* Front();
	static void Pop();
	static bool Empty();
};



class CollideManager
{
	CollideManager();
	~CollideManager() = default;

	CollideManager(const CollideManager&) = delete;
	CollideManager& operator=(const CollideManager&) = delete;

	void CheckCollide(unsigned int i, unsigned int j);
	static float GetCrossMag(const Vector2f& lastPoint, const Vector2f& point, const Vector2f& line1, const Vector2f& line2);
	std::vector<PolygonCollider>& polyColls;
	
public:
	static CollideManager& GetInstance();

	void Update();
	static int GetCross(const Vector2f& curPos, const Vector2f& lastPos, Vector2f* points, unsigned int size, Vector2f* crossPoint);
};
