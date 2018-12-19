#ifndef C_TEMP_STRING_H__
#define C_TEMP_STRING_H__


#include <stddef.h>
#include "cstring.h"


/*
 * Creates a new string.
 */
string _temp_string_create_nolen(const char *a);
string _temp_string_create_len(const char *a, size_t l);
#define _STRING_CREATE(_0,_1,_2,NAME,...) NAME
#define temp_string_create(...) _STRING_CREATE(__VA_ARGS__, _temp_string_create_stack, _temp_string_create_len, _temp_string_create_nolen)(__VA_ARGS__)


/*
 * Copies a string
 */
string _temp_string_copy_nolim(string str);
string _temp_string_copy_lim(string str, size_t start, size_t end);
#define _STRING_COPY(_0, _1, _2, NAME, ...) NAME
#define temp_string_copy(...) _STRING_COPY(__VA_ARGS__, _temp_string_copy_lim, NULL, _temp_string_copy_nolim)(__VA_ARGS__)


/*
 * Concatenates the given strings.
 */
string temp_string_concat(string *strs, size_t count);


/*
 * Splits a string with the given character as delimiter.
 */
string *temp_string_split(const string str, char delim, size_t *count);


#endif
