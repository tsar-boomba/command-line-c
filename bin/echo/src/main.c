#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @param argc Number of arguments (arg count)
 * @param argv An array of strings (arg value)
*/
int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	char **error = NULL;
	int thousand = strtol("1000", error, 10);

	printf("\nHello World!\n");
}
