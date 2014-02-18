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


char *Name = NULL;
char *Depends = NULL;
char *ExecPath = NULL;
char *ExecParams = NULL;
char *PIDFile = NULL;
char *Owner = NULL;
char *Group = NULL;


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
int parse_config(char var[100], char val[500], int line)
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
		printf("OK\n");
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
	unsigned int _size = 0;
	char* buffer = 0;
	char var[100], val[500];
	int res=0, line=1;

	if(stat(svconfig,&fcheck) != 0)
		return -EFAULT;

	FILE* fd = fopen(svconfig, "rt");

	if(!fd){
		printf("Cannot open %s for read!\n", svconfig);
		return -EFAULT;
	}

	/*
	 * Get lines count
	 */
	fseek(fd, 0, SEEK_END);
	_size = ftell(fd);
	fseek(fd,0,0);
	
	/*
	 * Allocate memory for buffer
	 */
	buffer = (char*) malloc(sizeof(char)*(_size +1));

	fread(buffer, sizeof(char), _size, fd);
	buffer[_size] = '\0';
	fclose(fd); 
	fd = 0;

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

int main()
{
	ExecPath = (char*)malloc(sizeof(ExecPath)+100);
	PIDFile = (char*)malloc(sizeof(char*)+100);
	char *t = "test.txt";
	if(svc_read_config(t)){
		printf("ExecPath: %s: %d\n", ExecPath, strlen(ExecPath));
	}
	return 1;
}

