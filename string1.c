#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination
 * @source: source
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *source)
{
	int x = 0;

	if (dest == source || source == 0)
	{
		return (dest);
	}
	while (source[x])
	{
		dest[x] = source[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *r;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		length++;
	}
	r = malloc(sizeof(char) * (length + 1));
	if (!r)
	{
		return (NULL);
	}
	for (length++; length--;)
	{
		r[length] = *--str;
	}
	return (r);
}

/**
 *_puts - prints an input string
 *@str: string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
	{
		return;
	}
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - prints c to standard output
 * @c: character to print
 * Return: 1 on success
 * On error, -1 is returned and errno is set appropriately.
 */
int _putchar(char c)
{
	static int p;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buffer, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
	{
		buffer[p++] = c;
	}
	return (1);
}
