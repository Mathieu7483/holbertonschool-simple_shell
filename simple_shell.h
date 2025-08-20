#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strlen(char *s);
char *my_getenv(const char *name);

/**
 * struct simple_shell - our version of a simple shell
 * @is_interactive: flag to check if the shell is in interactive mode
 * @exit_status: the exit status of the last command
 */
typedef struct simple_shell
{
int is_interactive;
int exit_status;
} simple_shell_t;

int parse_args(char *line, char **args);
void my_fork(char **args, char **argv, char **envp);
int exit_command(char *line);
void execute_command(char *line, char **envp);
char *_which(const char *command, const char *path_env);
int env_command(char **envp);

int main(int argc, char **argv, char **envp);
void run_shell(simple_shell_t *shell_state, char **argv, char **envp);

#endif /*simple_shell_h*/
