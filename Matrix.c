#include "Matrix.h"

void Init_Matrix(Matrix *matrix, int height, int width) {
	matrix->data = (Data **)malloc(sizeof(Data *) * height);

	for (int i = 0; i < height; i++) {
		matrix->data[i] = (Data *)malloc(sizeof(Data) * width);
	}

	matrix->height = height;
	matrix->width = width;

	return;
}

Matrix Argument_Matrix(Matrix matrix1, Matrix matrix2) {
	Matrix matrix;

	Init_Matrix(&matrix, matrix1.height, matrix1.width + matrix2.width);

	for (int i = 0; i < matrix.height; i++) {
		for (int j = 0; j < matrix1.width; j++) {
			matrix.data[i][j] = matrix1.data[i][j];
		}
		for (int j = 0; j < matrix2.width; j++) {
			matrix.data[i][matrix1.width + j] = matrix2.data[i][j];
		}
	}

	return matrix;
}

Matrix Elementry_Matrix_ij(Matrix matrix, int i, int j) {
	if (matrix.height < j) {
		printf("기본행렬을 연산을 없습니다.\n");
		exit(-1);
	}

	else if (matrix.height < i) {
		printf("기본행렬을 연산을 없습니다.\n");
		exit(-1);
	}

	if (i == j) {
		return matrix;
	}

	Matrix _matrix;

	Init_Matrix(&_matrix, matrix.height, matrix.width);

	for (int k = 0; k < matrix.height; k++) {
		for (int l = 0; l < matrix.width; l++) {
			_matrix.data[k][l] = matrix.data[k][l];
		}
	}

	Data *temp = (Data *)malloc(sizeof(Data) * matrix.width);

	for (int k = 0; k < _matrix.width; k++) {
		temp[k] = _matrix.data[i][k];
	}

	for (int k = 0; k < _matrix.width; k++) {
		_matrix.data[i][k] = _matrix.data[j][k];
	}

	for (int k = 0; k < _matrix.width; k++) {
		_matrix.data[j][k] = temp[k];
	}

	free(temp);

	return _matrix;
}

Matrix Elementry_Matrix_i_c(Matrix matrix, int i, double c) {
	if (matrix.height < i) {
		printf("기본행렬을 연산을 없습니다.\n");
		exit(-1);
	}

	Matrix _matrix;

	Init_Matrix(&_matrix, 1, matrix.width);

	for (int k = 0; k < _matrix.width; k++) {
		_matrix.data[0][k] = c * matrix.data[i][k];
	}

	return _matrix;
}

Matrix Elementry_Matrix_ij_c(Matrix matrix, int i, int j, double c) {
	Matrix elementry_matrix_ic = Elementry_Matrix_i_c(matrix, i, c);
	Matrix _matrix;

	Init_Matrix(&_matrix, matrix.height, matrix.width);

	for (int k = 0; k < _matrix.height; k++) {
		for (int l = 0; l < matrix.width; l++) {
			_matrix.data[k][l] = matrix.data[k][l];
		}
	}

	for (int k = 0; k < _matrix.width; k++) {
		_matrix.data[j][k] = matrix.data[j][k] + elementry_matrix_ic.data[0][k];
	}


	Free_Matrix(&elementry_matrix_ic);

	return _matrix;
}

Matrix REF(Matrix matrix) {

	Matrix _matrix, temp;

	Init_Matrix(&_matrix, matrix.height, matrix.width);

	for (int i = 0; i < matrix.height; i++) {
		for (int j = 0; j < matrix.width; j++) {
			_matrix.data[i][j] = matrix.data[i][j];
		}
	}

	for (int i = 0; i < _matrix.height; i++) {

		int not_zero_set_column = -1;


		for (int m = 0; m < _matrix.width; m++) {
			for (int n = i; n < _matrix.height; n++) {
				if (_matrix.data[n][m] != 0) {
					not_zero_set_column = m;
					break;
				}
			}

			if (not_zero_set_column != -1) {
				break;
			}
		}


		if (_matrix.data[i][not_zero_set_column] == 0) {
			for (int m = i; m < _matrix.height; m++) {
				if (_matrix.data[m][not_zero_set_column] != 0) {
					temp = Elementry_Matrix_ij(_matrix, i, m);
					Free_Matrix(&_matrix);
					_matrix = temp;
					break;
				}
			}
		}

		if (_matrix.data[i][not_zero_set_column] != 1) {
			Data scalar = _matrix.data[i][not_zero_set_column];

			for (int m = 0; m < _matrix.width; m++) {
				_matrix.data[i][m] = _matrix.data[i][m] / scalar;
			}
		}

		for (int m = i + 1; m < _matrix.height; m++) {
			if (_matrix.data[m][not_zero_set_column] != 0) {
				temp = Elementry_Matrix_ij_c(_matrix, i, m, -1 * _matrix.data[m][not_zero_set_column]);
				Free_Matrix(&_matrix);
				_matrix = temp;
			}
		}
	}

	return _matrix;
}

