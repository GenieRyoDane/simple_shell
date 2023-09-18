#include "shell.h"

/**
 *_Eputs - strin inputs
 * @st: the string that printed
 * Return: void
 */
void _Eputs(char *st)
{
	int j = 0;

	if (!st)
		return;
	while (st[j] != '\0')
	{
		_eputChar(st[j]);
		j++;
	}
}

/**
 * _eputChar - write  cd to stderr
 * @cd: The caracter that shows
 *
 * Return: 1 if true.
 * On the case of false, -1 is returned
 */
int _eputChar(char cd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (cd == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (cd != BUF_FLUSH)
		buff[j++] = cd;
	return (j);
}

/**
 * _putFd - write the character cd to the specified fd.
 * @cd: The text to be printed
 * @f: The address to write to is
 *Errno is set appropriately and -1 is returned in the event of an error.
 * Return: On success 1
 */
int _putFd(char cd, int f)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (cd == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(f, buff, j);
		j = 0;
	}
	if (cd != BUF_FLUSH)
		buff[j++] = cd;
	return (j);
}

/**
 *_PutSfd - prints an input sting
 * @s: the text to be printed
 * @f: The address to contact is
 *
 * Return: amount of characters entered
 */
int _PutSfd(char *s, int f)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putFd(*s++, f);
	}
	return (j);
}


