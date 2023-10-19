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

/* utilities.c */
char **cp_av_cmdv(size_t *ndest, char **src, int nsrc);

/* parser.c */
int parse(char **argv, size_t *cmdc);

/* search.c */
int search(char **cmdv, size_t *cmdc);

/* execute.c */
int execute(char **cmdv, size_t *cmdc);

#endif /* _MAIN_H_ */
