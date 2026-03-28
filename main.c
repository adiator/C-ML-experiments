#include "include/matrix.h"
#include "include/nn.h"
#include <stddef.h>
#include <stdio.h>

int main() {
  size_t hidden = 25;
  double lr = 0.01;

  Matrix *x_data = matrix_init(5, 1);
  Matrix *y_data = matrix_init(5, 1);

  for (size_t i = 0; i < 5; i++) {
    matrix_set(x_data, i, 0, i + 1.0);
    matrix_set(y_data, i, 0, (i + 1.0) * (i + 1.0) + 5.0);
  }

  Matrix *w1 = set_param(1, hidden);
  Matrix *b1 = set_param(5, hidden);
  Matrix *w2 = set_param(hidden, 1);
  double b2 = 0.02;

  Matrix *pred = forward_pass(x_data, w1, b1, w2, b2);

  matrix_print(matrix_transpose(pred));
  matrix_print(matrix_transpose(y_data));

  // for (int i = 0; i < 100; i++) {
  w1 = update_w1(x_data, w1, b1, w2, b2, y_data, lr);
  b1 = update_b1(x_data, w1, b1, w2, b2, y_data, lr);
  // w2 = update_w2(x_data, w1, b1, w2, b2, y_data, lr);
  // b2 = update_b2(x_data, w1, b1, w2, b2, y_data, lr);
  // }

  pred = forward_pass(x_data, w1, b1, w2, b2);
  matrix_print(matrix_transpose(pred));
  matrix_free(x_data);
  matrix_free(y_data);
  matrix_free(pred);
}
