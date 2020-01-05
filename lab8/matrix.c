#include "matrix.h"
#include <stdbool.h>

matrix_t matrix_create(int rows, int cols) { 
  
	matrix_t m = { rows, cols, malloc(sizeof(double) * rows * cols) };

	for (int i = 0; i < (rows * cols); i++) {
		m.elts[i] = 0;
	}

	return m;
	
}

double matrix_get(matrix_t m, int r, int c) { 

	return m.elts[r * m.cols + c];

}

void matrix_set(matrix_t m, int r, int c, double d) { 

	m.elts[r * m.cols + c] = d;
  
}


void matrix_free(matrix_t m) { 

	free(m.elts);
  
}

matrix_t matrix_multiply(matrix_t m1, matrix_t m2) { 
	assert(m1.cols == m2.rows);
	int rows = m1.rows;
	int cols = m2.cols;
	matrix_t res = matrix_create(rows, cols);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			double currentVal = 0;
			for (int k = 0; k < m1.cols; k++) {
				currentVal += matrix_get(m1, r, k) * matrix_get(m2, k, c);
			}

			matrix_set(res, r, c, currentVal);
		}
	}

	return res;
}

matrix_t matrix_transpose(matrix_t m) { 

	matrix_t res = matrix_create(m.cols, m.rows);
	for (int i = 0; i < res.rows; i++) {
		for (int j = 0; j < res.cols; j++) {
			matrix_set(res, i, j, matrix_get(m, j, i));
		}
	}

	return res;
  
}

matrix_t matrix_multiply_transposed(matrix_t m1, matrix_t m2) { 

	int rows = m1.rows;
	int cols = m2.rows;
	matrix_t res = matrix_create(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			double currentVal = 0;
			for (int k = 0; k < m1.cols; k++) {
				currentVal += matrix_get(m1, i, k) * matrix_get(m2, j, k);
			}

			matrix_set(res, i, j, currentVal);
		}
	}
  
	return res;
}

matrix_t matrix_multiply_fast(matrix_t m1, matrix_t m2) { 
	return matrix_multiply_transposed(m1, matrix_transpose(m2));
}

void matrix_print(matrix_t m) { 
  for (int i = 0; i < m.rows; i++) { 
    for (int j = 0; j < m.cols; j++) { 
      printf("%g\t", matrix_get(m, i, j));
    }
    printf("\n");
  }
  printf("\n");
}


