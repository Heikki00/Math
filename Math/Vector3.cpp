#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "MathUtility.h"

//Static const initialization:

const Vector3 Vector3::WORLD_UP = Vector3(0, 1, 0);
const Vector3 Vector3::WORLD_DOWN = Vector3(0, -1, 0);
const Vector3 Vector3::WORLD_LEFT = Vector3(-1, 0, 0);
const Vector3 Vector3::WORLD_RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::WORLD_FORW = Vector3(0, 0, 1);
const Vector3 Vector3::WORLD_BACK = Vector3(0, 0, -1);

Vector3::Vector3()
{
	x = y = z = 0;
}

Vector3::Vector3(F32 defValue)
{
	x = y = z = defValue;
}

Vector3::Vector3(F32 x, F32 y, F32 z)
{
	this->x = x; this->y = y; this->z = z;
}


Vector3::Vector3(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}


 
 
 
Vector4 Vector3::homogeneous() const
{
	return Vector4(x, y, z, 1);
}














