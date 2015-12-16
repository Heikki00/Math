#pragma once

#include "MathError.h"
#include "DataTypedefs.h"

template<U32 t>
class VectorT {
private:
	F32* elements;

public:

	VectorT() {
		elements = new F32[t];
	}

	~VectorT() {
		delete[] elements;
	}

	F32 getElement(U32 i) const
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to get element greater than t in VectorT\n");
			return 0.f;
		}
		return elements[i];
	}

	void setElement(U32 i, F32 f)
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to set element greater than t in VectorT\n");
			return;
		}
		elements[i] = f;
	}

	U32 getNumElements() const
	{
		return t;
	}

	F32 dot(const VectorT<t>& v) const
	{
		F32 dot = 0.f;
		for (U32 i = 0; i < t; ++i) {
			dot += getElement(i) * v.getElement(i);
		}

		return dot;
	}

	F32 lenght() const
	{
		F32 l2 = 0.f;

		for (U32 i = 0; i < t; ++i) {
			l2 += getElement(i) * getElement(i);
		}
		return sqrtf(l2);
	}

	F32 lenght2() const
	{
		F32 l2 = 0.f;

		for (U32 i = 0; i < t; ++i) {
			l2 += getElement(i) * getElement(i);
		}
		return l2;
	}

	VectorT<t> normalized() const
	{
		const F32 len = lenght();
		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) / len);
		}
		return res;
	}

	void normalize()
	{
		const F32 len = lenght();
		
		for (U32 i = 0; i < t; ++i) {
			setElement(i, getElement(i) / len);
		}

	}

	bool isZero() const
	{
		for (U32 i = 0; i < t; ++i) {
			if (getElement(i) != 0) return false;
		}
		return true;
	}

	VectorT<t> operator +(const VectorT<t>& v) const
	{
		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) + v.getElement());
		}
		return res;


	}

	VectorT<t> operator -(const VectorT<t>& v) const
	{

		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) - v.getElement());
		}
		return res;
	}

	VectorT<t> operator *(F32 f) const
	{
		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) * f);
		}
		return res;
	}

	VectorT<t> operator /(F32 f) const
	{

		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide VectorT by 0\n");
			return VectorT<t>();
		}

		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, getElement(i) * f);
		}
		return res;
	}

	VectorT<t> operator -() const
	{
		VectorT<t> res;
		for (U32 i = 0; i < t; ++i) {
			res.setElement(i, -getElement(i));
		}
		return res;
	}

	void operator +=(const VectorT<t>& v)
	{
		for (U32 i = 0; i < t; ++i) {
			setElement(i, getElement(i) + v.getElement(i));
		}
	}

	void operator -=(const VectorT<t>& v)
	{
		for (U32 i = 0; i < t; ++i) {
			setElement(i, getElement(i) - v.getElement(i));
		}
	}

	void operator *=(F32 f)
	{
		for (U32 i = 0; i < t; ++i) {
			setElement(i, getElement(i) * f);
		}
	}

	void operator /=(F32 f)
	{

		if (f == 0.f) {
			Math::mathError("ERROR: Tried to divide VectorT by 0\n");
			return;
		}

		for (U32 i = 0; i < t; ++i) {
			setElement(i, getElement(i) / f);
		}
	}

	bool operator ==(const VectorT<t>& v) const
	{
		return memcmp(elements, v.elements, t * sizeof(F32)) == 0;
	}

	bool operator !=(const VectorT<t>& v) const
	{
		return return memcmp(elements, v.elements, t * sizeof(F32)) != 0;;
	}

	F32& operator [](U32 i)
	{
		if (i >= t) {
			Math::mathError("ERROR: Tried to get reference to element greater than t in VectorT\n");
			return 0.f;
		}

		return elements[i];
	}

	const F32* toArray() const
	{
		return elements;
	}

	F32* toArray()
	{
		return elements;
	}

	friend VectorT<t> operator *(F32 f, const VectorT<t>& v) {
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














