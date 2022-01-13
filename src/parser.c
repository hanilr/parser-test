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
    if(subinstr(str_temp, "repeat(") == 0 && str_temp[lastpos(str_temp, "repeat")+1] == '(')
    {
        /* REPEAT LOOP SECTION */
        if(subinstr(str_temp, "break()") == 0) { /* break; */ }
    }
    if(subinstr(str_temp, "loop(") == 0 && str_temp[lastpos(str_temp, "loop")+1] == '(')
    {
        /* INFINITE LOOP SECTION */
        if(subinstr(str_temp, "break()") == 0) { /* break; */ }
    }
    if(subinstr(str_temp, "if(") == 0 && str_temp[lastpos(str_temp, "if")+1] == '(')
    {
        /* IF STATEMENT SECTION */
    }
    if(subinstr(str_temp, "ifelse(") == 0 && str_temp[lastpos(str_temp, "ifelse")+1] == '(')
    {
        /* IF ELSE STATEMENT SECTION */
    }

    /* COMMANDS */
    if(str_temp[lastpos(str_temp, "(")] == '(' && (str_temp[lastpos(str_temp, "(")+1] == '+' || str_temp[lastpos(str_temp, "(")+1] == '-' || str_temp[lastpos(str_temp, "(")+1] == '*' || str_temp[lastpos(str_temp, "(")+1] == '/'))
    {
        if(subinstr(str_temp, ")") != 0 || chrepeat(str_temp, ')') > 1 || chrepeat(str_temp, '(') > 1)
        {
            fprintf(stderr, "PARSER ERROR: Uncorrect syntax! (MATH)");
            exit(EXIT_FAILURE);
        }

        int content_line = dislen(str_temp, 0, "(", ")");
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
                if(z == 127) { exit(EXIT_FAILURE); }
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
    free((char*) str_temp);
}

/* MADE BY @hanilr */