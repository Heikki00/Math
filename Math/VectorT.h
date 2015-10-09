#pragma once

#include "MathError.h"

template<unsigned int t>
class VectorT {
private:
	float* elements;

public:

	VectorT() {
		elements = new float[t];
	}

	~VectorT() {
		delete[] elements;
	}

	float getElement(unsigned int i) const
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to get element greater than t in VectorT\n");
			return 0.f;
		}
		return elements[i];
	}

	void setElement(unsigned int i, float f)
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to set element greater than t in VectorT\n");
			return;
		}
		elements[i] = f;
	}

	unsigned int getNumElements() const
	{
		return t;
	}

	float dot(const VectorT<t>& v) const
	{
		float dot = 0.f;
		for (unsigned int i = 0; i < t; ++i) {
			dot += getElement(i) * v.getElement(i);
		}

		return dot;
	}

	float lenght() const
	{
		float l2 = 0.f;

		for (unsigned int i = 0; i < t; ++i) {
			l2 += getElement(i) * getElement(i);
		}
		return sqrtf(l2);
	}

	float lenght2() const
	{
		float l2 = 0.f;

		for (unsigned int i = 0; i < t; ++i) {
			l2 += getElement(i) * getElement(i);
		}
		return l2;
	}

	VectorT<t> normalized() const
	{
		const float len = lenght();
		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) / len);
		}
		return res;
	}

	void normalize()
	{
		const float len = lenght();
		
		for (unsigned int i = 0; i < t; ++i) {
			setElement(i, getElement(i) / len);
		}

	}

	bool isZero() const
	{
		for (unsigned int i = 0; i < t; ++i) {
			if (getElement(i) != 0) return false;
		}
		return true;
	}

	VectorT<t> operator +(const VectorT<t>& v) const
	{
		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) + v.getElement());
		}
		return res;


	}

	VectorT<t> operator -(const VectorT<t>& v) const
	{

		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) - v.getElement());
		}
		return res;
	}

	VectorT<t> operator *(float f) const
	{
		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) * f);
		}
		return res;
	}

	VectorT<t> operator /(float f) const
	{

		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide VectorT by 0\n");
			return VectorT<t>();
		}

		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) * f);
		}
		return res;
	}

	VectorT<t> operator -() const
	{
		VectorT<t> res;
		for (unsigned int i = 0; i < t; ++i) {
			res.setElement(i, -getElement(i));
		}
		return res;
	}

	void operator +=(const VectorT<t>& v)
	{
		for (unsigned int i = 0; i < t; ++i) {
			setElement(i, getElement(i) + v.getElement(i));
		}
	}

	void operator -=(const VectorT<t>& v)
	{
		for (unsigned int i = 0; i < t; ++i) {
			setElement(i, getElement(i) - v.getElement(i));
		}
	}

	void operator *=(float f)
	{
		for (unsigned int i = 0; i < t; ++i) {
			setElement(i, getElement(i) * f);
		}
	}

	void operator /=(float f)
	{

		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide VectorT by 0\n");
			return;
		}

		for (unsigned int i = 0; i < t; ++i) {
			setElement(i, getElement(i) / f);
		}
	}

	bool operator ==(const VectorT<t>& v) const
	{
		return memcmp(elements, v.elements, t * sizeof(float)) == 0;
	}

	bool operator !=(const VectorT<t>& v) const
	{
		return return memcmp(elements, v.elements, t * sizeof(float)) != 0;;
	}

	float& operator [](unsigned int i)
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to get reference to element greater than t in VectorT\n");
			return 0.f;
		}

		return elements[i];
	}

	float* toArray() const
	{
		float* arr = new float[t];
		memcpy(arr, elements, t * sizeof(float));
		return arr;
	}


	friend VectorT<t> operator *(float f, const VectorT<t>& v) {
		return v * f;

	}

	friend std::ostream& operator <<(std::ostream& os, const Vector4& v) {
		os << std::fixed << "VectorT" << "<" << v.getNumElements() << ">: (";
		for (int i = 0; i < (v.getNumElements() - 1); ++i) {
			os << v.elements[i] << ", ";
		}

		os << v.elements[v.getNumElements() - 1] << ")T" << std::endl;


		return os;
	}
};














