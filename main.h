#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* input.c */
char **tokenize(size_t *cmdc, char *line);
char **get_user_input(size_t *cmdc);

/* utilities */
char **cp_av_cmdv(size_t *ndest, char **src, int nsrc);

/* parser */
int parse(char **argv, size_t *cmdc);


#endif /* _MAIN_H_ */
