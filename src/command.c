/* COMMANDS MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* DIY LIBRARY */
#include "lib/command.h"
#include "lib/util.h"

void print_chars(char *str)
{
    for(int i = 0; strlen(str) > i; i+=1)
    {
        if(str[i] == '\\' && str[i+1] == 'n')
        {
            printf("\n");
            i+=1;
        }
        else if(str[i] == '\\' && str[i+1] == '0')
        {
            str[i+2] = 0;
            break;
        }
        else { printf("%c", str[i]); }
    }
}

void print(char *raw_str)
{
    if(raw_str[0] == 34 && chrepeat(raw_str, 34)%2 == 0)
    {
        char *str = (char*) malloc(strlen(raw_str)-1);
        memset(str, 0, strlen(raw_str)-1);
        for(int i = 0; strlen(raw_str)-2 > i; i+=1) { str[i] = raw_str[i+1]; }
        print_chars(str);
    }
    else { /* VARIABLE SECTION */ }
}

/* MADE BY @hanilr */