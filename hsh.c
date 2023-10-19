#include "main.h"

/**
 * display_prompt - print the prompt on the stdout
 * @prompt: text to print
 */
void display_prompt(char *prompt)
{
	/* if non-interactive mode, do not display */
	if (isatty(STDIN_FILENO) == 0)
		return;

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
		if (cmdv == NULL)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "\n", 1);
			cleanup(cmdv, &cmdc);
			break;
		}
		/* parse the commands in cmdv */
		if (parse(cmdv, &cmdc) != 0)
			break;
		/* search for the command */
		if (search(cmdv, &cmdc) != 0)
		{
			cleanup(cmdv, &cmdc);
			continue;
		}
		/* execute command*/
		if (execute(cmdv, &cmdc) != 0)
		{
			cleanup(cmdv, &cmdc);
			continue;
		}
		cleanup(cmdv, &cmdc);
	}
	cleanup(cmdv, &cmdc);
	free(prompt);
	return (EXIT_SUCCESS);
}
