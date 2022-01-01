/* PARSER MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/parser.h"
#include "lib/file.h"
#include "lib/util.h"
#include "lib/command.h"

void calc_parser(char *raw, int arg_count)
{
    char operation = raw[0];
    int result, x, y;

    int pos_x = lastpos_line(raw, " ", 1);
    int pos_y = lastpos_line(raw, " ", 2);

    if(raw[pos_x+2] != ' ') { /* IF MORE THEN ONE DIGIT SECTION */ }
    if(raw[pos_y+2] != ' ') { /* IF MORE THEN ONE DIGIT SECTION */ }

    x = raw[pos_x+1] - '0';
    y = raw[pos_y+1] - '0';
    result = calc(operation, x, y);

    if(arg_count > 2)
    {
        for(int i = 2; arg_count > i; i+=1)
        {
            int pos = lastpos_line(raw, " ", i+1);
            int temp = raw[pos+1] - '0';
            if(raw[pos+2] != ' ') { /* IF MORE THEN ONE DIGIT SECTION */ }
            result = calc(operation, result, temp);
        }
    }

    printf("%d ", result);
}

int parser(char *file_name)
{
    const char *whole_file = read_file(file_name);
    int line_of_str = chrepeat(whole_file, '\n')+1;
    if(chrepeat(whole_file, '\n') == 0) { line_of_str = 2; } /* IF ONLY ONE LINE IN A FILE */

    for(int i = 1; line_of_str+1 > i; i+=1)
    {
        const char *str_temp = (char*) malloc(strlen(get_line(file_name, i))+1);
        str_temp = get_line(file_name, i);

        /* STATEMENTS */
        if(i == line_of_str && whole_file[strlen(whole_file)] == '\0') { break; } /* IF LAST LINE EMPTY */

        if(subinstr(str_temp, "#") == 0) /* COMMENT SECTION */
        {
            char *temp = (char*) malloc(strlen(str_temp)+1);
            int comment_pos = lastpos(str_temp, "#");
            memset(temp, 0, strlen(temp)+1);

            for(int i = 0; comment_pos-1 > i; i+=1) { temp[i] = str_temp[i]; }
            str_temp = temp;
        }
        if(subinstr(str_temp, "$") == 0) 
        {
            /* VARIABLE SECTION */
        }

        /* COMMANDS */
        if(str_temp[0] == '(' && (subinstr(str_temp, "+") == 0 || subinstr(str_temp, "-") == 0 ||subinstr(str_temp, "*") == 0 ||subinstr(str_temp, "/") == 0))
        {
            if(subinstr(str_temp, "(") != 0 || subinstr(str_temp, ")") != 0) { return 1; }

            int content_line = dislen(str_temp, 0, "(", ")");
            int arg_count = chrepeat(str_temp, ' ');

            if(str_temp[strlen(str_temp)] == ' ') { arg_count-=1; }

            char *content = (char*) malloc(content_line+1);
            for(int i = 0; content_line > i; i+=1) { content[i] = str_temp[i+1]; }
            calc_parser(content, arg_count);
        } /* MATH */
        if(subinstr(str_temp, "print") == 0)
        {
            /* ERRORS */
            if(subinstr(str_temp, "\"") == 0 && chrepeat(str_temp, '"')%2 != 0) { return 1; }
            if(subinstr(str_temp, "(") != 0 || subinstr(str_temp, ")") != 0) { return 1; }

            int command_pos = lastpos(str_temp, "print");
            int content_line = dislen(str_temp, command_pos, "(", ")");

            char *content = (char*) malloc(content_line+1);
            memset(content, 0, content_line+1);
            for(int i = 0; content_line > i; i+=1) { content[i] = str_temp[command_pos+i+2]; }
            content[content_line+1] = '\0';
            print(content);
        } /* PRINT */
        free((char*) str_temp);
    }
    return 0;
}

/* MADE BY @hanilr */