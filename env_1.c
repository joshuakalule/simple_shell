#include "main.h"

/**
 * print_env - print the environment
 * @box: container
 * @found: A - found Else NOT FOUND
 */
void print_env(container_t *box, int *found)
{
	size_t i;

	*found = 1;
	for (i = 0; box->env[i] != NULL; i++)
		fprintf(stdout, "%s\n", box->env[i]);

	/* set the status to 0 (SUCCESS) */
	box->status = 0;
}

/**
 * gen_var - generate environment variable
 * @new_key: new VARIABLE
 * @new_value: new VALUE
 *
 * Return: malloc'ed pointer to new variable
 */
char *gen_var(char *new_key, char *new_value)
{
	char *new_var = NULL;
	size_t nkey, nvalue;

	nkey = strlen(new_key);
	nvalue = (new_value) ? strlen(new_value) : 0;

	new_var = malloc(sizeof(char) * (nkey + nvalue + 2));
	if (!new_var)
		return (NULL);

	memcpy(new_var, new_key, nkey);
	new_var[nkey] = '=';
	memcpy(new_var + (nkey + 1), new_value, nvalue);
	new_var[nkey + nvalue + 1] = '\0';

	return (new_var);
}

/**
 * modify_var - modify existing environment variable
 * @env: environment array
 * @pos: index of variable in environment array
 * @new_var: new environment variable
 *
 * Return: environment
 */
char **modify_var(char **env, int pos, char *new_var)
{
	char **new_env = NULL;

	if (!env || !new_var)
		return (NULL);

	new_env = arraydup(env);
	if (new_env == NULL)
		return (NULL);

	free(new_env[pos]);
	new_env[pos] = strdup(new_var);

	return (new_env);
}

/**
 * set_var - set new environment variable
 * @env: environment
 * @new_var: pointer to new var
 *
 * Return: environment
 */
char **set_var(char **env, char *new_var)
{
	size_t len_oldenv;
	size_t i;
	char **new_env = NULL;

	if (!new_var)
		return (NULL);
	len_oldenv = lenarr(env);
	new_env = malloc(sizeof(*new_env) * (len_oldenv + 1));
	if (!new_env)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
		new_env[i] = strdup(env[i]);
	new_env[i] = strdup(new_var);
	new_env[i + 1] = NULL;

	return (new_env);
}

/**
 * mysetenv - set environment variable
 * @box: container
 * @found: 1 - found Else NOT FOUND
 */
void mysetenv(container_t *box, int *found)
{
	char *new_var = NULL;
	char *new_var_key;
	char *new_var_value;
	char **new_env = NULL;
	size_t n = 0;
	int idx;

	*found = 1;
	if (box->cmdc != 3 || box->cmdv[1] == NULL)
	{
		fprintf(stderr, ".hsh: setenv: usage: setenv VARIABLE VALUE\n");
		box->status = 98;
		return;
	}
	new_var_key = box->cmdv[1];
	new_var_value = box->cmdv[2];
	new_var = gen_var(new_var_key, new_var_value);
	idx = varpos(box->env, new_var_key);
	if (idx == -1)
	{
		/* set */
		new_env = set_var(box->env, new_var);
	}
	else
	{
		/* modify */
		new_env = modify_var(box->env, idx, new_var);
	}
	if (new_env != NULL)
	{
		free_array(box->env, &n);
		box->env = new_env;
	}
	free(new_var);
}
