#pragma once
#include "Component.h"


class RigidBody : public Component
{
private:

	
public:
	RigidBody();


	Vector2f velocity;//�ӵ�
	float rotVelocity;//���ӷ�
	float mass;//����
	float angularInertia;//������ 0 ~ 1 ~ inf -- 0~1 : ������ ����� ��������, 1~inf : ������ �ٱ��� ��������
	float moment;//���Ʈ  ���� ��� mass * radius^2 / 2  collider���ؼ� ����ҵ�
	float staticFriction;// ��������
	float kineticFriction;// ����� ���������º��� �۾ƾ���
	float bounce;//ź��
	bool gravityWork;
	static float gravity;
	static Vector2f gravityDiraction;

	void CalcMoment();//polygonCollider �߰��ϰ��� ȣ��
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