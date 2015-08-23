#pragma once

#include "Matrix.h"

class Vector2;

//Class that represents 2x2 matrix. All functions expect to be used with 2D vectors
class Matrix2 : public Matrix < 2, 2 > {
public:

	//Constructs an identity matrix
	Matrix2(){ identity(); }

	//Constructs an matrix from 4 floats
	Matrix2(float r0c0, float r0c1,
		float r1c0, float r1c1
	
		){

		setElement(0, 0, r0c0); setElement(0, 1, r0c1);
		setElement(1, 0, r1c0); setElement(1, 1, r1c1);
		
	}

	//Copy constructor
	Matrix2(const Matrix2& m) : Matrix(m){}

	//Assignment operator
	inline Matrix2& operator =(const Matrix2& v){
		Matrix::operator=(v);
		return *this;
	}



	//Multiplies itself with Matrix2 of scale v. (Latest will be done first!)
	void scale(const Vector2& v);

	//Multiplies itself with Matrix2 representing rotation of angle. (Latest will be done first!)
	void rotate(float angle);

	
	//Optimized operator for multiplying Vector2s with Matrix2s. Also returns Vector2 in oppose to Matrix<2,1>
	Vector2 operator *(const Vector2& v) const;

	//Optimized operator for multiplying Matrix2s.Also returns Matrix2 in oppose to Matrix<2, 2>
	Matrix2 operator *(const Matrix2& m) const;

	//Sets matrix to identity
	void identity(){
		memset(elements, 0, sizeof(float) * 4);
		setElement(0, 0, 1.f); setElement(1, 1, 1.f);
	}





};


