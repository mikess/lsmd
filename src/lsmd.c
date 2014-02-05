/*
 * lsmd.c - Core process to start and stop services.
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

#include <linux/reboot.h>

#include "lsmd.h"
#include "../sysvinit/src/reboot.h"

char runlevel = "S";

int __init_sig(void);
int __init_svc(void);
int __check_proc(void);

void do_reboot(void);
void sigcatch(int signo);

void lsmd_signal_handler(int signum);
void lsmd_signal_all(int signum);


/*
 * lsmd_signal_handler - UNIX signal handler
 *
 * @signum	- signal number
 *
 */

void lsmd_signal_handler(int signum)
{
	switch(signum){
		case SIGINT :
			fprintf(stderr, "Receive SIGING signal... Sending SIGINT to all SVC service\n");
			lsmd_signal_all(signum);
			break;
		case SIGILL :
			fprintf(stderr, "Receive SIGING signal... Sending SIGILL to all SVC service\n");
			lsmd_signal_all(signum);
			break;
		default:
			fprintf(stderr, "Bad signal\n"); 	
	}
}

void lsmdd_signal_all(int signum){
	if(
}

/*
 *	__init_sig - initialize signal handlers
 */
int __init_sig(void)
{
	signal(SIGINT, lsmd_signal_handler);
	signal(SIGILL, lsmd_signal_handler);
	signal(SIGTERM, lsmd_signal_handler);
	signal(SIGABRT, lsmd_signal_handler);

	/*
	 * Sending SIGUSR1 to lsmdd start
	 * restarting all services from
	 * current runlevel
	 */
	signal(SIGUSR1, lsmd_signal_all);
}

/*
 *	do_reboot - initialize reboot procedure
 */
void do_reboot(void)
{
	sleep(10);
	sync();
	reboot(LINUX_REBOOT_CMD_RESTART);
}

/*
 * 	__check_proc - check /proc is mount
 *
 * TODO: check process 1
 *
 */
int __check_proc(void)
{
	DIR *procdir;
	procdir = opendir(PROCDIR);
	if(!procdir) return 1;
	closedir(procdir);
}


/*
 *	__init_svc - initialize SVC process
 *
 */
int __init_svc(int argc, char **argv)
{
	if(__check_proc()){
		printf("Unable to open /proc directory! /proc is mounted? Rebooting... ");
		do_reboot();
	}

	
}

int main(int argc, char **argv)
{
	printf("Linux Service Management Daemon v0.1\n");
	char *p;
	if ((p = strrchr(argv[0], '/')) != NULL)
		p++;
	else
		p = argv[0];

	/*
	 * Check privileges
	 */
	if (geteuid() != 0) {
		fprintf(stderr, "%s: must be superuser.\n", p);
		exit(1);
	}

	if(argc < 2){
		dprintf(stderr, "I can't determine current runlevel.\nRun: lsmdd [123456]\n");
		exit(1);
	}	

	int ret;
	
	ret = __init_svc(argc, argv);
	
	if(ret > 0){
		printf("Failed to initialize SVC process!\n");
		exit(-EFAULT);
	}
	
	
}
