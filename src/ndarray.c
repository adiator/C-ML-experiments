#include "../include/ndarray.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

NDArray *ndarray_init(size_t *shape, size_t dimensions) {
  if (dimensions == 0 || shape == NULL) {
    printf("Invalid dimensions or shape\n");
    return NULL;
  }
  size_t size = 1;
  size_t *shape0 = malloc(dimensions * sizeof(size_t));
  if (!shape0) {
    printf("Failed to allocate memory\n");
    return NULL;
  }
  for (size_t i = 0; i < dimensions; i++) {
    if (shape[i] == 0) {
      printf("Shape cannot be zero\n");
      free(shape0);
      return NULL;
    }
    size *= shape[i];
    shape0[i] = shape[i];
  }

  NDArray *arr = malloc(sizeof(NDArray));
  if (!arr) {
    printf("Failed to allocate NDArray\n");
    free(shape0);
    return NULL;
  }

  double *data = malloc(size * sizeof(double));
  if (!data) {
    printf("Failed to allocate memory for data\n");
    free(arr);
    free(shape0);
    return NULL;
  }

  size_t *strides = malloc(dimensions * sizeof(size_t));
  if (!strides) {
    printf("Failed to allocate memory\n");
    free(shape0);
    free(arr);
    free(data);
    return NULL;
  }

  for (size_t i = 0; i < dimensions; i++) {
    if (i == dimensions - 1) {
      strides[i] = 1;
    } else {
      strides[i] = 1;
      for (size_t j = i + 1; j < dimensions; j++) {
        strides[i] *= shape0[j];
      }
    }
  }

  arr->data = data;
  arr->ndim = dimensions;
  arr->shape = shape0;
  arr->size = size;
  arr->stride = strides;

  return arr;
}

size_t ndarray_offset(NDArray *arr, size_t *indices, size_t nindices) {
  if (!arr) {
    printf("NDArray does not exist\n");
    return SIZE_MAX;
  }

  if (nindices != arr->ndim) {
    printf("Incorect dimension\n");
    return SIZE_MAX;
  }

  if (!indices) {
    printf("Indices do not exist\n");
    return SIZE_MAX;
  }

  size_t index = 0;

  for (size_t i = 0; i < arr->ndim; i++) {
    if (arr->shape[i] <= indices[i]) {
      printf("Indices out of range\n");
      return SIZE_MAX;
    }
    index += indices[i] * arr->stride[i];
  }

  return index;
}

void ndarray_fill(NDArray *arr, double num) {
  if (!arr) {
    printf("NDArray does not exist\n");
    return;
  }

  for (size_t i = 0; i < arr->size; i++) {
    arr->data[i] = num;
  }
}

void ndarray_set(NDArray *arr, size_t *indices, size_t nindices, double num) {
  size_t offset = ndarray_offset(arr, indices, nindices);
  if (offset == SIZE_MAX) {
    return;
  }
  arr->data[offset] = num;
}

double ndarray_get(NDArray *arr, size_t *indices, size_t nindices) {
  size_t offset = ndarray_offset(arr, indices, nindices);
  if (offset == SIZE_MAX) {
    return 0.0;
  }

  return arr->data[offset];
}

void ndarray_free(NDArray *arr) {
  if (!arr) {
    printf("NDArray does not exist\n");
    return;
  }

  free(arr->data);
  free(arr->shape);
  free(arr->stride);
  free(arr);
}
