#include "simple_shell.h"
/**
*_strdup - duplicate a string
*@str: string to duplicate
*Return: Returns NULL if string = NULL
*On success, the _strdup function returns a pointer
*to the duplicated string. It returns NULL
*if insufficient memory was available
*/
char *_strdup(char *str)
{
char *a;
int i;
if (str == NULL)
{
return (NULL);
}
for (i = 0; str[i] != '\0'; i++)
{}
a = malloc(sizeof(char) * (i + 1));
if (a == NULL)
{
return (NULL);
}
for (i = 0; str[i] != '\0'; i++)
{
a[i] = str[i];
}
a[i] = '\0';
return (a);
}


/**
*_strcmp - compare the string
*@s1: source tab
*@s2: dest tab
*Return: value of comp
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 == *s2 && *s1 != '\0')
++s1, ++s2;
return (*s1 - *s2);
}


/**
*_strchr - search a char in a string
*@s: input
*@c: input
*Return: Always 0 success
*/
char *_strchr(char *s, char c)
{
int i;

for (i = 0; s[i] != '\0'; i++)
{
	if (s[i] == c)
		return (s + i);
}
if (c == '\0')
{
	return (s + i);
}
return ('\0');
}


/**
*_strlen - calculate the length of a string
*@s: string of character
* Return: Length of a string
*/
int _strlen(char *s)
{
int length = 0;
while (s[length])
{
length++;
}
return (length);
}


/**
*my_getenv - Retrieves the value of an environment variable.
*@name: The name of the environment variable to search for.
*Return: Pointer to the value string if found, otherwise NULL.
*/
char *my_getenv(const char *name)
{
	int i;

	size_t name_len;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (&environ[i][name_len + 1]);
		}
	}

	return (NULL);
}
