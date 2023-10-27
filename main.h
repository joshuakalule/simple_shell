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


/**
 * struct container_s - structure of all variables
 * @cmdv: array of input arguments
 * @cmdc: number of input args
 * @status: return code of previous execution
 * @eof: End Of File bool 1 - eof 0 - continue
 * @nline: line number in input
 * @env: environment
 * @aliases: alias array
 * @ac: main argc
 * @av: main argv
 * @prompt: prompt string
 */
typedef struct container_s
{
	char **cmdv;
	size_t cmdc;
	int status;
	int eof;
	int nline;
	char **env;
	char **aliases;
	int ac;
	char **av;
	char *prompt;
} container_t;

/* input.c */
char **get_user_input(container_t *box);

/* parser.c */
int parse(container_t *box);

/* search.c */
int search(container_t *box);

/* execute.c */
int execute(container_t *box);

/* utilities_1.c */
void free_array(char **array, size_t *narray);
char **arraydup(char **arr);
int check(char, char *);
char **split(size_t *arraylen, char *line, char *delim);
char **splitn(size_t *arraylen, char *line, char *delim);

/* utilities_2.c */
size_t lenarr(char **arr);
void free_ptr(char *ptr);
void cleanup(char **cmdv, size_t *cmdc);
void free_box(container_t *box);

/* path.c */
void free_list(dir_t *head);
dir_t *get_path_list(char **env);

/* path_1.c */
char *mygetenv(char *var, char **env);

/* env_1.c */
void print_env(container_t *box, int *found);
void mysetenv(container_t *box, int *found);

/* env_2.c */
int varpos(char **env, char *var_key);
void myunsetenv(container_t *box, int *found);

#endif /* _MAIN_H_ */
