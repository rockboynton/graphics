#include "matrix.h"
#include <iostream>
 
using namespace std;

int main(void)
{
	// test our matrix
	
	matrix m1(3,3);
	
	cout << "m1 - should be all zeros" << endl;
	cout << m1 << endl;
	
	matrix m2 = matrix::identity(3);

	cout << "m2 - should be 3 x 3 identity matrix" << endl;
	cout << m2 << endl;

	matrix m3 = m1 + m2;

	cout << "m3 - should be 3 x 3 identity matrix" << endl;
	cout << m3 << endl;

	matrix m4 = m3;

	cout << "m4 - should be all zeros after clear()" << endl;
	m4.clear();
	cout << m4 << endl;

	cout << "m5 - should be 5 on diagonal after global mult" << endl;
	matrix m5 = 5.0 * m2;
	cout << m5 << endl;

	cout << "m6 - should be 10 on diagonal after matrix add" << endl;
	matrix m6 = m5 + m5;
	cout << m6 << endl;

	cout << "m7 - should be 5 on diagonal after matrix mult" << endl;
	matrix m7 = m2 * 5.0;
	cout << m7 << endl;

	matrix m8(4, 2);
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m8[i][j] = ++count;
		}
	}

	cout << "m8 - before transpose" << endl;
	cout << m8 << endl;
	cout << "m9 - transposed m8" << endl;
	matrix m9 = ~m8;
	cout << m9 << endl;
	
	return 0;
}		