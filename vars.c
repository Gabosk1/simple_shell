#include "shell.h"

/**
 * is_chain - checks if the current character in the
 * buffer is a chain delimeter
 * @info: parameter struct
 * @buffer: the character buffer
 * @p: current position address in buffer
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *p)
{
	size_t i = *p;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = i;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @info: parameter struct
 * @buf: the char buffer
 * @p: current position address in buf
 * @s: buf starting position
 * @len: buf length
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t s, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[s] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[s] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * replace_alias - replaces aliases in tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	list_t *node;
	char *i;
	int x;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		i = _strchr(node->str, '=');
		if (!i)
		{
			return (0);
		}
		i = _strdup(i + 1);
		if (!i)
		{
			return (0);
		}
		info->argv[0] = i;
	}
	return (1);
}

/**
 * replace_vars - replaces variabless in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
		{
			continue;
		}
		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string address
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
