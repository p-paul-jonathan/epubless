#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array_string.h"

/* ============================================================
 *  Static helper functions
 * ============================================================ */

// Copy existing array contents to a new allocated array
static void dynamic_array_string_copy_array(struct DynamicArrayString *arr,
                                            char **new_array) {
  for (int i = 0; i < arr->len; i++) {
    new_array[i] = arr->array[i];
  }

  free(arr->array);
  arr->array = new_array;
}

// Double array capacity when full
static void dynamic_array_string_resize(struct DynamicArrayString *arr) {
  arr->capacity *= 2;
  char **new_array = (char **)malloc(arr->capacity * sizeof(char *));
  if (!new_array) {
    perror("Allocation failed during resize");
    exit(EXIT_FAILURE);
  }
  dynamic_array_string_copy_array(arr, new_array);
}

// Reduce array capacity when usage is low
static void dynamic_array_string_resize_down(struct DynamicArrayString *arr) {
  if (arr->len == 0) {
    free(arr->array);
    arr->array = NULL;
    arr->capacity = 0;
    return;
  }

  int new_capacity = arr->len;
  char **new_array = (char **)malloc(new_capacity * sizeof(char *));
  if (!new_array) {
    perror("Allocation failed during resize down");
    exit(EXIT_FAILURE);
  }

  arr->capacity = new_capacity;
  dynamic_array_string_copy_array(arr, new_array);
}

/* ============================================================
 *  Public API
 * ============================================================ */

void dynamic_array_string_free(struct DynamicArrayString *arr) {
  if (!arr)
    return;

  for (int i = 0; i < arr->len; i++) {
    free(arr->array[i]);
  }

  free(arr->array);
  arr->array = NULL;
  arr->capacity = 0;
  arr->len = 0;
}

char *dynamic_array_string_get_index(struct DynamicArrayString *arr,
                                     int index) {
  if (!arr || index >= arr->len || index < -arr->len) {
    fprintf(stderr, "Index out of range\n");
    return NULL;
  }

  return index >= 0 ? arr->array[index] : arr->array[arr->len + index];
}

int dynamic_array_string_get_capacity(struct DynamicArrayString *arr) {
  return arr ? arr->capacity : 0;
}

int dynamic_array_string_get_length(struct DynamicArrayString *arr) {
  return arr ? arr->len : 0;
}

void dynamic_array_string_init(struct DynamicArrayString *arr) {
  arr->capacity = 16;
  arr->len = 0;
  arr->array = (char **)malloc(arr->capacity * sizeof(char *));
  if (!arr->array) {
    perror("Allocation failed during initialization");
    exit(EXIT_FAILURE);
  }
}

void dynamic_array_string_push(struct DynamicArrayString *arr, char *str) {
  if (!arr || !str) {
    fprintf(stderr, "Push error: invalid argument\n");
    return;
  }

  if (arr->len == arr->capacity) {
    dynamic_array_string_resize(arr);
  }

  arr->array[arr->len++] = str;
}

char *dynamic_array_string_pop(struct DynamicArrayString *arr) {
  if (!arr || arr->len == 0) {
    fprintf(stderr, "Underflow error: array is empty\n");
    return NULL;
  }

  char *last = arr->array[arr->len - 1];
  arr->len--;

  if (arr->len > 0 && arr->len < arr->capacity / 4) {
    dynamic_array_string_resize_down(arr);
  }

  return last;
}

struct DynamicArrayString
dynamic_array_string_copy(struct DynamicArrayString arr) {
  struct DynamicArrayString new_arr;
  new_arr.capacity = arr.capacity;
  new_arr.len = arr.len;

  char **new_array = (char **)malloc(arr.capacity * sizeof(char *));
  if (!new_array) {
    perror("Allocation failed during copy");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < arr.len; i++) {
    new_array[i] = arr.array[i]; // Shallow copy
  }

  new_arr.array = new_array;
  return new_arr;
}
