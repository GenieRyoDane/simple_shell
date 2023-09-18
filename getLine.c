#include "shell.h"

/**
 * input_buffer - bufferfers chained commands
 * @inf:  struct
 * @buffer: address of bufferfer
 * @l: address of l var
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_table *inf, char **buffer, size_t *l)
{
	ssize_t rr = 0;
	size_t l_p = 0;

	if (!*l) /* if nothing left in the bufferfer, fill it */
	{
		/*bfree((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		rr = getLine(buffer, &l_p, stdin);
#else
		rr = _getLine(inf, buffer, &l_p);
#endif
		if (rr > 0)
		{
			if ((*buffer)[rr - 1] == '\n')
			{
				(*buffer)[rr - 1] = '\0'; /* remove trailing newline */
				rr--;
			}
			inf->count_line_flag = 1;
			remove_comments(*buffer);
			build_history_list(inf, *buffer, inf->counthist++);
			{
				*l = rr;
				inf->cmd_buffer = buffer;
			}
		}
	}
	return (rr);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_table *inf)
{
	static char *buffer; /* the ';' command chain bufferfer */
	static size_t i, j, l;
	ssize_t r = 0;
	char **buffer_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(inf, &buffer, &l);
	if (r == -1)
		return (-1);
	if (l)	/* wn bufferfer */
	{
		j = i; /* init ner position */
		p = buffer + i; /* get pourn */
		check_chain(inf, buffer, &j, i, l);
		while (j < l) /* boucle to final */
		{
			if (is_chain(inf, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* inc ';'' */
		if (i >= l) /* reachrfer? */
		{
			i = l = 0; /* reset poand lgth */
			inf->cmd_type_of_buffer = CMD_NORM;
		}

		*buffer_p = p; /* pass back pmmand position */
		return (_strlen(p)); /* return lommand */
	}

	*buffer_p = buffer; /* else notk bufferfer from _getline() */
	return (r); /* return lgth of bine() */
}

/**
 * read_buffer - reads a bufferfer
 * @inf: parameter struct
 * @buffer: bufferfer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_table *inf, char *buffer, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	rr = read(inf->readfile, buffer, READ_BUF_SIZE);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getLine - gets the next line of input from STDIN
 * @inf: parameter struct
 * @pt: address of pointer to bufferfer, preallocated or NULL
 * @lgth: size of preallocated ptr bufferfer if not NULL
 *
 * Return: s
 */
int _getLine(info_table *inf, char **pt, size_t *lgth)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *newp = NULL, *c;

	p = *pt;
	if (p && lgth)
		s = *lgth;
	if (i == l)
		i = l = 0;

	r = read_buffer(inf, buffer, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strChr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : l;
	newp = _realloc(p, s, s ? s + k : k + 1);
	if (!newp) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strnCat(newp, buffer + i, k - i);
	else
		_strncopy(newp, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = newp;

	if (lgth)
		*lgth = s;
	*pt = p;
	return (s);
}

/**
 * sigint_Handler - function that handl a sign
 * @signum: sign num
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


