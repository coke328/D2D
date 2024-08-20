#include "pch.h"
#include "CollideManager.h"
#include "CreateComponent.h"
#include "Collider.h"
#include "CollisionCheck.h"
#include "Mathf.h"
#include "GameObject.h"

std::list<Collision> Collision::Collisions;

CollideManager::CollideManager() : polyColls(CreateComponent<PolygonCollider>::Get().Vector())
{

}

void CollideManager::CheckCollide(unsigned int i, unsigned int j)
{

	Vector2f* points1 = polyColls[i].polygon.GetGlobalPoints();
	unsigned int size1 = polyColls[i].polygon.Size();
	Vector2f* points2 = polyColls[j].polygon.GetGlobalPoints();
	unsigned int size2 = polyColls[j].polygon.Size();

	Contact* contacts = new Contact[Collision::maxContacts];
	size_t size = 0;

	bool coll = false;
	for (unsigned int a = 0; a < size1; a++) {
		coll = true;
		for (unsigned int b = 0; b < size2; b++) {

			Vector2f corner = points2[(b + 1) % size2] - points2[b];
			Vector2f vec = points1[a] - points2[b];
			if (Mathf::Cross(corner, vec) < 0) { 
				coll = false;
				break; 
			}
			
		}

		if (coll && size < Collision::maxContacts) {

			Vector2f CrossP;
			int _j = GetCross(points1[a],polyColls[i].gameObject->m_transform.GetGlobalPosition(),
				points2, size2, &CrossP);
			if (_j == -1) continue;

			contacts[size].Init(0, a, _j, CrossP);
			size++;
		}
	}

	for (unsigned int a = 0; a < size2; a++) {
		coll = true;
		for (unsigned int b = 0; b < size1; b++) {

			Vector2f corner = points1[(b + 1) % size1] - points1[b];
			Vector2f vec = points2[a] - points1[b];
			if (Mathf::Cross(corner, vec) < 0) {
				coll = false;
				break;
			}
		}

		if (coll && size < Collision::maxContacts) {
			Vector2f CrossP;
			int _j = GetCross(points2[a], polyColls[j].gameObject->m_transform.GetGlobalPosition(),
				points1, size1, &CrossP);
			if (_j == -1) continue;

			contacts[size].Init(1, a, _j, CrossP);
			size++;
		}
	}

	if (size > 0) {
		Collision::CreateCollision(&polyColls[i], &polyColls[j], contacts, size);
	}
}

int CollideManager::GetCross(const Vector2f& P1, const Vector2f& P2, Vector2f* points, unsigned int size, Vector2f* crossPoint)
{
	std::vector<std::pair<int,float>> idx;
	std::vector<Vector2f> crossPoints;

	for (unsigned int i = 0; i < size; i++) {

		float t = GetCrossMag(P1, P2, points[i], points[(i + 1) % size]);
		if (t == -1) continue;

		crossPoint->x = P1.x + t * (P2.x - P1.x);
		crossPoint->y = P1.y + t * (P2.y - P1.y);

		idx.push_back({ i,t });
		crossPoints.push_back(*crossPoint);
	}
	if (idx.size() == 0) return -1;

	if (idx.size() == 1) {
		return idx.front().first;
	}
	else {
		float min = (crossPoints[0] - P2).Length();
		int minIdx = 0;
		for (int i = 1; i < idx.size(); i++) {
			float length = (crossPoints[i] - P2).Length();
			if (length < min) {
				min = length;
				minIdx = i;
			}
			
		}

		*crossPoint = crossPoints[minIdx];
		return minIdx;
	}
}

float CollideManager::GetCrossMag(const Vector2f& P1, const Vector2f& P2, const Vector2f& P3, const Vector2f& P4)
{
	float a, b, c, d, e, f, k, t, u;
	a = P2.x - P1.x;
	b = P3.x - P4.x;
	c = P2.y - P1.y;
	d = P3.y - P4.y;
	e = P3.x - P1.x;
	f = P3.y - P1.y;

	k = a * d - b * c;

	if (k == 0) return -1;

	t = (d * e - b * f) / k;
	u = (a * f - c * e) / k;
	if (t < 0 || t > 1 || u < 0 || u > 1) return -1;

	return t;
}

CollideManager& CollideManager::GetInstance()
{
	static CollideManager instance;
	return instance;
}

void CollideManager::Update()
{
	size_t size = polyColls.size();
	for (size_t i = 0; i < size -1; i++)
	{
		for (size_t j = i+1; j < size; j++)
		{
			if (CollisionCheck::AA_BB(polyColls[i].aabb, polyColls[j].aabb)) {
				CheckCollide(i, j);
			}
		}
	}
}

Collision::Collision(PolygonCollider* poly1, PolygonCollider* poly2, Contact* _contacts, size_t _size)
{
	polys[0] = poly1;
	polys[1] = poly2;
	contacts = _contacts;
	size = _size;
}

void Collision::CreateCollision(PolygonCollider* poly1, PolygonCollider* poly2, Contact* _contacts, size_t _size)
{
	//std::cout << "createColl" << std::endl;
	Collisions.emplace_back(poly1, poly2, _contacts, _size);

}

Collision* Collision::Front()
{
	if (Collisions.empty()) return nullptr;
	return &Collisions.front();
}

void Collision::Pop()
{
	if (Collisions.empty()) return;
	delete[] Collisions.front().contacts;
	Collisions.erase(Collisions.begin());
}

bool Collision::Empty()
{
	return Collisions.empty();
}

void Contact::Init(bool _pointObject, int pointidx, int corner, Vector2f collPoint)
{
	pointObject = _pointObject;
	pointIdx = pointidx;
	cornerIdx = corner;
	CollisionPoint = collPoint;
}
