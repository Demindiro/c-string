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

	string      h_str;
	string_t    s_str;
	const char *str;
	puts(" === 0: String creation ===");
	puts(" --- 0.0: No length given ---");
	for (size_t i = 0; i < 10; i++) {
		str = get_str();
		h_str = string_create(str);
		PRINT_STR(h_str);
		free(h_str);
	}
	puts(" --- 0.1: Length given ---");
	for (size_t i = 0; i < 10; i++) {
		str = get_str();
		h_str = string_create(str, strlen(str));
		PRINT_STR(h_str);
		free(h_str);
	}
	puts(" --- 0.2: Stack string ---");	
	for (size_t i = 0; i < 10; i++) {
		str = get_str();
		string_create(str, strlen(str), &s_str);
		PRINT_STR(&s_str);
	}

	return 0;
}
