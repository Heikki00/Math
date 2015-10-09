#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"



Vector4::Vector4()
{

}

Vector4::Vector4(float defValue)
{
	x = y = z = w = defValue;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}


