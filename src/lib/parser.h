/* PARSER HEADER FILE */

#ifndef _PARSER_H
#define _PARSER_H

struct variable
{
    char name[63];
    char value[2047];
    int count;
}; /* VARIABLE SECTION */

void calc_parser(char *raw, int arg_count);

void file_parser(char *file_name);

void parser(char *str_temp, struct variable *var, int var_count);

#endif /* MADE BY @hanilr */