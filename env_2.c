#include "main.h"

/**
 * varpos - check if a VARIABLE is in the environment
 * @env: environment
 * @var_key: VARIABLE
 *
 * Return: index of the variable in the environment
 *		   -1 if not found
 */
int varpos(char **env, char *var_key)
{
	int i;
	char **var_pair = NULL;
	size_t nvar_pair = 0;
	char *old_key;

	if (!env || !var_key)
		return (-1);

	for (i = 0; env[i] != NULL; i++)
	{
		var_pair = split(&nvar_pair, env[i], "=");
		if (var_pair == NULL)
			return (-1);

		old_key = var_pair[0];

		if (strcmp(old_key, var_key) == 0)
		{
			free_array(var_pair, &nvar_pair);
			return (i);
		}
		free_array(var_pair, &nvar_pair);
		var_pair = NULL;
	}
	return (-1);
}

/**
 * myunsetenv - unsetenv
 * @box: container
 * @found: A - found Else NOT FOUND
 */
void myunsetenv(container_t *box, int *found)
{
	int len_old = (int)lenarr(box->env);
	char **new_env = NULL;
	int idx, i_old, i_new = 0;
	size_t n = 0;

	*found = 1;
	if (box->cmdc != 2)
	{
		fprintf(stderr, "./hsh: unsetenv: usage: unsetenv VARIABLE\n");
		box->status = 99;
		return;
	}
	idx = varpos(box->env, box->cmdv[1]);
	if (idx == -1)
	{
		fprintf(stderr, "./hsh: unsetenv: VARIABLE name '%s' not found\n",
				box->cmdv[1]);
		box->status = 99;
		return;
	}
	new_env = malloc(sizeof(*new_env) * (len_old - 1));
	if (!new_env)
		return;
	for (i_old = 0; box->env[i_old] != NULL; i_old++)
	{
		if (i_old != idx)
			new_env[i_new++] = strdup(box->env[i_old]);
	}
	new_env[i_new] = NULL;

	free_array(box->env, &n);
	box->env = new_env;
}
















