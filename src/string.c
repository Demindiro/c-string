#include "../include/string.h"
#include <stdlib.h>
#include <string.h>


string _string_create_nolen(const char *a)
{
	return _string_create_len(a, strlen(a));
}

string _string_create_len(const char *a, size_t len)
{
	string str = malloc(sizeof(size_t) + len + 1);
	if (str == NULL)
		return NULL;
	str->len = len;
	memcpy(str->buf, a, len + 1);
	return str;
}

void _string_create_stack(const char *a, size_t len, string_t *str)
{
	str->len = len;
	memcpy(str->buf, a, len + 1);
}

