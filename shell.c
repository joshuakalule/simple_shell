#include "main.h"

#define EXIT_FAIL(a) {\
	if (lineptr)\
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
int main(int argc, char **argv, char **env)
{
	char *lineptr, **av;
	size_t n;
	ssize_t chars_read;
	pid_t child;
	int status;

	av = NULL;
	lineptr = NULL;
	n = 0;
	if (argc != 1)
		EXIT_FAIL(av)
	while (1)
	{
		/*write(STDOUT_FILENO, "($) ", 4);*/
		fflush(stdout);
		chars_read = getline(&lineptr, &n, stdin);
		if (chars_read == -1)
			EXIT_FAIL(av)
		av = malloc(sizeof(av));
		if (!av)
			EXIT_FAIL(av)
		av = line_to_av(lineptr, av, &n);
		child = fork();
		if (child == 0)
		{
			if (av[1])
				EXIT_FAIL(av)
			if (execve(av[0], av, env) == -1)
				EXIT_FAIL(av)
		}
		else
		{
			wait(&status);
			free_a(av, &n);
			free(lineptr);
		}
		fflush(stdin);
	}
	free_a(av, &n);
	free(lineptr);
	return (EXIT_SUCCESS);
}
