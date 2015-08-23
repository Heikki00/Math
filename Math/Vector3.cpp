#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

//Macro that initializes references in Vector3s constructors
#define INIT_REF_VEC3 x(elements[0]), y(elements[1]), z(elements[2])

//Static const initialization:

 const Vector3 Vector3::WORLD_UP = Vector3(0,1,0);
 const Vector3 Vector3::WORLD_DOWN = Vector3(0, -1, 0);
 const Vector3 Vector3::WORLD_LEFT = Vector3(-1, 0, 0);
 const Vector3 Vector3::WORLD_RIGHT = Vector3(1, 0, 0);
 const Vector3 Vector3::WORLD_FORW = Vector3(0, 0, -1);
 const Vector3 Vector3::WORLD_BACK = Vector3(0, 0, 1);

Vector3::Vector3() : INIT_REF_VEC3
{

}

Vector3::Vector3(float defValue) : INIT_REF_VEC3
{
	x = y = z = defValue;
}

Vector3::Vector3(float x, float y, float z) : INIT_REF_VEC3
{
	this->x = x; this->y = y; this->z = z;
}



Vector3::Vector3(const Vector<3>& v) : Vector(v), INIT_REF_VEC3
{

}

Vector3::Vector3(const Vector4& v) : INIT_REF_VEC3
{ 
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3(const Vector3& v) : Vector(v), INIT_REF_VEC3
{

}

#undef INIT_REF_VEC3

Vector3 Vector3::cross(const Vector3& other) const
{
	float xx = (y * other.z) - (z * other.y);
	float yy = (z * other.x) - (x * other.z);
	float zz = (x * other.y) - (y * other.x);

	return Vector3(xx, yy, zz);
}

Vector4 Vector3::homogeneous() const
{
	return Vector4(x, y, z, 1);
}

