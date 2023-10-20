#include "main.h"

/* search for cmds */

/**
 * search - looks for commands
 * @cmdv: array of commands
 * @cmdc: number of command tokens
 *
 * Return: 0 (Found) else NOT FOUND
 */
int search(char **cmdv, size_t *cmdc)
{
	size_t *unused1 __attribute__((unused)) = cmdc;

	/* the command in pos 1 is the main command, rest are arguments */
	/* e.g. './hsh', 'ls', '-l' */

	if (access(cmdv[0], F_OK | X_OK) != 0)
	{
		fprintf(stderr, "./hsh: No such file or directory\n");
		return (1);
	}

	return (0);
}
