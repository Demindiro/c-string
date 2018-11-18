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
	if (end > s->len || start > end) {
		errno = EINVAL;
		return NULL;
	}
	return string_create(s->buf + start, end - start);
}


string string_concat(string *s, size_t c)
{
	size_t l = 0;
	for (size_t i = 0; i < c; i++)
		l += s[i]->len;

	string r = malloc(sizeof(r->len) + l + 1);
	if (r == NULL)
		return NULL;

	size_t o = 0;
	for (size_t i = 0; i < c; i++) {
		memcpy(r->buf + o, s[i]->buf, s[i]->len);
		o += s[i]->len;
	}
	r->buf[o] = 0;

	r->len = l;
	return r;
}



/*
 * Other
 */
int string_eq(string s1, string s2)
{
	return s1->len == s2->len && memcmp(s1->buf, s2->buf, s1->len) == 0;
}


