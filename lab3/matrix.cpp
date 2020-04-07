#include "matrix.h"
#include <string>
#include <cmath>

// Helper for copy constructor and assignment operator
void matrix::copy(matrix& A, const matrix& B)
{
	for (int i = 0; i < A.rows; i++)
	{
		// allocate row
		A.the_matrix[i] = new double[A.cols];

		// copy row
		std::copy(B.the_matrix[i], B.the_matrix[i]+B.cols, A.the_matrix[i]);
	}
}

void matrix::transform(matrix& A, void func(double *)) {
	for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            func(&(A.the_matrix[i][j]));
        }
    }
}

// Parameterized constructor
matrix::matrix(unsigned int rows, unsigned int cols):rows(rows),cols(cols) 
{  
	if (rows < 1 || cols < 1)
	{
		throw std::runtime_error("Parameterized constructor: bad arguments");
	}
	
	// allocate 2d array
	this->the_matrix = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		// allocate row
		this->the_matrix[i] = new double[cols];

		// copy row
		std::fill(this->the_matrix[i], this->the_matrix[i] + this->cols, 0);
	}
}

// Copy constructor
matrix::matrix(const matrix& from):rows(from.rows),cols(from.cols)
{
	// allocate 2d array
	this->the_matrix = new double*[this->rows];
	copy(*this, from);
}

// Destructor
matrix::~matrix()
{
	for (int i = 0; i < this->rows; i++)
	{
		delete[] this->the_matrix[i];
	}
	delete[] this->the_matrix;
}

// Assignment operator
matrix& matrix::operator=(const matrix& rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < this->rows; i++)
		{
			delete[] this->the_matrix[i];
		}
		delete[] this->the_matrix;
	}

	this->rows = rhs.rows;
	this->cols = rhs.cols;

	// allocate 2d array
	this->the_matrix = new double*[this->rows];
	copy(*this, rhs);

	return *this;
}

// Named constructor (static)
matrix matrix::identity(unsigned int size)
{
	if (size < 1)
	{
		throw std::runtime_error("Named identity constructor: bad arguments");
	}

	// use p-constructor
	matrix I(size,size);
	for (int i = 0; i < size; i++)
	{
		I.the_matrix[i][i] = 1.0;
	}

	return I;
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
	transform(*this, [](double * val) {*val = 0.0;});
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
    for (int i = 0; i < rhs.rows; i ++)
    {
        os << "[ ";
        for (int j = 0; j < rhs.cols; j++)
        {
            os << rhs.the_matrix[i][j] << " ";
        }
        os << "]" << std::endl;
    }
	return os;
}

// Global scalar multiplication
matrix operator*(const double scale, const matrix& rhs)
{
	// stub
	matrix retval(rhs);
	return retval;
}

