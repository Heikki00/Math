#pragma once
#include <math.h>
#include "MathError.h"
#include <iostream>
#include "Matrix.h"




//Class to represent column vector of size 'size'. No own variables, just optimization (getColumns() == 0), hand few new methods.
//size is nonzero uint.
template<unsigned int size>
class Vector : public Matrix<size, 1>{
public:

	//So this class can access these
	using Matrix::getElement;
	using Matrix::setElement;

	Vector(){
		
	}

	//Constructor to create vector from matrix of same dimensions.
	explicit Vector(const Matrix<size, 1>& m) : Matrix(m){
		

	}

	//Copy constructor
	Vector(const Vector& v) : Matrix(v){
		
	}

	

	//Assignment operator, uses Vectors operator
	inline Vector& operator =(const Vector& v){
		Matrix::operator=(v);

		return *this;
	}

	//Addon operator that is optimized for vectors
	Vector operator +(const Vector& v) const
	{
		
		Vector result;


		for (unsigned int i = 0; i < size; ++i){
			result.setElement(i, elements[i] + v.elements[i]);
		}

		return result;
	}

	//Subtraction operator that is optimized for vectors
	Vector operator -(const Vector& v) const
	{
		
		Vector result;


		for (unsigned int i = 0; i < size; ++i){
			result.setElement(i, elements[i] - v.elements[i]);
		}

		return result;
	}

	//Scaling operator.
	friend Vector operator *(float scalar, const Vector& v){
		Vector result;

		for (unsigned int i = 0; i < v.getNumElements(); ++i){
			result.setElement(i, v.getElement(i) * scalar);

		}
		return result;
	
	}

	//Scaling with division
	Vector operator /(float scalar) const
	{
		Vector res;

		if (scalar == 0.f){

			Math::mathError("ERROR: Tried to divide vector by scalar 0");
			return res;
		}

		for (unsigned int i = 0; i < size; ++i){
			res.setElement(i, elements[i] / scalar);

		}
		
		return res;
	}

	//Inversion operator that is optimized for vectors
	Vector operator -() const{
		Vector res;

		for (unsigned int i = 0; i < size; ++i) res.setElement(i, -elements[i]);

		return res;
	}



	//Multiplication assignment operator
	void operator *=(float scalar)
	{
		for (unsigned int i = 0; i < size; ++i){
			elements[i] *= scalar;
		}
	}
	
	//Division assignment operator
	void operator /=(float scalar)
	{

		if (scalar == 0.f){

			Math::mathError("ERROR: Tried to divide vector by scalar 0");
			return;
		}
		
		for (unsigned int i = 0; i < size; ++i){
			elements[i] /= scalar;


		}
	}

	//Addon assignment operator
	void operator +=(const Vector& v)
	{
		


		for (unsigned int i = 0; i < size; ++i){
			elements[i] += v.elements[i];


		}
	}

	//Subtraction assignment operator
	void operator -=(const Vector& v)
	{
		

		for (unsigned int i = 0; i < size; ++i){
			elements[i] -= v.elements[i];


		}
	}
	
	//Equal operator. Defined for vectors of different dimensions(not equal). Only true, if v is a vectors that has same dimensions and same corresponding elements.
	template<unsigned int s>
	bool operator ==(const Vector<s>& v) const{
		if (size != s) return false;
		
		for (unsigned int i = 0; i < size; ++i) 
			if (getElement(i) != v.getElement(i)) return false;

		return true;
	}

	//Non-equal operator. Returns inverted result of equal to.
	template<unsigned int s>
	inline bool operator !=(const Vector<s>& v) const{ return !(this->operator==(v)); }

	//Returns element i. i must be < getNumElements()
	inline float operator [](unsigned int i) const{
		if (i >= size){
			Math::mathError("ERROR: tried to access element " + std::to_string(i) + " with [] in vector that has " + std::to_string(size) + " elements");
			return 0.f;
		}
		return elements[i];
	}
	
	//Returns dot product of this and v. Only defined for vectors of same dimension.
	//Overridden is child classes for optimization.
	float dot(const Vector& v) const
	{
		

		float sum = 0.0f;

		for (unsigned int i = 0; i < size; ++i){
			sum += elements[i] * v.elements[i];

		}

		return sum;
	}

	//Returns the length of vector (sqrt(v1, v2, v3 ... vn))
	//Overridden in child classes for optimization, called very often
	inline  float lenght() const{
		
		float sum = 0.0;
		for (unsigned int i = 0; i < size; ++i){ sum += (getElement(i) * getElement(i)); }
		return sqrt(sum);
		
	}

	//Normalizes this vector (divides it by it's lenght)
	//Overridden in child classes for optimization, called very often
	inline  void normalize(){
		float lenght = this->lenght();

		for (unsigned int i = 0; i < size; ++i){ elements[i] /= lenght; }

	}
	
	//Returns normalized version of this vector (divides it by it's lenght)
	//Overridden in child classes for optimization, called very often
	inline Vector normalized() const{
		return this->operator/(lenght());
	}


	//Returns element index. index must be < getNumElements()
	inline float getElement(unsigned int index) const{
		if (index >= size){
			Math::mathError("ERROR: tried to access element " + std::to_string(index) + " with getElement in vector that has " + std::to_string(size) + " elements");
			return 0.f;
		}
		return elements[index];
	}

	//Sets element index to val. index must be < getNumElements()
	inline void setElement(unsigned int index, float val){
		if (index >= size){
			Math::mathError("ERROR: tried to set element " + std::to_string(index) + " with setElement in vector that has " + std::to_string(size) + " elements");
			return;
		}
		elements[index] = val;
	}


	//Prints vector
	friend std::ostream& operator <<(std::ostream& os, const Vector& v){
		os << "VECTOR" << v.getNumElements() << ": (";
		for (unsigned int i = 0; i < v.getNumElements() - 1; ++i){
			os << std::fixed << v.elements[i] << ", ";
		}

		os << std::fixed << v.elements[v.getNumElements() - 1] << ")t\n";

		return os;
	}


	//Returns number of elements in this vector
	inline unsigned int getNumElements() const{ return size; }

	

};



