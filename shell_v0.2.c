#include "simple_shell.h"
/**
 * my_fork - personalized fork function to execute a command
 * @args: array of arguments for the command
 * Return: void
 */
void my_fork(char **args)
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
		fprintf(stderr, "./simple_shell: 1: %s: not found\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, args, NULL) == -1)
		{
			perror("execve");
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}

	free(full_path);
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
