#include "shell.h"

/**
 * hashage - main shell loop
 * @inf: the parameter & return inf struct
 * @ar: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hashage(info_table *inf, char **ar)
{
int bulding_re = 0;
ssize_t rr = 0;

	while (rr != -1 && bulding_re != -2)
	{
		clean_information(inf);
		if (is_interact(inf))
			_puts("$ ");
		_eputChar(BUF_FLUSH);
		rr = get_in(inf);
		if (rr != -1)
		{
			set_info(inf, ar);
			bulding_re = finded_bulding(inf);
			if (bulding_re == -1)
				finded_comand(inf);
		}
		else if (is_interact(inf))
			_putchar('\n');
		freeInformation(inf, 0);
	}
	write_history(inf);
	freeInformation(inf, 1);
	if (!is_interact(inf) && inf->statu)
		exit(inf->statu);
	if (bulding_re == -2)
	{
		if (inf->error_number == -1)
			exit(inf->statu);
		exit(inf->error_number);
	}
	return (bulding_re);
}

/**
 * finded_bulding - finds a comman of dbulding
 * @inf: the parameter & return inf struct
 *
 * Return: -1 if bulding not exist,
 *			0 if bulding executed with sucess,
 *			1 if bulding exist but not sucess,
 *			-2 if bulding flags exit()
 */
int finded_bulding(info_table *inf)
{
	int i, buld_ret_in = -1;
	bulding_tab tablebul[] = {
		{"exit", _myExit},
		{"env", _myEnv},
		{"help", _myHelp},
		{"history", _myhistory},
		{"setenv", _mySetEnv},
		{"unsetenv", _myUnsetEnv},
		{"cd", _myCd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; tablebul[i].type; i++)
		if (_strcmp(inf->argv[0], tablebul[i].type) == 0)
		{
			inf->counter_line++;
			buld_ret_in = tablebul[i].func(inf);
			break;
		}
	return (buld_ret_in);
}

/**
 * finded_comand - finds a command  at the PATH
 * @inf:  inf struct
 *
 * Return: void
 */
void finded_comand(info_table *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->count_line_flag == 1)
	{
		inf->counter_line++;
		inf->count_line_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!is_del(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(inf, _getEnv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		forked_comand(inf);
	}
	else
	{
		if ((is_interact(inf) || _getEnv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			forked_comand(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->statu = 127;
			printf_errors(inf, "not found\n");
		}
	}
}

/**
 * forked_comand - forks a an exec thread to run cmd
 * @inf:  inf struct
 *
 * Return: void
 */
void forked_comand(info_table *inf)
{
	pid_t cchildPid;

	cchildPid = fork();
	if (cchildPid == -1)
	{
		perror("syntacx error:");
		return;
	}
	if (cchildPid == 0)
	{
		if (execve(inf->path, inf->argv, getEnv(inf)) == -1)
		{
			freeInformation(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->statu));
		if (WIFEXITED(inf->statu))
		{
			inf->statu = WEXITSTATUS(inf->statu);
			if (inf->statu == 126)
				printf_errors(inf, "permission is forbiden\n");
		}
	}
}


