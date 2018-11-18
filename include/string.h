#ifndef C_STRING_H__
#define C_STRING_H__


#include <stddef.h>


/*
 * Basic string struct.
 * `string_t` is for stack allocation and `string` for heap allocatiob.
 */
typedef struct string {
	size_t len;
	char   buf[];
} string_t, *string;


/*
 * Creates a new string.
 */
string _string_create_nolen(const char *a);
string _string_create_len(const char *a, size_t l);
void _string_create_stack(const char *a, size_t l, string_t *str);
#define _STRING_CREATE(_0,_1,_2,NAME,...) NAME
#define string_create(...) _STRING_CREATE(__VA_ARGS__, _string_create_stack, _string_create_len, _string_create_nolen)(__VA_ARGS__)


/*
 * Copies a string
 */
string _string_copy_nolim(string str);
string _string_copy_lim(string str, size_t start, size_t end);
#define _STRING_COPY(_0, _1, _2, NAME, ...) NAME
#define string_copy(...) _STRING_COPY(__VA_ARGS__, _string_copy_lim, NULL, _string_copy_nolim)(__VA_ARGS__)


/*
 * Concatenates the given strings.
 */
string string_concat(string *strs, size_t count);


/*
 * Checks two strings for equality.
 */
int string_eq(string str1, string str2);


#endif
