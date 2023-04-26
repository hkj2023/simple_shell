#include "shell.h"
/**
 * _eputs - to puts the string
 * @str: the string to be printed
 * Return: void
 */
void _eputs(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
 * _eputchar - to writes to stderr
 * @c: the string
 * Return: Always 0 (Success)
 */
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 * _putfd - writes the character c to fd
 * @c: the string to be written
 * @fd: the filedescriptor
 * Return: Always 0 (Success)
 */
int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor
 * Return: Always 0 (Success)
 */
int _putsfd(char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += _putfd(*str++, fd);
}
return (i);
}

