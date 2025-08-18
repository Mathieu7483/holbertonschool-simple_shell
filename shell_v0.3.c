#include "simple_shell.h"

/**
 * _which - find the full path of a command
 * @command: name of the command
 * @path_env: string of character to PATH
 * Return: the full path of the command or NULL
 */
char *_which(const char *command, const char *path_env)
{
    char *path_copy, *path_token;
    char *file_path;
    struct stat st;
    int path_len, cmd_len;

    if (_strchr((char *)command, '/') != NULL)
    {
        if (stat(command, &st) == 0)
            return (_strdup((char *)command));
        return (NULL);
    }

    path_copy = _strdup((char *)path_env);
    if (path_copy == NULL)
    {
        perror("_strdup");
        return (NULL);
    }

    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        path_len = _strlen(path_token);
        cmd_len = _strlen((char *)command);
        file_path = malloc(path_len + cmd_len + 2);
        if (file_path == NULL)
        {
            perror("malloc");
            free(path_copy);
            return (NULL);
        }

        snprintf(file_path, path_len + cmd_len + 2, "%s/%s", path_token, command);

        if (stat(file_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return (file_path);
        }

        free(file_path);
        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

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
