#include "main.h"

#define CMDLEN 1024

/* search for cmds */

/**
 * check_in_path - checks for cmd in path
 * @cmd: command to check for
 * @abs_cmd: found command
 *
 * Return: 0 (SUCCESS) | 1 (FAIL)
 */
int check_in_path(char *cmd, char abs_cmd[])
{
	char *dir = NULL;
	dir_t *path_node;
	dir_t *pathlist = get_path_list();

	if (!cmd || !pathlist)
		return (1);

	/* traverse the path_list */
	path_node = pathlist;
	while (path_node != NULL)
	{
		dir = path_node->str;

		/* concat dir, /, and cmd */
		memcpy(abs_cmd, dir, strlen(dir));
		abs_cmd[strlen(dir)] = '/';
		memcpy(abs_cmd + (strlen(dir) + 1), cmd, strlen(cmd));

		/* check if the absolute command exists and is an executable */
		if (access(abs_cmd, F_OK | X_OK) == 0)
		{
			free_list(pathlist);
			return (0);
		}
		/* reset abs_cmd */
		memset(abs_cmd, 0, CMDLEN);
		/* next path directory */
		path_node = path_node->next;
	}
	free_list(pathlist);
	return (1);
}

/**
 * search - looks for commands
 * @cmdv: array of commands
 * @cmdc: number of command tokens
 *
 * Return: 0 (FOUND) else NOT found
 *
 * Description:
 * cmdv: 'cmd' 'arg1' 'arg2' ...
 */
int search(char **cmdv, size_t *cmdc)
{
	char abs_cmd[CMDLEN] = {'\0'};

	size_t *unused1 __attribute__((unused)) = cmdc;

	/**
	 * 1. check if the command exists and is executable as is
	 */
	if (access(cmdv[0], F_OK | X_OK) == 0)
	{
		/* cmd exists and is executable */
		return (0);
	}
	/**
	 * 2. check if the command exists and is executable in the directories
	 * in path
	 */
	else
	{
		if (check_in_path(cmdv[0], abs_cmd) == 0)
		{
			free(cmdv[0]);
			cmdv[0] = strdup(abs_cmd);
			return (0);
		}
	}

	fprintf(stderr, "./hsh: No such file or directory\n");
	return (1);
}
