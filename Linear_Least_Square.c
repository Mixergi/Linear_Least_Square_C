#include "Linear_Least_Square.h"

Matrix Add_X0(Matrix matrix) {
	Matrix _matrix;

	Init_Matrix(&_matrix, matrix.height, matrix.width + 1);

	for (int i = 0; i < _matrix.height; i++) {
		for (int j = 0; j < _matrix.width; j++) {
			if (j == 0) {
				_matrix.data[i][0] = 1;
			}
			else {
				_matrix.data[i][j] = matrix.data[i][0];
			}
		}
	}

	return _matrix;
}

Matrix Linear_Least_Square(Matrix X, Matrix Y) {
	Matrix answer;
	Matrix X_b = Add_X0(X);

	Matrix Xt_b = Transpose_Matrix(X_b);
	Matrix XtX = Multiple_Matrix(Xt_b, X_b);
	Matrix _XtX__1 = Inverse_Matrix(XtX);
	Matrix _XtXt__1_X = Multiple_Matrix(_XtX__1, Xt_b);
	answer = Multiple_Matrix(_XtXt__1_X, Y);

	Free_Matrix(&X_b);
	Free_Matrix(&Xt_b);
	Free_Matrix(&XtX);
	Free_Matrix(&_XtX__1);
	Free_Matrix(&_XtXt__1_X);

	return answer;

}