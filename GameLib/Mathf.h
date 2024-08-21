#pragma once
#include <math.h>

using namespace D2D1;

namespace Mathf 
{
	const float PI = 3.141592;

	Vector2f PosFromMatrix(const Matrix3x2F& matrix);
	float RotFromMatrix(const Matrix3x2F& matrix);
	Vector2f ScaleFromMatrix(const Matrix3x2F& matrix);

	Vector2f DirToVec(float R);


	inline float RadToDeg(float R) {
		return R * 180 / PI;
	}
	inline float DegToRad(float D) {
		return D / 180 * PI;
	}
	inline float Dot(const Vector2f& v1, const Vector2f& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	inline float Cross(const Vector2f& v1, const Vector2f& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	inline float Square(float a) {
		return a * a;
	}
}

