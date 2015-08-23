#pragma once
#include "MathError.h"
#include "Vector.h"

//Forward-declarations

class Vector2;
class Vector3;


//Class that represents 4-dimensional vector. Only variables are
//references to elements.
class Vector4 : public Vector<4>{
public:

	Vector4();
	
	//Initializes all elements to defValue
	explicit Vector4(float defValue);
	Vector4(float x, float y, float z, float w);

	//Constructs Vector4 from Vector that has 4 elements
	explicit Vector4(const Vector<4>& v);

	//Copy constructor
	Vector4(const Vector4& v);

	//Assignment operator, uses operator form Vector
	inline Vector4& operator =(const Vector4& v){
		Vector::operator=(v);
		return *this;
	}


	
	inline Vector4 operator +(const Vector4& v) const{ return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }

	inline Vector4 operator -(const Vector4& v) const{ return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }

	inline friend Vector4 operator *(float scalar, const Vector4& v){ return Vector4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar); }
	
	inline Vector4 operator /(float scalar) const{ 
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector4 by 0");
			return Vector4();
		}
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar); 
	}

	inline Vector4 operator -() const{ return Vector4(-x, -y, -z, -w); }


	inline void operator *=(float scalar){ x *= scalar; y *= scalar; z *= scalar; w *= scalar; }

	inline void operator /=(float scalar){ 
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector4 by 0");
			return;
		}

		x /= scalar; y /= scalar; z /= scalar; w /= scalar;
		
	
	}

	inline void operator +=(const Vector4& v){ x += v.x; y += v.y; z += v.z; w += v.w; }

	inline void operator -=(const Vector4& v){ x -= v.x; y -= v.y; z -= v.z; w -= v.w; }

	inline bool operator ==(const Vector4& v) const{ return x == v.x && y == v.y && z == v.z && w == v.w; }

	inline bool operator !=(const Vector4& v) const{ return !this->operator==(v); }

	inline bool isZero() const{ return x == 0 && y == 0 && z == 0 && w == 0; }

	//Optimized method, overrides one from Vector. Calculates lenght of vector with pythagoras theorem
	inline float lenght() const{
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	//Makes lenght of this vector to be 1 (divides it by it's lenght)
	inline void normalize(){
		float lenght = this->lenght();

		x /= lenght;
		y /= lenght;
		z /= lenght;
		w /= lenght;
	}

	//Returns normalized version of this vector
	inline Vector4 normalized() const{
		float lenght = this->lenght();

		return Vector4(x / lenght, y / lenght, z / lenght, w / lenght);

	}

	//Optimized method, returns dot product of this and v
	float dot(const Vector4& v) const{
		return x * v.x + y * v.y + z * v.z + w * v.w;

	}



	//Reference to elements[0]
	float& x;

	//Reference to elements[1]
	float& y;

	//Reference to elements[2]
	float& z;

	//Reference to elements[3]
	float& w;



};





