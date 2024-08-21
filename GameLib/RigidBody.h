#pragma once
#include "Component.h"


class RigidBody : public Component
{
private:

	
public:
	RigidBody();


	Vector2f velocity;//속도
	float rotVelocity;//각속력
	float mass;//질량
	float angularInertia;//각관성 0 ~ 1 ~ inf -- 0~1 : 질량이 가운데에 몰려있음, 1~inf : 질량이 바깥에 몰려있음
	float moment;//모멘트  원의 경우 mass * radius^2 / 2  collider통해서 계산할듯
	float staticFriction;// 정지마찰
	float kineticFriction;// 운동마찰 정지마찰력보다 작아야함
	float bounce;//탄성
	bool gravityWork;
	static float gravity;
	static Vector2f gravityDiraction;

	void CalcMoment();//polygonCollider 추가하고나서 호출
	void AddForce(Vector2f force);
	void AddRotForce(float f);
	void AddForceByPoint(Vector2f globalPoint, Vector2f force);
	std::pair<Vector2f, float> pointForce(Vector2f gPoint, Vector2f force);
	float GetMoment();
	void Reverse(float dt);
	void Update() override;
	void Destructor() override;

	void Gravity();
};