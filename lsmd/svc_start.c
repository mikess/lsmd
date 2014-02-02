/*
 * svc_start.c	- start services and instances functions
 *
 * Copyright (C) 2013 Michal Kulling <mike@mikes.pl>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <getopt.h>
#include <pwd.h>

#define SVC_TYPE_APP	1
#define SVC_TYPE_NET	2
#define SVC_TYPE_SYS	3
#define SVC_TYPE_MGMT	4

typedef struct sinst_s {
        int sid;
        char *name;
        char *ipath;
        char *fpid;
        char *fsock;
        char *factivator;
} svc_inst;


typedef struct ssvc_t{
	int sid;
	int type;
	char *sname;
	struct sinst_s *instances[10];
	char *activatod; // Not used
	char *pidfile;
	char *execpath;
	uid_t owner;
	gid_t group;
	char depends[64];
	int actions[];
} svc_first;

/*
 * svc_start_service - start a service and instances
 *
 * @service - struct with service information
 */
int svc_start_service(struct ssvc_t service)
{
	
	return 1;
}



int main(int argc, char **argv)
{
	printf("svcstart\n");
	return 0;
}
