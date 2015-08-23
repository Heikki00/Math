#pragma once
#include <memory.h>
#include <iostream>
#include <string>
#include "MathError.h"

//Base class for all math types. Basic matrix, includes operators for multiplication, addon, subtraction, division.
//Class stores its data to float array, in form of rows back to back.
//No overhead, because Matrix uses templates to keep track of sizes
//r and c must be nonzero
template<unsigned int rows, unsigned int columns>
class Matrix{
public:

	Matrix(){
		if (rows == 0 || columns == 0){
			Math::mathError("ERROR: Tried to create a matrix with zero dimension");
			return;
		}
		elements = new float[rows * columns]();

	}


	//Copy constructor
	Matrix(const Matrix& m){
		elements = new float[rows * columns]();
		

		memcpy(elements, m.elements, rows * columns * sizeof(float));

	}

	//Destructor
	~Matrix(){
		 delete[] elements;
	}

	//Assignment operator, does not delete and reallocate, just copies
	Matrix& operator =(const Matrix& m){
		if (this == &m) return *this;

		memcpy(elements, m.elements, rows * columns * sizeof(float));

		return *this;

	}


	//Matrix multiplication operator. Not very optimized(nor pretty), but it works. And only for multiplications that are mathematically possible('inner dimensions' match)
	//mCol is template for 'outer' dimension of matrix m. It can be any nonzero uint.
	template<unsigned int mCol>
	Matrix<rows, mCol> operator *(const Matrix<columns, mCol>& m) const
	{
		//Creates a result matrix that has roes of this and columns of m
		Matrix < rows, mCol > res;
	

		for (unsigned int i = 0; i < mCol; ++i){
		
			for (unsigned int i2 = 0; i2 < rows; ++i2){
				float dot = 0.0;
			
					for (unsigned int i3 = 0; i3 < columns; ++i3){
						dot += getElement(i2, i3) * m.getElement(i3, i);
				
					}
				res.setElement(i2, i, dot);
			
		}
		
	
		
	}


	return res;
	
	}


	//Scaling operator. Defined as friend, so mathmatically correct order can be achived. Not defined in other order(Matrix * scalar)
	friend Matrix operator *(float scalar, const Matrix& m) { 
		Matrix res;
		for (unsigned int r = 0; r < m.getRows(); ++r){
			for (unsigned int c = 0; c < m.getColumns(); ++c) res.setElement(r, c, m.getElement(r, c) * scalar);

		}

		return res;
	}


	//Matrix addon operator. Only defined for matrices with same dimensions(yayy, templates!)
	Matrix operator +(const Matrix& m) const{
		Matrix res;
		for (unsigned int r = 0; r < rows; ++r){
			for (unsigned int c = 0; c < columns; ++c) res.setElement(r, c, getElement(r, c) + m.getElement(r, c));

		}

		return res;

	}
	
	//Matrix subtraction operator. Only defined for same dimensions, nothing special here.
	Matrix operator -(const Matrix& m) const{

		Matrix res;
		for (unsigned int r = 0; r < rows; ++r){
			for (unsigned int c = 0; c < columns; ++c) res.setElement(r, c, getElement(r, c) - m.getElement(r, c));

		}

		return res;



	}

	//Scaling with division. basic stuff, f must be nonzero
	Matrix operator /(float f) const{
		Matrix res;
		if (f == 0.f){
			Math::mathError("ERROR: Tried to divide a matrix by scalar 0"); 
			return res;
		}
		for (unsigned int r = 0; r < rows; ++r){
			for (unsigned int c = 0; c < columns; ++c) res.setElement(r, c, getElement(r, c) / f);

		}

		return res;
	}
	
	//Inversion operator. Just inverts all components of matrix
	Matrix operator -() const{
		Matrix res;
		for (unsigned int r = 0; r < rows; ++r){
			for (unsigned int c = 0; c < columns; ++c) res.setElement(r, c, -getElement(r, c));

		}

		return res;
	}

	//Matrix multiplication assingment operator. Just multiplies *this with m, and copys the result.
	void operator *=(const Matrix& m){

		memcpy(elements, (this->operator*(m)).elements, rows * columns * sizeof(float));


	}

