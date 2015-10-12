#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "MathMemoryManager.h"

const F32 Matrix4::identityMatrix[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
const F32 Matrix4::zeroArray[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


Matrix4::Matrix4()
{
#ifdef MATH_CUSTOM_MEMORY
	elements = MathMemoryManager::newMat4();
#else
	elements = new F32[16];
#endif
	identity();

}

Matrix4::Matrix4(F32 f0, F32 f1, F32 f2, F32 f3, F32 f4, F32 f5, F32 f6, F32 f7, F32 f8, F32 f9, F32 f10, F32 f11, F32 f12, F32 f13, F32 f14, F32 f15)
{
#ifdef MATH_CUSTOM_MEMORY
	elements = MathMemoryManager::newMat4();
#else
	elements = new F32[16];
#endif

	elements[0] = f0;
	elements[1] = f1;
	elements[2] = f2;
	elements[3] = f3;
	elements[4] = f4;
	elements[5] = f5;
	elements[6] = f6;
	elements[7] = f7;
	elements[8] = f8;
	elements[9] = f9;
	elements[10] = f10;
	elements[11] = f11;
	elements[12] = f12;
	elements[13] = f13;
	elements[14] = f14;
	elements[15] = f15;

}

Matrix4::Matrix4(const Matrix4& m)
{

#ifdef MATH_CUSTOM_MEMORY
	elements = MathMemoryManager::newMat4();
#else
	elements = new F32[16];
#endif
	memcpy(elements, m.elements,sizeof(F32) * 16);
}

Matrix4::Matrix4(Matrix4&& m) {

	elements = m.elements;
	m.elements = nullptr;
}

Matrix4::Matrix4(F32* f)
{
#ifdef MATH_CUSTOM_MEMORY
	elements = MathMemoryManager::newMat4();
#else
	elements = new F32[16];
#endif
		memcpy(elements, f, sizeof(F32) * 16);
}

Matrix4::Matrix4(F32** f)
{
	elements = *f;
	*f = nullptr;
}

Matrix4& Matrix4::operator=(const Matrix4& m) {

	memcpy(elements, m.elements, sizeof(F32) * 16);
	return *this;
	
}

Matrix4& Matrix4::operator=(Matrix4&& m) {

	elements = m.elements;
	m.elements = nullptr;
	return *this;
}



Matrix4::~Matrix4()
{
	
#ifdef MATH_CUSTOM_MEMORY
	MathMemoryManager::deleteMat4(elements);
#else
	delete[] elements;
#endif
}

Vector4 Matrix4::operator*(const Vector4& v) const
{
	Vector4 res;

	res.x = v.x * getElement(0, 0) + v.y * getElement(0, 1) + v.z * getElement(0, 2) + v.w * getElement(0, 3);
	res.y = v.x * getElement(1, 0) + v.y * getElement(1, 1) + v.z * getElement(1, 2) + v.w * getElement(1, 3);
	res.z = v.x * getElement(2, 0) + v.y * getElement(2, 1) + v.z * getElement(2, 2) + v.w * getElement(2, 3);
	res.w = v.x * getElement(3, 0) + v.y * getElement(3, 1) + v.z * getElement(3, 2) + v.w * getElement(3, 3);

	return res;
}

void Matrix4::identity()
{
	
	memcpy(elements, identityMatrix, sizeof(F32) * 16);
}

bool Matrix4::isIdentity() const
{
	return memcmp(elements, identityMatrix, sizeof(F32) * 16) == 0;
}

bool Matrix4::isZero() const
{
	return memcmp(elements, zeroArray, sizeof(F32) * 16) == 0;
}

F32* Matrix4::toArray() const
{
	return elements;
}

F32 Matrix4::getElement(U32 r, U32 c) const
{

	if (r < 4 && c < 4) {
		return elements[(r * 4) + c];
	}
	else {
		Math::mathError("ERROR: Tried to access element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix4\n");
		return 0.f;
	}
}

F32 Matrix4::getElement(U32 pos) const
{
	if (pos < 16) return elements[pos];
	else {
		Math::mathError("ERROR: Tried to access element " + std::to_string(pos) + " in Matrix4\n");
		return 0.f;
	}
}

void Matrix4::setElement(U32 r, U32 c, F32 val)
{
	if (r < 4 && c < 4) {
		elements[(r * 4) + c] = val;
	}
	else {
		Math::mathError("ERROR: Tried to set element (" + std::to_string(r) + ", " + std::to_string(c) + ") in Matrix4\n");
	}
}

void Matrix4::setElement(U32 pos, F32 val)
{
	if (pos < 16) elements[pos] = val;
	else {
		Math::mathError("ERROR: Tried to set element " + std::to_string(pos) + " in Matrix4\n");
	}
}



void Matrix4::scale(F32 f)
{
	elements[0] *= f;
	elements[1] *= f;
	elements[2] *= f;
	elements[4] *= f;
	elements[5] *= f;
	elements[6] *= f;
	elements[8] *= f;
	elements[9] *= f;
	elements[10] *= f;
	elements[12] *= f;
	elements[13] *= f;
	elements[14] *= f;
}

void Matrix4::translate(const Vector3& t)
{
	elements[3] = t.x * elements[0] + t.y * elements[1] + t.z * elements[2] + elements[3];
	elements[7] = t.x * elements[4] + t.y * elements[5] + t.z * elements[6] + elements[7];
	elements[11] = t.x * elements[8] + t.y * elements[9] + t.z * elements[10] + elements[11];
	elements[15] = t.x * elements[12] + t.y * elements[13] + t.z * elements[14] + elements[15];
}

void Matrix4::rotate(const Vector3& axis, F32 angle)
{

	Matrix4 m;

	if (axis.isZero()) {
		Math::mathError("ERROR: Tried to create a rotation Matrix4 around zero vector");
		return;
	}

	F32 hAng = angle / 2.0f;

	F32 x = axis.x * sinf(hAng);
	F32 y = axis.y * sinf(hAng);
	F32 z = axis.z * sinf(hAng);
	F32 w = cosf(hAng);


	m.setElement(0, 0, 1 - 2 * (y * y) - 2 * (z * z)); m.setElement(0, 1, 2 * x * y - 2 * z * w); m.setElement(0, 2, 2 * x * z + 2 * y * w); m.setElement(0, 3, 0);
	m.setElement(1, 0, 2 * x * y + 2 * z * w); m.setElement(1, 1, 1 - 2 * (x * x) - 2 * (z * z)); m.setElement(1, 2, 2 * y * z - 2 * x * w); m.setElement(1, 3, 0);
	m.setElement(2, 0, 2 * x * z - 2 * y * w); m.setElement(2, 1, 2 * y * z + 2 * x * w); m.setElement(2, 2, 1 - 2 * (x * x) - 2 * (y * y)); m.setElement(2, 3, 0);
	m.setElement(3, 0, 0); m.setElement(3, 1, 0); m.setElement(3, 2, 0); m.setElement(3, 3, 1);

	
	this->operator*=(m);

}

void Matrix4::rotateX(F32 angle)
{
	this->operator*=(Matrix4(1, 0, 0, 0,
		0, cosf(angle), -sinf(angle), 0,
		0, sinf(angle), cosf(angle), 0,
		0, 0, 0, 1
		));
}

void Matrix4::rotateY(F32 angle)
{
	this->operator*=(Matrix4(cosf(angle), 0, sinf(angle), 0,
		0, 1, 0, 0,
		-sinf(angle), 0, cosf(angle), 0,
		0, 0, 0, 1
		));
}

void Matrix4::rotateZ(F32 angle)
{
	this->operator*=(Matrix4(cosf(angle), -sinf(angle), 0, 0,
		sinf(angle), cosf(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		));
}



bool Matrix4::operator!=(const Matrix4& m) const
{
	return memcmp(elements, m.elements, sizeof(F32) * 16) != 0;
}

bool Matrix4::operator==(const Matrix4& m) const
{
	return memcmp(elements, m.elements, sizeof(F32) * 16) == 0;
}

void Matrix4::operator-=(const Matrix4& m)
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
	elements[9] -= m.elements[9];
	elements[10] -= m.elements[10];
	elements[11] -= m.elements[11];
	elements[12] -= m.elements[12];
	elements[13] -= m.elements[13];
	elements[14] -= m.elements[14];
	elements[15] -= m.elements[15];
}

void Matrix4::operator+=(const Matrix4& m)
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
	elements[9] += m.elements[9];
	elements[10] += m.elements[10];
	elements[11] += m.elements[11];
	elements[12] += m.elements[12];
	elements[13] += m.elements[13];
	elements[14] += m.elements[14];
	elements[15] += m.elements[15];
}

void Matrix4::operator*=(F32 f)
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
	elements[9] *= f;
	elements[10] *= f;
	elements[11] *= f;
	elements[12] *= f;
	elements[13] *= f;
	elements[14] *= f;
	elements[15] *= f;

}

