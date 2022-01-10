/* PARSER HEADER FILE */

#ifndef _PARSER_H
#define _PARSER_H

struct variable
{
    char name[63];
    char value[2047];
}; /* VARIABLE SECTION */

void calc_parser(char *raw, int arg_count);

void parser(char *file_name);

#endif /* MADE BY @hanilr */