Matrix RREF(Matrix matrix) {
	Matrix _matrix = REF(matrix), temp;

	for (int i = 0; i < _matrix.height; i++) {
		for (int j = 0; j < _matrix.width; j++) {
			if (_matrix.data[i][j] == 1) {
				for (int k = i - 1; k >= 0; k--) {
					if (_matrix.data[k][j] != 0) {
						temp = Elementry_Matrix_ij_c(_matrix, i, k, -1 * _matrix.data[k][j]);
						Free_Matrix(&_matrix);
						_matrix = temp;
					}
				}
				break;
			}
		}
	}

	return _matrix;
}

Matrix Multiple_Matrix(Matrix matrix1, Matrix matrix2) {
	Matrix matrix;

	if (matrix1.height == 1 && matrix1.width == 1) {
		return Multiple_Scalar(matrix2, matrix1.data[0][0]);
	}

	else if (matrix2.height == 1 && matrix2.width == 1) {
		return Multiple_Scalar(matrix1, matrix2.data[0][0]);
	}

	Init_Matrix(&matrix, matrix1.height, matrix2.width);

	for (int i = 0; i < matrix.height; i++) {
		for (int j = 0; j < matrix.width; j++) {
			Data sum = 0;

			for (int k = 0; k < matrix1.width; k++) {
				sum += matrix1.data[i][k] * matrix2.data[k][j];
			}

			matrix.data[i][j] = sum;
		}
	}

	return matrix;
}

Matrix Multiple_Scalar(Matrix matrix, Data data) {
	Matrix _matrix;

	Init_Matrix(&_matrix, matrix.height, matrix.width);

	for (int i = 0; i < _matrix.height; i++) {
		for (int j = 0; j < matrix.width; j++) {
			_matrix.data[i][j] = matrix.data[i][j] * data;
		}
	}

	return _matrix;
}

Matrix Transpose_Matrix(Matrix matrix) {
	Matrix _matrix;

	Init_Matrix(&_matrix, matrix.width, matrix.height);

	for (int i = 0; i < _matrix.height; i++) {
		for (int j = 0; j < _matrix.width; j++) {
			_matrix.data[i][j] = matrix.data[j][i];
		}
	}

	return _matrix;
}

Matrix Inverse_Matrix(Matrix matrix) {
	Matrix _matrix, In, temp;

	Init_Matrix(&In, matrix.height, matrix.width);

	for (int i = 0; i < In.height; i++) {
		for (int j = 0; j < In.width; j++) {
			In.data[i][j] = 0;
			if (i == j) {
				In.data[i][j] = 1;
			}
		}
	}

	_matrix = Argument_Matrix(matrix, In);

	temp = RREF(_matrix);
	Free_Matrix(&_matrix);
	_matrix = temp;

	for (int i = 0; i < In.height; i++) {
		for (int j = matrix.width; j < _matrix.width; j++) {
			In.data[i][j - matrix.width] = _matrix.data[i][j];
		}
	}

	return In;
}

void Free_Matrix(Matrix *matrix) {
	free(matrix->data);
}

void Print_Matrix(Matrix matrix) {
	for (int i = 0; i < matrix.height; i++) {
		for (int j = 0; j < matrix.width; j++) {
			printf("%lf ", matrix.data[i][j]);
		}
		puts("");
	}
}