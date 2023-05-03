#include "main.h"

/**
 * free_list - frees the linked list
 * @head: pointer to list
 */
void free_list(listchar_t *head)
{
	listchar_t *current, *next_node;

	if (!head)
		return;
	current = head;
	while (1)
	{
		next_node = current->next;
		free(current);
		current = next_node;
		if (!current)
			break;
	}
}

/**
 * add_node_end - add node to the end of list
 * @head: address of pointer to list
 * @dir: pointer to directory to add
 *
 * Return: pointer to added node | NULL
 */
listchar_t *add_node_end(listchar_t **head, char *dir)
{
	listchar_t *new, *parent, *tmp;

	new = malloc(sizeof(listchar_t));
	if (!head || !new)
		return (NULL);
	new->dir = dir;
	new->next = NULL;

	parent = NULL;
	tmp = *head;
	while (tmp)
	{
		parent = tmp;
		tmp = tmp->next;
	}
	if (!parent)
		*head = new;
	else
		parent->next = new;
	new->prev = parent;
	return (new);
}

/**
 * add_node - add node to beginning of list
 * @head: address of pointer to list
 * @dir: pointer to directory to add
 *
 * Return: pointer to added node | NULL
 */
listchar_t *add_node(listchar_t **head, char *dir)
{
	listchar_t *new;

	new = malloc(sizeof(listchar_t));
	if (!head || !new)
		return (NULL);
	new->dir = dir;
	new->prev = NULL;
	new->next = *head;
	if (*head)
		(*head)->prev = new;
	*head = new;
	return (new);
}

/**
 * makepathlist - builds a linked list of the PATH directories
 * Return: pointer to list | NULL
 */
listchar_t *makepathlist(void)
{
	char *path, *dir;
	listchar_t *pathlist;
	char *delims = ":";

	pathlist = NULL;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dir = strtok(path, delims);
	while (dir)
	{
		if (add_node_end(&pathlist, dir) == NULL)
			return (NULL);
		dir = strtok(NULL, delims);
	}
	return (pathlist);
}
