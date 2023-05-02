#include "main.h"

/**
 * free_a - frees the av array
 * @av: pointer to array to free
 * @n: number of elements in av array
 */
void free_a(char **av, size_t *n)
{
	size_t i;

	if (!av || !*av)
		return;
	for (i = 0; av[i] != NULL; i++)
		free(av[i]);
	free(av);
	av = NULL;
	*n = 0;
}

/**
 * line_to_av - generates *argv[]
 * @str: string input from the terminal
 * @av: array to populate
 * @n: number of elements in av array
 * Return: *argv[]
 */
char **line_to_av(char *str, char **av, size_t *n)
{
	char *word;
	size_t _n, len;
	char *delim = " ";

	_n = 0;
	word = strtok(str, delim);
	while (word)
	{
		len = strlen(word);
		av = realloc(av, sizeof(av) * (_n + 2));
		if (!av)
		{
			free_a(av, n);
			exit(EXIT_FAILURE);
		}

		av[_n] = malloc(sizeof(**av) * (len + 1));
		if (!av[_n])
		{
			free_a(av, n);
			exit(EXIT_FAILURE);
		}

		strncpy(av[_n], word, len);
		if (av[_n][len - 1] == '\n')
			av[_n][len - 1] = '\0';
		word = strtok(NULL, delim);
		_n++;
	}
	av[_n] = NULL;
	return (av);
}
