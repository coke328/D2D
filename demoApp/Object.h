#pragma once
#include "GameLib.h"
#include "Shapes.h"

class Object : public GameObject {
public:
	pComponent<PolygonRender*> polyRender;
	pComponent<PolygonCollider*> polyColl;
	pComponent<RigidBody*> rigidbody;

	objectsShape shape;

	Object(objectsShape _shape);

	virtual ~Object() = default;

	void Init() override;
	virtual void init() = 0;

	void SetRigidBody(float mass, float inertia, float bounce, float staticFriction, float kineticFriction);
};

class MovePoly : public Object {
	float speed;
	float rotspeed;
	Vector2f mouseStart;
public:
	MovePoly();
	void init() override;

	void Update() override;

	void FixedUpdate() override;
};

class Floor : public GameObject {
	pComponent<PolygonRender*> polyRender;
	pComponent<PolygonCollider*> polyColl;
public:

	virtual ~Floor() = default;

	void Init() override;
};


class Stone : public Object 
{

};
