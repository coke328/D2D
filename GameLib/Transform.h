#pragma once
#include "Vector2f.h"
#include "Typedef.h"

void PrintMatrix(const Matrix& m);

class GameObject;

class transform
{
private:
	//friend Transform; // this class is made by shared_ptr so this not work

	transform* parent;
	std::list<transform*> childs;
	size_t childSize;

	GameObject* gameObject;

	
protected:
	Vector2f LPosition;
	float LRotation;
	Vector2f LScale;

	Matrix LMatrix;
	Matrix GMatrix;

	bool Changed;
	bool isModified;

	void CalcLMatrix();//set function들을 쓰면 계산 add할때는 계산 x
	void Modified();
public:
	transform();
	~transform();

	void Init(GameObject* _gameObject);

	void SetParent(transform* _parent);
	GameObject* GetGameObject();

	bool IsModified();
	void EndofFrame();

	void AddLocalPosition(Vector2f deltaPos);
	void SetLocalPosition(Vector2f Pos);
	void AddGlobalPosition(Vector2f deltaPos);
	void SetGlobalPosition(Vector2f Pos);

	void AddLocalRotation(float deltaR);
	void SetLocalRotation(float R);
	void SetGlobalRotation(float R);

	void AddLocalScale(Vector2f deltaScale);
	void SetLocalScale(Vector2f Scale);

	Vector2f GetLocalPosition();
	Vector2f GetGlobalPosition();

	float GetLocalRotation();
	float GetGlobalRotation();

	Vector2f GetLocalScale();

	void CalcGMatrix();

	void SetLocalMatrix(Matrix matrix);
	const Matrix& GetGlobalMatrix();
	const Matrix& GetLocalMatrix();
};