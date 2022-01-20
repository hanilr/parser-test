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
    if(chrepeat(raw, '+') > 1 || chrepeat(raw, '-') > 1 || chrepeat(raw, '*') > 1 || chrepeat(raw, '/') > 1)
    {
        fprintf(stderr, "CALCULATOR PARSER ERROR: Too much operation symbol!");
        exit(EXIT_FAILURE);
    }
    char operation = raw[0];
    int result, x, y;

    int pos_x = lastpos_line(raw, " ", 1);
    int pos_y = lastpos_line(raw, " ", 2);
    x = raw[pos_x+1] - '0';
    y = raw[pos_y+1] - '0';
    result = calc(operation, x, y);

    if(arg_count > 2)
    {
        int i = 2;
        while(arg_count > i+1)
        {
            int pos = lastpos_line(raw, " ", i+1);
            int temp = raw[pos+1] - '0';
            result = calc(operation, result, temp);
            i+=1;
        }
    }
    printf("%d ", result);
}

void file_parser(char *file_name)
{
    const char *whole_file = read_file(file_name);
    int line_of_str = chrepeat(whole_file, '\n')+1, i = 1;
    if(chrepeat(whole_file, '\n') == 0) { line_of_str = 2; } /* IF ONLY ONE LINE IN A FILE */
    
    struct variable var[128];
    var[0].count = 1;

    while(line_of_str+1 > i)
    {
        if(i == line_of_str && whole_file[strlen(whole_file)] == '\0') { break; } /* IF LAST LINE EMPTY */
        const char *str_temp = (char*) malloc(strlen(get_line(file_name, i))+1);
        str_temp = get_line(file_name, i);
        parser((char*) str_temp, var, var[0].count);
        free((char*) str_temp);
        i+=1;
    }
}

