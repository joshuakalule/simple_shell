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
 * init - initiate the box conatining all variables
 * @box: conatainer of all variables
 * @ac: argc (main)
 * @av: argv (main)
 * @env: env (main)
 */
void init(container_t *box, int ac, char **av, char **env)
{
	box->cmdv = NULL;
	box->cmdc = 0; /* length of cmdv array */

	box->status = 0; /* return code of previous command */
	box->eof = 0;
	box->nline = 0;

	box->ac = ac;
	box->av = av;
	box->env = arraydup(env);

	box->aliases = NULL;
	box->prompt = strdup("($) ");
}

/**
 * main - entry point to the program
 * @ac: number of arguments passed to the program
 * @av: array of arguments passed to the program
 * @env: array of environment arguments passed to the program
 *
 * Return: 0(Success)
 *
 * Description:
 * mode: 1 (interactive) 0 (non-interactive)
 */
int main(int ac, char *av[], char *env[])
{
	container_t *box;
	int status;

	/* initiate box */
	box = malloc(sizeof(container_t));
	init(box, ac, av, env);

	while (1)
	{
		/* pre-cleanuo */
		cleanup(box->cmdv, &box->cmdc);
		if (box->eof == 1)
			break;

		display_prompt(box->prompt);
		/* get_user input and tokenize into cmdv */
		box->cmdv = get_user_input(box);
		(box->nline)++;
		if (box->cmdv == NULL)
		{
			if (isatty(STDIN_FILENO) == 1 && box->eof == 1)
				write(STDOUT_FILENO, "\n", 1);
			continue;
		}
		/* parse the commands in cmdv */
		if (parse(box) != 0)
			break;
		/* search for the command */
		if (search(box) != 0)
			continue;
		/* execute command*/
		if (execute(box) != 0)
			continue;
	}
	status = box->status;
	free_box(box);
	return (status);
}
