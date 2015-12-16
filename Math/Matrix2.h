#pragma once
#include <iostream>
#include "DataTypedefs.h"

class Vector2;

//Class that represents 2x2 matrix. All functions expect to be used with 2D vectors
class Matrix2 {
public:

	//Inits matrix to identity
	Matrix2();

	//Constructs matrix from 4 elements(row-major)
	Matrix2(F32, F32, F32, F32);

	//Copy constructor
	Matrix2(const Matrix2& m);

	//Matrix multiplication
	Matrix2 operator *(const Matrix2& m) const;

	//Scaling operator
	Matrix2 operator *(F32 f) const;

	//Matrix addition
	Matrix2 operator +(const Matrix2& m) const;

	//Matrix subtraction
	Matrix2 operator -(const Matrix2& m) const;

	//Matrix inversion
	Matrix2 operator -() const;


	//Compound matrix multiplication
	void operator *=(const Matrix2& m);

	//Compound matrix scaling
	void operator *=(F32 f);

	//Compound matrix addition
	void operator +=(const Matrix2& m);

	//Compound matrix subtraction
	void operator -=(const Matrix2& m);


	//Equal operator
	bool operator ==(const Matrix2& m) const;

	//Non-equal operator
	bool operator !=(const Matrix2& m) const;

	//Returns a pointer to start of row i
	F32* operator [](U32 i) { return &elements[i * 2]; }


	//Matrix-vector multiplication
	Vector2 operator *(const Vector2& v) const;


	//Sets this matrix to identity
	void identity();

	//Returns true if matrix is identity matrix
	bool isIdentity() const;

	//Returns true if all elements are zero
	bool isZero() const;


	//Returns pointer to array of elements of this matrix
	const F32* toArray() const;

	//Returns pointer to array of elements of this matrix
	F32* toArray();

	//Returns element at row r and column c
	F32 getElement(U32 r, U32 c) const;

	//Returns element at position pos(row-major order)
	F32 getElement(U32 pos) const;

	//Sets element at row r and column c to value val
	void setElement(U32 r, U32 c, F32 val);

	//Sets element at position pos to value val(row-major order)
	void setElement(U32 pos, F32 val);


	//Multiplies this matrix by matrix that scales by f
	void scale(F32 f);

	//Multiplies this matrix by matrix that rotates by angle
	void rotate(F32 angle);


	//Transposes this matrix
	void transpose();

	//Returns transposed version of this matrix
	Matrix2 transposed() const;

	//Inverts this matrix
	void invert();

	//Returns inverted version of this matrix
	Matrix2 inverse() const;



	friend Matrix2 operator *(F32 f, const Matrix2& m) { return m * f; }

	friend std::ostream& operator <<(std::ostream& os, const Matrix2& m) {
		os << std::fixed << "Matrix2: [" << m.elements[0] << ", " << m.elements[1] << "]\n";
		os << std::fixed << "         [" << m.elements[2] << ", " << m.elements[3] << "]\n";



		return os;
	}


private:


	F32 elements[4];

	static const F32 zeroArray[4];

	static const F32 identityMatrix[4];
};

