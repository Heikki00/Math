#include "Matrix3.h"
#include "Vector3.h"



Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 res;


	res.x = v.x * getElement(0, 0) + v.y * getElement(0, 1) + v.z * getElement(0, 2);
	res.y = v.x * getElement(1, 0) + v.y * getElement(1, 1) + v.z * getElement(1, 2);
	res.z = v.x * getElement(2, 0) + v.y * getElement(2, 1) + v.z * getElement(2, 2);


	return res;

}

Matrix3 Matrix3::operator*(const Matrix3& m) const
{
	Matrix3 res;

	res.setElement(0, 0, getElement(0, 0) * m[0][0] + getElement(0, 1) * m[1][0] + getElement(0, 2) * m[2][0]);
	res.setElement(1, 0, getElement(1, 0) * m[0][0] + getElement(1, 1) * m[1][0] + getElement(1, 2) * m[2][0]);
	res.setElement(2, 0, getElement(2, 0) * m[0][0] + getElement(2, 1) * m[1][0] + getElement(2, 2) * m[2][0]);


	res.setElement(0, 1, getElement(0, 0) * m[0][1] + getElement(0, 1) * m[1][1] + getElement(0, 2) * m[2][1]);
	res.setElement(1, 1, getElement(1, 0) * m[0][1] + getElement(1, 1) * m[1][1] + getElement(1, 2) * m[2][1]);
	res.setElement(2, 1, getElement(2, 0) * m[0][1] + getElement(2, 1) * m[1][1] + getElement(2, 2) * m[2][1]);


	res.setElement(0, 2, getElement(0, 0) * m[0][2] + getElement(0, 1) * m[1][2] + getElement(0, 2) * m[2][2]);
	res.setElement(1, 2, getElement(1, 0) * m[0][2] + getElement(1, 1) * m[1][2] + getElement(1, 2) * m[2][2]);
	res.setElement(2, 2, getElement(2, 0) * m[0][2] + getElement(2, 1) * m[1][2] + getElement(2, 2) * m[2][2]);



	return res;
}

void Matrix3::scale(const Vector3& v)
{
	Matrix3 m;
	m.setElement(0, 0, v.x);
	m.setElement(1, 1, v.y);
	m.setElement(2, 2, v.z);

	this->operator*=(m);
}

void Matrix3::rotate(const Vector3& axis, float angle)
{


	Matrix3 m;

	float hAng = angle / 2.0f;

	float x = axis.x * sinf(hAng);
	float y = axis.y * sinf(hAng);
	float z = axis.z * sinf(hAng);
	float w = cosf(hAng);


	m.setElement(0, 0, 1 - 2 * (y * y) - 2 * (z * z)); m.setElement(0, 1, 2 * x * y - 2 * z * w); m.setElement(0, 2, 2 * x * z + 2 * y * w);
	m.setElement(1, 0, 2 * x * y + 2 * z * w); m.setElement(1, 1, 1 - 2 * (x * x) - 2 * (z * z)); m.setElement(1, 2, 2 * y * z - 2 * x * w);
	m.setElement(2, 0, 2 * x * z - 2 * y * w); m.setElement(2, 1, 2 * y * z + 2 * x * w); m.setElement(2, 2, 1 - 2 * (x * x) - 2 * (y * y));
	


	this->operator*=(m);




}



