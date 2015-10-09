#pragma once
#include "MathError.h"
#include <iostream>

//Forward-declarations

class Vector2;
class Vector4;


//Class that represents 3-dimensional vector. Contains 3 floats
//Also includes static const variables for world-up, world-left etc.
class Vector3 {
public:
	float x, y, z;

	//Inits zero vector
	Vector3();

	//Inits vector to default value
	explicit Vector3(float defValue);

	//Constructs vector from 3 components
	Vector3(float x, float y, float z);

	//Constructs vector from x, y and z of Vector4
	explicit Vector3(const Vector4& v);


	//Returns the element in specified position
	inline float getElement(unsigned int i) const {
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;

		default:
			Math::mathError("ERROR: Tried to get element other than 0, 1 or 2 in Vector3\n");
			return 0.f;
		}
	};

	//Sets the value of the element in specified position
	inline void setElement(unsigned int i, float f) {
		switch (i)
		{
		case 0: x = f; return;
		case 1: y = f; return;
		case 2: z = f; return;

		default:
			Math::mathError("ERROR: Tried to set element other than 0, 1 or 2 in Vector3\n");
			return;
		}
	};

	//Returns the dot product between two vectors
	inline float dot(const Vector3& v) const
	{
		return x*v.x + y * v.y + z * v.z;
	}

	//Returns the length of the vector. Has square root in it, use lenght2 when possible
	inline float lenght() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	//Returns the length squared. Cheaper that lenght()
	inline float lenght2() const
	{
		return x*x + y*y + z*z;
	}

	//Returns the normalized version of this vector
	inline Vector3 normalized() const
	{
		float len = sqrtf(x*x + y*y + z*z);

		return Vector3(x * len, y * len, z * len);

	}

	//Normalizes this vector
	inline void normalize()
	{
		float len = sqrtf(x*x + y*y + z*z);
		x /= len;
		y /= len;
		z /= len;

	}

	//Returns true if all elements in this vector are 0
	inline bool isZero() const
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	//Returns the homogeneous version of this vector(x,y,z,1)
	Vector4 homogeneous() const;

	//Returns the cross product between 2 vectors
	inline Vector3 cross(const Vector3& other) const {
		float xx = (y * other.z) - (z * other.y);
		float yy = (z * other.x) - (x * other.z);
		float zz = (x * other.y) - (y * other.x);

		return Vector3(xx, yy, zz);
	};


	//Addition operator
	inline Vector3 operator +(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	//Subtraction operator
	inline Vector3 operator -(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	//Scaling operator
	inline Vector3 operator *(float f) const
	{
		return Vector3(x * f, y * f, z * f);
	}

	//Scaling with division
	inline Vector3 operator /(float f) const
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide Vector3 by 0\n");
			return Vector3();
		}
		return Vector3(x / f, y / f, z / f);
	}

	//Compound addition
	inline void operator +=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	//Compound subtraction
	inline void operator -=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	//Compound scaling
	inline void operator *=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
	}

	//Compound scaling with division
	inline void operator /=(float f)
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide-assign Vector3 by 0\n");
			return;
		}

		x /= f;
		y /= f;
		z /= f;
	}

	//Comparison operator
	inline bool operator ==(const Vector3& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	//Inverted comparison operator
	inline 	bool operator !=(const Vector3& v) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

	//Returns a reference to the specified element
	inline float& operator [](unsigned int i)
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;

		default:
			Math::mathError("ERROR: Tried to get reference to element other than 0, 1 or 2 in Vector3\n");
			return *((float*)(nullptr));
		}
	}

	//Inversion operator
	inline Vector3 operator -() const {
		return Vector3(-x, -y, -z);
	}

	//Returns an array containing all the elements
	inline float* toArray()
	{
		return reinterpret_cast<float*>(this);
	}




	static const Vector3 Vector3::WORLD_UP;
	static const Vector3 Vector3::WORLD_DOWN;
	static const Vector3 Vector3::WORLD_LEFT;
	static const Vector3 Vector3::WORLD_RIGHT;
	static const Vector3 Vector3::WORLD_FORW;
	static const Vector3 Vector3::WORLD_BACK;

	//Scaling with scalar first
	inline friend Vector3 operator *(float f, const Vector3& v) {
		return v * f;

	}

	//Printing
	friend std::ostream& operator <<(std::ostream& os, const Vector3& v) {
		os << std::fixed << "Vector3: (" << v.x << ", " << v.y << ", " << v.z << ")T" << std::endl;
		return os;
	}

};



















