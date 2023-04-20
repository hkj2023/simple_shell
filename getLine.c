#include "main.h"

/**
 * _input_buf - to make buffer
 * @itr: user defined data
 * @buf: the buf string
 * @len: the length of string
 * Return - Always 0 (Success)
 */

ssize_t _input_buf(itr_r *itr, char **buf, size_t *len)
{
ssize_t siz; = 0;
size_t length;
siz = 0;
if (!*len)
{

free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
siz = getline(buf, &length, stdin);
#else
siz = _getline(itr, buf, &length);
#endif
if (siz > 0)
{
if ((*buf)[siz - 1] == '\n')
{
(*buf)[r - 1] = '\0';
siz--;
}
itr.count_line = 1;
remove_comments(*buf);
build_history_list(itr, *buf, itr->histcount++);
{
*len = siz;
itr->cmd_buf = buf;
}
}
}
return (siz);
}
