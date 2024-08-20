#include "pch.h"
#include "Mathf.h"

Vector2f Mathf::PosFromMatrix(const Matrix3x2F& matrix)
{
    return { matrix.dx,matrix.dy };
}

float Mathf::RotFromMatrix(const Matrix3x2F& matrix)
{
    return Vector2f(matrix.m11,matrix.m21).Direction();
}

Vector2f Mathf::ScaleFromMatrix(const Matrix3x2F& matrix)
{
    return Vector2f(
        Vector2f(matrix.m11, matrix.m21).Length(),
        Vector2f(matrix.m12, matrix.m22).Length()
    );
}

Vector2f Mathf::DirToVec(float R)
{
    return { cosf(R),sinf(R) };
}