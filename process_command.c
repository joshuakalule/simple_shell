#include "main.h"

/**
 * add_path_to_cmd - makes full path of cmd using PATH
 * @av: array containing the cmd
 * @new_cmd: command to replace it with
 *
 * Return: 0 (SUCCESS) | -1 (FAIL)
 */
int add_path_to_cmd(char **av, char *new_cmd)
{
	size_t o_len, n_len;

	if (!av || !*av || !new_cmd)
		return (-1);

	o_len = strlen(av[0]);
	n_len = strlen(new_cmd);

	/*clear the old string*/
	av[0] = realloc(av[0], n_len + 1);
	if (!av[0])
		return (-1);
	memset((void *)av[0], '\0', o_len);
	memcpy((void *)av[0], (void *)new_cmd, n_len);
	av[0][n_len] = '\0';
	return (0);
}

/**
 * path_in_PATH - checks if the path of a cmd is in PATH
 * @_cmd: command
 * @head: path linked list
 *
 * Description:
 * e.g cmd = '/usr/bin/ls'
 * checks if '/usr/bin' is in PATH
 *
 * Return: 0 (FOUND) | -1 (NOT FOUND)
 */
int path_in_PATH(char *_cmd, listchar_t *head)
{
	char ch = '/';
	char *token, *tmp;
	char path[1024] = "\0";
	char *cmd = strdup(_cmd);

	if (!cmd || !head)
	{
		free(cmd);
		return (-1);
	}
	if (strchr(cmd, ch) == NULL)
	{
		free(cmd);
		return (-1);
	}

	token = NULL;
	token = strtok(cmd, &ch);
	while (token)
	{
		tmp = strtok(NULL, &ch);
		if (tmp == NULL)
			break;
		if (path[0] != '\0')
			strcat(path, "/");
		else
			path[0] = '/';
		strcat(path, token);
		token = tmp;
	}

	/*printf("path: %s\n", path);*/
	if (checklist(head, path) == 0)
	{
		free(cmd);
		return (0);
	}
	free(cmd);
	return (-1);
}

/**
 * check_in_path - check if the instruction can be executed
 * @av: array containing the instruction chucks
 * @head: path linked list
 *
 * Return: 0  (Can be executed)
 *         -1 (Not found)
 */
int check_in_path(char **av, listchar_t *head)
{
	char *cmd, *n_cmd;
	size_t c_len, o_len, n_len;
	listchar_t *tmp;

	if (!av || !*av)
		return (-1);
	cmd = strdup(av[0]);
	if (!cmd)
		return (-1);
	if ((path_in_PATH(cmd, head) == 0) && (access(cmd, F_OK | X_OK) == 0))
	{
		free(cmd);
		return (0);
	}
	tmp = head;
	c_len = strlen(cmd);
	o_len = c_len;
	n_cmd = strdup(cmd);
	while (tmp)
	{
		/* 2 for '/' and '\0'*/
		n_len = strlen(tmp->dir) + c_len + 2;
		if (n_len > o_len)
			n_cmd = realloc(n_cmd, n_len);
		if (!n_cmd)
		{
			break;
		}
		memset((void *)n_cmd, '\0', o_len);
		memcpy((void *)n_cmd, (void *)(tmp->dir), strlen(tmp->dir) + 1);
		strcat(n_cmd, "/");
		strcat(n_cmd, cmd);
		if (access(n_cmd, F_OK | X_OK) == 0)
		{
			if (add_path_to_cmd(av, n_cmd) != 0)
				break;
			free(n_cmd);
			free(cmd);
			return (0);
		}
		o_len = n_len;
		tmp = tmp->next;
	}
	free(cmd);
	free(n_cmd);
	return (-1);
}
