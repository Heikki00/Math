#pragma once
#include "MathError.h"
#include "DataTypedefs.h"

//Forward-declarations

class Vector2;
class Vector3;


//Class that represents 4-dimensional vector. Contains 4 F32s.
class Vector4 {
public:
	F32 x, y, z, w;

	//Inits zero vector
	Vector4();

	//Inits vector to default value
	explicit Vector4(F32 defValue);

	//Constructs vector from 4 values
	Vector4(F32 x, F32 y, F32 z, F32 w);


	//Returns the element in specified position
	inline F32 getElement(U32 i) const
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;

		default:
			Math::mathError("ERROR: Tried to get element other than 0, 1, 2 or 3 in Vector4\n");
			return 0.f;
		}
	}

	//Sets the value of the element in specified position
	inline void setElement(U32 i, F32 f)
	{
		switch (i)
		{
		case 0: x = f; return;
		case 1: y = f; return;
		case 2: z = f; return;
		case 3: w = f; return;

		default:
			Math::mathError("ERROR: Tried to set element other than 0, 1, 2 or 3 in Vector4\n");
			return;
		}
	}


	//Returns the dot product between two vectors
	inline F32 dot(const Vector4& v) const
	{
		return x*v.x + y*v.y + z*v.z + w*v.w;
	}

	//Returns the length of the vector. Has square root in it, use lenght2 when possible
	inline F32 lenght() const
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	//Returns the length squared. Cheaper that lenght()
	inline F32 lenght2() const
	{
		return x*x + y*y + z*z + w*w;
	}

	//Returns the normalized version of this vector
	inline Vector4 normalized() const
	{
		F32 len = lenght();

		return Vector4(x / len, y / len, z / len, w / len);
	}

	//Normalizes this vector
	inline void normalize()
	{
		F32 len = lenght();

		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}

	//Returns true if all elements in this vector are 0
	inline bool isZero() const
	{
		return w == 0 && x == 0 && y == 0 && z == 0;
	}


	//Addition operator
	inline Vector4 operator +(const Vector4& v) const
	{
		Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	//Subtraction operator
	inline Vector4 operator -(const Vector4& v) const
	{
		Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	//Scaling operator
	inline Vector4 operator *(F32 f) const
	{
		Vector4(x * f, y * f, z * f, w * f);
	}

	//Scaling with division
	inline Vector4 operator /(F32 f) const
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide Vector4 by 0\n");
			return Vector4();
		}
		return Vector4(x / f, y / f, z / f, w / f);
	}

	//Compound addition
	inline void operator +=(const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

	//Compound subtraction
	inline void operator -=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}

	//Compound scaling
	inline void operator *=(F32 f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
	}

	//Compound scaling with division
	inline void operator /=(F32 f)
	{
		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide-assign Vector4 by 0\n");
			return;
		}

		x /= f;
		y /= f;
		z /= f;
		w /= f;
	}

	//Comparison operator
	inline bool operator ==(const Vector4& v) const
	{
		return x == v.x && y == v.z && z == v.z && w == v.w;
	}

	//Inverted comparison operator
	inline bool operator !=(const Vector4& v) const
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	//Returns a reference to the specified element
	inline F32& operator [](U32 i)
	{
		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;

		default:
			Math::mathError("ERROR: Tried to get reference to element other than 0, 1, 2 or 3 in Vector4\n");
			return *((F32*)(nullptr));
		}
	}

	//Inversion operator
	inline Vector4 operator -() const {
		return Vector4(-x, -y, -z, -w);
	}

	//Returns an array containing all the elements
	inline F32* toArray()
	{
		return reinterpret_cast<F32*>(this);
	}

	//Returns an array containing all the elements
	inline const F32* toArray() const
	{
		return reinterpret_cast<const F32*>(this);
	}

	//Scaling with scalar first
	inline friend Vector4 operator *(F32 f, const Vector4& v) {
		return v * f;

	}

	//Printing
	friend std::ostream& operator <<(std::ostream& os, const Vector4& v) {
		os << std::fixed << "Vector4: (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")T" << std::endl;
		return os;
	}









};





