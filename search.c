#include "main.h"

#define CMDLEN 1024

/* search for cmds */

/**
 * print_env - print the environment
 * @env: environment
 */
void print_env(char **env)
{
	size_t i;

	for (i = 0; env[i] != NULL; i++)
		fprintf(stdout, "%s\n", env[i]);
}

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
 * search - looks for commands
 * @cmdv: array of commands
 * @cmdc: number of command tokens
 * @line: line number
 * @status: pointer to status code
 * @eof: pointer to eof variable
 * @env: environment
 *
 * Return: 0 (FOUND) else NOT found
 *
 * Description:
 * cmdv: 'cmd' 'arg1' 'arg2' ...
 */
int search(char **cmdv, size_t *cmdc, int line, int *status, int *eof,
		char **env)
{
	char abs_cmd[CMDLEN] = {'\0'};

	size_t *unused1 __attribute__((unused)) = cmdc;

	/* 1. command exists and is executable as is */
	if (access(cmdv[0], F_OK | X_OK) == 0)
	{
		return (0);
	}
	/* 2. command is executable in the path */
	else if (check_in_path(cmdv[0], abs_cmd, env) == 0)
	{
		free(cmdv[0]);
		cmdv[0] = strdup(abs_cmd);
		return (0);
	}
	/* 3. cammand is special case */
	else
	{
		if (strncmp(cmdv[0], "exit", strlen("exit")) == 0)
		{
			*eof = 1;
			*status = (cmdv[1]) ? atoi(cmdv[1]) : *status;
			return (1);
		}
		else if (strncmp(cmdv[0], "env", strlen("env")) == 0)
		{
			print_env(env);
			*status = 0;
			return (1);
		}
	}

	*status = 127;
	fprintf(stderr, "./hsh: %d: %s: not found\n", line, cmdv[0]);
	return (1);
}
