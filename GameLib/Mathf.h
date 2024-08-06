#pragma once
#include "Vector2f.h"
#include <math.h>

using namespace D2D1;

namespace Mathf 
{
	const float PI = 3.141592;

	Vector2f PosFromMatrix(const Matrix3x2F& matrix);
	float RotFromMatrix(const Matrix3x2F& matrix);
	Vector2f ScaleFromMatrix(const Matrix3x2F& matrix);

	Vector2f DirToVec(float R);

	float RadToDeg(float R);
	float DegToRad(float D);
}

