#include "Matrix3.h"
#include "Vector3.h"

const float Matrix3::identityMatrix[9] = { 1,0,0,0,1,0,0,0,1 };
const float Matrix3::zeroArray[9] = { 0 };


Matrix3::Matrix3()
{
	elements = new float[9];
	identity();
	

}


Matrix3::Matrix3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8)
{
	elements = new float[9];

	elements[0] = f0;
	elements[1] = f1;
	elements[2] = f2;
	elements[3] = f3;
	elements[4] = f4;
	elements[5] = f5;
	elements[6] = f6;
	elements[7] = f7;
	elements[8] = f8;
	

}

Matrix3::Matrix3(const Matrix3& m)
{
	
	elements = new float[9];
	memcpy(elements, m.elements, sizeof(float) * 9);
	
}

Matrix3::Matrix3(Matrix3&& m)
{

	elements = m.elements;
	m.elements = nullptr;
}

Matrix3& Matrix3::operator=(const Matrix3& m)
{
	
	memcpy(elements, m.elements, sizeof(float) * 9);
	return *this;
}

Matrix3& Matrix3::operator=(Matrix3&& m)
{

	elements = m.elements;
	m.elements = nullptr;
	return *this;
}

Matrix3::~Matrix3() {

	delete[] elements;
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

Matrix3 Matrix3::operator*(float f) const
{
	Matrix3 res = *this;

	res *= f;

	return res;
}

Matrix3 Matrix3::operator+(const Matrix3& m) const
{
	Matrix3 res = *this;

	res += m;

	return res;
}

Matrix3 Matrix3::operator-(const Matrix3& m) const
{
	Matrix3 res = *this;

	res -= m;

	return res;

}

Matrix3 Matrix3::operator-() const
{
	Matrix3 res;

	res.elements[0] = -elements[0];
	res.elements[1] = -elements[1];
	res.elements[2] = -elements[2];
	res.elements[3] = -elements[3];
	res.elements[4] = -elements[4];
	res.elements[5] = -elements[5];
	res.elements[6] = -elements[6];
	res.elements[7] = -elements[7];
	res.elements[8] = -elements[8];

	return res;
}

void Matrix3::operator*=(const Matrix3& m)
{
	*this = *this * m;

}

void Matrix3::operator*=(float f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[3] *= f;
	elements[4] *= f;
	elements[5] *= f;
	elements[6] *= f;
	elements[7] *= f;
	elements[8] *= f;
}

void Matrix3::operator+=(const Matrix3& m)
{
	elements[0] += m.elements[0];
	elements[1] += m.elements[1];
	elements[2] += m.elements[2];
	elements[3] += m.elements[3];
	elements[4] += m.elements[4];
	elements[5] += m.elements[5];
	elements[6] += m.elements[6];
	elements[7] += m.elements[7];
	elements[8] += m.elements[8];
}

void Matrix3::operator-=(const Matrix3& m)
{
	elements[0] -= m.elements[0];
	elements[1] -= m.elements[1];
	elements[2] -= m.elements[2];
	elements[3] -= m.elements[3];
	elements[4] -= m.elements[4];
	elements[5] -= m.elements[5];
	elements[6] -= m.elements[6];
	elements[7] -= m.elements[7];
	elements[8] -= m.elements[8];
}

bool Matrix3::operator==(const Matrix3& m) const
{
	return memcmp(elements, zeroArray, sizeof(float) * 9) == 0;
}

bool Matrix3::operator!=(const Matrix3& m) const
{
	return memcmp(elements, zeroArray, sizeof(float) * 9) != 0;
}



Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 res;

	res.x = v.x * getElement(0, 0) + v.y * getElement(0, 1) + v.z * getElement(0, 2);
	res.y = v.x * getElement(1, 0) + v.y * getElement(1, 1) + v.z * getElement(1, 2);
	res.z = v.x * getElement(2, 0) + v.y * getElement(2, 1) + v.z * getElement(2, 2);

	return res;
}





void Matrix3::identity()
{
	memcpy(elements, identityMatrix, sizeof(float) * 9);
}

bool Matrix3::isIdentity() const
{
	return memcmp(elements, identityMatrix, sizeof(float) * 9) == 0;
}

