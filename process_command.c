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


int check_cmd(char *_cmd)
{
	char *cmd;
	const char *ch = "/";
	int starts_with_ch = 0;

	if (!_cmd)
		return (-1);
	cmd = strdup(_cmd);
	if (cmd[0] == *ch)
		starts_with_ch = 1;
	
	if (strchr(cmd, '.') == NULL && starts_with_ch == 0)
	{
		free(cmd);
		return (1);
	}
	free(cmd);
	if (access(_cmd, F_OK | X_OK) == 0)
		return (0);
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
	int cmd_pass;

	if (!av || !*av)
		return (-1);
	cmd = strdup(av[0]);
	if (!cmd)
		return (-1);
	cmd_pass = check_cmd(cmd);
	if (cmd_pass == 0)
	{
		free(cmd);
		return (0);
	}
	else if (cmd_pass == -1)
	{
		free(cmd);
		return (-1);
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
