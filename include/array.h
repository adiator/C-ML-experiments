#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct {
  double *data;
  size_t length;
} Array;

Array *array_init(size_t length);
Array *array_zeros(size_t length);
Array *array_ones(size_t length);
Array *array_arange(double start, double stop, double step);
void array_fill(Array *arr, double num);
void array_set(Array *arr, size_t index, double num);
double array_get(Array *arr, size_t index);
void array_print(Array *arr);
void array_free(Array *arr);
Array *array_add(Array *arr1, Array *arr2);
Array *array_sub(Array *arr1, Array *arr2);
Array *array_scalar_mul(Array *arr, double scalar);
Array *array_scalar_add(Array *arr, double scalar);
double array_dot(Array *arr1, Array *arr2);
double array_sum(Array *arr);
double array_mean(Array *arr);
double array_min(Array *arr);
double array_max(Array *arr);
#endif // !NDARRAY_H
