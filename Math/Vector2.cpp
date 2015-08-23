#include "Vector2.h"
#include "Vector3.h"

//Macro to initialize references in Vector2s constructors
#define INIT_REF_VEC2 x(elements[0]), y(elements[1])

Vector2::Vector2() :INIT_REF_VEC2
{

}

Vector2::Vector2(const Vector<2>& v) : Vector(v), INIT_REF_VEC2
{

}

Vector2::Vector2(float x, float y) : INIT_REF_VEC2
{
	this->x = x; this->y = y;
}

Vector2::Vector2(float defValue) : INIT_REF_VEC2
{
	x = y = defValue;
}

Vector2::Vector2(const Vector2& v) : Vector(v), INIT_REF_VEC2
{

}

Vector2::Vector2(const Vector3& v) : INIT_REF_VEC2{
	x = v.x;
	y = v.y;
}

#undef INIT_REF_VEC2

Vector3 Vector2::homogeneous() const
{
	return Vector3(x, y, 1);
}



