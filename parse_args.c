#include "simple_shell.h"
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
