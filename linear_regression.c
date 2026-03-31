#include "include/array.h"
#include "include/linreg.h"
#include <stddef.h>
#include <stdio.h>

int main() {
  double w = 0.01;
  double b = 0.05;
  double lr = 0.03;

  Array *x_data = array_init(4);
  Array *y_data = array_init(4);

  for (int i = 0; i < 4; i++) {
    array_set(x_data, i, (i + 1) * 2);
    array_set(y_data, i, (i + 1) * 2 * 3 + 5);
  }

  Array *pred = forward_pass(x_data, w, b);

  array_print(y_data);
  array_print(pred);

  for (int i = 0; i < 300; i++) {
    training_step(x_data, y_data, &w, &b, lr);
  }

  pred = forward_pass(x_data, w, b);

  printf("%f\n", loss(x_data, y_data, w, b));
  array_print(pred);

  array_free(x_data);
  array_free(y_data);
  array_free(pred);
}
