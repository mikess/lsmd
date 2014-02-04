/*
 * lsmd_trace.c - tracing, monitoring a service / instance status
 *
 * (C) 2014 Michal Kulling <mike@mikes.pl
 *
 */

#define LSM_PROC_RUN		1
#define LSM_PROC_NOEXIST	0

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <malloc.h>


char *proc_pid;

struct stat stpid;

/*
 * lsmd_process_check  - get process status
 *
 * @pid	- process PID
 */
int lsmd_process_check(pid_t pid)
{
	if(pid == 0){
		return LSM_PROC_RUN;
	}

	proc_pid = malloc(sizeof(char *));
	
	sprintf(proc_pid, "/proc/%d", pid);

	if (stat(proc_pid, &stpid) == -1 && errno == ENOENT) {	
		printf("PID %d doesn't exists!\n", pid);
	}	

	free(proc_pid);
}


