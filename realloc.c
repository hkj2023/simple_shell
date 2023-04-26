#include "shell.h"

/**
 * _memset - fill memory with a constant
 * @s: memory address
 * @x: constant byte.
 * @n: bytes filled.
 * Return: Always 0 (Success).
 */
char *_memset(char *s, char x, unsigned int n)
{
unsigned int i;
i = 0;
while (i < n)
{
*(s + i)  = x;
i++;
}
return (s);
}

/**
 * ffree - to make strings free
 * @b: string character
 */
void ffree(char **b)
{
char **a = b;
if (!b)
return;
while (*b)
free(*b++);
free(a);
}

/**
 * _realloc - to reallocates a memory
 * @ptr: void pointer
 * @old_size: integer
 * @new_size: integer
 * Return: Always 0 (Success)
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}
if (ptr == NULL)
ptr = malloc(new_size);
if (new_size == old_size)
return (ptr);
free(ptr);
ptr = malloc(new_size);
return (ptr);
}

