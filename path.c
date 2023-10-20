#include "main.h"

/* linked list for PATH variable */


/**
 * free_list - frees the path_list linked list
 * @head: pointer to the first node of the list
 */
void free_list(dir_t *head)
{
	dir_t *current, *next;

	if (head == NULL)
		return;

	current = head;
	next = NULL;
	while (1)
	{
		free(current->str);
		next = current->next;
		free(current);
		current = next;

		if (current == NULL)
			break;
	}
}

/**
 * add_node_end - add node to the end of linked list
 * @head: pointer to the first node of the list
 * @dirstr: directory string to add as a node
 *
 * Return: pointer to the added node
 */
dir_t *add_node_end(dir_t **head, char *dirstr)
{
	dir_t *new, *node, *parent;

	if (!head)
		return (NULL);

	new = malloc(sizeof(dir_t));
	if (!new)
		return (NULL);
	new->str = (dirstr) ? strdup(dirstr) : NULL;
	new->next = NULL;

	parent = node = *head;
	while (node != NULL)
	{
		parent = node;
		node = node->next;
	}

	if (parent == NULL)
		*head = new;
	else
		parent->next = new;

	return (new);
}

/**
 * get_path_list - generate a singly linked list of the PATH directories
 *
 * Return: pointer to the first node of the linked list
 */
dir_t *get_path_list()
{
	char *pathstr = getenv("PATH");
	char **path_dirs = NULL;
	dir_t *head = NULL;
	size_t npaths = 0;
	size_t i;
	int status = 0;

	path_dirs = split(&npaths, pathstr, ":", &status);
	if (path_dirs == NULL)
		return (NULL);

	for (i = 0; i < npaths; i++)
		add_node_end(&head, path_dirs[i]);

	free_array(path_dirs, &npaths);
	return (head);
}
