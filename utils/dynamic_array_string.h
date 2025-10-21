#ifndef DYNAMIC_ARRAY_STRING_H
#define DYNAMIC_ARRAY_STRING_H

// Dynamic array of strings implementation

struct DynamicArrayString {
  char **array;
  int capacity;
  int len;
};

// Initialization and cleanup
void dynamic_array_string_init(struct DynamicArrayString *arr);
void dynamic_array_string_free(struct DynamicArrayString *arr);

// Core operations
void dynamic_array_string_push(struct DynamicArrayString *arr, char *str);
char *dynamic_array_string_pop(struct DynamicArrayString *arr);
struct DynamicArrayString dynamic_array_string_copy(struct DynamicArrayString arr);

// Accessors
char *dynamic_array_string_get_index(struct DynamicArrayString *arr, int index);
int dynamic_array_string_get_length(struct DynamicArrayString *arr);
int dynamic_array_string_get_capacity(struct DynamicArrayString *arr);

#endif // DYNAMIC_ARRAY_STRING_H
