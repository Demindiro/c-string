#include "../include/string.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/*
 * Creations
 */
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
	memcpy(str->buf, a, len);
	str->buf[len] = 0;
	return str;
}

void _string_create_stack(const char *a, size_t len, string_t *str)
{
	str->len = len;
	memcpy(str->buf, a, len);
	str->buf[len] = 0;
}


string _string_copy_nolim(string s)
{
	return string_create(s->buf, s->len);
}

string _string_copy_lim(string s, size_t start, size_t end)
{
	if (end >= s->len || start > end) {
		errno = EINVAL;
		return NULL;
	}
	return string_create(s->buf + start, end - start);
}


/*
 * Other
 */
int string_eq(string s1, string s2)
{
	return s1->len == s2->len && memcmp(s1->buf, s2->buf, s1->len) == 0;
}

