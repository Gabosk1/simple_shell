#include "shell.h"

/**
 * **strtow - splits a string into words. Repeated delimiters are ignored
 * @str: input string
 * @ds: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *ds)
{
	char **i;
	int x, y, z, w, wordnum = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!ds)
		ds = " ";
	for (w = 0; str[w] != '\0'; w++)
	{
		if (!is_delim(str[w], ds) && (is_delim(str[w + 1], ds) || !str[w + 1]))
			wordnum++;
	}

	if (wordnum == 0)
		return (NULL);
	i = malloc((1 + wordnum) * sizeof(char *));
	if (!i)
		return (NULL);
	for (w = 0, x = 0; x < wordnum; x++)
	{
		while (is_delim(str[w], ds))
			w++;
		y = 0;
		while (!is_delim(str[w + y], ds) && str[w + y])
			y++;

		i[x] = malloc((y + 1) * sizeof(char));
		if (!i[x])
		{
			for (y = 0; y < x; y++)
				free(i[y]);
			free(i);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			i[x][z] = str[w++];
		i[x][z] = 0;
	}
	i[x] = NULL;
	return (i);
}

/**
 * **strtow2 - splits a string into words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	char **a;
	int x, z, y, u;
	int wordnum = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
	{
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
		{
			wordnum++;
		}
	}
	if (wordnum == 0)
		return (NULL);
	a = malloc((1 + wordnum) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, z = 0; z < wordnum; z++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		y = 0;
		while (str[x + y] != d && str[x + y] && str[x + y] != d)
			y++;
		a[z] = malloc((y + 1) * sizeof(char));
		if (!a[z])
		{
			for (y = 0; y < z; y++)
				free(a[y]);
			free(a);
			return (NULL);
		}
		for (u = 0; u < y; u++)
			a[z][u] = str[x++];
		a[z][u] = 0;
	}
	a[z] = NULL;
	return (a);
}
