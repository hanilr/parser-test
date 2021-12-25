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
    const char *file_content = read_file(argv[1]);
    if(parser(file_content) != 0) { printf("PARSER ERROR"); }
    
    return 0;
}

/* MADE BY @hanilr */