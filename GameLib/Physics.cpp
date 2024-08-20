#include "pch.h"
#include "Physics.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Mathf.h"
#include "TimeSystem.h"

void Physics::SolveContact(GameObject* objects[2], Contact& contact, RigidBody* rb[2], PolygonCollider* coll[2])
{
	if (contact.cornerIdx == -1) return;

	unsigned int A = (unsigned int)contact.pointObject;//point
	unsigned int B = (unsigned int)(!contact.pointObject);//corner

	Vector2f* cornerP = coll[B]->polygon.GetGlobalPoints();
	unsigned int cornerCnt = coll[B]->polygon.Size();
	Vector2f currentPoint = coll[A]->polygon.GetGlobalPoints()[contact.pointIdx];
	
	Vector2f n = (cornerP[(contact.cornerIdx + 1) % cornerCnt] - cornerP[contact.cornerIdx]).Normalize();
	n = { n.y,-n.x };

	float mA = 1;
	float mB = 1;

	if (rb[0] != nullptr && rb[1] != nullptr) {
		CalcForce(objects, rb, contact, n);
		mA = rb[A]->mass;
		mB = rb[B]->mass;
	}
	else if (rb[0] == nullptr && rb[1] == nullptr) {

	}
	else {
		if (rb[A] != nullptr) {
			CalcHalfForce(A, objects, rb, contact, n);
			mA = 0;
			mB = 1;
		}
		else {
			CalcHalfForce(B, objects, rb, contact, n);
			mA = 1;
			mB = 0;
		}
	}

	float tmp = Mathf::Dot(n, cornerP[contact.cornerIdx] - currentPoint);
	Vector2f correctionVec = n * tmp;//((tmp > 0) ? tmp : 0)

	objects[A]->m_transform.AddGlobalPosition(correctionVec * mB / (mA + mB));
	objects[B]->m_transform.AddGlobalPosition(-correctionVec * mA / (mA + mB));
}

void Physics::CalcForce(GameObject* objects[2], RigidBody* rb[2], Contact& contact, Vector2f n)
{
	float bounce = CalcBounce(rb[0]->bounce, rb[1]->bounce);
	float staticFriction = CalcFriction(rb[0]->staticFriction, rb[1]->staticFriction);
	float kineticFriction = CalcFriction(rb[0]->kineticFriction, rb[1]->kineticFriction);

	Vector2f r0 = objects[0]->m_transform.GetGlobalPosition() - contact.CollisionPoint;
	Vector2f r1 = objects[1]->m_transform.GetGlobalPosition() - contact.CollisionPoint;

	float I0 = rb[0]->moment * rb[0]->angularInertia;
	float I1 = rb[1]->moment * rb[1]->angularInertia;


	Vector2f tangent = { n.y,-n.x };
	Vector2f relativeVel = (rb[1]->velocity + Vector2f(rb[1]->rotVelocity * r1.y, -rb[1]->rotVelocity * r1.x))
		- (rb[0]->velocity + Vector2f(rb[0]->rotVelocity * r0.y, -rb[0]->rotVelocity * r0.x));
	float mag = (1 / rb[0]->mass + 1 / rb[1]->mass +
		Mathf::Square(Mathf::Cross(r0, n)) / I0 + Mathf::Square(Mathf::Cross(r1, n)) / I1);
	float normalForce = Mathf::Dot(n, relativeVel) / mag;
	float tangentForce = Mathf::Dot(tangent, relativeVel) / mag;
	Vector2f J = n * normalForce * -(bounce + 1);
	

	forces[0] -= J;
	forces[1] += J;
	rotForces[0] += Mathf::Cross(r0, J);
	rotForces[1] -= Mathf::Cross(r1, J);

	int sign = (tangentForce >= 0) ? 1 : -1;

	std::pair<Vector2f, float> force;
	if (tangentForce * sign <= staticFriction * abs(normalForce)) {
		force = rb[0]->pointForce(contact.CollisionPoint, -tangent * tangentForce);
		forces[0] += force.first;
		rotForces[0] += force.second;

		force = rb[1]->pointForce(contact.CollisionPoint, tangent * tangentForce);
		forces[1] += force.first;
		rotForces[1] += force.second;
	}
	else {
		float f = kineticFriction * normalForce;

		force = rb[0]->pointForce(contact.CollisionPoint, tangent * f * sign);
		forces[0] += force.first;
		rotForces[0] += force.second;

		force = rb[1]->pointForce(contact.CollisionPoint, -tangent * f * sign);
		forces[1] += force.first;
		rotForces[1] += force.second;
	}
}

