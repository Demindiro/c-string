#include "../include/string.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define PRINT_STR(str) printf("len = %lu, buf = %s\n", (str)->len, (str)->buf)


static const char **strs;
static size_t strs_count;
static size_t strs_index = -1;

static const char *get_str()
{
	strs_index = (strs_index + 1) % strs_count;
	return strs[strs_index];
}



int main(int argc, const char **argv)
{
	if (argc < 2) {
		const char *cmd = argc == 1 ? argv[0] : "test";
		fprintf(stderr, "Usage: %s <strings>\n", cmd);
		return 1;
	}
	strs = argv + 1;
	strs_count = argc - 1;

	puts(" === 0: String creation ===");
	puts(" --- 0.0: No length given ---");
	for (size_t i = 0; i < 10; i++) {
		string str = string_create(get_str());
		PRINT_STR(str);
		free(str);
	}
	puts(" --- 0.1: Length given ---");
	for (size_t i = 0; i < 10; i++) {
		const char *a = get_str();
		string str = string_create(a, strlen(a));
		PRINT_STR(str);
		free(str);
	}
	puts(" --- 0.2: Stack string ---");	
	for (size_t i = 0; i < 10; i++) {
		/* TODO intialize string_t directly */
		const char *a = get_str();
		char buf[sizeof(size_t) + 256];
		string_t *str = (void *)buf;
		string_create(a, strlen(a), str);
		PRINT_STR(str);
	}
	puts(" --- 0.3: string_copy (no limits) ---");
	for (size_t i = 0; i < 10; i++) {
		string str = string_create(get_str());
		string cpy = string_copy(str);
		PRINT_STR(str);
		PRINT_STR(cpy);
		free(cpy);
		free(str);
	}
	puts(" --- 0.4: string_copy (limits: 1, str->len - 1) ---");
	for (size_t i = 0; i < 10; i++) {
		string str = string_create(get_str());
		string cpy = string_copy(str, 1, str->len - 1);
		PRINT_STR(str);
		PRINT_STR(cpy);
		free(cpy);
		free(str);
	}
	puts(" --- 0.5 string_concat ---");
	for (size_t i = 0; i < 10; i++) {
		string a = string_create(get_str());
		string b = string_create(get_str());
		string c = string_concat(a, b);
		printf("'%s' + '%s' --> '%s' (%lu)\n", a->buf, b->buf, c->buf, c->len);
		free(a);
		free(b);
		free(c);
	}
	puts("");

	puts(" === 1: String comparison === ");
	puts(" --- 1.0: string_eq ---");
	puts(" --- 1.0.1: Same string ---");
	for (size_t i = 0; i < 10; i++) {
		string str = string_create(get_str());
		PRINT_STR(str);
		printf("%d\n", string_eq(str, str));
		free(str);
	}
	puts(" --- 1.0.1: Different string ---");
	for (size_t i = 0; i < 10; i++) {
		string str1 = string_create(get_str());
		string str2 = string_create(get_str());
		PRINT_STR(str1);
		PRINT_STR(str2);
		printf("%d\n", string_eq(str1, str2));
		free(str1);
		free(str2);
	}
	puts("");

	return 0;
}
