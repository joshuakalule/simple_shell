#include "main.h"

/**
 * mygetenv - replicate getenv
 * @var: variable name
 * @env: environment
 *
 * Return: malloc'ed pointer to the environment variable value
 */
char *mygetenv(char *var, char **env)
{
	size_t i;
	char **envpair = NULL;
	char *env_key, *env_value;
	size_t nenvpair = 0;

	if (!env || !*env)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		envpair = split(&nenvpair, env[i], "=");
		if (!envpair || !envpair[0])
			return (NULL);
		env_key = envpair[0];
		env_value = (envpair[1]) ? strdup(envpair[1]) : NULL;

		if (strcmp(env_key, var) == 0 &&
				env_key[strlen(var)] == '\0')
		{
			free_array(envpair, &nenvpair);
			envpair = NULL;
			return (env_value);
		}

		free_ptr(env_value);
		free_array(envpair, &nenvpair);
		envpair = NULL;
	}

	return (NULL);
}
