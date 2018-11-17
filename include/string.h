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

#endif
