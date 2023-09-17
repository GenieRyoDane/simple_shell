#include "shell.h"

/**
 * _myEnv - prints the current environment
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myEnv(info_table *inf)
{
	printSlistStr(inf->envi);
	return (0);
}

/**
 * _getEnv - gets the value of an environ variable
 * @inf: Structure containing potential arguments. Used to maintain
 * @fn: env var name
 * Rerurn: a character
 */
char *_getEnv(info_table *inf, const char *fn)
{
	list_table *nod = inf->envi;
	char *k;

	while (nod)
	{
		k = starts_with(nod->stri, fn);
		if (k && *k)
			return (k);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * _mySetEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mySetEnv(info_table *inf)
{
	if (inf->argc != 3)
	{
		_eputs("try to a correct number of args\n");
		return (1);
	}
	if (_setEnv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myUnsetEnv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _myUnsetEnv(info_table *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs("give a  big args.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetEnv(inf, inf->argv[i]);
	return (0);
}

/**
 * _populateEnvList - populates env linked list
 * @inf:  arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _populateEnvList(info_table *inf)
{
	list_table *nod = NULL;
	size_t i;

	for (i = 0; environ_mod[i]; i++)
		addNodeEnd(&nod, environ_mod[i], 0);
	inf->envi = nod;
	return (0);
}


