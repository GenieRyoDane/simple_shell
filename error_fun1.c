#include "shell.h"

/**
 * _ErraToi - convert ta caracter to hexadecimal number
 * @st: the string to be converted
 * Return: 0 if converted
 *       -1 oothewise
 */
int _ErraToi(char *st)
{
	int j = 0;
	unsigned long int res = 0;

	if (*st == '+')
	st++;
	for (j = 0;  st[j] != '\0'; j++)
	{
		if (st[j] >= '0' && st[j] <= '9')
		{
			res *= 10;
			res += (st[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * printError - prints an error message
 * @inf: the parameter & return inf struct
 * @esr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printError(info_table *inf, char *esr)
{
	_Eputs(inf->filename);
	_Eputs(": ");
	printD(inf->counter_line, STDERR_FILENO);
	_Eputs(": ");
	_Eputs(inf->argv[0]);
	_Eputs(": ");
	_Eputs(esr);
}

/**
 * printD - function prints a decimal (integer) number (bs 10)
 * @inp: the inp
 * @f: the filedescriptor to write to
 * Return: number of characters printed
 */
int printD(int inp, int f)
{
	int (*__putchar)(char) = _putchar;
	int i, ct = 0;
	unsigned int mia, curt;

	if (f == STDERR_FILENO)
		__putchar = _putchar;
	if (inp < 0)
	{
		mia = -inp;
		__putchar('-');
		ct++;
	}
	else
		mia = inp;
	curt = mia;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (mia / i)
		{
			__putchar('0' + curt / i);
			ct++;
		}
		curt %= i;
	}
	__putchar('0' + curt);
	ct++;

	return (ct);
}

/**
 * convNum - converter function
 * @num: number
 * @bs: bs
 * @fg: argument fg
 * Return: character
 */
char *convNum(long int num, int bs, int fg)
{
	static char *array;
	static char bf[50];
	char sn = 0;
	char *ptr;
	unsigned long n = num;

	if (!(fg & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sn = '-';

	}
	array = fg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &bf[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bs];
		n /= bs;
	} while (n != 0);

	if (sn)
		*--ptr = sn;
	return (ptr);
}

/**
 * remComents - replace '#' with '\0'
 * @bf: address of  string that  modify
 * Return: in all case 0;
 */
void remComents(char *bf)
{
	int j;

	for (j = 0; bf[j] != '\0'; j++)
		if (bf[j] == '#' && (!j || bf[j - 1] == ' '))
		{
			bf[j] = '\0';
			break;
		}
}
