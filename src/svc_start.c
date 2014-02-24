#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>
#include <pwd.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        argc -= optind;
        argv += optind;
	int p = getpid();
	printf("P: %d\n", getpid());
	char *st = "/usr/sbin/sshd";
	*--argv = st;
	execve(st, argv, NULL);	
	printf("P: %d\n", getpid());
}
