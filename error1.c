#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: Always 0 (Success)
 */

int _erratoi(char *s)
{
int i = 0;
unsigned long int result = 0;
if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
 * print_error - prints an error message
 * @itr: user defined struct
 * @estr: string
 * Return: Always 0 (Success)
 */

void print_error(itr_r *itr, char *estr)
{
_eputs(itr->fname);
_eputs(": ");
print_d(itr->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(itr->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
 * print_d - prints decimal value
 * @input: the input
 * @fd: the filedescriptor
 * Return: Always 0 (Success)
 */

int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;
return (count);
}

/**
 * convert_number - converter function
 * @num: number
 * @base: base
 * @flags: flags
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[100];
char sign = 0;
char *ptr;
unsigned long n = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do	{
*--ptr = array[n % base];
n /= base;
} while (n != 0);
if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * remove_comments - to remove comments
 * @buf: string
 * Return: Always 0 (Success)
 */

void remove_comments(char *buf)
{
int i;
for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
