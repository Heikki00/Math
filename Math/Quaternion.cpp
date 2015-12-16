#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"


void Quaternion::axisAngle(const Vector3& axis, F32 angle)
{


	F32 hAng = angle / 2.f;
	x = axis.x * sinf(hAng);
	y = axis.y * sinf(hAng);
	z = axis.z * sinf(hAng);
	w = cosf(hAng);



}

Vector3 Quaternion::operator*(const Vector3& q) const
{
	Quaternion res;


	res.w = -x * q.x - y * q.y - z * q.z;
	res.x = w * q.x + y * q.z - z * q.y;
	res.y = w * q.y + z * q.x - x * q.z;
	res.z = w * q.z + x * q.y - y * q.x;

	return (res * this->conjugate()).axis();
}



Matrix4 Quaternion::toMatrix() const
{
	return Matrix4(1 - 2 * (y * y) - 2 * (z * z), 2 * x * y - 2 * z * w, 2 * x * z + 2 * y * w, 0,
		2 * x * y + 2 * z * w, 1 - 2 * (x * x) - 2 * (z * z), 2 * y * z - 2 * x * w, 0,
		2 * x * z - 2 * y * w, 2 * y * z + 2 * x * w, 1 - 2 * (x * x) - 2 * (y * y), 0,
		0, 0, 0, 1
		);


}

Vector3 Quaternion::axis() const
{
	return Vector3(x, y, z);
}

const F32* Quaternion::toArray() const
{
	return reinterpret_cast<const F32*>(this);
}

F32* Quaternion::toArray()
{
	return reinterpret_cast<F32*>(this);
}

Vector3 Quaternion::getLeft() const
{
	return this->operator*(Vector3::WORLD_LEFT);
}

Vector3 Quaternion::getRight() const
{
	return  this->operator*(Vector3::WORLD_RIGHT);
}

Vector3 Quaternion::getUp() const
{
	return  this->operator*(Vector3::WORLD_UP);
}

Vector3 Quaternion::getDown() const
{
	return  this->operator*(Vector3::WORLD_DOWN);
}

Vector3 Quaternion::getForw() const
{
	return  this->operator*(Vector3::WORLD_FORW);
}

Vector3 Quaternion::getBack() const
{
	return  this->operator*(Vector3::WORLD_BACK);
}


















