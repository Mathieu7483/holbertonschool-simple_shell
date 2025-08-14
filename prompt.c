#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
/**
* prompt - Entry point for the simple shell prompt program.
*
* Return: 0 on success, or another value on error.
*/
int prompt(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			printf("\nEOF.\n");
			break;
		}

		printf("Tu as tapé cette commande: %s", line);
	}

	free(line);
	return (0);
}
