#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
  double *data;
  size_t rows;
  size_t cols;
} Matrix;

Matrix *matrix_init(size_t rows, size_t cols);
void matrix_fill(Matrix *mat, double num);
void matrix_set(Matrix *mat, size_t row, size_t col, double num);
double matrix_get(Matrix *mat, size_t row, size_t col);
void matrix_print(Matrix *mat);
void matrix_free(Matrix *mat);
Matrix *matrix_add(Matrix *mat1, Matrix *mat2);
Matrix *matrix_sub(Matrix *mat1, Matrix *mat2);
Matrix *matrix_scalar_mul(Matrix *mat, double scalar);
Matrix *matrix_scalar_add(Matrix *mat, double num);
Matrix *matrix_transpose(Matrix *mat);
Matrix *matrix_matmul(Matrix *mat1, Matrix *mat2);
double matrix_total_sum(Matrix *mat);
Matrix *matrix_sum(Matrix *mat, size_t axis);
#endif // !MATRIX_H
