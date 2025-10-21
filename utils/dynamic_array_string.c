#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct DynamicArrayString {
  char **array;
  int capacity;
  int len;
};

void dynamic_array_string_init(struct DynamicArrayString *arr) {
  arr->capacity = 16;
  arr->len = 0;
  arr->array = (char **)malloc(arr->capacity * sizeof(char *));

  if (!arr->array) {
    perror("allcation of array failed");
    exit(EXIT_FAILURE);
  }
}

static void dynamic_array_string_copy_array(struct DynamicArrayString *arr,
                                            char **new_array) {
  for (int i = 0; i < arr->len; i++) {
    new_array[i] = arr->array[i];
  }

  free(arr->array);
  arr->array = new_array;
}

static void dynamic_array_string_resize(struct DynamicArrayString *arr) {
  arr->capacity *= 2;
  char **new_array = (char **)malloc(arr->capacity * sizeof(char *));

  if (!new_array) {
    perror("allcation of array failed");
    exit(EXIT_FAILURE);
  }

  dynamic_array_string_copy_array(arr, new_array);
}

static void dynamic_array_string_resize_down(struct DynamicArrayString *arr) {
  char **new_array = (char **)malloc(arr->len * sizeof(char *));

  if (!new_array) {
    perror("allcation of array failed");
    exit(EXIT_FAILURE);
  }

  arr->capacity = arr->len;
  dynamic_array_string_copy_array(arr, new_array);
}

void dynamic_array_string_push(struct DynamicArrayString *arr, char *str) {
  if (arr->len == arr->capacity) {
    dynamic_array_string_resize(arr);
  }

  arr->array[arr->len] = str;
  arr->len++;
}

char *dynamic_array_string_pop(struct DynamicArrayString *arr) {
  if (arr->len == 0) {
    fprintf(stderr, "underflow error");
    return NULL;
  }

  char *last = arr->array[arr->len - 1];
  arr->len--;

  if (arr->len <= arr->capacity / 2) {
    dynamic_array_string_resize_down(arr);
  }

  return last;
}

int dynamic_array_string_get_capacity(struct DynamicArrayString *arr) {
  return arr->capacity;
}

int dynamic_array_string_get_length(struct DynamicArrayString *arr) {
  return arr->len;
}

char *dynamic_array_string_get_index(struct DynamicArrayString *arr, int index) {
  if (index >= arr->len || index < -arr->len) {
    fprintf(stderr, "out of range");
    return NULL;
  }

  return  index >= 0 ? arr->array[index] : arr->array[arr->len + index];
}

struct DynamicArrayString dynamic_array_string_copy(struct DynamicArrayString arr) {
  struct DynamicArrayString new_dynamic_array_string;
  new_dynamic_array_string.capacity = arr.capacity;
  new_dynamic_array_string.len = arr.len;

  char **new_array = (char **)malloc(arr.capacity * sizeof(char *));
  if (!new_array) {
    fprintf(stderr, "malloc error");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < arr.len; i++) {
    new_array[i] = arr.array[i];
  }

  new_dynamic_array_string.array = new_array;

  return new_dynamic_array_string;
}

void dynamic_array_string_free(struct DynamicArrayString *arr) {
  free(arr->array);
  arr->array = NULL;
  arr->capacity = 0;
  arr->len = 0;
}

