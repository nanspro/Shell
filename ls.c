#include "ls.h"
// execution of ls command
int ls (char** args) {
	
	DIR *curDir;
	struct dirent* info_archivo;
	struct stat fileStat;
	
	char fullpath[256];
	
	int detail = 0,hidden = 1,name = 0;

	for (int i = 1; i < 1024; ++i){
		
		if (args[i] == NULL){
			break;
		}
		if (strcmp(args[i], "-l") == 0 ){
			detail = 1;
		}
		else if (strcmp(args[i], "-a") == 0 ){
			hidden = 0;
		}
		else if ( strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0 ){
			hidden = 0;
			detail = 1;
		}
		else{
			name = i;
		}
	}


	if (name == 0){
		name = 1;
		args[1] = ".";
	}

	curDir = opendir(args[name]);

	if (curDir == NULL){
		perror("Error in opening dir");
		exit(-1);
	}

	while ((info_archivo = readdir(curDir)) != 0) {
		if (hidden && info_archivo->d_name[0] == '.'){
			continue;
		} 
		
		strcpy (fullpath, args[name]);
		
		strcat (fullpath, "/");
		
		strcat (fullpath, info_archivo->d_name);

		if (detail){
			if (!stat(fullpath, &fileStat)) {
				printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
				printf("\t%d\t",(int) fileStat.st_nlink);
			}
			else{
				perror("Error in stat");
			}
		}

		printf ("%s ", info_archivo->d_name);

		printf("\n");

	}
	closedir(curDir);
}
