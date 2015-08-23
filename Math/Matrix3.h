#pragma once
#include "Matrix.h"

class Vector3;

//Class that represents 3x3 matrix. All fuctions expect to be used with 3d vectors(So you wont be scaling homogeneous vector2 with scale()).
//Because deals with non-homogeneous coordinates, no translation.
//If you want to use matrixes with 2D homogeneous coordinates, look to Math::homogeneous2D namespace inside Math.h
//No own variables nor references
class Matrix3 : public Matrix < 3, 3 > {
public:

	//Constructs an identity matrix
	Matrix3(){ identity(); }

	//Constructs an matrix from 9 floats
	Matrix3(float r0c0, float r0c1, float r0c2,
		float r1c0, float r1c1, float r1c2,
		float r2c0, float r2c1, float r2c2
		){

		setElement(0, 0, r0c0); setElement(0, 1, r0c1); setElement(0, 2, r0c2);
		setElement(1, 0, r1c0); setElement(1, 1, r1c1); setElement(1, 2, r1c2);
		setElement(2, 0, r2c0); setElement(2, 1, r2c1); setElement(2, 2, r2c2);
		

	}

	//Copy constructor
	Matrix3(const Matrix3& m) : Matrix(m){}

	//Assignment operator
	inline Matrix3& operator =(const Matrix3& v){
		Matrix::operator=(v);
		return *this;
	}



	//Multiplies itself with Matrix3 of scale v(Latest will be done first!)
	void scale(const Vector3& v);

	//Multiplies itself with Matrix3 representing rotation of angle around axis
	void rotate(const Vector3& axis, float angle);

	//Optimized operator for multiplying Vector3s with Matrix3s. Also returns Vector3 in oppose to Matrix<3,1>
	Vector3 operator *(const Vector3& v) const;

	//Optimized operator for multiplying Matrix3s. Also returns Matrix4 in oppose to Matrix<3,3>
	Matrix3 operator *(const Matrix3& m) const;

	
	//Sets matrix to identity
	void identity(){ 
		memset(elements, 0, sizeof(float) * 9);
		setElement(0, 0, 1.f); setElement(1, 1, 1.f); setElement(2, 2, 1.f);
	}





};