void parser(char *str_temp, struct variable *var, int var_count)
{
    /* STATEMENTS */
    if(subinstr(str_temp, "#") == 0) /* COMMENT SECTION */
    {
        int comment_pos = lastpos(str_temp, "#");
        while(strlen(str_temp)+1 > comment_pos)
        {
            str_temp[comment_pos] = '\0';
            comment_pos+=1;
        }
    }
    if(str_temp[0] == '$') /* VARIABLE SECTION */
    {
        if(var_count == 129)
        {
            fprintf(stderr, "PARSER ERROR: Too much variable!");
            exit(EXIT_FAILURE);
        }

        int var_pos = lastpos(str_temp, "$")+1, x = 0, y = 0;
        int content_pos = lastpos(str_temp, "\"")+1;
        char *temp = (char*) malloc(strlen(str_temp)+1);

        while(strlen(str_temp) > x)
        {
            temp[x] = str_temp[var_pos+x];
            if(str_temp[var_pos+x+1] == ' ' || str_temp[var_pos+x+1] == '=')
            {
                temp[x+1] = '\0';
                break;
            }
            x+=1;
        }
        strcpy(var[var_count].name, temp);
        memset(temp, 0, strlen(temp)+1);
        while(strlen(str_temp) > y)
        {
            temp[y] = str_temp[content_pos+y];
            if(str_temp[content_pos+y+1] == '\"')
            {
                temp[y+1] = '\0';
                break;
            }
            y+=1;
        }
        strcpy(var[var_count].value, temp);
        free(temp);
        var[0].count+=1;
    }
    if(subinstr(str_temp, "repeat(") == 0) /* REPEAT LOOP SECTION */
    {
        
        int command_pos = lastpos(str_temp, "repeat("), times;
        int times_line = dislen(str_temp, command_pos, "(", ")");
        int content_pos  = lastpos(str_temp, "{");
        int content_line = dislen(str_temp, content_pos, "{", "}");
        char *content = (char*) malloc(content_line+1);

        int i = 0;
        while(content_line > i)
        {
            content[i] = str_temp[content_pos+i+1];
            i+=1;
        }

        if(times_line == 1) { times = str_temp[command_pos+1] - '0'; }
        else
        {
            times = str_temp[command_pos+1] - '0';
            int i = 1;
            while(times_line > i)
            {
                times = (times * 10) + (str_temp[command_pos+i+1] - '0');
                i+=1;
            }
        }

        while(times > 0)
        {
            parser(content, var, var_count);
            times-=1;
        }
        memset(str_temp, 0, strlen(str_temp)+1);
        free(content);
    }
    if(subinstr(str_temp, "if(") == 0) /* IF STATEMENT SECTION */
    {
        int command_pos = lastpos(str_temp, "if("), times;
        int command_line = dislen(str_temp, command_pos, "(", ")");
        int content_pos  = lastpos(str_temp, "{");
        int content_line = dislen(str_temp, content_pos, "{", "}");
        char *content = (char*) malloc(content_line+1);
        char *command = (char*) malloc(command_line+1);

        int i = 0;
        while(command_line > i)
        {
            command[i] = str_temp[command_pos+i+1];
            i+=1;
        }
        i = 0;
        while(content_line > i)
        {
            content[i] = str_temp[content_pos+i+1];
            i+=1;
        }

        if(subinstr(command, "==") == 0) /* IF EQUAL */
        {
            if(subinstr(command, "$") == 0) /* VARIABLE SECTION */
            {
                int space_pos = lastpos_line(command, " ", 1), var_point;
                int sspace_pos = lastpos_line(command, " ", 2); /* SECOND SPACE */
                char *var_buffer = (char*) malloc(space_pos);
                char *var_equal = (char*) malloc(command_line-(sspace_pos+1)+1);

                i = 0;
                while(space_pos > i+1)
                {
                    var_buffer[i] = command[i+1];
                    i+=1;
                }
                i = 0;
                int equal_line = dislen(command, sspace_pos, " ", ":");
                while(equal_line > i)
                {
                    var_equal[i] = command[sspace_pos+i+1];
                    i+=1;
                }
                i = 0;
                while(127 > i)
                {
                    if(subinstr(var[i].name, var_buffer) == 0)
                    {
                        var_point = i;
                        break;
                    }
                    if(i == 126)
                    {
                        fprintf(stderr, "PARSER ERROR: No variable detected! (IF)");
                        exit(EXIT_FAILURE);
                    }
                    i+=1;
                }
                i = 0;
                if(subinstr(var[var_point].value, var_equal) == 0 && subinstr(content, ",") != 0) { parser(content, var, var_count); } /* TRUE */
                else if(subinstr(var[var_point].value, var_equal) == 0 && subinstr(content, ",") == 0) /* IF ELSE TRUE */
                {
                    int else_pos = lastpos(content, ",");
                    char *content_if = (char*) malloc(else_pos+1);
                    memset(content_if, 0, content_line+1);
                    while(else_pos > i)
                    {
                        content_if[i] = content[i];
                        i+=1;
                    }
                    parser(content_if, var, var_count);
                    free(content_if);
                }
                else /* IF ELSE FALSE */
                {
                    int else_pos = lastpos(content, ",");
                    int else_dis = dislen(content, else_pos, ",", ";");
                    char *content_else = (char*) malloc(else_dis+1);
                    memset(content_else, 0, else_dis+1);
                    while(else_dis > i)
                    {
                        content_else[i] = content[else_pos+i+1];
                        i+=1;
                    }
                    parser(content_else, var, var_count);
                    free(content_else);
                }
                free(var_equal);
                free(var_buffer);
            }
            else { /* NONE VARIABLE SECTION */ }
        }
        else { /* OTHER LOGICAL OPERATIONS */ }
        memset(str_temp, 0, strlen(str_temp)+1);
        free(command);
        free(content);
    }

    /* COMMANDS */
    if(str_temp[lastpos(str_temp, "(")] == '(' && (str_temp[lastpos(str_temp, "(")+1] == '+' || str_temp[lastpos(str_temp, "(")+1] == '-' || str_temp[lastpos(str_temp, "(")+1] == '*' || str_temp[lastpos(str_temp, "(")+1] == '/'))
    {
        if(subinstr(str_temp, ")") != 0)
        {
            fprintf(stderr, "PARSER ERROR: Uncorrect syntax! (MATH)");
            exit(EXIT_FAILURE);
        }

        int content_pos = lastpos(str_temp, "(");
        int content_line = dislen(str_temp, content_pos, "(", ")");
        int arg_count = chrepeat(str_temp, ' '), x = 0;
        if(str_temp[strlen(str_temp)] == ' ') { arg_count-=1; }

        char *content = (char*) malloc(content_line+1);
        while(content_line > x)
        {
            content[x] = str_temp[x+1];
            x+=1;
        }
        calc_parser(content, arg_count);
        free(content);
    } /* MATH */
    if(subinstr(str_temp, "print(") == 0)
    {
        /* ERRORS */
        if(subinstr(str_temp, ")") != 0)
        {
            fprintf(stderr, "PARSER ERROR: Uncorrect syntax! (PRINT)");
            exit(EXIT_FAILURE);
        }

        int command_pos = lastpos(str_temp, "print"), x = 0;
        int content_line = dislen(str_temp, command_pos, "(", ")");

        char *content = (char*) malloc(content_line+1);
        memset(content, 0, content_line+1);
        while(content_line > x)
        {
            content[x] = str_temp[command_pos+x+2];
            x+=1;
        }
        content[content_line+1] = '\0';

        if(subinstr(content, "$") == 0)
        {
            if(subinstr(content, "\"") == 0)
            {
                fprintf(stderr, "PARSER ERROR: Uncorrect syntax! (VARIABLE)");
                exit(EXIT_FAILURE);
            }

            char *var_buffer = (char*) malloc(content_line);
            int var_pos = lastpos(content, "$");
            int var_len = dislen(content, var_pos, "$", "\0");
            int var_point, y = 0, z = 0;

            while(var_len+1 > y)
            {
                var_buffer[y] = content[var_pos+y+1];
                if(y == var_len)
                {
                    var_buffer[y+1] == '\0';
                    break;
                }
                y+=1;
            }
            while(128 > z)
            {
                if(subinstr(var[z].name, var_buffer) == 0)
                {
                    var_point = z;
                    break;
                }
                if(z == 127)
                {
                    fprintf(stderr, "PARSER ERROR: No variable detected! (PRINT)");
                    exit(EXIT_FAILURE);
                }
                z+=1;
            }
            print_chars(var[var_point].value);
            free(var_buffer);
        } /* VARIABLE SECTION */
        else { print(content); }
        free(content);
    } /* PRINT */
    if(subinstr(str_temp, "clrscr()") == 0) { clrscr(); } /* CLEAR SCREEN */
    if(subinstr(str_temp, "quit()") == 0) { quit(); } /* QUIT */
}

/* MADE BY @hanilr */