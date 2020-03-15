/**
 * The header file for mylib.c, contains all the methods from mylib.c.
 *
 * @author Kezia Somerville-Petch.
 * @author Yashna Shetty.
 * @author Hayley Sleeman.
 */

#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern int getword(char*, int, FILE*);
extern int find_prime(int x);
extern FILE *open_file(char *filename);
extern void print_help(int ifHelp);

#endif
