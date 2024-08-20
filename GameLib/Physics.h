#pragma once
#include "Vector2f.h"
#include "CollideManager.h"

class RigidBody;
class PolygonCollider;

class Physics
{
	enum CollisionType
	{
		normalCollision,
		onesideCollision,
		onlyCollision
	};


	Physics() = default;
	void SolveContact(GameObject* objects[2], Contact& contact, RigidBody* rb[2], PolygonCollider* coll[2]);
	void CalcForce(GameObject* objects[2], RigidBody* rb[2], Contact& contact, Vector2f n);
	void CalcHalfForce(bool gotrb, GameObject* objects[2], RigidBody* rb[2], Contact& contact, Vector2f n);
	void Friction();
	float CalcFriction(float f1, float f2);
	float CalcBounce(float b1, float b2);

	Vector2f forces[2];
	float rotForces[2];

public:
	void ProcessCollision();

	static Physics& GetInstance();
	static Vector2f ForceConvert(Vector2f force, Vector2f surfaceNormal, float friction, float bounceness);

	static Vector2f Force(Vector2f force, float mass);
	static float AngularForce(float force, float angularInertia, float moment);
	
};

