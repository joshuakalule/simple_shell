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
 *
 * Return: 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *lineptr;
	size_t n, len, line_no;
	char **av;
	int status, EXIT_STATUS;
	/*int i;*/
	pid_t child;
	listchar_t *pathlist = makepathlist();

	EXIT_STATUS = EXIT_SUCCESS;
	if (argc != 1)
		exit(EXIT_FAILURE);
	lineptr = NULL;
	av = NULL;
	n = 0;
	line_no = 0;
	while (1)
	{
		(!isatty(STDIN_FILENO)) ? (line_no++) : (line_no = line_no);

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
		{
			EXIT_STATUS = 2;
			break;
		}

		av = line_to_av(lineptr);
		if (!av || !*av)
		{
			free(lineptr);
			free_av(av);
			av = NULL;
			n = 0;
			continue;
		}
		/* av[0] may be changed here */
		if (check_in_path(av, pathlist) != 0)
		{
		dprintf(STDERR_FILENO, "%s: %lu: %s: not found\n", argv[0], line_no, av[0]);
			free_av(av);
			free(lineptr);
			av = NULL;
			n = 0;
			EXIT_STATUS = 127;
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
			EXIT_STATUS = EXIT_SUCCESS;
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
	return (EXIT_STATUS);
}
