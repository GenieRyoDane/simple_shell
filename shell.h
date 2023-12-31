#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ_mod;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_of_str
{
	int numero;
	char *stri;
	struct list_of_str *next;
} list_table;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct infopass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int counter_line;
	int error_number;
	int count_line_flag;
	char *filename;
	list_table *envi;
	list_table *historic;
	list_table *alia;
	char **environ_mod;
	int changed_env;
	int statu;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_type_of_buffer; /* CMD_type ||, &&, ; */
	int readfile;
	int counthist;
} info_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct bulding
{
	char *type;
	int (*func)(info_table *);
} bulding_tab;

/* function of shell boucle.c */
int hashage(info_table *, char **);
int finded_bulding(info_table *);
void finded_comand(info_table *);
void forked_comand(info_table *);

/* toem_parser.c */
int is_cmd(info_table *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_table *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/*  func_errors methods */
void _Eputs(char *);
int _eputChar(char);
int _putFd(char c, int fd);
int _PutSfd(char *str, int fd);

/* function of string */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* function of string_fun1.c */
char *_strCpy(char *, char *);
char *_strDup(const char *);
void _puts(char *);
int _putchar(char);

/* exits_fun.c */
char *_strncopy(char *, char *, int);
char *_strnCat(char *, char *, int);
char *_strChr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free_memory_fun */
int B_free(void **);

/* the function of _atoi.c */
int is_interact(info_table *);
int is_del(char, char *);
int _isalphanum(int);
int _atoi(char *);

/*  function error 1 .c */
int _ErraToi(char *);
void printError(info_table *, char *);
int printD(int, int);
char *convNum(long int, int, int);
void remComents(char *);

/* function of buldding */
int _myExit(info_table *);
int _myCd(info_table *);
int _myHelp(info_table *);

/* toem_builtin1.c */
int _myhistory(info_table *);
int _myalias(info_table *);

/*getline function */
ssize_t get_in(info_table *);
int _getLine(info_table *, char **, size_t *);
void sigint_Handler(int);

/* function about information .c */
void clean_information(info_table *);
void set_info(info_table *, char **);
void freeInformation(info_table *, int);

/* function environ_mod.c */
char *_getEnv(info_table *, const char *);
int _myEnv(info_table *);
int _mySetEnv(info_table *);
int _myUnsetEnv(info_table *);
int _populateEnvList(info_table *);

/* function of env */
char **getEnv(info_table *);
int _unsetEnv(info_table *, char *);
int _setEnv(info_table *, char *, char *);

/* function of history  */
char *getHistoryFile(info_table *info);
int writeHistory(info_table *inf);
int readHistory(info_table *inf);
int buildHistoryList(info_table *inf, char *buffer, int countline);
int renuHisto(info_table *inf);

/* fucnction list table */
list_table *addNode(list_table **, const char *, int);
list_table *addNodeEnd(list_table **, const char *, int);
size_t printSlistStr(const list_table *);
int deleteNodeAtIndex(list_table **, unsigned int);
void freeList(list_table **);

/* toem_lists1.c */
size_t list_len(const list_table *);
char **list_to_strings(list_table *);
size_t print_list(const list_table *);
list_table *node_starts_with(list_table *, char *, char);
ssize_t get_node_index(list_table *, list_table *);

/* toem_vars.c */
int is_chain(info_table *, char *, size_t *);
void check_chain(info_table *, char *, size_t *, size_t, size_t);
int replace_alias(info_table *);
int replace_vars(info_table *);
int replace_string(char **, char *);

#endif
