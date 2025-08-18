#include "simple_shell.h"

/**
* exit_command - Check if command is exit builtin
* @command: command to check
* Return: 1 if exit command, 0 if not
*/
int exit_command(char *command)
{
	if (strcmp(command, "exit") == 0)
		return (1);
	return (0);
}
