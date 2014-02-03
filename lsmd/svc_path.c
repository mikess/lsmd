/*
 * svc_path.c - operation on svc directory
 *
 * Copyright (C) 2014 Michal Kulling <mike@mikes.pl>
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

/*
 * svc_path_init  - create basic directory tree for SVC
 * 
 * @svc_root_path - root directory for SVC
 *
 * TODO: verify owner and group of SVC_ROOT
 */
int svc_root_path_init(char *svc_root_path)
{	
	struct stat svcdir = {0};

	if(stat(svc_root_path, &svcdir) == -1){
		if(mkdir(svc_root_path,0700) < 0){
			printf("Cannot create %s SVC root directory!\n", svc_root_path);
			return -EFAULT;
		}
	}

	return 1;
}

/*
 * svc_path_create_service - create directory tree for service
 *
 * @svc_group	- the name of service group
 * @svc_service - the name of service
 *
 */
int svc_path_create_service(char *svc_group, char *svc_service)
{
	char *service_path = "";
	struct stat svcdir = {0};

	sprintf(service_path, "%s/%s

	strcpy(service_path, SVC_SERVICES);
	strcpy(service_path, svc_group);
	
	if(stat(service_path, &svcdir) == -1){
		printf("%s application group not initialized!\n", service_path);
		return -EFAULT;
	}
	
	
	
}
