#ifndef NDARRAY_H
#define NDARRAY_H

#include <stddef.h>

typedef struct {
  double *data;
  size_t ndim;
  size_t *shape;
  size_t size;
  size_t *stride;
} NDArray;

NDArray *ndarray_init(size_t *shape, size_t dimensions);
size_t ndarray_offset(NDArray *arr, size_t *indices, size_t nindices);
void ndarray_fill(NDArray *arr, double num);
void ndarray_set(NDArray *arr, size_t *indices, size_t nindices, double num);
double ndarray_get(NDArray *arr, size_t *indices, size_t nindices);
void ndarray_free(NDArray *arr);
#endif // !NDARRAY_H
