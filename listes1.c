#include "shell.h"

/**
 * listLen - determines length of linked list
 * @ah: pointer to first nod
 *
 * Return: size of list
 */
size_t listLen(const list_table *ah)
{
	size_t k = 0;

	while (ah)
	{
		ah = ah->next;
		k++;
	}
	return (k);
}

/**
 * listToStrings - returns an array of strings of the list->str
 * @hd: pointer to first nod
 *
 * Return: array of strings
 */
char **listToStrings(list_table *hd)
{
	list_table *nod = hd;
	size_t m = listLen(hd), n;
	char **sts;
	char *st;

	if (!hd || !m)
		return (NULL);
	sts = malloc(sizeof(char *) * (m + 1));
	if (!sts)
		return (NULL);
	for (m = 0; nod; nod = nod->next, m++)
	{
		st = malloc(_strlen(nod->stri) + 1);
		if (!st)
		{
			for (n = 0; n < m; n++)
				free(sts[n]);
			free(sts);
			return (NULL);
		}

		st = _strCpy(st, nod->stri);
		sts[m] = st;
	}
	sts[m] = NULL;
	return (sts);
}


/**
 * printList - prints all elements of a list_t linked list
 * @kh: pointer to first nod
 * Return: size of list
 */
size_t printList(const list_table *kh)
{
	size_t j = 0;

	while (kh)
	{
		_puts(convNum(kh->numero, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(kh->stri ? kh->stri : "(nil)");
		_puts("\n");
		kh = kh->next;
		j++;
	}
	return (j);
}

/**
 * nodStartsWth - returns nod whose string starts with pref
 * @nod: pointer to list hd
 * @pref: string to match
 * @c: the next character after pref to match
 *
 * Return: match nod or null
 */
list_table *nodStartsWth(list_table *nod, char *pref, char c)
{
	char *pp = NULL;

	while (nod)
	{
		pp = starts_with(nod->stri, pref);
		if (pp && ((c == -1) || (*pp == c)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a nod
 * @hd: pointer to list hd
 * @nod: pointer to the nod
 *
 * Return: index of nod or -1
 */
ssize_t getNodeIndex(list_table *hd, list_table *nod)
{
	size_t k = 0;

	while (hd)
	{
		if (hd == nod)
			return (k);
		hd = hd->next;
		k++;
	}
	return (-1);
}
