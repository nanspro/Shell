#include "pinfo.h"
char pinfo(char **args, char *home)
{
	char procpath[PATH_MAX+1];
	int count=0;
	int pid; 
	char status; 
	char name[20];
	strcpy(procpath, "/proc/");

	if(args[1])
		strcat(procpath, args[1]);
	else
		strcat(procpath, "self");

	char statpath[PATH_MAX+1];
	strcpy(statpath, procpath);
	strcat(statpath, "/stat");

	FILE *stat = fopen(statpath, "r");
	if(stat == NULL){
		perror("shell");
		return 0;
	}
	char msg[100];
	fscanf(stat, "%d", &pid);
	fscanf(stat, "%s", name);
	fscanf(stat, "%c", &status);

	if(home == NULL){
		return status;
	}

	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "Process Status: %c\n", status);
	fclose(stat);

	strcpy(statpath, procpath); 
	strcat(statpath, "/statm");
	FILE *mem = fopen(statpath, "r");
	if(mem == NULL){
		perror("shell");
		return 0;
	}
	int size;
	fscanf(mem, "%d", &size);
	fprintf(stdout, "Memory: %d\n", size);
	fclose(mem);

	char exepath[PATH_MAX+1];
	strcpy(statpath, procpath);
	strcat(statpath, "/exe");

	readlink(statpath, exepath, sizeof(exepath));
	if(count)
	{
		perror("shell");
	}

	char *ret;

	ret = strstr(exepath, home);
	int baseL = strlen(home);

	char relpath[PATH_MAX+1];
	if(ret!=NULL)
	{
		relpath[0] = '~'; relpath[1] = '\0';
		strcat(relpath, (const char *)&exepath[baseL]);
	}
	else
	{
		strcpy(relpath, exepath);
		relpath[strlen(exepath)] = '\0';
	}

	int i = 0;
	while(exepath[i])
		exepath[i++] = '\0';

	fprintf(stdout, "Executable Path: %s\n", relpath);
	return status;
}