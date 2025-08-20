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
