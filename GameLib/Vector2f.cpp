#include "pch.h"

Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}

Vector2f::Vector2f(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vector2f& Vector2f::operator=(const Vector2f& v)
{    
    x = v.x;
    y = v.y;
    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& v)
{
    return {x + v.x,y + v.y};
}

Vector2f Vector2f::operator-(const Vector2f& v)
{
    return { x - v.x,y - v.y };
}

Vector2f Vector2f::operator*(float m)
{
    return { x * m,y * m };
}

Vector2f Vector2f::operator*(const Matrix& m)
{
    Matrix tmp = Matrix::Translation(x, y) * m;
    return { tmp.dx,tmp.dy };
}

Vector2f Vector2f::operator/(float d)
{
    return { x / d,y / d };
}

Vector2f Vector2f::operator-()
{
    return { -x,-y };
}

Vector2f& Vector2f::operator+=(const Vector2f& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2f::operator D2D1_VECTOR_2F()
{
    return { x,y };
}

Vector2f::operator D2D1_POINT_2F()
{
    return { x,y };
}

float Vector2f::Length()
{
    return sqrtf(x * x + y * y);
}

float Vector2f::sqrLength()
{
    return (x*x+y*y);
}

Vector2f Vector2f::Normalize()
{
    float l = Length();
    return { x / l,y / l };
}

float Vector2f::Direction()//radian
{
    return atan2f(y,x);
}

