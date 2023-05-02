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

char **line_to_av(char *, char **, size_t *);
void free_a(char **, size_t *);

#endif /* _MAIN_H_ */
