#include "matrix.h"
#include <string>
#include <cmath>


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
	for (int i = 0; i < this->rows; i++)
	{
		// allocate row
		this->the_matrix[i] = new double[this->cols];

		// copy row
		std::copy(from.the_matrix[i], from.the_matrix[i]+from.cols, this->the_matrix[i]);
	}
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

