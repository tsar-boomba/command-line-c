#include <stdio.h>
#include <string.h>
#include "types.h"

/**
 * @param argc Number of arguments (arg count)
 * @param argv An array of strings (arg value)
*/
int main(int argc, char *argv[]) {
	if (argc < 2) {
		fputc('\n', stdout);
		return 0;
	}

	i32 n_flag = !strcmp("-n", argv[1]);

	for (i32 i = n_flag ? 2 : 1; i < argc; i++) {
		printf(i == argc - 1 ? "%s" : "%s ", argv[i]);
	}

	if (!n_flag) {
		fputc('\n', stdout);
	}
}
