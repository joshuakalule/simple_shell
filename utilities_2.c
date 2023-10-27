#include "main.h"

/**
 * lenarr - get the length of a NULL terminated array
 * @arr: NULL terminated array
 *
 * Return: size of the array
 */
size_t lenarr(char **arr)
{
	size_t i;

	if (!arr)
		return (0);

	for (i = 0; arr[i] != NULL; i++)
		;

	return (i + 1);
}

/**
 * free_ptr - safe free
 * @ptr: pointer to free
 */
void free_ptr(char *ptr)
{
	if (ptr == NULL)
		return;

	free(ptr);
}

/**
 * cleanup - clear cmdv and reset cmdc
 * @cmdv: array of tokens
 * @cmdc: number of tokens
 */
void cleanup(char **cmdv, size_t *cmdc)
{
	size_t i;

	if (!cmdv || *cmdc == 0)
		return;

	for (i = 0; i < *cmdc; i++)
	{
		free(cmdv[i]);
	}
	free(cmdv);
	cmdv = NULL;
	*cmdc = 0;
}

/**
 * free_box - free box
 * @box: box
 */
void free_box(container_t *box)
{
	size_t narray = 0;

	if (!box)
		return;
	/* cmdv */
	if (box->cmdv)
		cleanup(box->cmdv, &box->cmdc);

	/* prompt */
	if (box->prompt)
		free(box->prompt);

	/* env */
	if (box->env)
		free_array(box->env, &narray);

	free(box);
}
