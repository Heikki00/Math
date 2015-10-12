#pragma once
#include "MathError.h"
#include <iostream>
#include "DataTypedefs.h"
//Forward-declarations:

class Vector3;
class Vector4;



//Class that represents 2-dimensional vector. Contains 2 F32s
class Vector2 {
public:
	F32 x, y;

	//Inits zero vector
	Vector2();

	//Inits vector to default value
	explicit Vector2(F32 defValue);

	//Constructs vector from 2 values
	Vector2(F32 x, F32 y);

	//Constructs vector from x and y of Vecotr3
	explicit Vector2(const Vector3&);


	//Returns the element in specified position
	inline F32 getElement(U32 i) const {
		if (i > 1)Math::mathError("ERROR: Tried to get element other than 0 or 1 in Vector2\n");
		return i == 0 ? x : y;
	};

	//Sets the value of the element in specified position
	inline void setElement(U32 i, F32 f) {
		switch (i)
		{
		case 0: x = f; return;
		case 1: y = f; return;

		default:
			Math::mathError("ERROR: Tried to set element other than 0 or 2 in Vector2\n");
			return;
		}
	};

	//Returns the dot product between two vectors
	inline F32 dot(const Vector2& v) const {
		return x * v.x + y * v.y;
	};

	//Returns the length of the vector. Has square root in it, use lenght2 when possible
	inline F32 lenght() const {
		return sqrtf(x*x + y*y);
	};

	//Returns the length squared. Cheaper that lenght()
	inline F32 lenght2() const {
		return x*x + y*y;
	};

	//Returns the normalized version of this vector
	inline Vector2 normalized() const {
		F32 len = lenght();
		return Vector2(x / len, y / len);
	};

	//Normalizes this vector
	inline void normalize()
	{
		F32 len = lenght();
		x /= len;
		y /= len;
	};

	//Returns true if all elements in this vector are 0
	inline bool isZero() const {
		return x == 0 && y == 0;
	};

	//Returns the homogeneous version of this vector(x,y,1)
	Vector3 homogeneous() const;;


	//Addition operator
	inline Vector2 operator +(const Vector2& v) const
	{
		Vector2(x + v.x, y + v.y);
	}

	//Subtraction operator
	inline Vector2 operator -(const Vector2& v) const
	{
		Vector2(x - v.x, y - v.y);
	}

	//Scaling operator
	inline Vector2 operator *(F32 f) const
	{
		Vector2(x * f, y * f);
	}

	//Scaling with division
	inline Vector2 operator /(F32 f) const
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide Vector2 by 0\n");
			return Vector2();
		}
		return Vector2(x / f, y / f);
	}

	//Compound addition
	inline void operator +=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	//Compound subtraction
	inline void operator -=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	//Compound scaling
	inline void operator *=(F32 f)
	{
		x *= f;
		y *= f;
	}

	//Compound scaling with division
	inline 	void operator /=(F32 f)
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide-assign Vector3 by 0\n");
			return;
		}

		x /= f;
		y /= f;
	}

	//Comparison operator
	inline 	bool operator ==(const Vector2& v) const
	{
		return x == v.x && y == v.y;
	}

	//Inverted comparison operator
	inline bool operator !=(const Vector2& v) const
	{
		return x != v.x || y != v.y;
	}

	//Returns a reference to the specified element
	inline F32& operator [](U32 i)
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;

		default:
			Math::mathError("ERROR: Tried to get reference to element other than 0, 1 or 2 in Vector3\n");
			return *((F32*)(nullptr));
		}
	}

	//Inversion operator
	inline 	Vector2 operator -() const {
		return Vector2(-x, -y);
	}

	//Returns an array containing all the elements
	inline F32* toArray() {
		return reinterpret_cast<F32*>(this);
	};

	//Scaling with scalar first
	inline friend Vector2 operator *(F32 f, const Vector2& v) {
		return v * f;

	}

	//Printing
	friend std::ostream& operator <<(std::ostream& os, const Vector2& v) {
		os << std::fixed << "Vector2: (" << v.x << ", " << v.y << ")T" << std::endl;
		return os;
	}


};





