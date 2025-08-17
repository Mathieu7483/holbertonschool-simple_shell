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

    /* If the command is an absolute or relative path */
    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &st) == 0)
        {
            return strdup(command);
        }
        return NULL;
    }

    /* duplicate the PATH environment variable */
    path_copy = strdup(path_env);
    if (path_copy == NULL) {
        perror("strdup");
        return NULL;
    }

    /* allocating memory for the file path */
    file_path = malloc(256); /* size of the path buffer */
    if (file_path == NULL) 
    {
        perror("malloc");
        free(path_copy);
        return NULL;
    }

    /* Read the PATH directories */
    path_token = strtok(path_copy, ":");
    while (path_token != NULL) 
    {
        /* Build the full path */
        sprintf(file_path, "%s/%s", path_token, command);

        /* Check if the file exists and is executable */
        if (stat(file_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(path_copy);
            return file_path; /* Found the file */
        }

        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    free(file_path);
    return NULL; /* File not found in PATH */
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
    char *path_env = getenv("PATH");
    char *full_path;

    if (args == NULL || args[0] == NULL) {
        return;
    }

    /* Handle PATH management */
    full_path = _which(args[0], path_env);
    if (full_path == NULL) {
        fprintf(stderr, "./simple_shell: 1: %s: not found\n", args[0]);
        return;
    }

    /* Create a child process */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(full_path);
        return;
    }

    if (pid == 0) {
        /* Code child process */
        if (execve(full_path, args, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        /* Code parent process */
        wait(&status);
    }
    free(full_path);
}

/**
 * main - entry point of simple shell program
 * Return: EXIT_SUCCESS on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes;
    char *token;
    char *args[256];
    int i;

    while (1) {
        printf("cisfun$ "); /* display the prompt */
        fflush(stdout);

        /* read a line from standard input */
        read_bytes = getline(&line, &len, stdin);
        if (read_bytes == -1) {
            /* Handle end of file (Ctrl+D) */
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline");
                break;
            }
        }

        /* delete the newline character at the end of the line */
        if (line[read_bytes - 1] == '\n') {
            line[read_bytes - 1] = '\0';
        }

        /* checking if the line is empty */
        if (strlen(line) == 0) {
            continue;
        }

        /* Tokenize the line into arguments */
        i = 0;
        token = strtok(line, " ");
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; /* finish the args array */

        /* Call to my_fork to execute the command */
        my_fork(args);
    }

    free(line);
    return EXIT_SUCCESS;
}
