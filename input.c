#include "main.h"

/**
 * get_user_input - get input from the user
 * @box: container
 *
 * Return: array of tokens found in input
 */
char **get_user_input(container_t *box)
{
	char *line = NULL;
	size_t len_line = 0;
	ssize_t nread;
	char **cmdv = NULL;

	nread = getline(&line, &len_line, stdin);
	if (nread == -1)
	{
		/* EOF */
		free(line);
		box->eof = 1;
		return (NULL);
	}

	/* tokenize the line */
	cmdv = split(&box->cmdc, line, " \n");
	if (cmdv == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (cmdv);
}
