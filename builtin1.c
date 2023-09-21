#include "shell.h"

/**
 * _myhistory - displays history list, one command by line, preceded
 *              by line numbers starting at 0.
 * @info: Structure contains potential arguments used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets an alias to string
 * @info: parameter struct
 * @str: string alias
 * Return: Always 1 on error and 0 on success
 */
int unset_alias(info_t *info, char *str)
{
	char c;
	char *p;
	int r;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	c = *p;
	*p = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (r);
}

/**
 * set_alias - set an alias to string
 * @info: parameter struct
 * @str: string alias
 * Return: 1 on error, 0 on success
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		p = _strchr(info->argv[k], '=');
		if (p)
		{
			set_alias(info, info->argv[k]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
		}
	}

	return (0);
}
