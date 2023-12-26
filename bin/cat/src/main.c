#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

usize read_buf_len = 0;
u8 *read_buf = NULL;

void read_stdin(void);

int main(int argc, char* argv[]) {
	i32 start_files = 0;

	// parse args
	for (i32 i = 1; i < argc; i++) {
		i32 arg_len = strlen(argv[i]);

		// Not sure if this can happen
		if (arg_len == 0) continue;

		if (argv[i][0] == '-') {
			// Might be flags or read stdin
			if (arg_len == 1) {
				// Read stdin ('-') is counted as a file
				start_files = i;
				break;
			} else {
				// parse flags
				for (i32 j = 1; j < arg_len; j++) {
					switch (argv[i][j]) {
						case 'b':
							break;
						default:
							printf("Received unknown flag: %c\n", argv[i][j]);
							return 1;
					}
				}
			}
		} else {
			// Files started, no more flags
			start_files = i;
			break;
		}
	}

	read_buf = calloc(1024, sizeof(u8));
	read_buf_len = 1024;

	if (read_buf == NULL) {
		fprintf(stderr, "ERROR: Failed to allocate buffer for reading files.");
		return 1;
	}

	if (start_files == 0) {
		// No files input, use stdin
		read_stdin();
		return 0;
	}

	for (i32 i = start_files; i < argc; i++) {
		i32 file_len = strlen(argv[i]);

		if (file_len == 0) continue;

		if (file_len == 1 && argv[i][0] == '-') {
			// Read stdin to EOF
			read_stdin();
		} else {
			FILE *file = fopen(argv[i], "r");

			if (file == NULL) {
				fprintf(stderr, "Error opening \"%s\": ", argv[i]);
				perror("");
				return 1;
			}

			// zero read buf before use always :D
			memset(read_buf, 0, read_buf_len);

			// Use len - 1 to always leave 0 byte at end
			while (fgets(read_buf, read_buf_len - 1, file) != NULL) {
				if (fputs(read_buf, stdout) == EOF) {
					fprintf(stderr, "Failed to write to stdout: ");
					perror("");
					exit(1);
				};
			}
		}
	}
}

void read_stdin(void) {
	memset(read_buf, 0, read_buf_len);

	while (fgets(read_buf, read_buf_len - 1, stdin) != NULL) {
		if (fputs(read_buf, stdout) == EOF) {
			fprintf(stderr, "Failed to write to stdout: ");
			perror("");
			exit(1);
		};
	}

	if (!feof(stdin)) {
		// An error ocurred because fgets returned null without being at EOF
		perror("Error while reading stdout");
		exit(1);
	}
}