void Physics::CalcHalfForce(bool gotrb, GameObject* objects[2], RigidBody* rb[2], Contact& contact, Vector2f n)
{
	unsigned int A = (unsigned int)gotrb;//got rb
	unsigned int B = (unsigned int)(!gotrb);//no rb

	float bounce = rb[A]->bounce;
	float staticFriction = rb[A]->staticFriction;
	float kineticFriction = rb[A]->kineticFriction;

	Vector2f rA = objects[A]->m_transform.GetGlobalPosition() - contact.CollisionPoint;

	float IA = rb[A]->moment * rb[A]->angularInertia;

	Vector2f tangent = { n.y,-n.x };
	Vector2f relativeVel = (rb[A]->velocity + Vector2f(rb[A]->rotVelocity * rA.y, -rb[A]->rotVelocity * rA.x));
	float mag = (1 / rb[A]->mass + Mathf::Square(Mathf::Cross(rA, n)) / IA);
	float normalForce = Mathf::Dot(n, relativeVel) / mag;
	float tangentForce = Mathf::Dot(tangent, relativeVel) / mag;
	Vector2f J = n * normalForce * -(bounce + 1);

	forces[A] += J;
	rotForces[A] -= Mathf::Cross(rA, J);
	
	std::pair<Vector2f, float> force;

	int sign = (tangentForce >= 0) ? 1 : -1;
	
	if (tangentForce * sign <= staticFriction * abs(normalForce)) {
		force = rb[A]->pointForce(contact.CollisionPoint, -tangent * tangentForce);
		forces[A] += force.first;
		rotForces[A] += force.second;
	}
	else {
		float f = kineticFriction * normalForce;

		force = rb[A]->pointForce(contact.CollisionPoint, tangent * f * sign);
		forces[A] += force.first;
		rotForces[A] += force.second;
	}
}

void Physics::Friction()
{
}


float Physics::CalcFriction(float f1, float f2)
{
	return (f1 + f2) / 2;
}

float Physics::CalcBounce(float b1, float b2)
{
	return (b1 + b2) / 2;
}

Vector2f Physics::Force(Vector2f force, float mass)
{
	return force / mass;
}

float Physics::AngularForce(float force, float angularInertia, float moment)
{
	return force / angularInertia / moment;
}

void Physics::ProcessCollision()
{
	while (!Collision::Empty()) {
		Collision* col = Collision::Front();

		if (col == nullptr) return;

		GameObject* objects[2];
		objects[0] = col->polys[0]->gameObject;
		objects[1] = col->polys[1]->gameObject;

		RigidBody* rb[2];
		rb[0] = objects[0]->GetComponent<RigidBody>();
		rb[1] = objects[1]->GetComponent<RigidBody>();

		unsigned int size = col->size;

		forces[0] = { 0,0 };
		forces[1] = { 0,0 };
		rotForces[0] = 0;
		rotForces[1] = 0;

		for (unsigned int i = 0; i < size; i++) {
			SolveContact(objects, col->contacts[i], rb, col->polys);
		}

		forces[0] = forces[0] / size;
		forces[1] = forces[1] / size;
		rotForces[0] = rotForces[0] / size;
		rotForces[1] = rotForces[1] / size;

		if (rb[0] != nullptr) {
			rb[0]->AddForce(forces[0]);
			rb[0]->AddRotForce(rotForces[0]);
		}
		if (rb[1] != nullptr) {
			rb[1]->AddForce(forces[1]);
			rb[1]->AddRotForce(rotForces[0]);
		}

		Collision::Pop();
	}
}

Physics& Physics::GetInstance()
{
	static Physics p;
	return p;
}

Vector2f Physics::ForceConvert(Vector2f force, Vector2f surfaceNormal, float friction, float bounceness)
{
	Vector2f result;
	result.y = (surfaceNormal.x * force.x + surfaceNormal.y * force.y) * (1-friction);
	result.x = (surfaceNormal.x * force.y - surfaceNormal.y * force.x) * bounceness;

	return result;
}
