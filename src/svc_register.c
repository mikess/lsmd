/*
 * svc_register.c - register, unregister, check register status
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
 * svc_reg_service - register a service
 *
 * @sname	- service name
 * @stype	- service type
 * @status	- status of service
 * @svc_info	- service info
 *
 * TODO: use only ssvc_s structure for exchanging data
 */
int svc_reg_service(char *sname, char *stype, int status, ssvc_s servinfo)
{
	
}

int svc_unreg_service(char *sname, char *stype);
