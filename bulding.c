#include "shell.h"

/**
 * _myExit - exits at the shell
 * @inf: Structure that contain arguments
 *  Return: exits  with a status 0
 *         when inf.argv[0] != "exit"
 */
int _myExit(info_table *inf)
{
	int checkExist;

	if (inf->argv[1])
	{
		checkExist = _erratoi(inf->argv[1]);
		if (checkExist == -1)
		{ /* check an exit arguement */
			inf->statu = 2;
			printf_errors(inf, "number is not a legal ");
			_Eputs(inf->argv[1]);
			_putchar('\n');
			return (1);
		}
		inf->error_number = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->error_number = -1;
	return (-2);
}

/**
 * _myCd - change directory
 * @inf: Structure contain a arguùments.
 *  Return: tend to  0
 */
int _myCd(info_table *inf)
{
	char *s, *dir, buffer[1024];
	int chdirRet;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd fail in this place<<\n");
	if (!inf->argv[1])
	{
		dir = _getEnv(inf, "HOME=");
		if (!dir)
		chdirRet = chdir((dir = _getEnv(inf, "PWD=")) ? dir : "/");
		else
			chdirRet = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-"))
	{
		if (!_getEnv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getEnv(inf, "OLDPWD=")), _putchar('\n');
		chdirRet = chdir((dir = _getEnv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirRet = chdir(inf->argv[1]);
	if (chdirRet == -1)
	{
		printf_errors(inf, " cd is forbiden");
		_Eputs(inf->argv[1]), _putchar('\n');
	}
	else
	{
		_setEnv(inf, "OLDPWD", _getEnv(inf, "PWD="));
		_setEnv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myHelp - help metho of the process
 * @inf:  structure contains arguments.
 *  Return: tend to  0
 */
int _myHelp(info_table *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("call of help method is correct \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}


