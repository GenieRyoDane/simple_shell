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
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rr = getLine(buffer, &l_p, stdin);
#else
		rr = _getLine(info, buffer, &l_p);
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
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain bufferfer */
	static size_t i, j, l;
	ssize_t r = 0;
	char **buffer_p = &(info->arg), *p;

	_putchar(buffer_FLUSH);
	r = input_buffer(info, &buffer, &l);
	if (r == -1) 
		return (-1);
	if (l)	/* wn bufferfer */
	{
		j = i; /* init ner position */
		p = buffer + i; /* get pourn */

		check_chain(info, buffer, &j, i, l);
		while (j < l) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* inc ';'' */
		if (i >= l) /* reachrfer? */
		{
			i = l = 0; /* reset poand lgth */
			info->cmd_buffer_type = CMD_NORM;
		}

		*buffer_p = p; /* pass back pmmand position */
		return (_strl(p)); /* return lommand */
	}

	*buffer_p = buffer; /* else notk bufferfer from _getline() */
	return (r); /* return lgth of bine() */
}

/**
 * read_buffer - reads a bufferfer
 * @info: parameter struct
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
	rr = read(inf->readfile, buffer, READ_buffer_SIZE);
	if (rr >= 0)
		*i = r;
	return (rr);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @pt: address of pointer to bufferfer, preallocated or NULL
 * @lgth: size of preallocated ptr bufferfer if not NULL
 *
 * Return: s
 */
int _getLine(info_table *inf, char **pt, size_t *lgth)
{
	static char buffer[READ_buffer_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *newp = NULL, *c;

	p = *pt;
	if (p && lgth)
		s = *lgth;
	if (i == l)
		i = l = 0;

	r = read_buffer(info, buffer, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : l;
	newp = _realloc(p, s, s ? s + k : k + 1);
	if (!newp) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(newp, buffer + i, k - i);
	else
		_strncpy(newp, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = newp;

	if (lgth)
		*lgth = s;
	*pt = p;
	return (s);
}

/**
 * s
 * @signum: 
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(buffer_FLUSH);
}


