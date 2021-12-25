/* UTIL MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/util.h"
#include "lib/file.h"
#include "lib/command.h"

int chrepeat(const char *str, int ascii)
{
    int word_buffer = 0;
    for(int i = 0; strlen(str) > i; i+=1) { if(str[i] == ascii) { word_buffer+=1; } }
    return word_buffer;
}

int dislen(const char *str, int pos, char *chr1, char *chr2)
{
    int x = pos, y = pos;

    for(pos; strlen(str) > pos; pos+=1)
    {
        if(str[x] == chr1[0])
        {
            if(str[y] == chr2[0]) { break; }
            else { y+=1; }
        }
        else { x+=1; }
    }
    return y-x-1;
}

int subinstr(const char *str, char *chr)
{
    int word_pos, buffer;
    for(word_pos = 0, buffer = 0; strlen(str) > word_pos; word_pos+=1)
    {
        if(str[word_pos] == chr[buffer]) { buffer+=1; }
        else { buffer = 0; }
        if(strlen(chr) == buffer) { return 0; }
    }
    return 1;
}

int lastpos(const char *str, char *chr)
{
    int word_pos, buffer;

    for(word_pos = 0, buffer = 0; strlen(str) > word_pos; word_pos+=1)
    {
        if(str[word_pos] == chr[buffer]) { buffer+=1; }
        else { buffer = 0; }
        if(strlen(chr) == buffer) { break; }
    }

    return word_pos;
} /* START WITH 0 */

const char *get_line(const char *str, int line)
{
    int x = 0, y = 0, temp_line = 0, lines = chrepeat(str, 10)+1;
    char *str_temp = (char*) malloc(strlen(str)+1);

    memset(str_temp, 0, strlen(str));
    while(lines>temp_line)
    {
        str_temp[x] = str[y];
        if(str[y] == 10 || str[y] == 0)
        {
            temp_line+=1;
            if(temp_line != line)
            {
                memset(str_temp, 0, strlen(str));
                x = -1;
            }
            else
            {
                str_temp[strlen(str_temp)+1] = 0;
                break;
            }
        }
        x+=1;
        y+=1;
    }
    return str_temp;
}

/* MADE BY @hanilr */