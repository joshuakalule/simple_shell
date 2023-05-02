#include "main.h"

#define EXIT_FAIL {\
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

	if (argc != 1)
		EXIT_FAIL
	lineptr = NULL;
	n = 0;
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		fflush(stdout);
		chars_read = getline(&lineptr, &n, stdin);
		if (chars_read == -1)
			EXIT_FAIL
		av = malloc(sizeof(av));
		if (!av)
			EXIT_FAIL
		av = line_to_av(lineptr);
		child = fork();
		if (child == 0)
		{
			/* temporary */
			if (av[1])
				EXIT_FAIL
			if (execve(av[0], av, env) == -1)
				EXIT_FAIL
		}
		else
		{
			if (wait(&status) == -1)
				EXIT_FAIL
		}
		fflush(stdin);
	}

	free(lineptr);
	return (EXIT_SUCCESS);
}
