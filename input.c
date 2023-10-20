#include "main.h"

/**
 * get_user_input - get input from the user
 * @cmdc: pointer to the number of tokens found in input
 * @eof: pointer to signal for EOF
 *
 * Return: array of tokens found in input
 */
char **get_user_input(size_t *cmdc, int *eof)
{
	char *line = NULL;
	size_t len_line = 0;
	ssize_t nread;
	char **cmdv = NULL;

	size_t *unused1 __attribute__((unused)) = cmdc;

	nread = getline(&line, &len_line, stdin);
	if (nread == -1)
	{
		/* EOF */
		free(line);
		*eof = 1;
		return (NULL);
	}

	/* tokenize the line */
	cmdv = split(cmdc, line, " \n");
	if (cmdv == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (cmdv);
}
