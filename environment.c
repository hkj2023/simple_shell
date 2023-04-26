#include "shell.h"

/**
 * _myenv - to print environment
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int _myenv(itr_r *itr)
{
print_list_str(itr->env);
return (0);
}

/**
 * _getenv - to gets environment
 * @itr: user defined struct
 * @name: the string
 * Return: Always 0 (Success)
 */
char *_getenv(itr_r *itr, const char *name)
{
list_t *node = itr->env;
char *p;
while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * _mysetenv - to set new environment
 * @itr: user defined struct
 *  Return: Always 0 (Success)
 */
int _mysetenv(itr_r *itr)
{
if (itr->argc != 3)
{
_eputs("Wrong number of arguement is Entered\n");
return (1);
}
if (_setenv(itr, itr->argv[1], itr->argv[2]))
return (0);
return (1);
}

/**
 * _myunsetenv - to unset environment
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int _myunsetenv(itr_r *itr)
{
int i;
if (itr->argc == 1)
{
_eputs("Too much few arguements entered!\n");
return (1);
}
for (i = 1; i <= itr->argc; i++)
_unsetenv(itr, itr->argv[i]);
return (0);
}

/**
 * populate_env_list - new linked list
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int populate_env_list(itr_r *itr)
{
list_t *node = NULL;
size_t i;
for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
itr->env = node;
return (0);
}

