/* FILE MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/file.h"

const char *read_file(char *file)
{
    char *file_content;
    long file_size;

    FILE *rf = fopen(file, "r");
    if(rf == 0) { fprintf(stderr, "FILE NOT EXIST!"); }

    fseek(rf, 0, SEEK_END);
    file_size = ftell(rf);
    fseek(rf, 0, SEEK_SET);

    file_content = (char*) malloc(file_size+1);
    fread(file_content, file_size, 1, rf);

    fclose(rf);
    return file_content;
}

/* MADE BY @hanilr */