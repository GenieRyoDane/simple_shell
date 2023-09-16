#include "shell.h"
/**
 * if shell is correct the result will return 1 else the return is 0
 */
int is_interact(info_t *inf)
{
	return ( inf->readfd <= 2 && isatty(STDIN_FILENO));
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

int _isalphanum(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * function _atoi that convert the string to char
 * s is sign and f is a variable like a flag 
 * op is the outpout to the finction _atoi
 * res is variable which we affected to op
 */

int _atoi(char *tab)
{
	int k,  f = 1 , s = 1 , op;
	unsigned int res = 0;

	for (k = 0;  tab[k] != '\0' && f != 10; k++)
	{
		if (tab[k] == '-')
			s *= -1;

		if (tab[k] >= '0' && tab[k] <= '9')
		{
			f= 0;
			res *= 10;
			res += (tab[k] - '0');
		}
		else if (f == 0)
			f = 10;
	}

	if (s == -1)
		op = -res;
	else
		op = res;

	return (op);
}

