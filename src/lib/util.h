/* UTIL HEADER FILE */

#ifndef _UTIL_H
#define _UTIL_H

int chrepeat(const char *str, int ascii); /* REPEAT TIMES OF A CHARACTER IN A STRING */

int dislen(const char *str, int first_pos, char *chr1, char *chr2); /* DISTANCE TWO CHARACTER IN A STRING */

int subinstr(const char *str, char *chr); /* CHECK SUBSTRING IF IN THE STRING */

int lastpos(const char *str, char *chr); /* LAST POSITION OF A WORD IN A STRING */

const char *get_line(const char *str, int line); /* GET WHOLE SPECIFIC LINE */

#endif /* MADE BY @hanilr */