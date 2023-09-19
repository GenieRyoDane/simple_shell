#include "shell.h"

/**
 * B_free - clean a pointer
 * @pr: adress of pointer that cleaned
 *
 * Return: 1 if empty, else 0.
 */
int B_free(void **pr)
{
	if (pr && *pr)
	{
		free(*pr);
		*pr = NULL;
		return (1);
	}
	return (0);
}


