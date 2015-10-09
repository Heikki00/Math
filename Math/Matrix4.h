#pragma once
#include "MathError.h"

//Forward-declarations

class Vector4;
class Vector3;

//Class that represents 4x4 matrix. All fuctions expect to be used with homogeneous 3d vectors(So you wont be scaling Vector4 with scale()).
//No own variables nor references
//TODO: Optimized(private?) constructor that doesn't init to identity. Use for operators where all values will be set
class Matrix4 {
public:
	//Inits matrix to identity
	Matrix4();

	//Constructs matrix from 16 elements(row-major)
	Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

	//Constructs matrix from float array. Copies the array
	Matrix4(float* f);

	//Constructs matrix from float array. Takes ownership of the pointer, assings it to null
	Matrix4(float** f);

	//Copy constructor
	Matrix4(const Matrix4& m);

	//Move constructor
	Matrix4(Matrix4&& m);

	//Assignment operator
	Matrix4& operator =(const Matrix4& m);

	//Assignment operator
	Matrix4& operator =(Matrix4&& m);

	//Destructor
	~Matrix4();


	//Matrix multiplication
	Matrix4 operator *(const Matrix4& m) const;

	//Scaling operator
	Matrix4 operator *(float f) const;

	//Matrix addition
	Matrix4 operator +(const Matrix4& m) const;

	//Matrix subtraction
	Matrix4 operator -(const Matrix4& m) const;

	//Matrix inversion
	Matrix4 operator -() const;


	//Compound matrix multiplication
	void operator *=(const Matrix4& m);

	//Compound matrix scaling
	void operator *=(float f);

	//Compound matrix addition
	void operator +=(const Matrix4& m);

	//Compound matrix subtraction
	void operator -=(const Matrix4& m);


	//Equal operator
	bool operator ==(const Matrix4& m) const;

	//Non-equal operator
	bool operator !=(const Matrix4& m) const;

	//Returns a pointer to start of row i
	float* operator [](unsigned int i) const { return elements + (i * 4); }

	//Matrix-vector multiplication
	Vector4 operator *(const Vector4& v) const;


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
	//EXPERIMENTAL OPTIMIZATION, TESTING NEEDED
	void scale(float f);

	//Multiplies this matrix by matrix that translates by t
	//EXPERIMENTAL OPTIMIZATION, TESTING NEEDED
	void translate(const Vector3& t);

	//Multiplies this matrix by matrix that rotates by angle around axis
	void rotate(const Vector3& axis, float angle);

	//Multiplies this matrix by matrix that rotates by angle around x-axis(note: x-axis != Vector3::WORLD_RIGHT)
	void rotateX(float angle);

	//Multiplies this matrix by matrix that rotates by angle around y-axis(note: y-axis != Vector3::WORLD_UP)
	void rotateY(float angle);

	//Multiplies this matrix by matrix that rotates by angle around z-axis(note: z-axis != Vector3::WORLD_FORW)
	void rotateZ(float angle);

	//Inverts this matrix
	void invert();

	//Returns an inverse of this matrix
	Matrix4 inverse() const;

	//Transposes this matrix(Flips rows and columns)
	void transpose();

	//Returns an transposed version of this matrix
	Matrix4 transposed() const;




	friend Matrix4 operator *(float f, const Matrix4& m) { return m * f; }

	friend std::ostream& operator <<(std::ostream& os, const Matrix4& m) {
		os << std::fixed << "Matrix4: [" << m.elements[0] << ", " << m.elements[1] << ", " << m.elements[2] << ", " << m.elements[3] << "]\n";

		os << std::fixed << "         [" << m.elements[4] << ", " << m.elements[5] << ", " << m.elements[6] << ", " << m.elements[7] << "]\n";
		os << std::fixed << "         [" << m.elements[8] << ", " << m.elements[9] << ", " << m.elements[10] << ", " << m.elements[11] << "]\n";
		os << std::fixed << "         [" << m.elements[12] << ", " << m.elements[13] << ", " << m.elements[14] << ", " << m.elements[15] << "]\n";

		return os;
	}




private:
	float* elements;

	static const float zeroArray[16];

	static const float identityMatrix[16];









};


