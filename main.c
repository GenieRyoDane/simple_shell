#include "shell.h"

/**
 * main - depart point
 * @n: arg  number
 * @v: arg vector or string
 *
 * Return: 0 in the best case, 1 in the case of errors
 */
int main(int n, char **v)
{
	info_table inf[] = { INFO_INIT };
	int fdd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdd)
		: "r" (fdd));

	if (n == 2)
	{
		fdd = open(v[1], O_RDONLY);
		if (fdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_Eputs(v[0]);
				_Eputs(": 0: Is closed ");
				_Eputs(v[1]);
				_putchar('\n');
				_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfile = fdd;
	}
	_populateEnvList(inf);
	readHistory(inf);
	hashage(inf, v);
	return (EXIT_SUCCESS);
}
