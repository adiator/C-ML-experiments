#ifndef LINREG_H
#define LINREG_H
#include "array.h"

Array *forward_pass(Array *x_data, double w, double b);
int validate_dataset(Array *x, Array *y);
double loss(Array *x, Array *y, double w, double b);
double update_w(Array *x, Array *y, double w, double b, double lr);
double update_b(Array *x, Array *y, double w, double b, double lr);
#endif // !LINREG_H
