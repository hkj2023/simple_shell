#include "shell.h"

/**
 * get_history_file - to gets history
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */

char *get_history_file(itr_r *itr)
{
char *buf, *dir;
dir = _getenv(itr, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * write_history - to create write file history
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int write_history(itr_r *itr)
{
ssize_t fd;
char *filename = get_history_file(itr);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = itr->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_history - reads history
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int read_history(itr_r *itr)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(itr);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(itr, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_history_list(itr, buf + last, linecount++);
free(buf);
itr->histcount = linecount;
while (itr->histcount-- >= HIST_MAX)
delete_node_at_index(&(itr->history), 0);
renumber_history(itr);
return (itr->histcount);
}

/**
 * build_history_list - adds new history list
 * @itr: user defined struct
 * @buf: the string
 * @linecount: to count line
 * Return: Always 0 (Success)
 */
int build_history_list(itr_r *itr, char *buf, int linecount)
{
list_t *node = NULL;
if (itr->history)
node = itr->history;
add_node_end(&node, buf, linecount);
if (!itr->history)
itr->history = node;
return (0);
}

/**
 * renumber_history - renumbers the history
 * @itr: user defined struct
 * Return: Always 0 (Success)
 */
int renumber_history(itr_r *itr)
{
list_t *node = itr->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (itr->histcount = i);
}

