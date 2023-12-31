#include "shell.h"

/**
 *_eputs - prints input string
 * @str: string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
	{
		return;
	}
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes C to stderr
 * @c: The character to be printed
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int j;

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

/**
 * _putfd - writes c to the given file descriptor
 * @c: The character to be printed
 * @fd: Filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

/**
 *_putsfd - prints input string
 * @str: string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of characters
 */
int _putsfd(char *str, int fd)
{
	int j;

	j = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
