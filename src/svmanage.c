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

static const int valsize = 5000;

int f_start = 0;
int f_stop = 0;


int exec_pid = -1;


/*
 * Define parameters
 */
char *Name = NULL;
char *Depends = NULL;
char *ExecPath = NULL;
char *ExecParams = NULL;
char *PIDFile = NULL;
char *Owner = NULL;
char *Group = NULL;


void show_help(void);

/*
 * parse_config - match variable name and assigne value
 *
 * @var		- variable name
 * @val		- value
 * @line	- which line
 *
 * TODO: do tests for paths
 *
 */
int parse_config(char var[100], char val[valsize], int line)
{
	if(!strcmp(var, "Name")){
		sprintf(Name,"%s", val);
		return 1;
	}else
	if(!strcmp(var, "Depends")){
		sprintf(Depends,"%s", val);
		return 1;
	}else
	if(!strcmp(var, "ExecPath")){
		sprintf(ExecPath,"%s", val);
		/*
		 * Check exists and executable
		 */
		return 1;
	}else
	if(!strcmp(var, "ExecParams")){
		sprintf(ExecParams,"%s", val);
		return 1;
	}else
	if(!strcmp(var, "PIDFile")){
		sprintf(PIDFile,"%s", val);
		return 1;
	}else
	if(!strcmp(var, "Owner")){
		sprintf(Owner,"%s", val);
		/* Verify exists */
		return 1;
	}else
	if(!strcmp(var, "Group")){
		sprintf(Group,"%s", val);
		/* Verify exists */
	}else{
		printf("Error at line #%d - unrecognized variable %s\n", line, var);
		return 0;
	}
	/* */
}

/*
 * svc_read_config - read a configuration file
 *
 * @svconfig 	- path to config file
 *
 */
int svc_read_config(char *svconfig)
{
	struct stat fcheck = {0};
	unsigned int filesize = 0;
	char *buffer = 0;
	char var[100], val[valsize];
	int res=0, line=1;

	if(stat(svconfig,&fcheck) != 0)
		return 0;

	FILE *fd;
	fd = fopen(svconfig, "r");
	
	if(fd < 0){
		printf("Cannot open %s for read!\n", svconfig);
		return 0;
	}

	/*
	 * Get lines count
	 */
	fseek(fd, 0, SEEK_END);
	filesize = ftell(fd);
	fseek(fd,0,0);
	
	/*
	 * Allocate memory for buffer
	 */
	buffer = (char*) malloc(sizeof(char)*(filesize +1));

	fread(buffer, sizeof(char), filesize, fd);
	buffer[filesize] = '\0';
	fclose(fd);

	/*
	 * Read a buffer and verify syntax
	 */
	char const * _buffer = buffer;
	while((res = sscanf(_buffer, "%[^\n=]=%[^\n]", var, val)) > -1) {
		if(res == 2 && var[0] != '#')
		if(!parse_config(var, val, line)){
			exit -1;
		}
		_buffer = strstr(_buffer, "\n")+1;
		line++;
	}
	
	free(buffer);
	return 1;
}

/*int main()
{
	ExecPath = (char*)malloc(sizeof(ExecPath)+valsize);
	PIDFile = (char*)malloc(sizeof(char*)+valsize);
	char *t = "test.txt";
	int ret = svc_read_config(t);
	if(ret != 0){
		printf("ExecPath: %s: %d\n", ExecPath, strlen(ExecPath));
	}
	return 1;
}*/


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

pid_t svc_exec_service(char *exec_path, char **exec_params)
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
 */
int svc_start_service(char *service_name)
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

	for(;;) {
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

void show_help(void)
{
	printf("service - control and manage system services\n",
		"LSMD v0.1 (C) 2014 Michal Kulling\n",
		"Usage:\n",
		"  service [start|stop|restart|status|reload] [service|instance] {-soihHFD}\n\n",
		"\t-e, --exec\t - path to service executable file\n",
		"\t-h, --help\t - show this help\n",
		"\t-i, --instance\t - specify instance name\n",
		"\t-n, --name\t - specify the name of service\n",
		"\t-p, --pidfile\t - specify path to pidfile\n",
		"\t-P, --params\t - specify parameters for service which was include\n",
		"\t-s, --start\t - start service\n",
		"\t-S, --stop\t - stop service\n",
		"\t-v, --version\t - show version of lsmd\n");
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

		int svc_read = svc_read_config(service);

		if(svc_read == 1)
			svc_start_service(service);
		
		/*
		 * If configuration file isn't completed or
		 * syntax error occured
		 */ 
		if(svc_read == -1){
			printf("Configuration file isn't completed or syntax error occured.\n");
			return 1;
		}

		/*
		 * Service/instance not found
		 */
		if(svc_read == 0){
			printf("%s - Service or instance not found.\n", service);
			return 1;
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

	svc_start_service(service);

	return 0;
}