void Matrix4::operator*=(const Matrix4& m)
{
	*this = *this * m;
}

Matrix4 Matrix4::operator-() const
{
	Matrix4 res = *this;
	res *= -1.f;
	return res;
}

Matrix4 Matrix4::operator-(const Matrix4& m) const
{
	Matrix4 res = *this;
	res -= m;
	return res;
}

Matrix4 Matrix4::operator+(const Matrix4& m) const
{
	Matrix4 res = *this;
	res += m;
	return res;
}

Matrix4 Matrix4::operator*(F32 f) const
{
	Matrix4 res = *this;
	res *= f;
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




void Matrix4::invert()
{
	*this = inverse();
}

Matrix4 Matrix4::inverse() const
{
	F32* inv = new F32[16];
	F32 det;


	inv[0] = elements[5] * elements[10] * elements[15] -
		elements[5] * elements[11] * elements[14] -
		elements[9] * elements[6] * elements[15] +
		elements[9] * elements[7] * elements[14] +
		elements[13] * elements[6] * elements[11] -
		elements[13] * elements[7] * elements[10];

	inv[4] = -elements[4] * elements[10] * elements[15] +
		elements[4] * elements[11] * elements[14] +
		elements[8] * elements[6] * elements[15] -
		elements[8] * elements[7] * elements[14] -
		elements[12] * elements[6] * elements[11] +
		elements[12] * elements[7] * elements[10];

	inv[8] = elements[4] * elements[9] * elements[15] -
		elements[4] * elements[11] * elements[13] -
		elements[8] * elements[5] * elements[15] +
		elements[8] * elements[7] * elements[13] +
		elements[12] * elements[5] * elements[11] -
		elements[12] * elements[7] * elements[9];

	inv[12] = -elements[4] * elements[9] * elements[14] +
		elements[4] * elements[10] * elements[13] +
		elements[8] * elements[5] * elements[14] -
		elements[8] * elements[6] * elements[13] -
		elements[12] * elements[5] * elements[10] +
		elements[12] * elements[6] * elements[9];

	inv[1] = -elements[1] * elements[10] * elements[15] +
		elements[1] * elements[11] * elements[14] +
		elements[9] * elements[2] * elements[15] -
		elements[9] * elements[3] * elements[14] -
		elements[13] * elements[2] * elements[11] +
		elements[13] * elements[3] * elements[10];

	inv[5] = elements[0] * elements[10] * elements[15] -
		elements[0] * elements[11] * elements[14] -
		elements[8] * elements[2] * elements[15] +
		elements[8] * elements[3] * elements[14] +
		elements[12] * elements[2] * elements[11] -
		elements[12] * elements[3] * elements[10];

	inv[9] = -elements[0] * elements[9] * elements[15] +
		elements[0] * elements[11] * elements[13] +
		elements[8] * elements[1] * elements[15] -
		elements[8] * elements[3] * elements[13] -
		elements[12] * elements[1] * elements[11] +
		elements[12] * elements[3] * elements[9];

	inv[13] = elements[0] * elements[9] * elements[14] -
		elements[0] * elements[10] * elements[13] -
		elements[8] * elements[1] * elements[14] +
		elements[8] * elements[2] * elements[13] +
		elements[12] * elements[1] * elements[10] -
		elements[12] * elements[2] * elements[9];

	inv[2] = elements[1] * elements[6] * elements[15] -
		elements[1] * elements[7] * elements[14] -
		elements[5] * elements[2] * elements[15] +
		elements[5] * elements[3] * elements[14] +
		elements[13] * elements[2] * elements[7] -
		elements[13] * elements[3] * elements[6];

	inv[6] = -elements[0] * elements[6] * elements[15] +
		elements[0] * elements[7] * elements[14] +
		elements[4] * elements[2] * elements[15] -
		elements[4] * elements[3] * elements[14] -
		elements[12] * elements[2] * elements[7] +
		elements[12] * elements[3] * elements[6];

	inv[10] = elements[0] * elements[5] * elements[15] -
		elements[0] * elements[7] * elements[13] -
		elements[4] * elements[1] * elements[15] +
		elements[4] * elements[3] * elements[13] +
		elements[12] * elements[1] * elements[7] -
		elements[12] * elements[3] * elements[5];

	inv[14] = -elements[0] * elements[5] * elements[14] +
		elements[0] * elements[6] * elements[13] +
		elements[4] * elements[1] * elements[14] -
		elements[4] * elements[2] * elements[13] -
		elements[12] * elements[1] * elements[6] +
		elements[12] * elements[2] * elements[5];

	inv[3] = -elements[1] * elements[6] * elements[11] +
		elements[1] * elements[7] * elements[10] +
		elements[5] * elements[2] * elements[11] -
		elements[5] * elements[3] * elements[10] -
		elements[9] * elements[2] * elements[7] +
		elements[9] * elements[3] * elements[6];

	inv[7] = elements[0] * elements[6] * elements[11] -
		elements[0] * elements[7] * elements[10] -
		elements[4] * elements[2] * elements[11] +
		elements[4] * elements[3] * elements[10] +
		elements[8] * elements[2] * elements[7] -
		elements[8] * elements[3] * elements[6];

	inv[11] = -elements[0] * elements[5] * elements[11] +
		elements[0] * elements[7] * elements[9] +
		elements[4] * elements[1] * elements[11] -
		elements[4] * elements[3] * elements[9] -
		elements[8] * elements[1] * elements[7] +
		elements[8] * elements[3] * elements[5];

	inv[15] = elements[0] * elements[5] * elements[10] -
		elements[0] * elements[6] * elements[9] -
		elements[4] * elements[1] * elements[10] +
		elements[4] * elements[2] * elements[9] +
		elements[8] * elements[1] * elements[6] -
		elements[8] * elements[2] * elements[5];

	det = elements[0] * inv[0] + elements[1] * inv[4] + elements[2] * inv[8] + elements[3] * inv[12];


	det = 1.0 / det;

	int i;
	for (i = 0; i < 16; i++)
		inv[i] *= det;

	return Matrix4(&inv);


	
}

void Matrix4::transpose()
{
	*this = transposed();
}

Matrix4 Matrix4::transposed() const
{
	Matrix4 m = *this;

	m.setElement(1, 0, getElement(0, 1));
	m.setElement(2, 0, getElement(0, 2));
	m.setElement(3, 0, getElement(0, 3));
	
	m.setElement(0, 1, getElement(1, 0));
	m.setElement(0, 2, getElement(2, 0));
	m.setElement(0, 3, getElement(3, 0));

	m.setElement(2, 1, getElement(1, 2));
	m.setElement(3, 1, getElement(1, 3));

	m.setElement(1, 2, getElement(2, 1));
	m.setElement(1, 3, getElement(3, 1));

	m.setElement(2, 3, getElement(3, 2));

	m.setElement(3, 2, getElement(2, 3));
	
	return m;
}

