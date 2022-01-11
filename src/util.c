/* UTIL MAIN FILE */

/* STANDARD LIBRARY */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DIY LIBRARY */
#include "lib/util.h"
#include "lib/file.h"
#include "lib/command.h"

int chrepeat(const char *str, char ascii)
{
    int word_buffer = 0, i = 0;
    while(strlen(str) > i)
    {
        if(str[i] == ascii) { word_buffer+=1; }
        i+=1;
    }
    return word_buffer;
}

int dislen(const char *str, int pos, char *chr1, char *chr2)
{
    int x = pos, y = pos;
    while(strlen(str) > pos)
    {
        if(str[x] == chr1[0])
        {
            if(str[y] == chr2[0]) { break; }
            else { y+=1; }
        }
        else { x+=1; }
        pos+=1;
    }
    return y-x-1;
}

int subinstr(const char *str, char *chr)
{
    int word_pos = 0, buffer = 0;
    while(strlen(str) > word_pos)
    {
        if(str[word_pos] == chr[buffer]) { buffer+=1; }
        else { buffer = 0; }
        if(strlen(chr) == buffer) { return 0; }
        word_pos+=1;
    }
    return 1;
}

int lastpos(const char *str, char *chr)
{
    int word_pos = 0, buffer = 0;
    while(strlen(str) > word_pos)
    {
        if(str[word_pos] == chr[buffer]) { buffer+=1; }
        else { buffer = 0; }
        if(strlen(chr) == buffer) { break; }
        word_pos+=1;
    }
    return word_pos;
} /* START WITH 0 */

int lastpos_line(const char *str, char *chr, int line)
{
    int pos = lastpos(str, chr), pos_line, x = 0, y = 0;
    if(line == 1) { return pos; }
    char *temp = (char*) malloc(strlen(str)+1);

    while(line > x)
    {
        while(strlen(str)-pos > y)
        {
            temp[y] = str[pos+y];
            y+=1;
        }
        y = 0;
        pos_line = lastpos(temp, chr);
        pos += pos_line+1;
        x+=1;
    }

    free(temp);
    return pos-1;
}

/* MADE BY @hanilr */