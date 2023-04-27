#include "shell.h"

/**
 * _strncpy - to copy string.
 * @dest: String destnation.
 * @src: the string source.
 * @n: the number of bytes to be copies
 * Return: Always 0 (Success).
 */

char *_strncpy(char *dest, char *src, int n)
{
int x, y;
x = 0;
y = 0;
while (src[x++])
y++;
for (x = 0; src[x] && x < n; x++)
dest[x] = src[x];
for (x = y; x < n; x++)
dest[x] = '\0';
return (dest);
}


/**
 * _strncat - to concatenate string.
 * @dest: The string to be concatinated.
 * @src: The string source.
 * @n: The number of bytes
 * Return: Always 0 (Success).
 */
char *_strncat(char *dest, char *src, int n)
{
int ind = 0, dlen = 0;
while (dest[ind++])
dlen++;
for (ind = 0; src[ind] && ind < n; ind++)
dest[dlen++] = src[ind];
return (dest);
}

/**
 * _strchr - locates a character
 * @s: string.
 * @c: character.
 * Return: Always 0 (Succes).
 */
char *_strchr(char *s, char c)
{
int i;
for (i = 0; s[i] >= '\0'; i++)
{
if (s[i] == c)
return (s + i);
}
return ('\0');
}
