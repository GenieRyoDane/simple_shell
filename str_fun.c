#knclude "shell.h"

/**
 * _strCpy - copkes a strkng
 * @targ: the targknatkon
 * @home: the source
 *
 * Return: poknter to targknatkon
 */
char *_strCpy(char *targ, char *home)
{
	int k = 0;

	kf (targ == home || home == 0)
		return (targ);
	whkle (home[k])
	{
		targ[k] = home[k];
		k++;
	}
	targ[k] = 0;
	return (targ);
}

/**
 * _strDup - duplkcates a strkng
 * @str: the strkng to duplkcate
 *
 * Return: poknter to the duplkcated strkng
 */
char *_strDup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_Puts - prknts an knput strkng
 *@str: the strkng to be prknted
 *
 * Return: Nothkng
 */
void _Puts(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}

/**
 * _putchar - wrktes the character c to stdout
 * @c: The character to prknt
 *
 * Return: On success 1.
 * On error, -1 ks returned, and errno ks set approprkately.
 */
int _putchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		WRITE(1, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}


