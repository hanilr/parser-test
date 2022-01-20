/* MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/file.h"
#include "lib/util.h"
#include "lib/parser.h"
#include "lib/command.h"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Parser-acc v1.0");
        char *com = (char*) malloc(128);
        struct variable var[1];
        while(1)
        {
            printf("\n> ");
            fgets(com, 128, stdin);
            parser(com, var, 0);
            memset(com, 0, 128);
        }
        free(com);
    }
    else if(argc > 2)
    {
        fprintf(stderr, "\nMISSING ARGUMENT!");
        return 1;
    }
    else { file_parser(argv[1]); }
    return 0;
}

/* MADE BY @hanilr */