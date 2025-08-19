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
* main - entry point for the simple shell program
* @argc: number of arguments
* @argv: array of argument strings
* @envp: array of environment variables
*
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;
	char *args[256];
	(void)argc, (void)argv;
	while (1)
	{
		printf("cisfun$ "); /* display the prompt */
		fflush(stdout);
		nread = getline(&line, &len, stdin);/* read a line from standard input */
		if (nread == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (_strlen(line) == 0)
			continue;
		if (_strcmp(line, "env") == 0)
		{
			env_command(envp);
			continue;
		}
		if (exit_command(line))
			break;
		parse_args(line, args);
		my_fork(args);
	}
	free(line);
	return (EXIT_SUCCESS);
}
