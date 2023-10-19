#include "main.h"

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

	if (access(cmdv[1], F_OK) != 0)
	{
		fprintf(stderr, "%s: No such file or directory\n", cmdv[0]);
		return (1);
	}

	return (0);
}

/**
 * display_prompt - print the prompt on the stdout
 * @prompt: text to print
 */
void display_prompt(char *prompt)
{
	if (isatty(STDIN_FILENO) == 1)

	if (prompt == NULL)
		exit(EXIT_FAILURE);

	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * cleanup - clear cmdv and reset cmdc
 * @cmdv: array of tokens
 * @cmdc: number of tokens
 */
void cleanup(char **cmdv, size_t *cmdc)
{
	size_t i;

	if (!cmdv || *cmdc == 0)
		return;

	for (i = 0; i < *cmdc; i++)
	{
		free(cmdv[i]);
	}
	free(cmdv);
	cmdv = NULL;
	*cmdc = 0;
}

/**
 * main - entry point to the program
 * @ac: number of arguments passed to the program
 * @av: array of arguments passed to the program
 * @envp: array of environment arguments passed to the program
 *
 * Return: 0(Success)
 *
 * Description:
 * mode: 1 (interactive) 0 (non-interactive)
 */
int main(int ac, char *av[], char *envp[])
{
	char **cmdv = NULL; /* array of commands */
	size_t cmdc = 0; /* length of cmdv array */
	char *prompt = strdup("($) ");

	int unused1 __attribute__((unused)) = ac;
	char **unused2 __attribute__((unused)) = av;
	char **unused3 __attribute__((unused)) = envp;

	while (1)
	{
		/* display prompt */
		display_prompt(prompt);
		/* get_user input and tokenize into cmdv */
		cmdv = get_user_input(&cmdc);

		/* EOF */
		if (cmdv == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* parse the commands in cmdv */
		if (parse(cmdv, &cmdc) != 0)
			break;
		/* search for the command */
		if (search(cmdv, &cmdc) != 0)
		{
			/* BREAK(mode); */
			continue;
		}
		/* execute command*/
	}
	cleanup(cmdv, &cmdc);
	free(prompt);
	return (EXIT_SUCCESS);
}
