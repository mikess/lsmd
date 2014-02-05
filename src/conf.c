#include <stdio.h>
#include <stdlib.h>

int main(){


char line[256];
int linenum=0;
char *path_config="./plik";
FILE *fconfig = fopen(path_config, "r");

while(fgets(line, 256, fconfig) != NULL)
{
        char var[256], val[256];

        linenum++;
        if(line[0] == '#' || line[0] == '/') continue;
        if(sscanf(line, "%s = %s", var, val) != 2)
        {
                fprintf(stderr, "Syntax error, line %d\n", linenum);
                continue;
        }

        printf("%s=%s\n", var, val);
}
}
