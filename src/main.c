/* MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>

/* DIY LIBRARY */
#include "lib/file.h"
#include "lib/util.h"
#include "lib/parser.h"
#include "lib/command.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("\nMISSING ARGUMENT!\n");
        return 1;
    }

    const char *file_content = read_file(argv[1]);
    if(parser(file_content) != 0) { printf("\nPARSER ERROR!\n"); }
    
    return 0;
}

/* MADE BY @hanilr */