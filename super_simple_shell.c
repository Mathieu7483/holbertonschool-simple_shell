#include "simple_shell.h"
/**
* free_args - Frees a dynamically allocated array of strings.
* @args: The array of strings to free.
*/
void free_args(char **args)
{
	int i = 0;

	if (args == NULL)
		return;
	while (args[i] != NULL)/* Free each string in the array */
	{
		free(args[i]);  /* Free the current string */
		i++;            /* Move to the next string */
	}
	free(args);
}

/**
* read_line - Reads a line from stdin.
* Return: A pointer to the line read, or NULL on error or EOF.
*/
char *read_line(void)
{
	char *line = NULL;

	size_t bufsize = 0;

	/*Read a line from stdin(keyboard), getline will allocate memory as needed*/
	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin)) /*Check if end-of-file (Ctrl+D) */
		{
			free(line);
			return (NULL);
		}
		else
		{
			free(line);
			perror("getline"); /* Print error message for getline failure */
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}

/**
* parse_line - Splits a line into tokens.
* @line: The line to parse.
* Return: An array of strings (tokens).
*/
char **parse_line(char *line)
{
	char **tokens = NULL;
	char *token;
	int bufsize = 64;
	int i = 0;

/*Allocate memory to store pointers to tokens*/
	tokens = malloc(bufsize * sizeof(char *));
	if (tokens == NULL) /* Check if memory allocation failed */
	{
		perror("malloc");/*print error on Malloc*/
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " \t\r\n\a");/* Split the line into tokens*/
	while (token != NULL)
	{
		tokens[i] = strdup(token);/*Make a copy of the token using strdup*/
		if (tokens[i] == NULL)
		{
			free_args(tokens);
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
		if (i >= bufsize) /*Check if we need more space for tokens*/
		{
			bufsize += 64; /*Increase the buffer size to accommodate more tokens*/
			tokens = realloc(tokens, bufsize * sizeof(char *));
			/*Resize the tokens array to hold more entries */
			if (tokens == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a"); /*Get the next token*/
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
* execute_command - Executes a command.
* @args: The array of command and its arguments.
* Return: The status of the executed command.
*/
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)/*Check if no command was entered*/
		return (1);

	pid = fork(); /* Create a new process */
	if (pid == 0)
	{
		/*Execute the command using execvp, which searches the PATH*/
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) /*Check if fork failed*/
	{
		perror("fork");
		return (1);
	}
	else
	{
		/*Wait for the child process to complete and store its exit status*/
		waitpid(pid, &status, 0);
	}

	return (WEXITSTATUS(status));
	/*Return the exit status of the child process*/
}

/**
* main - Entry point for the super simple shell program.
* @argc: Argument count.
* @argv: Argument vector.
*
* Return: Status code from the last executed command.
*/
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	char *line = NULL;

	char **args = NULL;

	int status = 0;

	while (1)
	{
		printf("Cisfun$ ");/*Prompt*/
		line = read_line();/* Read a line of input from the user */

		if (line == NULL)
		{
			printf("\n");
			break;
		}

		args = parse_line(line);/*Parse the input line into separate arguments*/
		if (args != NULL && args[0] != NULL)
		{
			status = execute_command(args);/*Execute the command and get its status*/
		}

		free(line); /*Free memory allocated for the input line*/
		if (args != NULL)
			free_args(args); /*Free memory allocated for command arguments*/
	}

	return (status); /*Return the status of the last executed command*/
}
