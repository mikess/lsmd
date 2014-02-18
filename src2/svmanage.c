/*
 * svmanage.c	- manage service and/or instances
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

static const char *service = NULL;
static const char *instance = NULL;

static const char *exec_path = NULL;
static const char *exec_params = NULL;
static const char *pidfile = NULL;

int f_start = 0;
int f_stop = 0;

int exec_pid = -1;

char *errstring;

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

char *__exec_path;
char *__exec_params;


int svc_read_service_cfg(void)
{
	
}


/*
 * svc_exec_service - execute a service
 *
 * @exec_path	- path to executable file
 * @exec_params	- parameters for exec
 *
 * exec_params couldn't be a NULL, if service doesn't need a parameters,
 * exec_params need contains 0 (zero).
 *
 */

pid_t svc_exec_service(char *exec_path, char *exec_params)
{
	struct stat sexec = {0};
	
	if(stat(exec_path, &sexec) == 0){
		execv(exec_path, exec_params);
	}
}

/*
 * svc_start_service - start a service and instances
 *
 * @service_name - service name
 * @instance	 - name of next instance
 */
int svc_start_service(const char *service_name, const char *instance)
{
	char service_path[256];
	service_path[0] = '\0';

	sprintf(service_path, "%s/%s", SVC_SERVICES, service_name);
	
	if(strlen(instance) > 0){
		sprintf(service_path, "%s/%s", service_path, instance);
	}

	printf("%s\n", service_path);
	
	DIR *svpath;
	struct dirent *ep;
	svpath = opendir(service_path);

	if(svpath == NULL){
		printf("Service or instance not found.\n");
		return 1;
	}

	return 0;	
}

void parse_argv(int argc, char * const *argv)
{
	static struct option longopts[] = {
		{ "help",	0, NULL, 'h'},
		{ "service",	1, NULL, 'n'},
		{ "instance",	1, NULL, 'i'},
		{ "version",	0, NULL, 'v'},
		{ "pidfile",	1, NULL, 'p'},
		{ "params", 	1, NULL, 'P'},
		{ "start",	0, NULL, 's'},
		{ "stop",	0, NULL, 'S'}
	};

	int c;

	for(;;;) {
		c = getopt_long(argc, argv, "hnvpPsS:",
				longopts, (int *) 0);

		if ( c == -1)
			break;
		switch(c) {
		case 'h':
			show_help();
			exit(0);
		case 'S':
			f_stop = 1;
			break;
		case 's':
			f_start = 1;
			break;
		case 'n':
			service = optarg;
			break;
		case 'i':
			instance = optarg;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'e':
			exec_path = optarg;
			break;
		case 'P':
			exec_params = optarg;
			break;	
		default:
			show_help();
		}
	}

}

int check_argv(char *arg)
{
	if(!strncmp("start",arg,6))
		f_start = 1;
	
	if(!strncmp("stop",arg,5))
		f_stop = 1;
	
	if(!strncmp("restart",arg,8))
		f_restart = 1;

	if(!strncmp("status",arg,7))
		f_status = 1;
}

void show_help(void)
{
	printf("service - control and manage system services\n",
	       "LSMD v0.1 (C) 2014 Michal Kulling\n",
	       "Usage:\n",
	       "  service [start|stop|restart|status|reload] [service|instance] {-soihHFD}\n");
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc == 1){
		printf("You must give a service name.\nYou can list all available service by 'svclist all'\n");
		exit(1);
	}

	/*
	 * Check short functions start, stop, restart, status
	 */

	if(!strcmp("start", argv[1])) {
		
		if(argc < 2)
			show_help();

		service = argv[2];

		int svc_read = svc_read_service_cfg(service);

		if(svc_read == 1)
			svc_start_service();
		
		/*
		 * If configuration file isn't completed or
		 * syntax error occured
		 */ 
		if(svc_read == -1){
			printf("Configuration file isn't completed or syntax error occured:\n%s", errstring);
			return -EFAULT;
		}

		/*
		 * Service/instance not found
		 */
		if(svc_read == 0){
			printf("%s - Service or instance not found.\n", service);
			return -EFAULT;
		}
	}

	if(!strcmp("stop", argv[1])) {
		if(argc < 2)
			show_help();

		service = argv[2];

		int svc_read = svc_read_service_cfg(service);
		
		if(svc_read)
			svc_stop_service();

		if(!svc_read){
			printf("Cannot stop service \"%s\" daemon.\n", service);
		}
	}

	if(!strcmp("status", argv[1])) {
		if(argc < 2)
			show_help();

			
	}
	parse_argv(argc, argv);
	argc -= optind;
	argv += optind;

	svc_start_service(service,instance);

	return 0;
}


