#ifndef _HEADER_H_
#define _HEADER_H_
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#endif /* _HEADER_H_ */

#ifndef _MAIN_H_
#define _MAIN_H_
/**
 * struct listchar_s - doubly linked list of strings
 * @dir: string pointer
 * @prev: previous node
 * @next: next node
 */
typedef struct listchar_s
{
	char *dir;
	struct listchar_s *prev;
	struct listchar_s *next;
} listchar_t;

extern char **environ;
char **line_to_av(char *);
void free_av(char **);
void free_list(listchar_t *);
listchar_t *add_node(listchar_t **, char *);
listchar_t *makepathlist(void);
listchar_t *add_node_end(listchar_t **, char *);
int add_path_to_cmd(char **, char *);
int check_in_path(char **, listchar_t *);
int checklist(listchar_t *head, char *str);
void printenv(void);

#endif /* _MAIN_H_ */
