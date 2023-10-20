#include "main.h"

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

