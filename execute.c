#include "main.h"

/**
 * execute - execute commands
 * @cmdv: array of commands
 * @cmdc: number of command tokens
 *
 * Return: 0(SUCCESS)
 */
int execute(char **cmdv, size_t *cmdc)
{
	pid_t child_pid;
	int status;

	size_t *unused __attribute__((unused)) = cmdc;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}

	if (child_pid == 0)
	{
		/* this executes within the child process */
		if (execve(cmdv[0], cmdv, environ) == -1)
		{
			perror("Error:");
		}
	}
	else
	{
		/* this executes within the parent process */
		wait(&status);
	}
	return (0);
}
