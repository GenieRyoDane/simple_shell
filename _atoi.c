#include "shell.h"
/**
 *is_interact - returns  will return 1 else the return is 0
 *@inf: is struct address
 *Return: 0 if not is in the interactive an 1 if intercative
 */

int is_interact(info_t *inf)
{
	return (inf->readfd <= 2 && isatty(STDIN_FILENO));
}

/**
 *is_del - returns the integr of delimter function
 *@d: is commapred to del is the incremented del
 *@del: is a pointer of caracter
 *Return: is equal a delimter then we return true else we return false
 */
int is_del(char d, char *del)
{
while (*del)
	if (*del++ == d)
		return (1);
return (0);
}

/**
 *_isalphanum -  function alphabetic that t cheaker if is a number or not
 * @d: is ASCCI  code of the letters is retur true or false
 * Return: true or false
 */

int _isalphanum(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - function atoi that convert the string to charter
 *@tab: is table of character
 *Return: integer returns
 */

int _atoi(char *tab)
{
	int k,  f = 1, s = 1, op;
	unsigned int res = 0;

	for (k = 0;  tab[k] != '\0' && f != 10; k++)
	{
		if (tab[k] == '-')
			s *= -1;

		if (tab[k] >= '0' && tab[k] <= '9')
		{	f = 0;
			res *= 10;
			res += (tab[k] - '0');
		}
		else if (f == 0)
			f = 10;
	}
	if (s == -1)
	{
		op = -res;
	}
	else
	{
		op = res;
	}
	return (op);
}
