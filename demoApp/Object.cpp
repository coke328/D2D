#include "Object.h"

Object::Object(objectsShape _shape, Vector2f _startPos)
{
	inertia = 3;
	bounce = 0.3;
	staticFriction = 0.50;
	kineticFriction = 0.30;

	polyRender = AddComponent<PolygonRender>();
	polyColl = AddComponent<PolygonCollider>();
	rigidbody = AddComponent<RigidBody>();

	shape = _shape;
	m_transform.SetGlobalPosition(_startPos);
}

void Object::Init()
{
	auto& shape_ = Shapes::GetShape(shape);
	polyRender.Get()->Init(shape_.first, shape_.second);
	polyColl.Get()->Init(shape_.first, shape_.second);

	polyRender.Get()->color = D2D1::ColorF(0, 0, 0);
	polyRender.Get()->lineThickness = 2;

	rigidbody.Get()->CalcMoment();

	switch (shape)
	{
	case Box_10x40:
		SetRigidBody(5, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_40x10:
		SetRigidBody(5, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_20x20:
		SetRigidBody(5, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_40x40:
		SetRigidBody(20, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_10x50:
		SetRigidBody(6, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_50x10:
		SetRigidBody(6, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_10x60:
		SetRigidBody(7, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_60x10:
		SetRigidBody(7, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_20x40:
		SetRigidBody(10, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Box_40x20:
		SetRigidBody(10, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Horn_20x20:
		SetRigidBody(3, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Horn_40x40:
		SetRigidBody(12, inertia, bounce, staticFriction, kineticFriction);
		break;
	case SlopeLeft_20x20:
		SetRigidBody(3, inertia, bounce, staticFriction, kineticFriction);
		break;
	case SlopeRight_20x20:
		SetRigidBody(3, inertia, bounce, staticFriction, kineticFriction);
		break;
	case SlopeLeft_40x20:
		SetRigidBody(6, inertia, bounce, staticFriction, kineticFriction);
		break;
	case SlopeRight_40x20:
		SetRigidBody(6, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Octagon_20x20:
		SetRigidBody(4, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Octagon_40x40:
		SetRigidBody(16, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Triangle_20:
		SetRigidBody(4, inertia, bounce, staticFriction, kineticFriction);
		break;
	case Triangle_40:
		SetRigidBody(13, inertia, bounce, staticFriction, kineticFriction);
		break;
	default:
		break;
	}

	init();
}

void Object::init()
{
}

void Object::SetRigidBody(float mass, float inertia, float bounce, float staticFriction, float kineticFriction)
{
	rigidbody.Get()->mass = mass;
	rigidbody.Get()->angularInertia = inertia;
	rigidbody.Get()->kineticFriction = kineticFriction;
	rigidbody.Get()->staticFriction = staticFriction;

	rigidbody.Get()->CalcMoment();
}

void Floor::Init()
{
	Vector2f* tmp = new Vector2f[4];
	tmp[0] = { 1200,-400 };
	tmp[1] = { -1200,-400 };
	tmp[2] = { -1200,-600 };
	tmp[3] = { 1200,-600 };
	polyRender = AddComponent<PolygonRender>();
	polyColl = AddComponent<PolygonCollider>();

	polyRender.Get()->Init(tmp, 4);
	polyColl.Get()->Init(tmp, 4);

	polyRender.Get()->color = D2D1::ColorF(255, 0, 0);
	polyRender.Get()->lineThickness = 2;
}

MovePoly::MovePoly() : Object(objectsShape::Box_40x40, {500,0})
{
	speed = 70;
	rotspeed = 300;
}

void MovePoly::init()
{
}

void MovePoly::Update()
{
}

void MovePoly::FixedUpdate()
{
	{
		//std::cout << rigidbody.Get()->velocity.x << std::endl;
		//std::cout << m_transform.GetLocalPosition().x << std::endl;

		if (InputSystem::GetInstance().IsKeyPress('W')) {
			rigidbody.Get()->AddForce({ 0,speed + 10 });
			//m_transform.AddGlobalPosition({ 0,speed });
			//rigidbody.Get()->velocity = { 0,speed };
		}
		if (InputSystem::GetInstance().IsKeyPress('S')) {
			rigidbody.Get()->AddForce({ 0,-speed });
			//m_transform.AddGlobalPosition({ 0,-speed });
			//rigidbody.Get()->velocity = { 0,-speed };
		}
		if (InputSystem::GetInstance().IsKeyPress('A')) {
			rigidbody.Get()->AddForce({ -speed,0 });
			//m_transform.AddGlobalPosition({ -speed,0 });
			//rigidbody.Get()->velocity = { -speed,0 };
		}
		if (InputSystem::GetInstance().IsKeyPress('D')) {
			rigidbody.Get()->AddForce({ speed,0 });
			//m_transform.AddGlobalPosition({ speed,0 });
			//rigidbody.Get()->velocity = { speed,0 };
		}
		if (InputSystem::GetInstance().IsKeyPress('Q')) {
			rigidbody.Get()->AddRotForce(rotspeed);
		}
		if (InputSystem::GetInstance().IsKeyPress('E')) {
			rigidbody.Get()->AddRotForce(-rotspeed);
		}


	}
}

Stone::Stone() : Object(objectsShape::Octagon_20x20, { 0,0 })
{
}

void Stone::init()
{
	m_transform.SetGlobalPosition({ -700,-350 });
	rigidbody.Get()->gravityWork = false;
	polyColl.Get()->ColliderOn = false;
}

void Stone::Shoot(Vector2f force)
{
	rigidbody.Get()->AddForce(force);
	rigidbody.Get()->gravityWork = true;
	polyColl.Get()->ColliderOn = true;
}

