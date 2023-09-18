#include "shell.h"

/**
 **_strncopy - copie strings
 *@d: the target string
 *@source: the home string
 *@l: the caracters that copied
 *Return: add two string
 */
char *_strncopy(char *d, char *source, int l)
{
	int m, n;
	char *sr = d;

	m = 0;
	while (source[m] != '\0' && m < l - 1)
	{
		d[m] = source[m];
		m++;
	}
	if (m < l)
	{
		n = m;
		while (n < l)
		{
			d[n] = '\0';
			n++;
		}
	}
	return (sr);
}

/**
 **_strnCat - add two string
 *@d: the 1 th  string
 *@source: the 2 th string
 *@l: the maximal bit used
 *Return: the add two strings
 */
char *_strnCat(char *d, char *source, int l)
{
	int m, n;
	char *sr = d;

	m = 0;
	n = 0;
	while (d[m] != '\0')
		m++;
	while (source[n] != '\0' && n < l)
	{
		d[m] = source[n];
		m++;
		n++;
	}
	if (n < l)
		d[m] = '\0';
	return (sr);
}

/**
 **_strChr - find a caracter in string
 *@sr: the converted string
 *@ch: the searched string
 *Return:  pointer of type caracter
 */
char *_strChr(char *sr, char ch)
{
	do {
		if (*sr == ch)
			return (sr);
	} while (*sr++ != '\0');

	return (NULL);
}


