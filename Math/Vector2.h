#pragma once
#include "MathError.h"
#include <iostream>

//Forward-declarations:

class Vector3;
class Vector4;



//Class that represents 2-dimensional vector. Contains 2 floats
class Vector2 {
public:
	float x, y;

	//Inits zero vector
	Vector2();

	//Inits vector to default value
	explicit Vector2(float defValue);

	//Constructs vector from 2 values
	Vector2(float x, float y);

	//Constructs vector from x and y of Vecotr3
	explicit Vector2(const Vector3&);


	//Returns the element in specified position
	inline float getElement(unsigned int i) const {
		if (i > 1)Math::mathError("ERROR: Tried to get element other than 0 or 1 in Vector2\n");
		return i == 0 ? x : y;
	};

	//Sets the value of the element in specified position
	inline void setElement(unsigned int i, float f) {
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
	inline float dot(const Vector2& v) const {
		return x * v.x + y * v.y;
	};

	//Returns the length of the vector. Has square root in it, use lenght2 when possible
	inline float lenght() const {
		return sqrtf(x*x + y*y);
	};

	//Returns the length squared. Cheaper that lenght()
	inline float lenght2() const {
		return x*x + y*y;
	};

	//Returns the normalized version of this vector
	inline Vector2 normalized() const {
		float len = lenght();
		return Vector2(x / len, y / len);
	};

	//Normalizes this vector
	inline void normalize()
	{
		float len = lenght();
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
	inline Vector2 operator *(float f) const
	{
		Vector2(x * f, y * f);
	}

	//Scaling with division
	inline Vector2 operator /(float f) const
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
	inline void operator *=(float f)
	{
		x *= f;
		y *= f;
	}

	//Compound scaling with division
	inline 	void operator /=(float f)
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
	inline float& operator [](unsigned int i)
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;

		default:
			Math::mathError("ERROR: Tried to get reference to element other than 0, 1 or 2 in Vector3\n");
			return *((float*)(nullptr));
		}
	}

	//Inversion operator
	inline 	Vector2 operator -() const {
		return Vector2(-x, -y);
	}

	//Returns an array containing all the elements
	inline float* toArray() {
		return reinterpret_cast<float*>(this);
	};

	//Scaling with scalar first
	inline friend Vector2 operator *(float f, const Vector2& v) {
		return v * f;

	}

	//Printing
	friend std::ostream& operator <<(std::ostream& os, const Vector2& v) {
		os << std::fixed << "Vector2: (" << v.x << ", " << v.y << ")T" << std::endl;
		return os;
	}


};





