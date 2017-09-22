#include "loop.h"
//loop to print name , <username@system_name:curr_dir> in this format
//also read_input,split_input,execute  functions are called in this function
void shell_loop(void){
		struct passwd *pw;
		uid_t uid;
		char hostname[1024];
		char dirpath[1024];

		uid = geteuid (); 
		pw = getpwuid (uid);
		hostname[1023] = '\0';
		gethostname(hostname, 1023);
		char *input,*line;
		char **args;
		int st;
		getcwd(home,101);

		do {
			char pwd[100],show[100]={};
			getcwd(pwd,100);
			int o=0,flag=0,h;
			for(o=0;o<strlen(home);o++){
				if(home[o]!=pwd[o]){
					flag=1;
					break;
				}
			}
			if(strlen(pwd)<strlen(home)){
				flag=1;
			}
			if(strlen(pwd)==strlen(home)){
				flag=2;
			}
			if(flag==2){
				show[0]='~';
			}
			if(flag==0){
				show[0]='~';
				for(h=o;h<strlen(pwd);h++){
					show[h-o+1]=pwd[h];
				//printf("%c",show[h-o+1]);
				}
			}
			else if(flag==1){
				for(h=0;h<strlen(pwd);h++){
					show[h]=pwd[h];
				//printf("%c",show[h]);
				}
			}
			printf("<%s@%s:%s>",pw->pw_name,hostname,show);
			input=shell_input();

			while(input)
			{
				line= strsep(&input,";");

				args = shell_split(line);

				st = shell_execute(args);
			}
			free(input);
			free(args);

		} while (1);

	}