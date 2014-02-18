/*
 * reader.c
 * Simple program to read file into a config struct
 * gcc -Wall reader.c -o reader
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define CFG_MAXBUF 2048
#define CFG_DELIM "="
 
struct svc_config_s
{
	char Name[CFG_MAXBUF];
	char Depend[CFG_MAXBUF];
	
	char ExecPath[CFG_MAXBUF];
	char ExecParams[CFG_MAXBUF];

	char PIDFile[CFG_MAXBUF];
	char Owner[CFG_MAXBUF];
	char Group[CFG_MAXBUF];
};

char *_val_map[7] = {
	"Name",
	"Depend",
	"ExecPath",
	"ExecParams",
	"PIDFile",
	"Owner",
	"dupa1"
};

/*
 * __check_config_syntax - check syntax
 *
 * @variable	- variable name
 * @value	- value
 *
 */
 
int __check_config_syntax(char variable[128], char value[CFG_MAXBUF])
{
	int c = strlen(*_val_map);
	printf("C: %d\n", c);
	int i = 0;
	while(i < c){
		printf("...\n");
		if(strncmp(variable, _val_map[i], strlen(_val_map[i]))){
			printf("Eho\n");
		}
		i++;
	}
}

/*
 * lsmd_read_service_conf - Reading service configuration file
 *
 * @path_config	- path to configuration file
 *
 */
struct svc_config_s svc_read_service_conf(char *path_config)
{
	struct svc_config_s configstruct;
	FILE *fconfig = fopen(path_config, "r");

	if (fconfig != NULL){

		char line[CFG_MAXBUF];
		int linenum=0;
		
		while(fgets(line, CFG_MAXBUF+8, fconfig) != NULL)
		{
			char var[128], val[CFG_MAXBUF];
			linenum++;

			if(line[0] == '#' || line[0] == '/') continue;

			if(sscanf(line, "%s = %s", var, val) != 2)
			{
				fprintf(stderr, "Syntax error, line %d\n", linenum);
				continue;
			}
		
			__check_config_syntax(var, val);
		}
		fclose(fconfig);
		return configstruct;	
	}
 
}
 
int main(int argc, char **argv)
{
	svc_read_service_conf("./plik");
	return 0;
}


