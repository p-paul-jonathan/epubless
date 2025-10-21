#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./dynamic_array_string.h"

struct DynamicArrayString split_string(char *string, char *delimiter) {
  struct DynamicArrayString splits;
  dynamic_array_string_init(&splits);

  char *dup = strdup(string);
  char *token = strtok(dup, delimiter);

  while (token != NULL){
    dynamic_array_string_push(&splits, strdup(token));
    token = strtok(NULL, delimiter);
  }

  free(dup);
  return splits;
}

char *join_string(struct DynamicArrayString *arr, char *delimiter) {
  if (arr->len == 0) {
    char *empty = (char *)malloc(sizeof(char));
    if (!empty) {
      fprintf(stderr, "malloc Error");
      exit(EXIT_FAILURE);
    }
    empty[0] = '\0';
    return empty;
  }

  int total_length = 0;
  for (int i = 0; i < arr->len; i++) { total_length += strlen(arr->array[i]); }
  total_length += strlen(delimiter) * (arr->len - 1);

  char *joined = (char *)malloc(total_length + 1);
  if (!joined) {
    fprintf(stderr, "malloc Error");
    exit(EXIT_FAILURE);
  }

  char *position = joined;
  int delim_len = strlen(delimiter);

  for (int i = 0; i < arr->len; i++) {
    int len = strlen(arr->array[i]);
    memcpy(position, arr->array[i], len);
    position += len;

    if (i != arr->len - 1) {
      memcpy(position, delimiter, delim_len);
      position += delim_len;
    }
  }
  *position = '\0';

  return joined;
}
