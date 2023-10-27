#include "main.h"

#define CMDLEN 1024

/* search for cmds */

/**
 * check_in_path - checks for cmd in path
 * @cmd: command to check for
 * @abs_cmd: found command
 * @env: environment
 *
 * Return: 0 (SUCCESS) | 1 (FAIL)
 */
int check_in_path(char *cmd, char abs_cmd[], char **env)
{
	char *dir = NULL;
	dir_t *path_node;
	dir_t *pathlist = get_path_list(env);

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
 * handle_exit - helper function to execute the exit command
 * @box: container
 * @found: 1 - found Else NOT FOUND
 */
void handle_exit(container_t *box, int *found)
{
	int num;

	*found = 1;
	if (box->cmdv[1] == NULL)
	{
		box->eof = 1;
		return;
	}

	num = atoi(box->cmdv[1]);
	if (num <= 0)
	{
		fprintf(stderr, "./hsh: %d: %s: Illegal number: %s\n", box->nline,
				box->cmdv[0], box->cmdv[1]);
		box->status = 2;
		return;
	}

	/* set exit code */
	box->status = num;
	/* EOF (True) */
	box->eof = 1;
}

/**
 * search - looks for commands
 * @box: container
 *
 * Return: 0 (FOUND) else NOT found
 *
 * Description:
 * cmdv: 'cmd' 'arg1' 'arg2' ...
 */
int search(container_t *box)
{
	char abs_cmd[CMDLEN] = {'\0'};
	int found = 0;

	/* 1. command exists and is executable as is */
	if (access(box->cmdv[0], F_OK | X_OK) == 0)
	{
		return (0);
	}
	/* 2. command is executable in the path */
	else if (check_in_path(box->cmdv[0], abs_cmd, box->env) == 0)
	{
		free(box->cmdv[0]);
		box->cmdv[0] = strdup(abs_cmd);
		return (0);
	}
	/* 3. cammand is special case */
	else
	{
		if (strcmp(box->cmdv[0], "exit") == 0)
			handle_exit(box, &found);
		else if (strcmp(box->cmdv[0], "env") == 0)
			print_env(box, &found);
		else if (strcmp(box->cmdv[0], "setenv") == 0)
			mysetenv(box, &found);
		else if (strcmp(box->cmdv[0], "unsetenv") == 0)
			myunsetenv(box, &found);
		if (found == 1)
			return (1);
	}
	box->status = 127;
	fprintf(stderr, "./hsh: %d: %s: not found\n", box->nline, box->cmdv[0]);
	return (1);
}
