#include <stdio.h>
#include <time.h>

#include "Linear_Least_Square.h"

int main()
{
	Matrix X, Y, Z;

	Init_Matrix(&X, 100, 1);
	Init_Matrix(&Y, 100, 1);

	srand(time(NULL));

	for (int i = 0; i < 100; i++) { 
		X.data[i][0] = rand() % 10;
		Y.data[i][0] = 2 * X.data[i][0] + 3 + rand() % 3  -1 ;
	}

	Print_Matrix(Linear_Least_Square(X, Y));
}