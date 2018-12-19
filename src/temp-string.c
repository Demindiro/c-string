#include "temp-cstring.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "temp-alloc.h"


/*
 * Creations
 */
string _temp_string_create_nolen(const char *a)
{
	return _temp_string_create_len(a, strlen(a));
}

string _temp_string_create_len(const char *a, size_t len)
{
	string str = temp_alloc(sizeof(size_t) + len + 1);
	if (str == NULL)
		return NULL;
	str->len = len;
	memcpy(str->buf, a, len);
	str->buf[len] = 0;
	return str;
}


string _temp_string_copy_nolim(string s)
{
	return temp_string_create(s->buf, s->len);
}

string _temp_string_copy_lim(string s, size_t start, size_t end)
{
	if (end > s->len || start > end) {
		errno = EINVAL;
		return NULL;
	}
	return temp_string_create(s->buf + start, end - start);
}


string temp_string_concat(string *s, size_t c)
{
	size_t l = 0;
	for (size_t i = 0; i < c; i++)
		l += s[i]->len;

	string r = temp_alloc(sizeof(r->len) + l + 1);
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

string *temp_string_split(string str, char delim, size_t *count)
{
	size_t  size   = 1024;
	*count  = 0;
	size_t  start  = 0, end = start;
	string *splits = temp_alloc(sizeof(*splits) * size);
	while (1) {
		if (str->buf[end] == delim || end >= str->len) {
			if (*count >= size) {
				return NULL; // TODO
				size_t ns  = (size * 3) / 2;
				void  *tmp = realloc(splits, sizeof(*splits) * ns);
				if (tmp == NULL)
					return NULL;
				splits = tmp;
				size   = ns;
			}
			string s = temp_string_copy(str, start, end);
			if (s == NULL)
				return NULL;
			splits[(*count)++] = s;
			if (end >= str->len)
				break;
			start = end + 1;
		}
		end++;
	}
	return splits;
}

/*
 * Other
 */
int _temp_string_eq(const string s1, const string s2)
{
	return s1->len == s2->len && memcmp(s1->buf, s2->buf, s1->len) == 0;
}

int _temp_string_eq_lit(const string s1, const char *s2)
{
	string str = temp_string_create(s2);
	int r = _temp_string_eq(s1, str);
	return r;
}
