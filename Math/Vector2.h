#pragma once
#include "Vector.h"
#include "MathError.h"

//Forward-declarations:

class Vector3;
class Vector4;



//Class that represents 2-dimensional vector. Only variables are
//references to elements.
class Vector2 : public Vector<2>{
public:

	Vector2();

	//Initializes all elements to defValue
	explicit Vector2(float defValue);
	Vector2(float x, float y);

	//constructs Vector2 from Vector that has 2 elements
	explicit Vector2(const Vector<2>& v);

	//Initializes elements form v.x and v.y. Intended use to go back from homogeneous coordinates
	explicit Vector2(const Vector3& v);

	//Copy constructor
	Vector2(const Vector2& v);

	//Assignment operator
	inline Vector2& operator =(const Vector2& v){
		Vector::operator=(v);
		return *this;
	}

	inline Vector2 operator +(const Vector2& v) const{ return Vector2(x + v.x, y + v.y); }

	inline Vector2 operator -(const Vector2& v) const{ return Vector2(x - v.x, y - v.y); }

	
	inline friend Vector2 operator *(float scalar, const Vector2& v){ return Vector2(v.x * scalar, v.y * scalar); }

	inline Vector2 operator /(float scalar) const{
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector2 by 0");
			return Vector2();
		}
		return Vector2(x / scalar, y / scalar);
	}

	inline Vector2 operator -() const{ return Vector2(-x, -y); }

	inline void operator *=(float scalar){ x *= scalar; y *= scalar; }

	inline void operator /=(float scalar){
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector2 by 0");
			return;
		}
		x /= scalar; y /= scalar;
	}

	inline void operator +=(const Vector2& v){ x += v.x; y += v.y; }

	inline void operator -=(const Vector2& v){ x -= v.x; y -= v.y; }

	inline bool operator ==(const Vector2& v) const{ return x == v.x && y == v.y; }
	
	inline bool operator !=(const Vector2& v) const{ return !this->operator==(v); }

	inline bool isZero() const{ return x == 0 && y == 0; }

	//Optimized method, overrides one from Vector.Calculates lenght of vector with pythagoras theorem
	inline float lenght() const{ return sqrtf(x*x + y*y); }

	//Makes lenght of this vector to be 1 (divides it by it's lenght)
	inline void normalize(){
		float lenght = this->lenght();

		x /= lenght;
		y /= lenght;

	}

	//Returns normalized version of this vector
	inline Vector2 normalized() const{
		float lenght = this->lenght();

		return Vector2(x / lenght, y / lenght);

	}


	//Optimized method, returns dot product of this and v
	float dot(const Vector2& v) const{
		return x * v.x + y * v.y;

	}
	
	//Converts this to homogeneous coordinates (Vector3(x,y,1))
	Vector3 homogeneous() const;


	float& x;
	float& y;




};





