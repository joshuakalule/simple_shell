#include "main.h"

#define EXIT_FAIL(a) {\
	free(lineptr);\
	free_a(a, &n);\
	perror(argv[0]);\
	exit(EXIT_FAILURE); }

/**
 * main - entry point of the program
 * @argc: number of arguments passed
 * @argv: array of arguments passed
 * @env: array of evironment variables
 *
 * Return: 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *lineptr;
	size_t n, len;
	char **av;
	int status;
	/*int i;*/
	pid_t child;
	listchar_t *pathlist = makepathlist();

	if (argc != 1)
		exit(EXIT_FAILURE);
	lineptr = NULL;
	av = NULL;
	n = 0;
	while (1)
	{
		if (getline(&lineptr, &n, stdin) == -1)
		{
			if (!isatty(STDIN_FILENO))
				break;
			free(lineptr);
			n = 0;
			continue;
		}
		len = strlen(lineptr);
		if (len > 0 && lineptr[len - 1] == '\n')
			lineptr[len - 1] = '\0';
		if (strncmp("exit", lineptr, 4) == 0)
			break;

		av = line_to_av(lineptr);
		if (!av || !*av)
		{
			free(lineptr);
			n = 0;
			continue;
		}
		/* av[0] may be changed here */
		if (check_in_path(av, pathlist) != 0)
		{
			free_av(av);
			free(lineptr);
			av = NULL;
			n = 0;
			perror(argv[0]);
			continue;
		}
		/**
		*printf("av: ");
		*for (i = 0; av[i] != NULL; i++)
		*	printf("'%s' ", av[i]);
		*printf("\n-----------------------------------------\n");
		*/

		child = fork();
		if (child == 0)
		{
			/*child*/
			if (execve(av[0], av, environ) == -1)
			{
				perror(argv[0]);
				break;
			}
		}
		else
		{
			/*parent*/
			wait(&status);
		}
		free_av(av);
		free(lineptr);
		av = NULL;
		n = 0;
	}
	free_av(av);
	free(lineptr);
	free_list(pathlist);
	return (EXIT_SUCCESS);
}
