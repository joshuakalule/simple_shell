#include "main.h"

/**
 * tokenize - get tokens from a lineptr
 * @cmdc: pointer to the number of tokens found
 * @line: lineptr
 *
 * Return: array of tokens
 */
char **tokenize(size_t *cmdc, char *line)
{
	char **cmdv;
	char *token = NULL;
	char *delim = " \n";

	if (!line)
		return (NULL);

	cmdv = NULL;
	*cmdc = 1;
	cmdv = malloc(sizeof(*cmdv) * (*cmdc));
	if (!cmdv)
		return (NULL);

	cmdv[0] = strdup("./hsh");
	token = strtok(line, delim);
	while (token != NULL)
	{
		cmdv = realloc(cmdv, sizeof(*cmdv) * (++(*cmdc)));
		if (!cmdv)
			return (NULL);

		cmdv[(*cmdc) - 1] = strdup(token);
		token = strtok(NULL, delim);
	}

	return (cmdv);
}


/**
 * get_user_input - get input from the user
 * @cmdc: pointer to the number of tokens found in input
 *
 * Return: array of tokens found in input
 */
char **get_user_input(size_t *cmdc)
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
		return (NULL);
	}

	/* tokenize the line */
	cmdv = tokenize(cmdc, line);
	free(line);

	return (cmdv);
}
