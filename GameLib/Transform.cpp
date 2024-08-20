#include "pch.h"
#include "Transform.h"
#include "Mathf.h"
#include "GameObject.h"



transform::transform()
{
	LPosition = { 0.000001,0.000001 };
	LRotation = 0;
	LScale = { 1,1 };

	LMatrix = Matrix::Identity();
	GMatrix = Matrix::Identity();

	Changed = true;
	isModified = true;

	gameObject = nullptr;
	childSize = 0;
	parent = nullptr;
}

transform::~transform()
{
	for (auto& child : childs) {
		child->parent = nullptr;
	}
	if (parent != nullptr) {
		for (auto child = parent->childs.begin(); child != parent->childs.end(); child++) {
			if (*child == this) {
				parent->childs.erase(child);
			}
		}
	}
}

void transform::Init(GameObject* _gameObject)
{
	gameObject = _gameObject;
}

void transform::SetParent(transform* _parent)//위치 유지
{
	if (parent != nullptr) {
		for (auto child = parent->childs.begin(); child != parent->childs.end(); child++) {
			if (*child == this) {
				parent->childs.erase(child);
				break;
			}
		}
	}

	Matrix LastMatrix = GetGlobalMatrix();
	parent = _parent;
	Matrix ParentMatrix = parent->GetGlobalMatrix();
	ParentMatrix.Invert();
	SetLocalMatrix(LastMatrix * ParentMatrix);
	Modified();
}

void transform::CalcLMatrix()
{
	if (Changed == false) return;
	LMatrix = Matrix::Scale(LScale.x, LScale.y) *
		Matrix::Rotation(Mathf::RadToDeg(LRotation)) *
		Matrix::Translation(LPosition.x, LPosition.y);
	//PrintMatrix(LMatrix);
	Changed = false;
}

void transform::Modified()
{
	isModified = true;
	Changed = true;
}

GameObject* transform::GetGameObject()
{
	return gameObject;
}

bool transform::IsModified()
{
	return isModified;
}

void transform::EndofFrame()
{
	isModified = false;
	//std::cout << "hi ------------------" << std::endl;
}

void transform::AddLocalPosition(Vector2f deltaPos)
{
	LPosition += deltaPos;
	Modified();
}

void transform::SetLocalPosition(Vector2f Pos)
{
	LPosition = Pos;
	Modified();
}

void transform::AddGlobalPosition(Vector2f deltaPos)
{

	if (parent != nullptr) {
		Matrix pMatrix = parent->GetGlobalMatrix();
		Matrix result = pMatrix * Matrix::Translation(deltaPos.x, deltaPos.y);
		pMatrix.Invert();
		result = result * pMatrix;
		LPosition += { result.dx, result.dy };
	}
	else {
		//SetLocalMatrix(GetLocalMatrix() * Matrix::Translation(deltaPos.x, deltaPos.y));
		LPosition += deltaPos;
	}
	Modified();
}

void transform::SetGlobalPosition(Vector2f Pos)
{
	Vector2f dVec = Pos - GetGlobalPosition();
	AddGlobalPosition(dVec);
	Modified();
}

void transform::AddLocalRotation(float r)
{
	LRotation += r;
	Modified();
}

void transform::SetLocalRotation(float R)
{
	LRotation = R;
	Modified();
}

void transform::SetGlobalRotation(float R)
{
	float dR = R - GetGlobalRotation();
	LRotation += dR;
	Modified();
}

void transform::AddLocalScale(Vector2f deltaScale)
{
	LScale += deltaScale;
	Modified();
}

void transform::SetLocalScale(Vector2f Scale)
{
	LScale = Scale;
	Modified();
}

Vector2f transform::GetLocalPosition()
{
	return LPosition;
}

Vector2f transform::GetGlobalPosition()
{
	CalcGMatrix();
	return { GMatrix.dx,GMatrix.dy };
}

float transform::GetLocalRotation()
{
	return LRotation;
}

float transform::GetGlobalRotation()
{
	CalcGMatrix();
	return Vector2f(GMatrix.m21, GMatrix.m11).Direction();
}

Vector2f transform::GetLocalScale()
{
	return LScale;
}

void transform::CalcGMatrix()
{
	CalcLMatrix();

	GMatrix = LMatrix;
	if (parent == nullptr) return; 

	GMatrix = GMatrix * parent->GetGlobalMatrix();

}

void transform::SetLocalMatrix(Matrix matrix)
{
	LMatrix = matrix;
	LPosition = Mathf::PosFromMatrix(matrix);
	LRotation = -Mathf::RotFromMatrix(matrix);
	LScale = Mathf::ScaleFromMatrix(matrix);
}

const Matrix& transform::GetGlobalMatrix()
{
	CalcGMatrix();
	return GMatrix;
}

const Matrix& transform::GetLocalMatrix()
{
	CalcLMatrix();
	return LMatrix;
}

void PrintMatrix(const Matrix& m)
{
	std::cout << m.m11 << "," << m.m12 << std::endl <<
		m.m21 << "," << m.m22 << std::endl <<
		m.dx << "," << m.dy << std::endl;
}
