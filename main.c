#include "simple_shell.h"
/**
 * main - Entry point for the simple shell program
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * @envp: Array of environment variables
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv, char **envp)
{
	simple_shell_t shell_state;
	(void)argc, (void)argv;

	shell_state.is_interactive = isatty(STDIN_FILENO);
	shell_state.exit_status = 0;

	run_shell(&shell_state, envp);

	return (shell_state.exit_status);
}

/**
 * run_shell - The main loop of the shell
 * @shell_state: Pointer to the shell's state structure
 * @envp: Array of environment variables
 */
void run_shell(simple_shell_t *shell_state, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[256];

	while (1)
	{
		if (shell_state->is_interactive)
			printf("cisfun$ ");
		fflush(stdout);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
			{
				if (shell_state->is_interactive)
					printf("\n");
				break;
			}
			perror("getline");
			shell_state->exit_status = EXIT_FAILURE;
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (_strlen(line) == 0)
			continue;
		if (exit_command(line))
			break;
		if (_strcmp(line, "env") == 0)
		{
			env_command(envp);
			continue;
		}
		parse_args(line, args);
		my_fork(args);
	}
	free(line);
}
