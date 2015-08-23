#pragma once
#include "Matrix.h"
#include "MathError.h"

//Forward-declarations

class Vector4;
class Vector3;

//Class that represents 4x4 matrix. All fuctions expect to be used with homogeneous 3d vectors(So you wont be scaling Vector4 with scale()).
//No own variables nor references
class Matrix4 : public Matrix < 4, 4 > {
public:

	//Constructs an identity matrix
	Matrix4(){ identity(); }

	//Constructs an matrix from 16 floats
	Matrix4(float r0c0, float r0c1, float r0c2, float r0c3,
		float r1c0, float r1c1, float r1c2, float r1c3,
		float r2c0, float r2c1, float r2c2, float r2c3,
		float r3c0, float r3c1, float r3c2, float r3c3
		){

		setElement(0, 0, r0c0); setElement(0, 1, r0c1); setElement(0, 2, r0c2); setElement(0, 3, r0c3);
		setElement(1, 0, r1c0); setElement(1, 1, r1c1); setElement(1, 2, r1c2); setElement(1, 3, r1c3);
		setElement(2, 0, r2c0); setElement(2, 1, r2c1); setElement(2, 2, r2c2); setElement(2, 3, r2c3);
		setElement(3, 0, r3c0); setElement(3, 1, r3c1); setElement(3, 2, r3c2); setElement(3, 3, r3c3);

	}

	//Copy constructor
	Matrix4(const Matrix4& m): Matrix(m){}
	
	//Assignment operator
	inline Matrix4& operator =(const Matrix4& v){
		Matrix::operator=(v);
		return *this;
	}
	
	//Multiplies itself with Matrix4 of translation v. (Latest will be done first!)
	void translate(const Vector3& v);

	//Multiplies itself with Matrix4 of scale v. (Latest will be done first!)
	void scale(const Vector3& v);

	//Multiplies itself with Matrix4 representing rotation of angle around nonzero normalized axis. (Latest will be done first!)
	void rotate(const Vector3& axis, float angle);


	//Multiplies itself with Matrix4 representing rotation of angle around X-axis in right-handed coordinate system
	void rotateX(float angle);

	//Multiplies itself with Matrix4 representing rotation of angle around Y-axis in right-handed coordinate system
	void rotateY(float angle);

	//Multiplies itself with Matrix4 representing rotation of angle around Z-axis in right-handed coordinate system
	void rotateZ(float angle);


	//Optimized operator for multiplying Vector4s with Matrix4s. Also returns Vector4 in oppose to Matrix<4,1>
	Vector4 operator *(const Vector4& v) const;

	//Optimized operator for multiplying Matrix4s. Also returns Matrix4 in oppose to Matrix<4,4>
	Matrix4 operator *(const Matrix4& m) const;




	//Sets matrix to identity
	void identity(){ 
		memset(elements, 0, sizeof(float) * 16);
		setElement(0, 0, 1.f); setElement(1, 1, 1.f); setElement(2, 2, 1.f); setElement(3, 3, 1.f);
	}





};


