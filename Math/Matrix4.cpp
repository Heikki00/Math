#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"


Vector4 Matrix4::operator*(const Vector4& v) const
{
	Vector4 res;


	res.x = v.x * getElement(0, 0) + v.y * getElement(0, 1) + v.z * getElement(0, 2) + v.w * getElement(0, 3);
	res.y = v.x * getElement(1, 0) + v.y * getElement(1, 1) + v.z * getElement(1, 2) + v.w * getElement(1, 3);
	res.z = v.x * getElement(2, 0) + v.y * getElement(2, 1) + v.z * getElement(2, 2) + v.w * getElement(2, 3);
	res.w = v.x * getElement(3, 0) + v.y * getElement(3, 1) + v.z * getElement(3, 2) + v.w * getElement(3, 3);

	

	return res;
}

Matrix4 Matrix4::operator*(const Matrix4& m) const
{
	Matrix4 res;

	res.setElement(0, 0, getElement(0, 0) * m[0][0] + getElement(0, 1) * m[1][0] + getElement(0, 2) * m[2][0] + getElement(0, 3) * m[3][0]);
	res.setElement(1, 0, getElement(1, 0) * m[0][0] + getElement(1, 1) * m[1][0] + getElement(1, 2) * m[2][0] + getElement(1, 3) * m[3][0]);
	res.setElement(2, 0, getElement(2, 0) * m[0][0] + getElement(2, 1) * m[1][0] + getElement(2, 2) * m[2][0] + getElement(2, 3) * m[3][0]);
	res.setElement(3, 0, getElement(3, 0) * m[0][0] + getElement(3, 1) * m[1][0] + getElement(3, 2) * m[2][0] + getElement(3, 3) * m[3][0]);

	res.setElement(0, 1, getElement(0, 0) * m[0][1] + getElement(0, 1) * m[1][1] + getElement(0, 2) * m[2][1] + getElement(0, 3) * m[3][1]);
	res.setElement(1, 1, getElement(1, 0) * m[0][1] + getElement(1, 1) * m[1][1] + getElement(1, 2) * m[2][1] + getElement(1, 3) * m[3][1]);
	res.setElement(2, 1, getElement(2, 0) * m[0][1] + getElement(2, 1) * m[1][1] + getElement(2, 2) * m[2][1] + getElement(2, 3) * m[3][1]);
	res.setElement(3, 1, getElement(3, 0) * m[0][1] + getElement(3, 1) * m[1][1] + getElement(3, 2) * m[2][1] + getElement(3, 3) * m[3][1]);

	res.setElement(0, 2, getElement(0, 0) * m[0][2] + getElement(0, 1) * m[1][2] + getElement(0, 2) * m[2][2] + getElement(0, 3) * m[3][2]);
	res.setElement(1, 2, getElement(1, 0) * m[0][2] + getElement(1, 1) * m[1][2] + getElement(1, 2) * m[2][2] + getElement(1, 3) * m[3][2]);
	res.setElement(2, 2, getElement(2, 0) * m[0][2] + getElement(2, 1) * m[1][2] + getElement(2, 2) * m[2][2] + getElement(2, 3) * m[3][2]);
	res.setElement(3, 2, getElement(3, 0) * m[0][2] + getElement(3, 1) * m[1][2] + getElement(3, 2) * m[2][2] + getElement(3, 3) * m[3][2]);

	res.setElement(0, 3, getElement(0, 0) * m[0][3] + getElement(0, 1) * m[1][3] + getElement(0, 2) * m[2][3] + getElement(0, 3) * m[3][3]);
	res.setElement(1, 3, getElement(1, 0) * m[0][3] + getElement(1, 1) * m[1][3] + getElement(1, 2) * m[2][3] + getElement(1, 3) * m[3][3]);
	res.setElement(2, 3, getElement(2, 0) * m[0][3] + getElement(2, 1) * m[1][3] + getElement(2, 2) * m[2][3] + getElement(2, 3) * m[3][3]);
	res.setElement(3, 3, getElement(3, 0) * m[0][3] + getElement(3, 1) * m[1][3] + getElement(3, 2) * m[2][3] + getElement(3, 3) * m[3][3]);


	return res;
}

void Matrix4::translate(const Vector3& v)
{
	Matrix4 m;
	m.setElement(0, 3, v.x);
	m.setElement(1, 3, v.y);
	m.setElement(2, 3, v.z);

	this->operator*=(m);
}

void Matrix4::scale(const Vector3& v)
{
	Matrix4 m;
	m.setElement(0, 0, v.x);
	m.setElement(1, 1, v.y);
	m.setElement(2, 2, v.z);

	this->operator*=(m);
}

void Matrix4::rotate(const Vector3& axis, float angle)
{
	Matrix4 m;
	
	if (axis.isZero()){
		Math::mathError("ERROR: Tried to create a rotation Matrix4 around zero vector");
		return;
	}

	float hAng = angle / 2.0f;

	float x = axis.x * sinf(hAng);
	float y = axis.y * sinf(hAng);
	float z = axis.z * sinf(hAng);
	float w = cosf(hAng);
	

	m.setElement(0, 0, 1 - 2 * (y * y) - 2 * (z * z)); m.setElement(0, 1, 2 * x * y - 2 * z * w); m.setElement(0, 2, 2 * x * z + 2 * y * w); m.setElement(0, 3, 0);
	m.setElement(1, 0, 2 * x * y + 2 * z * w); m.setElement(1, 1, 1 - 2 * (x * x) - 2 * (z * z)); m.setElement(1, 2, 2 * y * z - 2 * x * w); m.setElement(1, 3, 0);
	m.setElement(2, 0, 2 * x * z - 2 * y * w); m.setElement(2, 1, 2 * y * z + 2 * x * w); m.setElement(2, 2, 1 - 2 * (x * x) - 2 * (y * y)); m.setElement(2, 3, 0);
	m.setElement(3, 0, 0); m.setElement(3, 1, 0); m.setElement(3, 2, 0); m.setElement(3, 3, 1);


	this->operator*=(m);
	
}

void Matrix4::rotateX(float angle)
{
	this->operator*=(Matrix4(1, 0, 0, 0,
		0, cosf(angle), -sinf(angle), 0,
		0, sinf(angle), cosf(angle), 0,
		0, 0, 0, 1
		));
}

void Matrix4::rotateY(float angle)
{
	this->operator*=(Matrix4(cosf(angle), 0, sinf(angle), 0,
		0, 1, 0, 0,
		-sinf(angle), 0, cosf(angle), 0,
		0, 0, 0, 1
		));
}

void Matrix4::rotateZ(float angle)
{
	this->operator*=(Matrix4(cosf(angle), -sinf(angle), 0, 0,
		sinf(angle), cosf(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		));
}

