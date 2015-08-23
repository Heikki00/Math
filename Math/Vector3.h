#pragma once
#include "Vector.h"
#include "MathError.h"
#include <iostream>

//Forward-declarations

class Vector2;
class Vector4;


//Class that represents 3-dimensional vector. Only variables are
//references to elements.
//Also includes static const variables for world-up, world-left etc.
class Vector3 : public Vector<3>{
public:

	Vector3();

	//Initializes all elements to defValue
	explicit Vector3(float defValue);
	Vector3(float x, float y, float z);
	
	//Initializes elements form v.x, v.y and v.z. Intended use to go back from homogeneous coordinates
	explicit Vector3(const Vector4& v);

	//Constructs Vector3 from Vector that has 3 elements
	explicit Vector3(const Vector<3>& v);

	//Copy constructor
	Vector3(const Vector3& v);

	//Assignment operator, uses Vectors operator
	inline Vector3& operator =(const Vector3& v){
		Vector::operator=(v);
		return *this;
	}


	inline Vector3 operator +(const Vector3& v) const{ return Vector3(x + v.x, y + v.y, z + v.z); }

	inline Vector3 operator -(const Vector3& v) const{ return Vector3(x - v.x, y - v.y, z - v.z); }

	
	inline friend Vector3 operator *(float scalar, const Vector3& v){ return Vector3(v.x * scalar, v.y * scalar, v.z * scalar); }

	inline Vector3 operator /(float scalar) const{
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector3 by 0");
			return Vector3();
		}
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	inline Vector3 operator -() const{ return Vector3(-x, -y, -z); }


	inline void operator *=(float scalar){ x *= scalar; y *= scalar; z *= scalar; }

	inline void operator /=(float scalar){
		if (scalar == 0.f){
			Math::mathError("ERROR: Tried to divide Vector3 by 0");
			return;
		}
		x /= scalar; y /= scalar; z /= scalar;
	}

	inline void operator +=(const Vector3& v){ x += v.x; y += v.y; z += v.z; }

	inline void operator -=(const Vector3& v){ x -= v.x; y -= v.y; z -= v.z; }

	inline bool operator ==(const Vector3& v) const{ return x == v.x && y == v.y && z == v.z; }

	inline bool operator !=(const Vector3& v) const{ return !this->operator==(v); }
	
	inline bool isZero() const{ return x == 0 && y == 0 && z == 0; }

	//Returns cross product of this x other (etusormi x keskisormi == peukalo)
	Vector3 cross(const Vector3& other) const;

	//Optimized method, overrides one from Vector. Calculates lenght of vector with pythagoras theorem
	inline float lenght() const{
		return sqrtf(x*x + y*y + z*z);
	}

	//Makes lenght of this vector to be 1 (divides it by it's lenght)
	inline void normalize(){
		float lenght = this->lenght();
		
		x /= lenght;
		y /= lenght;
		z /= lenght;

	}

	//Returns normalized version of this vector
	inline Vector3 normalized() const{
		float lenght = this->lenght();

		return Vector3(x / lenght, y / lenght, z / lenght);

	}

	//Optimized method, returns dot product of this and v
	inline float dot(const Vector3& v) const{
		return x * v.x + y * v.y + z * v.z;

	}

	//Converts this to homogeneous coordinates (Vector4(x,y,z,1))
	Vector4 homogeneous() const;


	//Reference to elements[0]
	float& x;

	//Reference to elements[1]
	float& y;

	//Reference to elements[2]
	float& z;
	

	//Vector3(0,1,0)
	static const Vector3 WORLD_UP;
	//Vector3(0,-1,0)
	static const Vector3 WORLD_DOWN;
	//Vector3(-1,0,0)
	static const Vector3 WORLD_LEFT;
	//Vector3(1,0,0)
	static const Vector3 WORLD_RIGHT;
	//Vector3(0,0,-1)
	static const Vector3 WORLD_FORW;
	//Vector3(0,0,1)
	static const Vector3 WORLD_BACK;




};



















