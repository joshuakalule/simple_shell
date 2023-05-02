#include "main.h"

/**
 * line_to_av - generates *argv[]
 * @str: string input from the terminal
 * Return: *argv[]
 */
char **line_to_av(char *str)
{
	char **av;
	char *word;
	size_t n, len;
	char *delim = " ";

	av = malloc(sizeof(av));
	if (!av)
		exit(EXIT_FAILURE);

	n = 0;
	word = strtok(str, delim);
	while (word)
	{
		len = strlen(word);
		av = realloc(av, sizeof(av) * (n + 2));
		if (!av)
			exit(EXIT_FAILURE);

		av[n] = malloc(sizeof(**av) * (len + 1));
		if (!av[n])
			exit(EXIT_FAILURE);

		strncpy(av[n], word, len);
		if (av[n][len - 1] == '\n')
			av[n][len - 1] = '\0';
		word = strtok(NULL, delim);
		n++;
	}
	av[n] = NULL;
	return (av);
}