	//Matrix addon assignment operator. Nothing to say, really.
	void operator +=(const Matrix& m){
		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int i2 = 0; i2 < columns; ++i2)
				setElement(i, i2, getElement(i, i2) + m.getElement(i, i2));
	}

	//Matrix subtraction operator. Again, nothing special.
	void operator -=(const Matrix& m){
		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int i2 = 0; i2 < columns; ++i2)
				setElement(i, i2, getElement(i, i2) - m.getElement(i, i2));

	}

	
	//Equal operator. Defined for matrices of different dimensions(not equal). Only true, if m is a matrix that has same dimensions and same corresponding elements.
	template<unsigned int r, unsigned int c>
	inline bool operator ==(const Matrix<r, c>& m) const{
		if (r != rows || c != columns) return false;

		for (unsigned int i = 0; i < rows; ++i)
			for (unsigned int i2 = 0; i2 < columns; ++i2)
				if (getElement(i, i2) != m.getElement(i, i2)) return false;

		return true;

	}
	
	//Non-equal operator. Returns inverted result of equal to.
	template<unsigned int r, unsigned int c>
	inline bool operator !=(const Matrix<r, c>& m) const{
		return !(this->operator==(m));
	}
	
	//Returns pointer to start of row i. if i >= getRows(), return nullptr. Intended use is to access row with this, and then use operator[n] on pointer to access element in row i column n
	inline float* operator [](unsigned int i) const{
		if (i >= rows){
			Math::mathError("ERROR: Tried to access to nonexistent row with matrix operator []. i:" + std::to_string(i) + ", rows:" + std::to_string(rows));
			return nullptr;
		}
		return elements + i * columns;
	}

	//Returns true if all elements are zero
	inline  bool isZero() const{
		for (int r = 0; r < rows; ++r)
			for (int c = 0; c < columns; ++c)
				if (getElement(r, c) != 0.f) return false;

		return true;
	}

	//Returns the element in specified location. Row must be < getRows() and colum < getColums()
	inline float getElement(unsigned int row, unsigned int column) const{
		if (row >= rows || column >= columns){
			Math::mathError("ERROR: Tried to access row " + std::to_string(row) + " column " + std::to_string(column) + " in matrix that is " + std::to_string(rows) + "x" + std::to_string(columns));
			return 0.f;
		}
		return elements[row * columns + column]; 
	}

	// Sets the element in specified location to value. Row must be < getRows() and colum < getColums()
	inline void setElement(unsigned int row, unsigned int column, float value){
		if (row >= rows || column >= columns){
			Math::mathError("ERROR: Tried to access row " + std::to_string(row) + " column " + std::to_string(column) + " in matrix that is " + std::to_string(rows) + "x" + std::to_string(columns));
			return;
		}
		elements[row * columns + column] = value; 
	}

	//Returns the amount of rows in this matrix
	inline unsigned int getRows() const{ return rows; }

	//Returns the amount of columns in this matrix
	inline unsigned int getColumns() const{ return columns; }

	//Returns array of elements, that can be modified(and modifies this matrix)
	inline float* toArray(){ return elements; }

	//Operator for printing matrices. Unfortunately, cannot be moved to source file(todo?)
	//Prints everything with std::fixed flag, so no sientific notation.
	friend std::ostream& operator <<(std::ostream& os, const Matrix& m){

		//Print dimensions
		os << "MATRIX" << m.getRows() << "x" << m.getColumns() << ": ";
		
		//Print first bracket and element(no comma in front, and no offset string)
		os << std::fixed << '[' << m.elements[0];

		//Create the string of spaces so starts of rows align.
		std::string offsetString(9 + std::to_string(m.getRows()).length() + std::to_string(m.getColumns()).length(), ' ');


		//Print rest of the first row, comma is a prefix so nothing to worry about on last element.
		for (unsigned int i = 1; i < m.getColumns(); ++i) os << std::fixed << ", " << m.elements[i];

		//and closing bracket and newline
		os << "]\n";

		//Loop through rows, print offset string and bracket, print first element, print rest of elements with comma prefix, and closing bracket + newline
		for (unsigned int i = 1; i < m.getRows(); ++i){
			os << offsetString << '[';

			os << std::fixed << m.elements[0 + i * m.getColumns()];

			for (unsigned int i2 = 1; i2 < m.getColumns(); ++i2) os << std::fixed << ", " << m.elements[i2 + i * m.getColumns()];
			os << "]\n";

		}

		return os;
	}


	protected:
		//Array that holds all elements
		float* elements;

	



};








