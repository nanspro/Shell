#include "echo.h"
// Echo command function
int echo(char **args)
{
	int i;
	for(i=1; args[i]!=NULL; ++i)
	{
		printf("%s ",args[i]);
	}
	printf("\n");
	return 1;
}
