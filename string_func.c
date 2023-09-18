#include "shell.h"

/**
 * _strlen - give the lenght
 * @k: the string
 *
 * Return: inumber of caracter of a string
 */
int _strlen(char *k)
{
	int j = 0;

	if (!k)
		return (0);

	while (*k++)
		j++;
	return (j);
}

/**
 * _strcmp - return true or falde
 * @k1: 1 string
 * @k2: 2 strig
 *
 * Return: integer  negatif or positve or equal
 */
int _strcmp(char *k1, char *k2)
{
	while (*k1 && *k2)
	{
		if (*k1 != *k2)
			return (*k1 - *k2);
		k1 = k1 + 1;
		k2 = k2 + 1;
	}
	if (*k1 == *k2)
		return (0);
	else
		return (*k1 < *k2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @hst: charcter
 * @nl: li bghina nl9w
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hst, const char *nl)
{
	while (*nl)
		if (*nl++ != *hst++)
			return (NULL);
	return ((char *)hst);
}

/**
 * _strcat - concaten string one and two
 * @home:  destination buffer
 * @target:  source buffer
 *
 * Return: pointer to  buffer
 */
char *_strcat(char *home, char *target)
{
	char *re = target;

	while (*home)
		home++;
	while (*target)
		*home++ = *target++;
	*home = *target;
	return (re);
}


