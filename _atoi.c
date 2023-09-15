#include "shell.h"

/**
 * interactive : if shell is interactive returns true
 * @info: structure address
 *
 * Return: 0 otherwise, 1 if interactive mode,
 */
int interactive(info_t *info)
{
	return ( info->readfd <= 2 && isatty(STDIN_FILENO));
}

/**
 * is_del : if character is a delimeter, check
 * @d: character to check
 * @del:  delimeter string
 * Return: 0 if false ,1 if true
 */
int is_del(char d, char *del)
{
	while (*del)
		if (*del++ == d)
			return (1);
	return (0);
}

/**
 *_isalphabetic - checks for alphabetic charac
 *@d: The charac to input
 *Return: 1 if c is alpha, 0 otherwise
 */

int _isalphabetic(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@st: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *st)
{
	int k,  flag = 0 , sign = 1 , output;
	unsigned int result = 0;

	for (k = 0;  st[k] != '\0' && flag != 2; k++)
	{
		if (st[k] == '-')
			sign *= -1;

		if (st[k] >= '0' && st[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (st[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

