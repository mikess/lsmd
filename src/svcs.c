#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	pid_t pid = fork(); // create child process

	
	char *e = malloc(sizeof(e));
	char *p = malloc(sizeof(p));
	e = "./d.sh";
	p = "AAAA";
	char *f = malloc(sizeof(f)*2);
	sprintf(f, "%s %s", e, p);
	system(f);
	printf("Youpee!\n");
}
