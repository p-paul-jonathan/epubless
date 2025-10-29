#include "string_helpers.h"

// ---- Static Helpers (none currently) ----

// ---- Public Functions ----

char *join_string(struct DynamicArrayString *arr, char *delimiter) {
  if (!arr || !delimiter) {
    fprintf(stderr, "join_string: invalid arguments\n");
    exit(EXIT_FAILURE);
  }

  if (arr->len == 0) {
    char *empty = malloc(sizeof(char));
    if (!empty) {
      fprintf(stderr, "join_string: malloc error\n");
      exit(EXIT_FAILURE);
    }
    empty[0] = '\0';
    return empty;
  }

  size_t delimiter_len = strlen(delimiter);
  size_t total_length = 0;

  for (int i = 0; i < arr->len; i++) {
    total_length += strlen(arr->array[i]);
  }
  total_length += delimiter_len * (arr->len - 1);

  char *joined = malloc(total_length + 1);
  if (!joined) {
    fprintf(stderr, "join_string: malloc error\n");
    exit(EXIT_FAILURE);
  }

  char *pos = joined;
  for (int i = 0; i < arr->len; i++) {
    size_t len = strlen(arr->array[i]);
    memcpy(pos, arr->array[i], len);
    pos += len;

    if (i != arr->len - 1) {
      memcpy(pos, delimiter, delimiter_len);
      pos += delimiter_len;
    }
  }
  *pos = '\0';

  return joined;
}

struct DynamicArrayString split_string(char *string, char *delimiter) {
  if (!string || !delimiter) {
    fprintf(stderr, "split_string: invalid arguments\n");
    exit(EXIT_FAILURE);
  }

  struct DynamicArrayString splits;
  dynamic_array_string_init(&splits);

  char *dup = strdup(string);
  if (!dup) {
    fprintf(stderr, "split_string: strdup error\n");
    exit(EXIT_FAILURE);
  }

  char *token = strtok(dup, delimiter);
  while (token != NULL) {
    dynamic_array_string_push(&splits, strdup(token));
    token = strtok(NULL, delimiter);
  }

  free(dup);
  return splits;
}
