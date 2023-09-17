#include "shell.h"

/**
 * clean_information -  struct
 * @inf:  address
 */
void clean_information(info_table *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - struct info
 * @inf:  address
 * @v:  vector
 */
void set_info(info_table *inf, char **v)
{
	int i = 0;

	inf->fname = v[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (k = 0; inf->argv && inf->argv[k]; k++)
			;
		inf->argc = k;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * freeInformation - struct fields
 * @inf:  address
 * @kk:  1 if all field is free
 */
void freeInformation(info_table *inf, int kk)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (kk)
	{
		if (!inf->cmd_buffer)
			free(inf->arg);
		if (inf->env)
			free_list(&(info->env));
		if (inf->historic)
			free_list(&(info->historic));
		if (inf->alia)
			free_list(&(inf->alia));
		ffree(inf->environ_mod);
			inf->environ_mod = NULL;
		bfree((void **)info->cmd_buf);
		if (inf->readfile > 2)
			close(inf->readfile);
		_putchar(BUF_FLUSH);
	}
}


