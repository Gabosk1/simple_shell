#include "shell.h"

/**
 * _strlen - returns the string length
 * @s: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
	{
		return (0);
	}

	while (*s++)
	{
		a++;
	}
	return (a);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hs, const char *nd)
{
	while (*nd)
	{
		if (*nd++ != *hs++)
		{
			return (NULL);
		}
	}
	return ((char *)hs);

}

/**
 * _strcat - concatenates two strings
 * @dest: destination buffer
 * @source: source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *source)
{
	char *r = dest;

	while (*dest)
	{
		dest++;
	}
	while (*source)
	{
		*dest++ = *source++;
	}
	*dest = *source;
	return (r);
}
