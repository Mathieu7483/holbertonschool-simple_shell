#include "simple_shell.h"
/**
* my_fork - personalized fork function to execute a command
* @args: array of arguments for the command
* @argv: array of arguments from main function
* @envp: array of environment variables
* Return: void
*/
void my_fork(char **args, char **argv, char **envp)
{
	pid_t pid;
	int status;

	char *path_env = my_getenv("PATH");

	char *full_path;

	if (args == NULL || args[0] == NULL)
		return;

	full_path = _which(args[0], path_env);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return;
	}

	if (pid == 0) /* Child process */
	{
		if (execve(full_path, args, envp) == -1)
		{
			fprintf(stderr, "%s: 1: %s: %s\n", argv[0], args[0], strerror(errno));
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		waitpid(pid, &status, 0);
		free(full_path);
	}
}

/**
* parse_args - tokenize a command line into arguments
* @line: input command line string
* @args: array to store the resulting arguments
* Return: number of arguments parsed
*/
int parse_args(char *line, char **args)
{
	int i = 0;

	char *token;

	token = strtok(line, " ");
	while (token != NULL && i < 255)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL; /* Terminate the array */
	return (i);
}

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

	run_shell(&shell_state, argv, envp);

	return (shell_state.exit_status);
}

/**
 * run_shell - The main loop of the shell
 * @shell_state: Pointer to the shell's state structure
 * @argv: Array of argument strings
 * @envp: Array of environment variables
 */
void run_shell(simple_shell_t *shell_state, char **argv, char **envp)
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
		my_fork(args, argv, envp);
	}
	free(line);
}
