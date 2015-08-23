#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

//Macro that initializes references in Vector4s constructors
#define INIT_REF_VEC4 x(elements[0]), y(elements[1]), z(elements[2]), w(elements[3])



Vector4::Vector4() :INIT_REF_VEC4
{

}

Vector4::Vector4(float defValue) : INIT_REF_VEC4
{
	x = y = z = w = defValue;
}

Vector4::Vector4(float x, float y, float z, float w) : INIT_REF_VEC4
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

Vector4::Vector4(const Vector4& v) : Vector(v), INIT_REF_VEC4
{
	
}

Vector4::Vector4(const Vector<4>& v) : Vector(v), INIT_REF_VEC4
{

}

#undef INIT_REF_VEC4