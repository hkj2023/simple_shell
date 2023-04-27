#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * bfree - frees & NULL a pointer
 * @ptr: address of the pointer
 * Return: Always 0 (Success)
 */

int bfree(void **ptr)
{
if (ptr && *ptr)
{
bfree(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
