#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include "./dynamic_array_string.h"

struct DynamicArrayString split_string(char *string, char *delimiter);
char *join_string(struct DynamicArrayString *arr, char *delimiter);

#endif
