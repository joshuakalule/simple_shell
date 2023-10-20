#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

/* input.c */
char **tokenize(size_t *cmdc, char *line);
char **get_user_input(size_t *cmdc);

/* parser.c */
int parse(char **argv, size_t *cmdc);

/* search.c */
int search(char **cmdv, size_t *cmdc);

/* execute.c */
int execute(char **cmdv, size_t *cmdc);

/* utilities.c */
void free_array(char **array, size_t *narray);
int check(char, char *);
char **split(size_t *arraylen, char *line, char *delim);

#endif /* _MAIN_H_ */
