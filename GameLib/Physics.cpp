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
	Vector2f correctionVec = n * tmp / (mA + mB);//((tmp > 0) ? tmp : 0)

	objects[A]->m_transform.AddGlobalPosition(correctionVec * mB);
	objects[B]->m_transform.AddGlobalPosition(-correctionVec * mA);

	if (rb[A] != nullptr) {
		//forces[A] += (correctionVec * mB) * rb[A]->mass;
		
	}
		

	if (rb[B] != nullptr) {
		//forces[B] -= (correctionVec * mA) * rb[B]->mass;
		
	}
		
}

void Physics::CalcForce(GameObject* objects[2], RigidBody* rb[2], Contact& contact, Vector2f n)
{

	float bounce = CalcBounce(rb[0]->bounce, rb[1]->bounce);
	float staticFriction = CalcFriction(rb[0]->staticFriction, rb[1]->staticFriction);
	float kineticFriction = CalcFriction(rb[0]->kineticFriction, rb[1]->kineticFriction);

	Vector2f r0 = objects[0]->m_transform.GetGlobalPosition() - contact.CollisionPoint;
	Vector2f r1 = objects[1]->m_transform.GetGlobalPosition() - contact.CollisionPoint;

	float I0 = rb[0]->GetMoment();
	float I1 = rb[1]->GetMoment();


	Vector2f tangent = { n.y,-n.x };
	Vector2f relativeVel = (rb[1]->velocity + Vector2f(rb[1]->rotVelocity * r1.y, -rb[1]->rotVelocity * r1.x))
		- (rb[0]->velocity + Vector2f(rb[0]->rotVelocity * r0.y, -rb[0]->rotVelocity * r0.x));
	float mag = (1 / rb[0]->mass + 1 / rb[1]->mass +
		Mathf::Square(Mathf::Cross(r0, n)) / I0 + Mathf::Square(Mathf::Cross(r1, n)) / I1);
	float normalVel = Mathf::Dot(n, relativeVel);
	float normalForce = normalVel / mag;
	float tangentForce = Mathf::Dot(tangent, relativeVel) / mag;
	Vector2f J = n * normalForce * -(bounce + 1) / 2;
	
	forces += J;
	rotForces[0] += Mathf::Cross(r0, J);
	rotForces[1] -= Mathf::Cross(r1, J);

	if (abs(tangentForce) < staticFriction * abs(normalVel)) {
		Vector2f tanJ = tangent * tangentForce / 2;
		frictionForces += tanJ;
		frictionRotForces[0] += Mathf::Cross(r0, tanJ);
		frictionRotForces[1] += -Mathf::Cross(r1, tanJ);

	}
	else {
		float f = kineticFriction * normalForce;

		Vector2f tanJ = tangent * f / 2;
		frictionForces += tanJ;
		frictionRotForces[0] += Mathf::Cross(r0, tanJ);
		frictionRotForces[1] += -Mathf::Cross(r1, tanJ);
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

	float IA = rb[A]->GetMoment();

	Vector2f tangent = { n.y,-n.x };
	Vector2f relativeVel = (rb[A]->velocity + Vector2f(rb[A]->rotVelocity * rA.y, -rb[A]->rotVelocity * rA.x));
	float mag = (1 / rb[A]->mass + Mathf::Square(Mathf::Cross(rA, n)) / IA);
	float normalVel = Mathf::Dot(n, relativeVel);
	float normalForce = normalVel / mag;
	float tangentVel = Mathf::Dot(tangent, relativeVel);
	float tangentForce = tangentVel / mag;
	Vector2f J = n * normalForce * -(bounce + 1);

	float sign = gotrb ? -1 : 1;
	forces += J * sign;
	rotForces[A] -= Mathf::Cross(rA, J);

	if (abs(tangentForce) < staticFriction * abs(normalVel)) {
		Vector2f tanJ = tangent * tangentForce / 2;
		frictionForces += tanJ * sign;
		frictionRotForces[A] += -Mathf::Cross(rA, tanJ);
	}
	else {
		float f = kineticFriction * normalForce;

		Vector2f tanJ = tangent * f / -2;
		frictionForces += tanJ * sign;
		frictionRotForces[A] += -Mathf::Cross(rA, tanJ);
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
	return (b1 * b2) / (b1 + b2);
}

void Physics::ResetForces()
{
	forces = { 0,0 };
	rotForces[0] = 0;
	rotForces[1] = 0;
	frictionForces = { 0,0 };
	frictionRotForces[0] = 0;
	frictionRotForces[1] = 0;
}

Vector2f Physics::Force(Vector2f force, float mass)
{
	return force / mass;
}

float Physics::AngularForce(float force, float angularInertia, float moment)
{
	return force / (angularInertia * moment);
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

		ResetForces();

		for (unsigned int i = 0; i < size; i++) {
			SolveContact(objects, col->contacts[i], rb, col->polys);
		}

		forces = forces / size;
		rotForces[0] = (rotForces[0]) / size;
		rotForces[1] = (rotForces[1]) / size;

		

		if (rb[0] != nullptr && rb[1] != nullptr) {
			

			rb[0]->AddForce(-forces);
			rb[0]->AddRotForce(rotForces[0]);

			frictionForces = frictionForces / size;
			frictionRotForces[0] = frictionRotForces[0] / size;
			
			//rb[0]->AddForce(-frictionForces);
			//rb[0]->AddRotForce(frictionRotForces[0]);

			rb[1]->AddForce(forces);
			rb[1]->AddRotForce(rotForces[1]);

			frictionRotForces[1] = frictionRotForces[1] / size;
			//rb[1]->AddForce(frictionForces);
			//rb[1]->AddRotForce(frictionRotForces[1]);
		}
		else if (rb[0] == nullptr && rb[1] == nullptr) {

		}
		else {
			int A = int(rb[0] == nullptr);
			
			float sign = (A ? -1 : 1);
			rb[A]->AddForce(forces * sign);
			rb[A]->AddRotForce(rotForces[A]);

			frictionForces = frictionForces / size;
			frictionRotForces[A] = frictionRotForces[A] / size;
			//rb[A]->AddForce(frictionForces * sign);
			//rb[A]->AddRotForce(frictionRotForces[A]);
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
