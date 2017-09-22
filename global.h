#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <sys/utsname.h>
#include <linux/limits.h>
#include <grp.h>
#include <dirent.h>
// includes all header files required by our shell
char home[101];
#define R_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"