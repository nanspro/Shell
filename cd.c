#include "cd.h"
// Change directories 
int cd(char **args) {
	if(args[1]!=NULL)
	{
		if(chdir(args[1]) != 0)
		{
			perror("shell");
		}
	}
	else
	{
		chdir(home);
	}
	return 1;
}	