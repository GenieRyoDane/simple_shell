#include "shell.h"

/**
 * addNode - add tolist
 * @heead: address of pointer to heead node
 * @stri: stri
 * @numero: node of history
 *
 * Return: taille de la liste
 */
list_table *addNode(list_table **heead, const char *stri, int numero)
{
	list_table *newheead;

	if (!heead)
		return (NULL);
	newheead = malloc(sizeof(list_table));
	if (!newheead)
		return (NULL);
	_memset((void *)newheead, 0, sizeof(list_table));
	newheead->numero = numero;
	if (stri)
	{
		newheead->stri = _strdup(stri);
		if (!newheead->stri)
		{
			free(newheead);
			return (NULL);
		}
	}
	newheead->next = *heead;
	*heead = newheead;
	return (newheead);
}

/**
 * addNodeEnd - additione dans la fin
 * @heead: address
 * @stri: stri champs de node
 * @numero:  utiliser pour historic
 *
 * Return: size of list
 */
list_table *addNodeEnd(list_table **heead, const char *stri, int numero)
{
	list_table *newNode, *node;

	if (!heead)
		return (NULL);

	node = *heead;
	newNode = malloc(sizeof(list_table));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_table));
	newNode->numero = numero;
	if (stri)
	{
		newNode->stri = _strdup(stri);
		if (!newNode->stri)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*heead = newNode;
	return (newNode);
}

/**
 * printListStri - prints only the stri element of a list_tablelinked list
 * @m: pointer to first node
 *
 * Return: size of list
 */
size_t printListStri(const list_table *m)
{
	size_t k = 0;

	while (m)
	{
		_puts(m->stri ? m->stri : "(nil)");
		_puts("\n");
		m = m->next;
		k++;
	}
	return (k);
}

/**
 * deleteNodeAtindexe - deletes node at given indexe
 * @heead: address of pointer to first node
 * @indexe: indexe of node to delete
 *
 * Return: 1  if true,  0 if false
 */
int deleteNodeAtindexe(list_table **heead, unsigned int indexe)
{
	list_table *node, *prev_node;
	unsigned int i = 0;

	if (!heead || !*heead)
		return (0);

	if (!indexe)
	{
		node = *heead;
		*heead = (*heead)->next;
		free(node->stri);
		free(node);
		return (1);
	}
	node = *heead;
	while (node)
	{
		if (i == indexe)
		{
			prev_node->next = node->next;
			free(node->stri);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes that contains in the  list
 * @heead_ptr: address of pointer to heead node
 *
 * Return: void
 */
void freeList(list_table **heead_ptr)
{
	list_table *nod, *nextNode, *heead;

	if (!heead_ptr || !*heead_ptr)
		return;
	heead = *heead_ptr;
	nod = heead;
	while (nod)
	{
		nextNode = nod->next;
		free(nod->stri);
		free(nod);
		nod = nextNode;
	}
	*heead_ptr = NULL;
}


