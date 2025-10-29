#ifndef DYNAMIC_ARRAY_STRING_H
#define DYNAMIC_ARRAY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A dynamic array of C strings.
 *
 * - Automatically resizes on push/pop.
 * - Performs **shallow copy** for elements.
 * - Caller is responsible for `malloc`/`strdup` before push.
 * - Use `dynamic_array_string_free()` to release all memory.
 */
struct DynamicArrayString {
  char **array;
  int capacity;
  int len;
};

/* ===== Public API (alphabetical order) ===== */

struct DynamicArrayString
dynamic_array_string_copy(struct DynamicArrayString arr);
void dynamic_array_string_free(struct DynamicArrayString *arr);
int dynamic_array_string_get_capacity(struct DynamicArrayString *arr);
char *dynamic_array_string_get_index(struct DynamicArrayString *arr, int index);
int dynamic_array_string_get_length(struct DynamicArrayString *arr);
void dynamic_array_string_init(struct DynamicArrayString *arr);
char *dynamic_array_string_pop(struct DynamicArrayString *arr);
void dynamic_array_string_push(struct DynamicArrayString *arr, char *str);

#endif // DYNAMIC_ARRAY_STRING_H
