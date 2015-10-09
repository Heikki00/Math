#pragma once
#include <iostream>

class Vector3;

//Class that represents 3x3 matrix. All fuctions expect to be used with 3d vectors(So you wont be scaling homogeneous vector2 with scale()).
//Because deals with non-homogeneous coordinates, no translation.
//If you want to use matrixes with 2D homogeneous coordinates, look to Math::homogeneous2D namespace inside Math.h
//No own variables nor references
class Matrix3 {
public:

	//Inits matrix to identity
	Matrix3();

	//Constructs matrix from 9 elements(row-major)
	Matrix3(float, float, float, float, float, float, float, float, float);

	//Copy constructor
	Matrix3(const Matrix3& m);
		
	//Move constructor
	Matrix3(Matrix3&& m);

	//Assignment operator
	Matrix3& operator =(const Matrix3& m);

	//Assignment operator
	Matrix3& operator =(Matrix3&& m);



	//Destructor
	~Matrix3();


	//Matrix multiplication
	Matrix3 operator *(const Matrix3& m) const;

	//Scaling operator
	Matrix3 operator *(float f) const;

	//Matrix addition
	Matrix3 operator +(const Matrix3& m) const;

	//Matrix subtraction
	Matrix3 operator -(const Matrix3& m) const;

	//Matrix inversion
	Matrix3 operator -() const;


	//Compound matrix multiplication
	void operator *=(const Matrix3& m);

	//Compound matrix scaling
	void operator *=(float f);

	//Compound matrix addition
	void operator +=(const Matrix3& m);

	//Compound matrix subtraction
	void operator -=(const Matrix3& m);


	//Equal operator
	bool operator ==(const Matrix3& m) const;

	//Non-equal operator
	bool operator !=(const Matrix3& m) const;

	//Returns a pointer to start of row i
	float* operator [](unsigned int i) const { return elements + (i * 3); }

	//Matrix-vector multiplication
	Vector3 operator *(const Vector3& v) const;

	//Sets this matrix to identity
	void identity();

	//Returns true if matrix is identity matrix
	bool isIdentity() const;

	//Returns true if all elements are zero
	bool isZero() const;


	//Returns pointer to array of elements of this matrix
	float* toArray() const;

	//Returns element at row r and column c
	float getElement(unsigned int r, unsigned int c) const;

	//Returns element at position pos(row-major order)
	float getElement(unsigned int pos) const;

	//Sets element at row r and column c to value val
	void setElement(unsigned int r, unsigned int c, float val);

	//Sets element at position pos to value val(row-major order)
	void setElement(unsigned int pos, float val);



	//Multiplies this matrix by matrix that scales by f
	void scale(float f);

	//Multiplies this matrix by matrix that rotates by angle around axis
	void rotate(const Vector3& axis, float angle);


	//Multiplies this matrix by matrix that rotates by angle around x-axis(note: x-axis != Vector3::WORLD_RIGHT)
	void rotateX(float angle);

	//Multiplies this matrix by matrix that rotates by angle around y-axis(note: y-axis != Vector3::WORLD_UP)
	void rotateY(float angle);

	//Multiplies this matrix by matrix that rotates by angle around z-axis(note: z-axis != Vector3::WORLD_FORW)
	void rotateZ(float angle);

	//Inverts the matrix
	void invert();

	//Returns an inverted version of this matrix
	Matrix3 inverse() const;

	//Transposes this matrix(Flips rows and columns)
	void transpose();

	//Returns an transposed version of this matrix
	Matrix3 transposed() const;

	friend Matrix3 operator *(float f, const Matrix3& m) { return m * f; }

	friend std::ostream& operator <<(std::ostream& os, const Matrix3& m) {
		os << std::fixed << "Matrix3: [" << m.elements[0] << ", " << m.elements[1] << ", " << m.elements[2] << "]\n";

		os << std::fixed << "         [" << m.elements[3] << ", " << m.elements[4] << ", " << m.elements[5] << "]\n";
		os << std::fixed << "         [" << m.elements[6] << ", " << m.elements[7] << ", " << m.elements[8] << "]\n";


		return os;
	}



private:
	float* elements;

	static const float zeroArray[9];

	static const float identityMatrix[9];

};


