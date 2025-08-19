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

	if (_strchr((char *)command, '/') != NULL)/*Check if absolute or relative*/
	{
		if (stat(command, &st) == 0)/*check if command exist*/
			return (_strdup((char *)command));/*if yes return duplicate*/
		return (NULL);/*otherwise return NULL*/
	}
	path_copy = _strdup((char *)path_env);/*Duplicate PATH to avoid modification*/
	if (path_copy == NULL)
	{
		perror("_strdup");/*print error if memory allocation fails*/
		return (NULL);
	}
	path_token = strtok(path_copy, ":");/*Tokenize PATH string by ':'*/
	while (path_token != NULL)
	{
		path_len = _strlen(path_token);/*length of the current dir and the command*/
		cmd_len = _strlen((char *)command);
		file_path = malloc(path_len + cmd_len + 2);/*Allocate memory for path*/
		if (file_path == NULL)
		{
			perror("malloc");/*print memory allocation failure*/
			free(path_copy);
			return (NULL);
		}
		snprintf(file_path, path_len + cmd_len + 2, "%s/%s", path_token, command);
		if (stat(file_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);/*Free the PATH copy before returning*/
			return (file_path);/*Return the full path found*/
		}
		free(file_path);/*Free temporary path*/
		path_token = strtok(NULL, ":");/*Get next directory*/
	}
	free(path_copy);/*Free the duplicated PATH*/
	return (NULL);/*Command not found*/
}
