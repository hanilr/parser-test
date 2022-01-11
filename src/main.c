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
            if(subinstr(com, "quit()") == 0) { break; }
            else
            {
                FILE *wf = fopen("test/temp", "w");
                fwrite(com, 1, strlen(com), wf);
                fclose(wf);
                parser("test/temp");

                remove("test/temp");
                memset(com, 0, strlen(com)+1);
            }
        }
        free(com);
    }
    else if(argc > 2)
    {
        fprintf(stderr, "MISSING ARGUMENT!");
        return 1;
    }
    else { parser(argv[1]); }
    return 0;
}

/* MADE BY @hanilr */