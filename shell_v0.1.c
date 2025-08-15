#include "simple_shell.h"
/**
 * execute_command - create child and execute programm
 * @command: command to execute
 * @envp: environment variables
*/
void execute_command(char *command, char **envp)
{
    pid_t pid;
    int status;

    pid = fork();/** create child */
    if (pid == -1)
	{
        perror("fork");/**error if child doesn't works */
        return;
    }

    if (pid == 0)
	{
        char *argv[2];
        argv[0] = command;
        argv[1] = NULL;
		/* Execute the command with arguments and environment */
		execve(command, argv, envp);

		perror(command);/* Display error message if execve fails */
        exit(1);
    }
	else
	{
		waitpid(pid, &status, 0);/* Wait for child process to complete */
    }
}

/**
*main - entry point for the simple shell program
*@argc: number of arguments
*@argv: array of argument strings
*@envp: array of environment variables
*Return: 0 on success, 1 on error
*/
int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    
    (void)argc;/*ignore argc and argv for the gcc*/
    (void)argv;

    while (1)
	{
        printf("#cisfun$ ");/*our prompt Cisfun$ */
        fflush(stdout);/*free the memory buffered*/

		nread = getline(&line, &len, stdin);/* Read user input from stdin */

        if (nread == -1) 
		{
            if (feof(stdin))/*if not read exit program*/
			{

                printf("\n");
                break;
            }
			else
			{

                perror("getline");/*display error on getline and quit*/
                exit(1);
            }
        }
		
		if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';/*Remove the newline character at the end of the input*/
		}

        if (strlen(line) > 0)
		{

			
			if (strcmp(line, "exit") == 0)/*Check if user wants to exit the shell*/
			{
                break;
            }
			execute_command(line, envp); /*Execute the user command with environment variables*/
        }
    }

    free(line);
    return (0);
}
