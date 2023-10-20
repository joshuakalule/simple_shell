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

/**
 * struct dir_s - linked list of the PATH directories
 * @str: directory str
 * @next: pointer to the next directory
 */
typedef struct dir_s
{
	char *str;
	struct dir_s *next;
} dir_t;

/* input.c */
char **get_user_input(size_t *cmdc, int *eof);

/* parser.c */
int parse(char **argv, size_t *cmdc);

/* search.c */
int search(char **cmdv, size_t *cmdc, int line, int *status, int *eof,
		char **env);

/* execute.c */
int execute(char **cmdv, size_t *cmdc, char **env, int *status);

/* utilities_1.c */
void free_array(char **array, size_t *narray);
int check(char, char *);
char **split(size_t *arraylen, char *line, char *delim);

/* utilities_2.c */
void free_ptr(char *ptr);

/* path.c */
void free_list(dir_t *head);
dir_t *get_path_list(char **env);

/* path_1.c */
char *mygetenv(char *var, char **env);

#endif /* _MAIN_H_ */
