#include "read-split.h"
// read the input 
char *shell_input(void){
		int bufsize = R_BUFSIZE;
		int position = 0;
		char *buffer = malloc(sizeof(char) * bufsize);
		int c;

		if (!buffer) {
			fprintf(stderr, "memory allocation error\n");
			exit(EXIT_FAILURE);
		}

		while (1) {
    // Read a character
			c = getchar();

			if (c == EOF) {
				exit(EXIT_SUCCESS);
			} else if (c == '\n') {
				buffer[position] = '\0';
				return buffer;
			} else {
				buffer[position] = c;
			}
			position++;

    // If we have exceeded the buffer, reallocate.
			if (position >= bufsize) {
				bufsize += R_BUFSIZE;
				buffer = realloc(buffer, bufsize);
				if (!buffer) {
					fprintf(stderr, "memory allocation error\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
//tokenize the readed input and converting it to args
char **shell_split(char *line)
{
	int bufsize = TOK_BUFSIZE, pos = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_bk;

	if (!tokens) {
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL) {
		tokens[pos] = token;
		pos++;

		if (pos >= bufsize) {
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				free(tokens_bk);
				fprintf(stderr, "memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[pos] = NULL;
	return tokens;
}