bool Matrix3::isZero() const
{
	return memcmp(elements, zeroArray, sizeof(float) * 9) == 0;
}

float* Matrix3::toArray() const
{
	return elements;
}

float Matrix3::getElement(unsigned int r, unsigned int c) const
{
	if (r < 3 && c < 3) {
		return elements[(r * 3) + c];
	}
	else {
		Math::mathError("ERROR: Tried to access element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix3\n");
		return 0.f;
	}
}

float Matrix3::getElement(unsigned int pos) const
{
	if (pos < 9) return elements[pos];
	else {
		Math::mathError("ERROR: Tried to access element " + std::to_string(pos) + " in Matrix3\n");
		return 0.f;
	}
}

void Matrix3::setElement(unsigned int r, unsigned int c, float val)
{
	if (r < 3 && c < 3) {
		elements[(r * 3) + c] = val;
	}
	else {
		Math::mathError("ERROR: Tried to set element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix3\n");
	}
}

void Matrix3::setElement(unsigned int pos, float val)
{
	if (pos < 9) elements[pos] = val;
	else {
		Math::mathError("ERROR: Tried to set element " + std::to_string(pos) + " in Matrix3\n");
	}
}

void Matrix3::scale(float f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[3] *= f;
	elements[4] *= f;
	elements[5] *= f;
	elements[6] *= f;
	elements[7] *= f;
	elements[8] *= f;
}

void Matrix3::rotate(const Vector3& axis, float angle)
{
	Matrix3 m;

	if (axis.isZero()) {
		Math::mathError("ERROR: Tried to create a rotation Matrix3 around zero vector");
		return;
	}

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

void Matrix3::rotateX(float angle)
{
	this->operator*=(Matrix3(1, 0, 0,
		0, cosf(angle), -sinf(angle),
		0, sinf(angle), cosf(angle)
		));
}

void Matrix3::rotateY(float angle)
{
	this->operator*=(Matrix3(cosf(angle), 0, sinf(angle),
		0, 1, 0,
		-sinf(angle), 0, cosf(angle)
		));
}

void Matrix3::rotateZ(float angle)
{
	this->operator*=(Matrix3(cosf(angle), -sinf(angle), 0,
		sinf(angle), cosf(angle), 0,
		0, 0, 1
		));
}

void Matrix3::invert()
{
	*this = inverse();
}

Matrix3 Matrix3::inverse() const
{

	Matrix3 m, cof;
	
	m.elements[0] = getElement(1, 1) * getElement(2, 2) - getElement(1, 2) * getElement(2, 1);

	m.elements[1] = -(getElement(1, 0) * getElement(2, 2) - getElement(1, 2) * getElement(2, 0));

	m.elements[2] = getElement(1, 0) * getElement(2, 1) - getElement(2, 0) * getElement(1, 1);

	m.elements[3] = -(getElement(0, 1) * getElement(2, 2) - getElement(2, 1) * getElement(0, 2));

	m.elements[4] = getElement(0, 0) * getElement(2, 2) - getElement(2, 0) * getElement(0, 2);

	m.elements[5] = -(getElement(0, 0) * getElement(2, 1) - getElement(2, 0) * getElement(0, 1));

	m.elements[6] = getElement(0, 1) * getElement(1, 2) - getElement(1, 1) * getElement(0, 2);

	m.elements[7] = -(getElement(0, 0) * getElement(1, 2) - getElement(1, 0) * getElement(0, 2));

	m.elements[8] = getElement(0, 0) * getElement(1, 1) - getElement(1, 0) * getElement(0, 1);
	cof = m;
	
	float det = elements[0] * m.elements[0] - elements[1] * m.elements[1] + elements[2] * m.elements[2];
	
	m.transpose();
	
	
	
	m *= 1.f / det;
	
	return m;

}

void Matrix3::transpose()
{
	
	*this = transposed();
	
}

Matrix3 Matrix3::transposed() const
{
	
	Matrix3 m = *this;

	m.setElement(0, 1, getElement(1, 0));
	m.setElement(0, 2, getElement(2, 0));

	m.setElement(1, 0, getElement(0, 1));
	m.setElement(2, 0, getElement(0, 2));

	m.setElement(1, 2, getElement(2, 1));
	
	m.setElement(2, 1, getElement(1, 2));
	
	return m;

}
