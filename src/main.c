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
        printf("\nParser-acc v1.0");
        char *com = (char*) malloc(128);
        while(1)
        {
            printf("\n> ");
            fgets(com, 128, stdin);
            struct variable var[127];
            int var_count = 0;
            parser(com, var, var_count);
        }
        free(com);
    }
    else if(argc > 2)
    {
        fprintf(stderr, "MISSING ARGUMENT!");
        return 1;
    }
    else { file_parser(argv[1]); }
    return 0;
}

/* MADE BY @hanilr */