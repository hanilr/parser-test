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

/* MADE BY @hanilr */