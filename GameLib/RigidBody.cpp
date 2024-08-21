#include "pch.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "TimeSystem.h"
#include "Physics.h"

float RigidBody::gravity = 5.f;
Vector2f RigidBody::gravityDiraction = { 0,-1 };

void RigidBody::Update()
{

	float delT = TimeSystem::GetInstance().GetDeltaTime();
	gameObject->m_transform.AddGlobalPosition(velocity * delT);
	gameObject->m_transform.AddLocalRotation(rotVelocity * delT);


	AddForce(gravityDiraction * gravity * mass);
	//std::cout << (velocity).x << std::endl;
}

void RigidBody::Destructor()
{
}

void RigidBody::Gravity()
{
	
}

RigidBody::RigidBody() : velocity(0,0),
						rotVelocity(0),
						mass(10),
						angularInertia(1),
						moment(5000),
						staticFriction(0.5),
						kineticFriction(0.3),
						bounce(0.5)
{
}

void RigidBody::CalcMoment()
{
	PolygonCollider* coll = gameObject->GetComponent<PolygonCollider>();

	Vector2f* points = coll->polygon.GetLocalPoints();
	unsigned int size = coll->polygon.Size();

	float sum = 0;
	for (unsigned int i = 0; i < size; i++) {
		sum += points[i].sqrLength();
	}
	sum /= size;
	
	moment = mass * sum / 2;
}

void RigidBody::AddForce(Vector2f force)
{
	velocity += Physics::Force(force, mass);
}

void RigidBody::AddRotForce(float f)
{
	rotVelocity += Physics::AngularForce(f, angularInertia, moment);
}

void RigidBody::AddForceByPoint(Vector2f globalPoint, Vector2f force)
{
	Vector2f localPos = globalPoint - gameObject->m_transform.GetGlobalPosition();

	Vector2f normal = localPos.Normalize();

	float fx = (normal.x * force.y - normal.y * force.x) * localPos.Length();
	Vector2f fy = normal * (normal.x * force.x + normal.y * force.y);

	AddForce(fy);
	AddRotForce(fx);

}

std::pair<Vector2f, float> RigidBody::pointForce(Vector2f gPoint, Vector2f force)
{
	Vector2f localPos = gPoint - gameObject->m_transform.GetGlobalPosition();

	Vector2f normal = localPos.Normalize();

	float fx = (normal.x * force.y - normal.y * force.x) * localPos.Length();
	Vector2f fy = normal * (normal.x * force.x + normal.y * force.y);

	return { fy,fx };
}

void RigidBody::AddForceByPointAndUpdate(Vector2f globalPoint, Vector2f force)
{
	Vector2f localPos = globalPoint - gameObject->m_transform.GetGlobalPosition();

	Vector2f normal = localPos.Normalize();

	float fx = (normal.x * force.y - normal.y * force.x) * localPos.Length();
	Vector2f fy = normal * (normal.x * force.x + normal.y * force.y);

	Vector2f tmpVel = velocity;
	float tmpRotVel = rotVelocity;

	AddForce(fy);
	AddRotForce(fx);

	Update();

	velocity = tmpVel;
	rotVelocity = tmpRotVel;
}

float RigidBody::GetMoment()
{
	return angularInertia / moment;
}

void RigidBody::Reverse(float dt)
{
	gameObject->m_transform.AddLocalRotation(-rotVelocity * dt);
	gameObject->m_transform.AddGlobalPosition(-velocity * dt);
}

