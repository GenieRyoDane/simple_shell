#include "shell.h"
/**
 * if shell is correct the result will return 1 else the return is 0
 */
int interactive(info_t *info)
{
	return ( info->readfd <= 2 && isatty(STDIN_FILENO));
}

/**
 *function delimter
 */
int is_del(char d, char *del)
{
	while (*del)
		if (*del++ == d)return (1);
	return (0);
}

/**
 * function alphabetic that tcheaker if is a caracter
 */

int _isalphabetic(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * function _atoi that convert the string to char
 */

int _atoi(char *tab)
{
	int k,  flag = 1 , sign = 1 , output;
	unsigned int result = 0;

	for (k = 0;  tab[k] != '\0' && flag != 10; k++)
	{
		if (tab[k] == '-')
			sign *= -1;

		if (tab[k] >= '0' && tab[k] <= '9')
		{
			flag = 0;
			result *= 10;
			result += (tab[k] - '0');
		}
		else if (flag == 0)
			flag = 10;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

