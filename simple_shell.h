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

/**
*struct simple_shell - our version of a simple shell

typedef struct simple_shell
{

<<<<<<< HEAD
}*/

void execute_command(char *command, char **envp);
int main(int argc, char **argv, char **envp);
int parse_args(char *line, char **args);
=======
} simple_shell_t;

void execute_command(char *command, char **envp);
int main(int argc, char **argv, char **envp);
int exit_command(char *command);
>>>>>>> 6bf8a2e77ea0ed8968ee9405b57a666ef5131716

#endif /*simple_shell_h*/
