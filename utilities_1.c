#include "main.h"

/**
 * check - look for ch within str
 * @ch: char to look for
 * @str: string to look into
 *
 * Return: 0 (SUCCESS) 1(FAIL)
 */
int check(char ch, char *str)
{
	size_t i;

	if (ch == '\0' || !str || *str == '\0')
		return (1);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (ch == str[i])
			return (0);
	}

	return (1);
}


/**
 * free_array - frees a malloced array
 * @array: array
 * @narray: length of the array
 */
void free_array(char **array, size_t *narray)
{
	size_t i;

	if (!array)
		return;

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);
	array = NULL;
	*narray = 0;
}

/**
 * arraydup - make a copy of an array
 * @arr: array
 *
 * Return: new array
 */
char **arraydup(char **arr)
{
	int i;
	size_t len = 0;
	char **new_arr;

	len = lenarr(arr);

	new_arr = malloc(sizeof(*new_arr) * len);
	if (!new_arr)
		return (NULL);

	for (i = 0; arr[i] != NULL; i++)
		new_arr[i] = strdup(arr[i]);

	new_arr[i] = NULL;
	return (new_arr);
}

/**
 * add_token - add the contents of buf as an item into the array
 * @arr: array
 * @narr: pointer to the length of the array
 * @buf: buffer
 * @nb: pointer to the number of characters in the buffer
 *
 * Return: array of tokens
 */
char **add_token(char **arr, size_t *narr, char *buf, size_t *nb)
{
	size_t n = *narr;
	size_t bufsize = *nb;

	/* malloc the pointer to this data */
	if (arr == NULL)
		arr = malloc(sizeof(*arr) * ++n);
	else
		arr = realloc(arr, sizeof(*arr) * ++n);
	if (!arr)
		return (NULL);
	/* malloc space for the data and '\0' */
	arr[n - 1] = malloc(sizeof(char) * bufsize + 1);
	/* copy data to the array */
	memcpy(arr[n - 1], buf, bufsize);
	/* add '\0' */
	arr[n - 1][bufsize] = '\0';
	*narr = n;

	return (arr);
}

/**
 * split - splits a string by the chars in delim into an array
 * @arraylen: pointer to the length of the created array
 * @line: string to split
 * @delim: characters to split at
 *
 * Return: null terminated array of tokens split from line
 */
char **split(size_t *arraylen, char *line, char *delim)
{
	char *buf = NULL, **arr = NULL;
	size_t bufsize = 0, i = 0, n = 0;

	if (!delim || !*delim)
		return (NULL);
	for (;; i++)
	{
		if (check(line[i], delim) == 0 || line[i] == '\0')
		{
			if (buf != NULL)
			{
				arr = add_token(arr, &n, buf, &bufsize);
				if (arr == NULL)
					return (NULL);
				free(buf);
				buf = NULL;
				bufsize = 0;
			}
		}
		else
		{   /* current char not in delim */
			buf = (buf == NULL) ? malloc(++bufsize) : realloc(buf, ++bufsize);
			if (buf == NULL)
				return (NULL);
			buf[bufsize - 1] = line[i];
		}
		if (line[i] == '\0')
			break;
	}
	if (n != 0)
	{
		arr = realloc(arr, sizeof(*arr) * (n + 1));
		if (!arr)
			return (NULL);
		arr[n] = NULL;
	}
	*arraylen = n;
	return (arr);
}
