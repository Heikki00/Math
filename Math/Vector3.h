#pragma once
#include "MathError.h"
#include <iostream>
#include "DataTypedefs.h"

//Forward-declarations

class Vector2;
class Vector4;


//Class that represents 3-dimensional vector. Contains 3 F32s
//Also includes static const variables for world-up, world-left etc.
class Vector3 {
public:
	F32 x, y, z;

	//Inits zero vector
	Vector3();

	//Inits vector to default value
	explicit Vector3(F32 defValue);

	//Constructs vector from 3 components
	Vector3(F32 x, F32 y, F32 z);

	//Constructs vector from x, y and z of Vector4
	explicit Vector3(const Vector4& v);


	//Returns the element in specified position
	inline F32 getElement(U32 i) const {
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
	inline void setElement(U32 i, F32 f) {
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
	inline F32 dot(const Vector3& v) const
	{
		return x*v.x + y * v.y + z * v.z;
	}

	//Returns the length of the vector. Has square root in it, use lenght2 when possible
	inline F32 lenght() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	//Returns the length squared. Cheaper that lenght()
	inline F32 lenght2() const
	{
		return x*x + y*y + z*z;
	}

	//Returns the normalized version of this vector
	inline Vector3 normalized() const
	{
		F32 len = sqrtf(x*x + y*y + z*z);

		return Vector3(x * len, y * len, z * len);

	}

	//Normalizes this vector
	inline void normalize()
	{
		F32 len = sqrtf(x*x + y*y + z*z);
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
		F32 xx = (y * other.z) - (z * other.y);
		F32 yy = (z * other.x) - (x * other.z);
		F32 zz = (x * other.y) - (y * other.x);

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
	inline Vector3 operator *(F32 f) const
	{
		return Vector3(x * f, y * f, z * f);
	}

	//Scaling with division
	inline Vector3 operator /(F32 f) const
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
	inline void operator *=(F32 f)
	{
		x *= f;
		y *= f;
		z *= f;
	}

	//Compound scaling with division
	inline void operator /=(F32 f)
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
	inline F32& operator [](U32 i)
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;

		default:
			Math::mathError("ERROR: Tried to get reference to element other than 0, 1 or 2 in Vector3\n");
			return *((F32*)(nullptr));
		}
	}

	//Inversion operator
	inline Vector3 operator -() const {
		return Vector3(-x, -y, -z);
	}

	//Returns an array containing all the elements
	inline F32* toArray()
	{
		return reinterpret_cast<F32*>(this);
	}




	static const Vector3 Vector3::WORLD_UP;
	static const Vector3 Vector3::WORLD_DOWN;
	static const Vector3 Vector3::WORLD_LEFT;
	static const Vector3 Vector3::WORLD_RIGHT;
	static const Vector3 Vector3::WORLD_FORW;
	static const Vector3 Vector3::WORLD_BACK;

	//Scaling with scalar first
	inline friend Vector3 operator *(F32 f, const Vector3& v) {
		return v * f;

	}

	//Printing
	friend std::ostream& operator <<(std::ostream& os, const Vector3& v) {
		os << std::fixed << "Vector3: (" << v.x << ", " << v.y << ", " << v.z << ")T" << std::endl;
		return os;
	}

};



















