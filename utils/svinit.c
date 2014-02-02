/*
 * svinit.c - Core process to start and stop services.
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


int __init_sv(int argc, char **argv){
	
}

int main(int argc, char **argv)
{
	int ret;
	
	ret = __init_sv(argc, argv);
	
	if(ret > 0){
		printf("Failed to initialize SV process!\n");
		exit(-EFAULT);
	}
	
	
}
