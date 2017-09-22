#include "execute.h"
// this function find corresponding function of entered command and executes it.
int shell_execute(char **args)
	{
		int i;
//   char home[101];
// getcwd(home,101);
		if (args[0] == NULL) {
    // An empty command was entered.
			return 1;
		}

		else if(strcmp(args[0],"echo")==0){
			return echo(args);
		}
		else if(strcmp(args[0],"pwd")==0){
			return pwd();
		}
		else if(strcmp(args[0],"cd")==0){
			return cd(args);
		}
		else if(strcmp(args[0],"pinfo")==0){
			return pinfo(args,home);
		}
		else if(strcmp(args[0],"quit")==0){
		//return exit();
		}
		else if(strcmp(args[0],"ls")==0){
			ls(args);
		}

		else {return shell_launch(args);}
	}
