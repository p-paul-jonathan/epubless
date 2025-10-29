#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array_string.h"

// Splits a string by the given delimiter into a DynamicArrayString.
// Caller is responsible for freeing the resulting array and its contents.
struct DynamicArrayString split_string(char *string, char *delimiter);

// Joins an array of strings into a single string separated by the given
// delimiter. Returns a newly allocated string that must be freed by the caller.
char *join_string(struct DynamicArrayString *arr, char *delimiter);

#endif // STRING_HELPERS_H
