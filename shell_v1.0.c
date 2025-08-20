#include "simple_shell.h"

int env_command(char **envp)
{
	int a = 0;

	if (envp == NULL)
	return (-1);

	for (a = 0; envp[a] != NULL; a++)/*for*/
	{
		printf("%s\n", envp[a]);
	}
	return (0);
}
