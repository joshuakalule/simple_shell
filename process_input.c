#include "main.h"

/**
 * free_av - frees the av array
 * @av: pointer to array to free
 */
void free_av(char **av)
{
	size_t i;

	if (!av)
		return;
	for (i = 0; av[i] != NULL; i++)
		free(av[i]);
	free(av);
}

/**
 * line_to_av - generates *argv[]
 * @str: string input from the terminal
 * Return: *argv[]
 */
char **line_to_av(char *str)
{
	char *token, **av;
	char *delims = " \"";
	size_t len, n;

	av = NULL;
	n = 0;
	token = NULL;
	token = strtok(str, delims);
	while (token)
	{
		len = strlen(token);
		if (!av)
			av = malloc(sizeof(av) * 1);
		else
			av = realloc(av, sizeof(av) * (n + 1));
		if (!av)
			return (NULL);
		av[n] = malloc(sizeof(**av) * (len + 1));
		if (!av)
		{
			free_av(av);
			return (NULL);
		}
		memcpy((void *)av[n], (void *)token, len);
		av[n][len] = '\0';
		token = strtok(NULL, delims);
		n++;
	}
	if (!av)
		av = malloc(sizeof(av) * 1);
	else
		av = realloc(av, sizeof(av) * (n + 1));
	if (!av)
	{
		free_av(av);
		return (NULL);
	}
	av[n] = NULL;
	return (av);
}
