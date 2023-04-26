#include "shell.h"

/**
 * hsh - the shell loop
 * @itr: user defined struct
 * @av: the string
 * Return: Always 0 (Success)
 */
int hsh(itr_r *itr, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clear_itr(itr);
if (is_interactive(itr))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(itr);
if (r != -1)
{
set_itr(itr, av);
builtin_ret = find_builtin(itr);
if (builtin_ret == -1)
find_cmd(itr);
}
else if (is_interactive(itr))
_putchar('\n');
free_itr(itr, 0);
}
write_history(itr);
free_itr(itr, 1);
if (!is_interactive(itr) && itr->status)
exit(itr->status);
if (builtin_ret == -2)
{
if (itr->err_num == -1)
exit(itr->status);
exit(itr->err_num);
}
return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @itr: user defined struct
 * Return: 0 (Success)
 */
int find_builtin(itr_r *itr)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (_strcmp(itr->argv[0], builtintbl[i].type) == 0)
{
itr->line_count++;
built_in_ret = builtintbl[i].func(itr);
break;
}
return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @itr: user defined struct
 * Return:
 */
void find_cmd(itr_r *itr)
{
char *path = NULL;
int i, k;
itr->path = itr->argv[0];
if (itr->linecount_flag == 1)
{
itr->line_count++;
itr->linecount_flag = 0;
}
for (i = 0, k = 0; itr->arg[i]; i++)
if (!is_delim(itr->arg[i], " \t\n"))
k++;
if (!k)
return;
path = find_path(itr, _getenv(itr, "PATH="), itr->argv[0]);
if (path)
{
itr->path = path;
fork_cmd(itr);
}
else
{
if ((is_interactive(itr) || _getenv(itr, "PATH=")
|| itr->argv[0][0] == '/') && is_cmd(itr, itr->argv[0]))
fork_cmd(itr);
else if (*(itr->arg) != '\n')
{
itr->status = 127;
print_error(itr, "not found\n");
}
}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @itr: user defined struct
  * Return:
 */
void fork_cmd(itr_r *itr)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(itr->path, itr->argv, get_environ(itr)) == -1)
{
free_itr(itr, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(itr->status));
if (WIFEXITED(itr->status))
{
itr->status = WEXITSTATUS(itr->status);
if (itr->status == 126)
print_error(itr, "Permission denied\n");
}
}
}

