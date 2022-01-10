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
    if(rf == 0)
    {
        fprintf(stderr, "FILE ERROR: File not exist! (Read File)");
        exit(EXIT_FAILURE);
    }

    fseek(rf, 0, SEEK_END);
    file_size = ftell(rf);
    fseek(rf, 0, SEEK_SET);

    file_content = (char*) malloc(file_size+1);
    fread(file_content, file_size, 1, rf);

    fclose(rf);
    return file_content;
}

const char *get_line(char *file, int line)
{
    int current_line = 0;
    long file_size;

    FILE *gl = fopen(file, "r");
    if(gl == 0)
    {
        fprintf(stderr, "FILE ERROR: File not exist! (Get Line)");
        exit(EXIT_FAILURE);
    }

    fseek(gl, 0, SEEK_END);
    file_size = ftell(gl);
    fseek(gl, 0, SEEK_SET);

    char *str_temp = (char*) malloc(file_size+1);
    while(line > current_line)
    {
        fgets(str_temp, file_size+1, gl);
        current_line+=1;
    }

    fclose(gl);
    return str_temp;
}

/* MADE BY @hanilr */