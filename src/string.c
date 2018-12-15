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

string *string_split(string str, char delim, size_t *count)
{
	size_t  size   = 256;
	*count  = 0;
	size_t  start  = 0, end = start;
	string *splits = malloc(sizeof(*splits) * size);
	while (1) {
		if (str->buf[end] == delim || end >= str->len) {
			if (*count >= size) {
				size_t ns  = (size * 3) / 2;
				void  *tmp = realloc(splits, sizeof(*splits) * ns);
				if (tmp == NULL) {
					for (size_t i = 0; i < *count; i++)
						free(splits[i]);
					free(splits);
					return NULL;
				}
				splits = tmp;
				size   = ns;
			}
			string s = string_copy(str, start, end);
			if (s == NULL) {
				for (size_t i = 0; i < *count; i++)
					free(splits[i]);
				free(splits);
				return NULL;
			}
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
int _string_eq(const string s1, const string s2)
{
	return s1->len == s2->len && memcmp(s1->buf, s2->buf, s1->len) == 0;
}

int _string_eq_lit(const string s1, const char *s2)
{
	string str = string_create(s2);
	int r = _string_eq(s1, str);
	free(str);
	return r;
}
