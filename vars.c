#include "shell.h"

/**
 * is_chain - test chain
 * @itr: user defined struct
 * @buf: the string buffer
 * @p: location of string
 * Return: Always 0 (Success)
 */
int is_chain(itr_r *itr, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
itr->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
itr->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
itr->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
 * check_chain - status of chain
 * @itr: user defined struct
 * @buf: the string
 * @p: location of string
 * @i: starting position in string
 * @len: length
 * Return: void
 */

void check_chain(itr_r *itr, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (itr->cmd_buf_type == CMD_AND)
{
if (itr->status)
{
buf[i] = 0;
j = len;
}
}
if (itr->cmd_buf_type == CMD_OR)
{
if (!itr->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}

/**
 * replace_alias - to replaces an aliases.
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int replace_alias(itr_r *itr)
{
int i;
list_t *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(itr->alias, itr->argv[0], '=');
if (!node)
return (0);
free(itr->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
itr->argv[0] = p;
}
return (1);
}

/**
 * replace_vars - replaces vars.
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int replace_vars(itr_r *itr)
{
int i = 0;
list_t *node;
for (i = 0; itr->argv[i]; i++)
{
if (itr->argv[i][0] != '$' || !itr->argv[i][1])
continue;
if (!_strcmp(itr->argv[i], "$?"))
{
replace_string(&(itr->argv[i]),
_strdup(convert_number(itr->status, 10, 0)));
continue;
}
if (!_strcmp(itr->argv[i], "$$"))
{
replace_string(&(itr->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(itr->env, &itr->argv[i][1], '=');
if (node)
{
replace_string(&(itr->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&itr->argv[i], _strdup(""));
}
return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: Always 0 (Success)
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
