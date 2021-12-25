/* PARSER MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/parser.h"
#include "lib/util.h"
#include "lib/command.h"

int parser(const char *str)
{
    int line_of_str = chrepeat(str, 10)+1;

    for(int i = 1; line_of_str+1 > i; i+=1)
    {
        const char *str_temp = (char*) malloc(strlen(get_line(str, i))+1);
        str_temp = get_line(str, i);

        /* STATEMENTS */
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
        if(subinstr(str_temp, "print") == 0)
        {
            /* ERRORS */
            if(subinstr(str_temp, "\"") == 0 && chrepeat(str_temp, 34)%2 != 0) { return 1; }
            if(subinstr(str_temp, "(") != 0 || subinstr(str_temp, ")") != 0) { return 1; }

            int command_pos = lastpos(str_temp, "print");
            int content_line = dislen(str_temp, command_pos, "(", ")");

            char *content = (char*) malloc(content_line+1);
            memset(content, 0, content_line+1);
            for(int i = 0; content_line > i; i+=1) { content[i] = str_temp[command_pos+i+2]; }
            content[content_line+1] = '\0';
            print(content);
        }
    }
    return 0;
}

/* MADE BY @hanilr */