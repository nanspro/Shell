#include "pwd.h"
int pwd(void) {
	char *dir = malloc(1024*sizeof(char));
	getcwd(dir,1024);
	printf("%s\n",dir);
	free(dir);
}
