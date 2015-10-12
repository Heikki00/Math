#include "Vector2.h"
#include "Vector3.h"


Vector2::Vector2()
{

}


Vector2::Vector2(F32 x, F32 y)
{
	this->x = x; this->y = y;
}

Vector2::Vector2(F32 defValue)
{
	x = y = defValue;
}



Vector2::Vector2(const Vector3& v) {
	x = v.x;
	y = v.y;
}





 
Vector3 Vector2::homogeneous() const
{
	return Vector3(x, y, 1);
}
