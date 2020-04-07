#include "matrix.h"
#include <string>
#include <cmath>

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw std::runtime_error("p-constructor bad arguments");
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	// stub
}

// Destructor
matrix::~matrix()
{
	// stub
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	// stub
	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	// use p-constructor
	return matrix(size,size);
}


// Binary operations
matrix matrix::operator+(const matrix& rhs) const
{
	// stub
	matrix retVal(rhs);
	return retVal;
}


matrix matrix::operator*(const matrix& rhs) const
{
	// stub
	matrix retVal(rhs);
	return retVal;
}

matrix matrix::operator*(const double scale) const
{
	// stub
	matrix retVal(*this);
	return retVal;
}


// Unary operations
matrix matrix::operator~() const
{
	// stub
	matrix retVal(*this);
	return retVal;
}
	

void matrix::clear()
{
	// stub
	return;
}

double* matrix::operator[](unsigned int row)
{
	// stub
	return NULL;
}

double* matrix::operator[](unsigned int row) const
{
	// stub
	return NULL;
}


// Global insertion and operator
std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	// stub
	os << "todo";
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	// stub
	matrix retval(rhs);
	return retval;
}

