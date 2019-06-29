#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef double Data;

typedef struct _matrix {
	Data **data;
	int width;
	int height;
}Matrix;

void Print_Matrix(Matrix matrix);

void Init_Matrix(Matrix *matrix, int height, int width);

Matrix Argument_Matrix(Matrix matrix1, Matrix matrix2);

Matrix Elementry_Matrix_ij(Matrix matrix, int i, int j);

Matrix Elementry_Matrix_i_c(Matrix matrix, int i, double c);

Matrix Elementry_Matrix_ij_c(Matrix matrix, int i, int j, double c);

Matrix REF(Matrix matrix);

Matrix RREF(Matrix matrix);

Matrix Multiple_Matrix(Matrix matrix1, Matrix matrix2);

Matrix Multiple_Scalar(Matrix matrix, Data data);

Matrix Transpose_Matrix(Matrix matrix);

Matrix Inverse_Matrix(Matrix matrix);

Matrix Add_X0(Matrix matrix);

void Free_Matrix(Matrix *matrix);