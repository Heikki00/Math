#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"



Vector4::Vector4()
{

}

Vector4::Vector4(F32 defValue)
{
	x = y = z = w = defValue;
}

Vector4::Vector4(F32 x, F32 y, F32 z, F32 w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}


