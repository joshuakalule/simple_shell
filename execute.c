#include "main.h"

/**
 * execute - execute commands
 * @box: container
 *
 * Return: 0(SUCCESS)
 */
int execute(container_t *box)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}

	if (child_pid == 0)
	{
		/* this executes within the child process */
		if (execve(box->cmdv[0], box->cmdv, box->env) == -1)
		{
			perror("Error:");
		}
	}
	else
	{
		/* this executes within the parent process */
		wait(&status);
		if (status == 512)
			box->status = 2;
		else
			box->status = 0;
		return (status);
	}
	return (0);
}
