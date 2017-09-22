#include "launch.h"
// function to print message after background process exits.
void sigh(int signum)
{
	pid_t wpid;
	int procstatus;
	int status;
	wpid=waitpid(-1,&status,WNOHANG);
	if(wpid>0	&& (WIFEXITED(status)==0))
	{
		printf("Process exited normally\n");

	}
	if(wpid >0 && WIFSIGNALED(status)==0)
	{
		printf("Process exited by user\n");

	}

}
//this is for running processes both foreground and background.
int shell_launch(char **args)
{
	pid_t pid;
	int status;
	int i=0, flag = 0;
	char strpid[15];
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],"&")==0)
		{
			args[i]=NULL;
			flag = 1;
			break;
		}
		i++;
	}

	pid = fork();
	if (pid == 0) {
    // Child process
		if (execvp(args[0], args) == -1) {
			perror("shell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
    // Error forking
		perror("shell");
	} else {
    // Parent process
		if(flag==0){
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		else{
			printf("%s [%d]\n", args[0], pid);
			signal(SIGCHLD, sigh);
		}}

		return 1;
	}
