#include "../include/array.h"
#include <stdio.h>

#include <stddef.h>
#include <stdlib.h>

Array *array_init(size_t length) {
  if (length == 0) {
    printf("Array length must be greater than 0\n");
    return NULL;
  }
  double *data = malloc(length * sizeof(double));
  if (!data) {
    printf("Failed to allocate array data");
    return NULL;
  }

  Array *array = malloc(sizeof(Array));
  if (!array) {
    printf("Failed to allocate NDArray");
    free(data);
    return NULL;
  }
  array->data = data;
  array->length = length;

  return array;
}

Array *array_zeros(size_t length) {
  Array *arr = array_init(length);
  array_fill(arr, 0.0);
  return arr;
}

Array *array_ones(size_t length) {
  Array *arr = array_init(length);
  array_fill(arr, 1.0);
  return arr;
}

Array *array_arange(double start, double stop, double step) {
  if (step == 0.0) {
    printf("Invalid step\n");
    return NULL;
  }
  if ((step > 0.0 && start >= stop) || (step < 0.0 && start <= stop)) {
    printf("Invalid range for given step\n");
    return NULL;
  }

  size_t length = 0;
  double curr = start;

  if (step > 0.0) {
    while (curr < stop) {
      length++;
      curr += step;
    }
  } else {
    while (curr > stop) {
      length++;
      curr += step;
    }
  }
  Array *arr = array_init(length);

  if (!arr) {
    return NULL;
  }
  double num = start;
  for (size_t i = 0; i < length; i++) {
    arr->data[i] = num;
    num += step;
  }

  return arr;
}

void array_fill(Array *arr, double num) {
  if (!arr) {
    return;
  }
  for (size_t i = 0; i < arr->length; i++) {
    arr->data[i] = num;
  }
}

void array_set(Array *arr, size_t index, double num) {
  if (!arr) {
    return;
  }
  if (index < arr->length) {
    arr->data[index] = num;
  } else {
    printf("Memory out of bounds\n");
  }
}

double array_get(Array *arr, size_t index) {
  if (index < arr->length && arr) {
    return arr->data[index];
  } else {
    printf("Memory out of bounds\n");
    return 0.0;
  }
}

void array_print(Array *arr) {
  if (!arr) {
    printf("NULL\n");
    return;
  }
  printf("[");
  for (size_t i = 0; i < arr->length; i++) {
    if (i == arr->length - 1) {
      printf("%f", arr->data[i]);
    } else {
      printf("%f, ", arr->data[i]);
    }
  }
  printf("]\n");
}

void array_free(Array *arr) {
  if (!arr)

    return;
  free(arr->data);
  free(arr);
}

Array *array_add(Array *arr1, Array *arr2) {
  if (!arr1 || !arr2) {
    printf("Array/Arrays doesnt exist\n");
    return NULL;
  }

  if (arr1->length != arr2->length) {
    printf("Arrays must be of same size\n");
    return NULL;
  }

  Array *result = array_init(arr1->length);
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < arr1->length; i++) {
    result->data[i] = arr1->data[i] + arr2->data[i];
  }

  return result;
}

Array *array_sub(Array *arr1, Array *arr2) {
  if (!arr1 || !arr2) {
    printf("Array/Arrays doesnt exist\n");
    return NULL;
  }

  if (arr1->length != arr2->length) {
    printf("Arrays must be of same size\n");
    return NULL;
  }

  Array *result = array_init(arr1->length);
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < arr1->length; i++) {
    result->data[i] = arr1->data[i] - arr2->data[i];
  }

  return result;
}

Array *array_scalar_mul(Array *arr, double scalar) {
  if (!arr) {
    printf("Array/Arrays doesnt exist\n");
    return NULL;
  }
  Array *result = array_init(arr->length);
  if (!result) {
    return NULL;
  }

  for (size_t i = 0; i < arr->length; i++) {
    result->data[i] = scalar * arr->data[i];
  }

  return result;
}

Array *array_scalar_add(Array *arr, double scalar) {
  if (!arr) {
    printf("Array/Arrays doesnt exist\n");
    return NULL;
  }
  Array *result = array_init(arr->length);
  if (!result) {
    return NULL;
  }

  for (size_t i = 0; i < arr->length; i++) {
    result->data[i] = scalar + arr->data[i];
  }

  return result;
}

double array_dot(Array *arr1, Array *arr2) {
  if (!arr1 || !arr2) {
    printf("Array/Arrays doesnt exist\n");
    return 0.0;
  }
  if (arr1->length != arr2->length) {
    printf("Arrays must be of same size\n");
    return 0.0;
  }

  double result = 0.0;

  for (size_t i = 0; i < arr1->length; i++) {
    result += arr1->data[i] * arr2->data[i];
  }

  return result;
}

double array_sum(Array *arr) {
  if (!arr) {
    printf("Array doesnt exist\n");
    return 0.0;
  }
  double result = 0.0;
  for (size_t i = 0; i < arr->length; i++) {
    result += arr->data[i];
  }
  return result;
}

double array_mean(Array *arr) {
  if (!arr) {
    printf("Array doesnt exist\n");
    return 0.0;
  }

  return array_sum(arr) / arr->length;
}

double array_min(Array *arr) {
  if (!arr) {
    printf("Array doesnt exist\n");
    return 0.0;
  }

  double min = arr->data[0];
  for (size_t i = 1; i < arr->length; i++) {
    if (arr->data[i] < min) {
      min = arr->data[i];
    }
  }

  return min;
}

double array_max(Array *arr) {
  if (!arr) {
    printf("Array doesnt exist\n");
    return 0.0;
  }

  double max = arr->data[0];
  for (size_t i = 1; i < arr->length; i++) {
    if (arr->data[i] > max) {
      max = arr->data[i];
    }
  }

  return max;
}
