#include "Matrix2.h"
#include "Vector2.h"



Vector2 Matrix2::operator*(const Vector2& v) const
{
	Vector2 res;


	res.x = v.x * getElement(0, 0) + v.y * getElement(0, 1);
	res.y = v.x * getElement(1, 0) + v.y * getElement(1, 1);


	return res;
}

Matrix2 Matrix2::operator*(const Matrix2& m) const
{
	Matrix2 res;

	res.setElement(0, 0, getElement(0, 0) * m[0][0] + getElement(0, 1) * m[1][0]);
	res.setElement(1, 0, getElement(1, 0) * m[0][0] + getElement(1, 1) * m[1][0]);


	res.setElement(0, 1, getElement(0, 0) * m[0][1] + getElement(0, 1) * m[1][1]);
	res.setElement(1, 1, getElement(1, 0) * m[0][1] + getElement(1, 1) * m[1][1]);

	return res;
}

void Matrix2::scale(const Vector2& v)
{
	Matrix2 m;
	m.setElement(0, 0, v.x);
	m.setElement(1, 1, v.y);


	this->operator*=(m);
}

void Matrix2::rotate(float angle)
{
	Matrix2 res;

	res.setElement(0, 0, cosf(angle));
	res.setElement(0, 1, -sinf(angle));
	res.setElement(1, 0, sinf(angle));
	res.setElement(1, 1, cosf(angle));

	this->operator*=(res);
}

