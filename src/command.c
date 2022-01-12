/* COMMANDS MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* DIY LIBRARY */
#include "lib/command.h"
#include "lib/util.h"

int calc(char operation, int x, int y)
{
    switch((int) operation)
    {
        case '+':
            return x+y;
        case '-':
            return x-y;
        case '*':
            return x*y;
        case '/':
            if(x%y == 0) { return x/y; }
            else { return 0; }
    }
}

void print_chars(char *str)
{
    int i = 0;
    while(strlen(str) > i)
    {
        if(str[i] == '\\' && str[i+1] == 'n')
        {
            printf("\n");
            i+=1;
        }
        else if(str[i] == '\\' && str[i+1] == '0') { break; }
        else { printf("%c", str[i]); }
        i+=1;
    }
}

void print(char *raw_str)
{
    if(raw_str[0] == '"' && chrepeat(raw_str, '"')%2 == 0)
    {
        char *str = (char*) malloc(strlen(raw_str)-1);
        int i = 0;
        
        memset(str, 0, strlen(raw_str)-1);
        while(strlen(raw_str)-2 > i)
        {
            str[i] = raw_str[i+1];
            i+=1;
        }
        print_chars(str);
        free(str);
    }
}

void clrscr(void) { printf("\033[2J \033[H"); }

void quit(void) { exit(EXIT_SUCCESS); }

/* MADE BY @hanilr */