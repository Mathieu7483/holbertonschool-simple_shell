#include "simple_shell.h"
/**
* execute_command - create child and execute program
* @command: command to execute
* @envp: environment variables
*
* Return: void
*/
void execute_command(char *command, char **envp)
{
	pid_t pid;
	int status;
	char *argv[2];

	pid = fork(); /* create child */
	if (pid == -1)
	{
		perror("fork"); /* error if child doesn't work */
		return;
	}
	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;
		/* Execute the command with arguments and environment */
		execve(command, argv, envp);
		perror(command); /* Display error message if execve fails */
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0); /* Wait for child process to complete */
	}
}
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
			printf("$ ");
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
		my_fork(args, envp);
	}
	free(line);
}
