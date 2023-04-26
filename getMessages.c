#include "shell.h"

/**
 * clear_itr - clears all argument
 * @itr: struct address
 */
void clear_itr(itr_r *itr)
{
itr->arg = NULL;
itr->argv = NULL;
itr->path = NULL;
itr->argc = 0;
}

/**
 * set_itr - initializes new argument
 * @itr: struct address
 * @av: argument
 */
void set_itr(itr_r *itr, char **av)
{
int i = 0;
itr->fname = av[0];
if (itr->arg)
{
itr->argv = strtow(itr->arg, " \t");
if (!itr->argv)
{
itr->argv = malloc(sizeof(char *) * 2);
if (itr->argv)
{
itr->argv[0] = _strdup(itr->arg);
itr->argv[1] = NULL;
}
}
for (i = 0; itr->argv && itr->argv[i]; i++)
;
itr->argc = i;
replace_alias(itr);
replace_vars(itr);
}
}

/**
 * free_itr - frees the field
 * @itr: struct address
 * @all: true if freeing all fields
 */
void free_itr(itr_r *itr, int all)
{
ffree(itr->argv);
itr->argv = NULL;
itr->path = NULL;
if (all)
{
if (!itr->cmd_buf)
free(itr->arg);
if (itr->env)
free_list(&(itr->env));
if (itr->history)
free_list(&(itr->history));
if (itr->alias)
free_list(&(itr->alias));
ffree(itr->environ);
itr->environ = NULL;
bfree((void **)itr->cmd_buf);
if (itr->readfd > 2)
close(itr->readfd);
_putchar(BUF_FLUSH);
}
}
