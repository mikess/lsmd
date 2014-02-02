/*
 * lsmd.c - Core process to start and stop services.
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

#include <linux/reboot.h>

#include "lsmd.h"
#include "../sysvinit/src/reboot.h"


int __init_sig(void);
int __init_svc(void);
int __check_proc(void);


int 


void do_reboot(void);

/*
 *	__init_sig - initialize signal handlers
 */
int __init_sig(void)
{
	
}

/*
 *	do_reboot - initialize reboot procedure
 */
void do_reboot(void)
{
//	init_reboot(BMAGIC_REBOOT);
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

	if(argc == 1){
		printf("Starting LSMD...");
	}	

	int ret;
	
	ret = __init_svc(argc, argv);
	
	if(ret > 0){
		printf("Failed to initialize SVC process!\n");
		exit(-EFAULT);
	}
	
	
}
