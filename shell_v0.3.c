#include "simple_shell.h"

/**
 * is_executable - check if file is executable
 * @st: stat structure
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(struct stat *st)
{
	return (S_ISREG(st->st_mode) &&
		(st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)));
}

/**
 * check_direct_path - check if command has direct path
 * @command: command to check
 * Return: duplicated path if found, NULL otherwise
 */
char *check_direct_path(const char *command)
{
	struct stat st;

	if (_strchr((char *)command, '/') != NULL)
	{
		if (stat(command, &st) == 0 && is_executable(&st))
			return (_strdup((char *)command));
		return (NULL);
	}
	return (NULL);
}

/**
 * _which - find the full path of a command
 * @command: name of the command
 * @path_env: string of character to PATH
 * Return: the full path of the command or NULL
 */
char *_which(const char *command, const char *path_env)
{
	char *path_copy, *path_token, *file_path, *direct_path;
	struct stat st;
	int path_len, cmd_len;

	if (command == NULL || *command == '\0')
		return (NULL);
	direct_path = check_direct_path(command);
	if (direct_path != NULL)
		return (direct_path);
	if (path_env == NULL || *path_env == '\0')
		return (NULL);
	path_copy = _strdup((char *)path_env);
	if (path_copy == NULL)
		return (NULL);
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		if (*path_token == '\0')
			path_token = ".";
		path_len = _strlen(path_token);
		cmd_len = _strlen((char *)command);
		file_path = malloc(path_len + cmd_len + 2);
		if (file_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		snprintf(file_path, path_len + cmd_len + 2, "%s/%s",
			path_token, command);
		if (stat(file_path, &st) == 0 && is_executable(&st))
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
