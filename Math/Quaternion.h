#pragma once
#include <math.h>
#include <iostream>
#include "MathError.h"
class Vector3;
class Matrix4;

//Class that represent Quaternion. It includes 4 floats, and is intended to represent 3D rotations.
//Is not child nor has child classes.
class Quaternion{
public:

	//Constructs an identity Quaternion
	Quaternion(){ x = y = z = 0; w = 1; }
	Quaternion(float x, float y, float z, float w){ this->x = x; this->y = y; this->z = z; this->w = w; }
	
	//Constructs a Quaternion that represents rotation of angle around axis
	Quaternion(const Vector3& axis, float angle){ x = y = z = 0; w = 1; axisAngle(axis, angle); }

	//Copy constructor
	Quaternion(const Quaternion& q){ x = q.x; y = q.y; z = q.z; w = q.w; }
	
	//Assignment operator
	Quaternion& operator =(const Quaternion& q){
		if (&q == this) return *this;
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}

	//Destructor
	~Quaternion(){

	}


	//Addon operator
	Quaternion operator +(const Quaternion& q) const{
		return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	//Scaling operator
	friend Quaternion operator*(float f, const Quaternion& q){
		return Quaternion(f * q.x, f * q.y, f * q.z, f * q.w);
	}

	//Scaling operator
	Quaternion operator /(float f) const{
		if (f == 0){
			Math::mathError("ERROR: Tried to divide a Quaternion by 0");
			return Quaternion();
		}
		return Quaternion(x / f, y / f, z / f, w / f);
	}

	//Multiplication operator.
	Quaternion operator *(const Quaternion& q) const{
		Quaternion res;

		res.w = q.w * w - q.x * x - q.y * y - q.z * z;

		res.x = q.w * x + q.x * w - q.y * z + q.z * y;

		res.y = q.w * y + q.x * z + q.y * w - q.z * x;

		res.z = q.w * z - q.x * y + q.y * x + q.z * w;

		return res;

	
	}

	//Multiplication operator, that takes in a vector. Returns a Quaternion, from witch can be extracted the rotated vector with axis()
	Quaternion operator *(const Vector3& v) const;

	//Multiplication assignment operator
	void operator *=(const Quaternion& q){
		*this = this->operator*(q);
	}

	//Equality operator. Nothing special here.
	bool operator ==(const Quaternion& q) const{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	//Inverted equality operator. Just what did you expect?
	bool operator !=(const Quaternion& q) const{
		return !(this->operator==(q));
	}


	
	//Returns Matrix4 that represents the same rotation as this Quaternion
	Matrix4 toMatrix() const;

	//Rotates v, and returns the rotated vector. Shortcut to (q * v).axis()
	Vector3 rotateVector(const Vector3& v) const;

	//Returns the dot product of Quaternion
	float dot(const Quaternion& q) const{ return x * q.x + y * q.y + z * q.z + w * q.w; }

	//Sets Quaternion to represent rotation of angle around axis. Wipes out old values.
	void axisAngle(const Vector3& axis, float angle);

	//Returns the lenght of quaternion. Don't try to think about it too much...
	inline float lenght() const{ return sqrtf(x*x + y*y + z*z + w*w); }

	//Normalizes Quaternion (divides it's components by it's lenght)
	inline void normalize(){
		float l = lenght();

		x /= l;
		y /= l;
		z /= l;
		w /= l;


	}

	//Returns normalized version of this Quaternion
	inline Quaternion normalized() const{
		float l = lenght();
		return Quaternion(x / l, y / l, z / l, w / l);
	}

	//Returns Vector3(x,y,z)
	Vector3 axis() const;

	//Returns Conjugate of this Quaternion
	inline Quaternion conjugate() const{ return Quaternion(-x, -y, -z, w); }

	//Returns the inverse of this Quaternion
	inline Quaternion inverse() const{
		float len = lenght();
		return conjugate() / (x*x + y*y + z*z + w*w);
	}

	//Operator for printing Quaternions
	friend std::ostream& operator << (std::ostream& os, const Quaternion& q){
		os << std::fixed << "Quaternion: (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl;
		return os;

	}


	Vector3 getLeft() const;
	Vector3 getRight() const;
	Vector3 getUp() const;
	Vector3 getDown() const;
	Vector3 getForw() const;
	Vector3 getBack() const;

	float x, y, z, w;



};









