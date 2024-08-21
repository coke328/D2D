#include "Object.h"

Object::Object(objectsShape _shape)
{
	shape = _shape;
}

void Object::Init()
{

	polyRender = AddComponent<PolygonRender>();
	polyColl = AddComponent<PolygonCollider>();
	rigidbody = AddComponent<RigidBody>();

	auto& shape_ = Shapes::GetShape(shape);
	polyRender.Get()->Init(shape_.first, shape_.second);
	polyColl.Get()->Init(shape_.first, shape_.second);

	polyRender.Get()->color = D2D1::ColorF(0, 0, 0);
	polyRender.Get()->lineThickness = 2;

	rigidbody.Get()->CalcMoment();

	init();
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

MovePoly::MovePoly() : Object(objectsShape::Box_40x40) 
{
	speed = 50;
	rotspeed = 300;
}

void MovePoly::init()
{
	SetRigidBody(5, 2, 0.1, 0.7, 0.7);
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
			rigidbody.Get()->AddForce({ 0,speed });
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
