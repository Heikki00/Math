#include "Matrix2.h"
#include "Vector2.h"


const F32 Matrix2::identityMatrix[4] = { 1,0,1,0 };
const F32 Matrix2::zeroArray[4] = { 0 };


Matrix2::Matrix2()
{

	identity();


}

Matrix2::Matrix2(F32 f0, F32 f1, F32 f2, F32 f3) {

	elements[0] = f0;
	elements[1] = f1;
	elements[2] = f2;
	elements[3] = f3;
}


Matrix2::Matrix2(const Matrix2& m)
{
	memcpy(elements, m.elements, sizeof(F32) * 4);
}






#pragma region Operators


Matrix2 Matrix2::operator*(const Matrix2& m) const
{
	Matrix2 res;

	res.setElement(0, elements[0] * m.elements[0] + elements[1] * m.elements[2]);
	res.setElement(1, elements[0] * m.elements[1] + elements[1] * m.elements[3]);
	res.setElement(2, elements[2] * m.elements[0] + elements[3] * m.elements[2]);
	res.setElement(3, elements[2] * m.elements[1] + elements[3] * m.elements[3]);

	return res;
}

Matrix2 Matrix2::operator*(F32 f) const
{
	Matrix2 ret = *this;

	ret *= f;

	return ret;
}

Matrix2 Matrix2::operator+(const Matrix2& m) const
{
	Matrix2 ret = *this;

	ret += m;

	return ret;
}

Matrix2 Matrix2::operator-(const Matrix2& m) const
{
	Matrix2 ret = *this;

	ret -= m;

	return ret;

}

Matrix2 Matrix2::operator-() const
{
	Matrix2 m;
	m.elements[0] = -elements[0];
	m.elements[1] = -elements[1];
	m.elements[2] = -elements[2];
	m.elements[3] = -elements[3];
	return m;
}

void Matrix2::operator*=(const Matrix2& m)
{
	*this = *this * m;
}

void Matrix2::operator*=(F32 f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[3] *= f;
}

void Matrix2::operator+=(const Matrix2& m)
{
	elements[0] += m.elements[0];
	elements[1] += m.elements[1];
	elements[2] += m.elements[2];
	elements[3] += m.elements[3];
}

void Matrix2::operator-=(const Matrix2& m)
{

	elements[0] -= m.elements[0];
	elements[1] -= m.elements[1];
	elements[2] -= m.elements[2];
	elements[3] -= m.elements[3];

}

bool Matrix2::operator==(const Matrix2& m) const
{
	return memcmp(elements, m.elements, sizeof(F32) * 4) == 0;
}

bool Matrix2::operator!=(const Matrix2& m) const
{
	return memcmp(elements, m.elements, sizeof(F32) * 4) != 0;
}

Vector2 Matrix2::operator*(const Vector2& v) const
{
	Vector2 res;


	res.x = v.x * elements[0] + v.y * elements[1];
	res.y = v.x * elements[2] + v.y * elements[3];

	return res;
}

#pragma endregion Operators




void Matrix2::identity()
{
	memcpy(elements, identityMatrix, sizeof(F32) * 4);

}

bool Matrix2::isIdentity() const
{
	return memcmp(elements, identityMatrix, sizeof(F32) * 4) == 0;
}

bool Matrix2::isZero() const
{
	return memcmp(elements, zeroArray, sizeof(F32) * 4) == 0;
}



F32* Matrix2::toArray()
{
	return &elements[0];
}

F32 Matrix2::getElement(U32 r, U32 c) const
{
	if (r < 2 && c < 2) {
		return elements[(r * 2) + c];
	}
	else {
		Math::mathError("ERROR: Tried to access element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix2\n");
		return 0.f;
	}
}

F32 Matrix2::getElement(U32 pos) const
{
	if (pos < 4) return elements[pos];
	else {
		Math::mathError("ERROR: Tried to access element " + std::to_string(pos) + " in Matrix2\n");
		return 0.f;
	}
}


void Matrix2::setElement(U32 r, U32 c, F32 val)
{
	if (r < 2 && c < 2) {
		elements[(r * 2) + c] = val;
	}
	else {
		Math::mathError("ERROR: Tried to set element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix2\n");
	}

}

void Matrix2::setElement(U32 pos, F32 val)
{

	if (pos < 4) elements[pos] = val;
	else {
		Math::mathError("ERROR: Tried to set element " + std::to_string(pos) + " in Matrix2\n");
	}
}

void Matrix2::scale(F32 f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[3] *= f;
}

void Matrix2::rotate(F32 angle)
{
	Matrix2 m(cosf(angle), -sinf(angle),
		sinf(angle), cosf(angle));


	this->operator*=(m);

}

void Matrix2::transpose()
{
	std::swap(elements[1], elements[2]);
}

Matrix2 Matrix2::transposed() const
{
	return Matrix2(elements[0], elements[2], elements[1], elements[3]);
}

void Matrix2::invert()
{
	*this = inverse();
}

Matrix2 Matrix2::inverse() const
{
	return (1.f / (elements[0] * elements[3] - elements[1] * elements[2])) * Matrix2(elements[3], -elements[1], -elements[2], elements[0]);
}
