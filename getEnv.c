#include "shell.h"

/**
 * get_environ_mod - returns the string array copy of our environ_mod
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnv(info_table *inf)
{
	if (!inf->environ_mod || inf->changed_env)
	{
		inf->environ_mod = list_to_strings(inf->envi);
		inf->changed_env = 0;
	}

	return (inf->environ_mod);
}

/**
 * _unsetenv - Remove an environ_modment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @b: the string env var property
 */
int _unsetEnv(info_table *inf, char *b)
{
	list_table *nod = inf->envi;
	size_t i = 0;
	char *m;

	if (!nod || !b)
		return (0);

	while (nod)
	{
		m = starts_with(nod->str, b);
		if (m && *m== '=')
		{
			inf->changed_env = delete_node_at_index(&(inf->envi), i);
			i = 0;
			nod = inf->envi;
			continue;
		}
		nod = nod->next;
		i++;
	}
	return (inf->changed_env);
}

/**
 * _setenv - Initialize a new environ_modment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @b: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setEnv(info_table *inf, char *b, char *val)
{
	char *res= NULL;
	list_table *nod;
	char *p;

	if (!b || !val)
		return (0);

	res = malloc(_strlen(b) + _strlen(val) + 2);
	if (!res)
		return (1);
	_strcpy(res, b);
	_strcat(res, "=");
	_strcat(res, val);
	nod = inf->envi;
	while (nod)
	{
		p = starts_with(nod->str, b);
		if (p && *p == '=')
		{
			free(nod->str);
			nod->str = res;
			inf->changed_env = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(inf->envi), res, 0);
	free(res);
	inf->changed_env = 1;
	return (0);
}


