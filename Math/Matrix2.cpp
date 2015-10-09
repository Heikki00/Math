#include "Matrix2.h"
#include "Vector2.h"


const float Matrix2::identityMatrix[4] = { 1,0,1,0 };
const float Matrix2::zeroArray[4] = { 0 };


Matrix2::Matrix2()
{
	elements = new float[4];
	identity();


}

Matrix2::Matrix2(float f0, float f1, float f2, float f3) {
	elements = new float[4];
	elements[0] = f0;
	elements[1] = f1;
	elements[2] = f2;
	elements[3] = f3;
}


Matrix2::Matrix2(const Matrix2& m)
{
	elements = new float[4];
	memcpy(elements, m.elements, sizeof(float) * 4);
}

Matrix2::Matrix2(Matrix2&& m)
{
	elements = m.elements;
	m.elements = nullptr;
}

Matrix2& Matrix2::operator=(const Matrix2& m)
{
	memcpy(elements, m.elements, sizeof(float) * 4);
	return *this;
}

Matrix2& Matrix2::operator=(Matrix2&& m)
{
	elements = m.elements;
	m.elements = nullptr;
	return *this;
}

Matrix2::~Matrix2()
{
	delete[] elements;
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

Matrix2 Matrix2::operator*(float f) const
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

void Matrix2::operator*=(float f)
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
	return memcmp(elements, m.elements, sizeof(float) * 4) == 0;
}

bool Matrix2::operator!=(const Matrix2& m) const
{
	return memcmp(elements, m.elements, sizeof(float) * 4) != 0;
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
	memcpy(elements, identityMatrix, sizeof(float) * 4);

}

bool Matrix2::isIdentity() const
{
	return memcmp(elements, identityMatrix, sizeof(float) * 4) == 0;
}

bool Matrix2::isZero() const
{
	return memcmp(elements, zeroArray, sizeof(float) * 4) == 0;
}



float* Matrix2::toArray() const
{
	return elements;
}

float Matrix2::getElement(unsigned int r, unsigned int c) const
{
	if (r < 2 && c < 2) {
		return elements[(r * 2) + c];
	}
	else {
		Math::mathError("ERROR: Tried to access element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix2\n");
		return 0.f;
	}
}

float Matrix2::getElement(unsigned int pos) const
{
	if (pos < 4) return elements[pos];
	else {
		Math::mathError("ERROR: Tried to access element " + std::to_string(pos) + " in Matrix2\n");
		return 0.f;
	}
}


void Matrix2::setElement(unsigned int r, unsigned int c, float val)
{
	if (r < 2 && c < 2) {
		elements[(r * 2) + c] = val;
	}
	else {
		Math::mathError("ERROR: Tried to set element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix2\n");
	}

}

void Matrix2::setElement(unsigned int pos, float val)
{

	if (pos < 4) elements[pos] = val;
	else {
		Math::mathError("ERROR: Tried to set element " + std::to_string(pos) + " in Matrix2\n");
	}
}

void Matrix2::scale(float f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[3] *= f;
}

void Matrix2::rotate(float angle)
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
