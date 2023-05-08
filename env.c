#include "main.h"

void printenv(char **env)
{
	if (!*env)
	{
		printf("SHLVL=0\n");
		return;
	}
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
