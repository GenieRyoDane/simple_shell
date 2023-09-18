#include "shell.h"

/**
 * getHistoryFile -  getter the file history
 * @inf:  struct param
 *
 * Return: a character that conatin the history file
 */

char *getHistoryFile(info_table *inf)
{
	char *bf, *dir;

	dir = _getEnv(inf, "HOME=");
	if (!dir)
		return (NULL);
	bf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_strCpy(bf, dir);
	_strcat(bf, "/");
	_strcat(bf, HIST_FILE);
	return (bf);
}

/**
 * writeHistory - append to exist file and created if doenst exist
 * @inf: the param struct
 *
 * Return: 1 if true ,  -1 other case
 */
int writeHistory(info_table *inf)
{
	ssize_t fid;
	char *filnum = getHistoryFile(inf);
	list_table *nod = NULL;

	if (!filnum)
		return (-1);

	fid = open(filnum, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filnum);
	if (fid == -1)
		return (-1);
	for (nod = inf->historic; nod; nod = nod->next)
	{
		_PutSfd(nod->stri, fid);
		_putFd('\n', fid);
	}
	_putFd(BUF_FLUSH, fid);
	close(fid);
	return (1);
}

/**
 * readHistory - reads history from file
 * @inf: the parameter struct
 *
 * Return: counthist on success, 0 otherwise
 */
int readHistory(info_table *inf)
{
	int i, last = 0, lc = 0;
	ssize_t fid, rdlen, fsize = 0;
	struct stat st;
	char *bf = NULL, *filnum = getHistoryFile(inf);

	if (!filnum)
		return (0);

	fid = open(filnum, O_RDONLY);
	free(filnum);
	if (fid == -1)
		return (0);
	if (!fstat(fid, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bf = malloc(sizeof(char) * (fsize + 1));
	if (!bf)
		return (0);
	rdlen = read(fid, bf, fsize);
	bf[fsize] = 0;
	if (rdlen <= 0)
		return (free(bf), 0);
	close(fid);
	for (i = 0; i < fsize; i++)
		if (bf[i] == '\n')
		{
			bf[i] = 0;
			buildHistoryList(inf, bf + last, lc++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(inf, bf + last, lc++);
	free(bf);
	inf->counthist = lc;
	while (inf->counthist-- >= HIST_MAX)
		deleteNodeAtIndex(&(inf->historic), 0);
	renuHisto(inf);
	return (inf->counthist);
}

/**
 * buildHistoryList - build a history to list
 * @inf: Struct that containt the information
 * @bf: bffer
 * @lc: the history lc, counthist
 *
 * Return: all case egal 0
 */
int buildHistoryList(info_table *inf, char *bf, int lc)
{
	list_table *nod = NULL;

	if (inf->historic)
		nod = inf->historic;
	addNodeEnd(&nod, bf, lc);

	if (!inf->historic)
		inf->historic = nod;
	return (0);
}

/**
 * renuHisto - after change we reconaize the historic file
 * @inf: Struct
 * Return: return integer that contains the counter list
 */
int renuHisto(info_table *inf)
{
	list_table *nod = inf->historic;
	int j = 0;

	while (nod)
	{
		nod->numero = j++;
		nod = nod->next;
	}
	return (inf->counthist = j);
}


