#include "../include/linreg.h"
#include "../include/array.h"
#include <stdio.h>

double predict(double x, double w, double b) { return w * x + b; }

Array *forward_pass(Array *x_data, double w, double b) {
  if (!x_data) {
    printf("Array does not exist\n");
    return NULL;
  }
  Array *ans = array_scalar_add(array_scalar_mul(x_data, w), b);
  if (!ans) {
    return NULL;
  }

  return ans;
}

int validate_dataset(Array *x, Array *y) {
  if (!x) {
    printf("X data does not exist\n");
    return 1;
  }
  if (!y) {
    printf("X data does not exist\n");
    return 1;
  }
  if (x->length == 0 || y->length == 0) {
    printf("Array length must be greater than 0\n");
    return 1;
  }
  if (x->length != y->length) {
    printf("X and Y array lengths do not match\n");
    return 1;
  }

  return 0;
}

double loss(Array *x, Array *y, double w, double b) {
  validate_dataset(x, y);
  Array *f_pass = forward_pass(x, w, b);
  if (!f_pass) {
    return 0.0;
  }

  Array *loss_arr = array_sub(y, f_pass);
  if (!loss_arr) {
    return 0.0;
  }

  double loss = array_dot(loss_arr, loss_arr);
  double mse = loss / loss_arr->length;

  return mse;
}

double update_w(Array *x, Array *y, double w, double b, double lr) {
  validate_dataset(x, y);
  Array *f_pass = forward_pass(x, w, b);
  if (!f_pass) {
    return 0.0;
  }

  Array *diff = array_sub(f_pass, y);
  if (!diff) {
    return 0.0;
  }
  return w - lr * ((2.0 / diff->length) * (array_dot(diff, x)));
}
double update_b(Array *x, Array *y, double w, double b, double lr) {
  validate_dataset(x, y);
  Array *f_pass = forward_pass(x, w, b);
  if (!f_pass) {
    return 0.0;
  }
  Array *diff = array_sub(f_pass, y);
  if (!diff) {
    return 0.0;
  }
  return b - lr * ((2.0 / diff->length) * (array_sum(diff)));
}
