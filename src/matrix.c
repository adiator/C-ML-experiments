#include "../include/matrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *matrix_init(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    printf("Rows and cols must be greater than 0\n");
    return NULL;
  }
  Matrix *mat = malloc(sizeof(Matrix));
  if (!mat) {
    printf("Failed to allocate matrix\n");
    return NULL;
  }

  double *data = malloc(rows * cols * sizeof(double));
  if (!data) {
    printf("Failed to allocate memory for data\n");
    free(mat);
    return NULL;
  }

  mat->data = data;
  mat->rows = rows;
  mat->cols = cols;

  return mat;
}

void matrix_fill(Matrix *mat, double num) {
  if (!mat) {
    printf("FILL: Matrix doesn't exist\n");
    return;
  }

  size_t length = mat->rows * mat->cols;

  for (size_t i = 0; i < length; i++) {
    mat->data[i] = num;
  }
}

void matrix_set(Matrix *mat, size_t row, size_t col, double num) {
  if (!mat) {
    printf("SET: Matrix doesn't exist\n");
    return;
  }
  if (row >= mat->rows || col >= mat->cols) {
    printf("SET: Invalid index\n");
    return;
  }

  size_t index = row * mat->cols + col;

  mat->data[index] = num;
}

double matrix_get(Matrix *mat, size_t row, size_t col) {

  if (!mat) {
    printf("GET: Matrix doesn't exist\n");
    return 0.0;
  }
  if (row >= mat->rows || col >= mat->cols) {
    printf("GET: Invalid index\n");
    return 0.0;
  }

  size_t index = row * mat->cols + col;
  return mat->data[index];
}

void matrix_print(Matrix *mat) {
  if (!mat) {
    printf("NULL\n");
    return;
  }

  for (size_t i = 0; i < mat->rows; i++) {
    printf("[");
    for (size_t j = 0; j < mat->cols; j++) {
      if (j == mat->cols - 1) {
        printf("%f", matrix_get(mat, i, j));
      } else {
        printf("%f, ", matrix_get(mat, i, j));
      }
    }
    printf("]\n");
  }
}

void matrix_free(Matrix *mat) {
  if (!mat) {
    return;
  }

  free(mat->data);
  free(mat);
}

Matrix *matrix_add(Matrix *mat1, Matrix *mat2) {
  if (!mat1 || !mat2) {
    printf("ADD: Matrix/Matrices don't exist\n");
    return NULL;
  }

  if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
    printf("ADD: Matrices must be of the same shape\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat1->rows, mat1->cols);
  if (!result) {
    return NULL;
  }

  double num;
  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat1->cols; j++) {
      num = matrix_get(mat1, i, j) + matrix_get(mat2, i, j);
      matrix_set(result, i, j, num);
    }
  }

  return result;
}

Matrix *matrix_sub(Matrix *mat1, Matrix *mat2) {
  if (!mat1 || !mat2) {
    printf("SUB: Matrix/Matrices don't exist\n");
    return NULL;
  }

  if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
    printf("SUB: Matrices must be of the same shape\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat1->rows, mat1->cols);
  if (!result) {
    return NULL;
  }

  double num;
  for (size_t i = 0; i < mat1->rows; i++) {
    for (size_t j = 0; j < mat1->cols; j++) {
      num = matrix_get(mat1, i, j) - matrix_get(mat2, i, j);
      matrix_set(result, i, j, num);
    }
  }

  return result;
}
Matrix *matrix_scalar_mul(Matrix *mat, double scalar) {
  if (!mat) {
    printf("SCALARMUL: Matrix/Matrices don't exist\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat->rows, mat->cols);
  if (!result) {
    return NULL;
  }

  double num;
  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      num = matrix_get(mat, i, j) * scalar;
      matrix_set(result, i, j, num);
    }
  }

  return result;
}

Matrix *matrix_scalar_add(Matrix *mat, double num) {
  if (!mat) {
    printf("SCALARADD: Matrix/Matrices don't exist\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat->rows, mat->cols);
  if (!result) {
    return NULL;
  }
  double value;
  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      value = matrix_get(mat, i, j) + num;
      matrix_set(result, i, j, value);
    }
  }

  return result;
}

Matrix *matrix_transpose(Matrix *mat) {
  if (!mat) {
    printf("TRANSPOSE: Matrix don't exist\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat->cols, mat->rows);
  if (!result) {
    return NULL;
  }

  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      result->data[j * result->cols + i] = mat->data[i * mat->cols + j];
    }
  }

  return result;
}

Matrix *matrix_matmul(Matrix *mat1, Matrix *mat2) {
  if (!mat1 || !mat2) {
    printf("MATMUL: Matrix/Matrices don't exist\n");
    return NULL;
  }

  if (mat1->cols != mat2->rows) {
    printf("MATMUL: Matrix shapes incompatible\n");
    return NULL;
  }

  Matrix *result = matrix_init(mat1->rows, mat2->cols);
  if (!result) {
    return NULL;
  }

  double sum;
  for (size_t m1row = 0; m1row < mat1->rows; m1row++) {
    for (size_t m2col = 0; m2col < mat2->cols; m2col++) {
      sum = 0.0;
      for (size_t i = 0; i < mat1->cols; i++) {
        sum += mat1->data[m1row * mat1->cols + i] *
               mat2->data[mat2->cols * i + m2col];
      }
      result->data[m1row * result->cols + m2col] = sum;
    }
  }

  return result;
}

double matrix_total_sum(Matrix *mat) {
  if (!mat) {
    printf("TOTALSUM: Matrix don't exist\n");
    return 0.0;
  }

  Matrix *ans = matrix_init(mat->rows, 1);
  if (!ans) {
    return 0.0;
  }
  double sum = 0.0;
  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      sum += matrix_get(mat, i, j);
    }
  }
  return sum;
}

Matrix *matrix_sum(Matrix *mat, size_t axis) {
  if (!mat) {
    printf("SUM: Matrix don't exist\n");
    return NULL;
  }
  Matrix *ans;
  if (axis == 0) {
    ans = matrix_init(1, mat->cols);
  } else {
    ans = matrix_init(mat->rows, 1);
  }
  if (!ans) {
    return NULL;
  }

  if (axis == 0) {
    for (size_t i = 0; i < mat->cols; i++) {
      double sum = 0.0;
      for (size_t j = 0; j < mat->rows; j++) {
        sum += matrix_get(mat, j, i);
      }
      matrix_set(ans, 0, i, sum);
    }

  } else {
    for (size_t i = 0; i < mat->rows; i++) {
      double sum = 0.0;
      for (size_t j = 0; j < mat->cols; j++) {
        sum += matrix_get(mat, i, j);
      }
      matrix_set(ans, i, 0, sum);
    }
  }

  return ans;
}
