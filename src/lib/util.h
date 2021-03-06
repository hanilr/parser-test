/* UTIL HEADER FILE */

#ifndef _UTIL_H
#define _UTIL_H

int chrepeat(const char *str, char ascii); /* REPEAT TIMES OF A CHARACTER IN A STRING */

int dislen(const char *str, int first_pos, char *chr1, char *chr2); /* DISTANCE TWO CHARACTER IN A STRING */

int subinstr(const char *str, char *chr); /* CHECK SUBSTRING IF IN THE STRING */

int lastpos(const char *str, char *chr); /* LAST POSITION OF A WORD IN A STRING */

int lastpos_line(const char *str, char *chr, int line); /* LIKE 'lastpos' BUT YOU CAN GET LINES */

#endif /* MADE BY @hanilr */