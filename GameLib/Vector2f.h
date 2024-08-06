#pragma once
#include "Typedef.h"

class Vector2f
{
public:
	float x;
	float y;

	Vector2f();
	Vector2f(float _x, float _y);

	Vector2f& operator=(const Vector2f& v);
	Vector2f operator+(const Vector2f& v);
	Vector2f operator-(const Vector2f& v);
	Vector2f operator*(float m);
	Vector2f operator*(const Matrix& m);
	Vector2f operator/(float d);
	Vector2f operator-();
	Vector2f& operator+=(const Vector2f& v);
	Vector2f& operator-=(const Vector2f& v);
	operator D2D1_VECTOR_2F();
	operator D2D1_POINT_2F();

	float Length();
	float sqrLength();
	Vector2f Normalize();
	float Direction();

};