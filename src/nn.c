#include "../include/nn.h"
#include "../include/matrix.h"
#include <stddef.h>
#include <stdio.h>

Matrix *relu(Matrix *mat) {
  if (!mat) {
    printf("Matrix does not exist\n");
    return NULL;
  }
  Matrix *result = matrix_init(mat->rows, mat->cols);
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < mat->rows; i++) {
    for (size_t j = 0; j < mat->cols; j++) {
      if (matrix_get(mat, i, j) < 0) {
        matrix_set(mat, i, j, 0);
      }
    }
  }

  return result;
}

Matrix *set_param(size_t rows, size_t cols) {
  Matrix *mat = matrix_init(rows, cols);
  if (!mat) {
    return NULL;
  }
  matrix_fill(mat, 0.1);
  return mat;
}

int validate_dataset(Matrix *x, Matrix *y) {
  if (!x) {
    printf("X data does not exist\n");
    return 1;
  }
  if (!y) {
    printf("X data does not exist\n");
    return 1;
  }
  if (x->cols == 0 || x->rows == 0 || y->cols == 0 || y->rows == 0) {
    printf("Matrices cannot have 0 rows or columns\n");
    return 1;
  }
  if (x->cols != y->cols || x->rows != y->rows) {
    printf("X and Y matrix shapes do not match\n");
    return 1;
  }
  return 0;
}

Matrix *layer_one(Matrix *x_data, Matrix *w, Matrix *b) {
  if (!x_data) {
    printf("Matrix does not exist\n");
    return NULL;
  }
  if (!w) {
    printf("Matrix does not exist\n");
    return NULL;
  }

  if (!b) {
    printf("Matrix does not exist\n");
    return NULL;
  }

  Matrix *ans = relu(matrix_add(matrix_matmul(x_data, w), b));
  if (!ans) {
    return NULL;
  }

  return ans;
}
Matrix *forward_pass(Matrix *x_data, Matrix *w1, Matrix *b1, Matrix *w2,
                     double b2) {

  if (!x_data) {
    printf("Matrix does not exist\n");
    return NULL;
  }
  if (!w2) {
    printf("Matrix does not exist\n");
    return NULL;
  }

  Matrix *l1 = layer_one(x_data, w1, b1);
  if (!l1) {
    return NULL;
  }

  Matrix *ans = matrix_scalar_add(matrix_matmul(l1, w2), b2);

  if (!ans) {
    return NULL;
  }

  return ans;
}

Matrix *dl_dy(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
              Matrix *y) {
  if (validate_dataset(x, y)) {
    return NULL;
  }

  Matrix *ans = matrix_scalar_mul(
      matrix_sub(forward_pass(x, w1, b1, w2, b2), y), 2.0 / x->cols);

  if (!ans) {
    return NULL;
  }
  return ans;
}

Matrix *dl_dw2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y) {

  if (validate_dataset(x, y)) {
    return NULL;
  }

  Matrix *ans = matrix_matmul(matrix_transpose(layer_one(x, w1, b1)),
                              dl_dy(x, w1, b1, w2, b2, y));
  if (!ans) {
    return NULL;
  }

  return ans;
}

double dl_db2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
              Matrix *y) {
  if (validate_dataset(x, y)) {
    return 0.0;
  }

  return matrix_total_sum(dl_dy(x, w1, b1, w2, b2, y));
}

Matrix *dl_dh(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
              Matrix *y) {
  if (validate_dataset(x, y)) {
    return NULL;
  }

  Matrix *ans =
      matrix_matmul(w2, matrix_transpose(dl_dy(x, w1, b1, w2, b2, y)));
  if (!ans) {
    return NULL;
  }
  Matrix *l1 = matrix_transpose(layer_one(x, w1, b1));
  if (!l1) {
    return NULL;
  }

  for (size_t i = 0; i < l1->rows; i++) {
    for (size_t j = 0; j < l1->cols; j++) {
      if (matrix_get(l1, i, j) == 0.0) {
        matrix_set(ans, i, j, 0.0);
      }
    }
  }

  return ans;
}

Matrix *dl_dw1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y) {
  if (validate_dataset(x, y)) {
    return NULL;
  }
  Matrix *ans = matrix_matmul(matrix_transpose(x),
                              matrix_transpose(dl_dh(x, w1, b1, w2, b2, y)));
  if (!ans) {
    return NULL;
  }

  return ans;
}

Matrix *dl_db1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
               Matrix *y) {
  if (validate_dataset(x, y)) {
    return NULL;
  }

  Matrix *ans = matrix_sum(dl_dh(x, w1, b1, w2, b2, y), 0);

  if (!ans) {
    return NULL;
  }

  return ans;
}

Matrix *update_w1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr) {
  validate_dataset(x, y);

  Matrix *ans =
      matrix_sub(w1, matrix_scalar_mul(dl_dw1(x, w1, b1, w2, b2, y), lr));
  if (!ans) {
    return NULL;
  }

  return ans;
}

Matrix *update_b1(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr) {
  validate_dataset(x, y);

  Matrix *ans =
      matrix_sub(b1, matrix_scalar_mul(dl_db1(x, w1, b1, w2, b2, y), lr));
  if (!ans) {
    return NULL;
  }

  return ans;
}

Matrix *update_w2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                  Matrix *y, double lr) {
  validate_dataset(x, y);

  Matrix *ans =
      matrix_sub(w2, matrix_scalar_mul(dl_dw2(x, w1, b1, w2, b2, y), lr));
  if (!ans) {
    return NULL;
  }

  return ans;
}

double update_b2(Matrix *x, Matrix *w1, Matrix *b1, Matrix *w2, double b2,
                 Matrix *y, double lr) {
  validate_dataset(x, y);

  return b2 - dl_db2(x, w1, b1, w2, b2, y) * lr;
}
