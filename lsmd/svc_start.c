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

#include "lsmd.h"

#define SVC_TYPE_APP	1
#define SVC_APP		"applications"
#define SVC_TYPE_NET	2
#define SVC_NET		"network"
#define SVC_TYPE_SYS	3
#define SVC_SYS		"system"
#define SVC_TYPE_MGMT	4
#define SVC_MGMT	"management"
#define SVC_TYPE_USER	5
#define SVC_USER	"user"

static const char *service = "";
static const char *instance = "";

struct sinst_s {
        int sid;
        char *name;
        char *ipath;
        char *fpid;
        char *fsock;
        char *factivator;
} svc_inst;


struct ssvc_t{
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
	int actions[64];
	struct ssvc_t *next;
} svc_first;

/*int svc_register_service(struct)
{
	
}*/

/*
 * svc_start_service - start a service and instances
 *
 * @service - struct with service information
 */
int svc_start_service(const char *service_name, const char *instance)
{
	/*
	 * Looking for services service_name
	 *	
	 * /etc/lsmd/svc.list
	 *	
	 */
	
	char service_path[256];
	service_path[0] = '\0';
	strcat(service_path, SVC_SERVICES);
	strcat(service_path, service_name);

	if(strlen(instance) > 0){
		strcat(service_path, "/");
		strcat(service_path, instance);
	}
	
	printf("path: >%s<\n", service_path);

	DIR *svpath;
	struct dirent *ep;
	svpath = opendir(service_path);

	if(svpath == NULL){
		printf("Service or instance not found.\n");
		return 1;
	}

	return 0;	
}



int main(int argc, char **argv)
{
	if(argc == 1){
		printf("You must give a service name.\nYou can list all available service by 'svclist all'\n");
		exit(1);
	}

	service = argv[1];	

	if(argc > 2){
		instance = argv[2];
	}

	svc_start_service(service,instance);

	return 0;
}









