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

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_of_str
{
	int num;
	char *str;
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
	unsigned int line_count;
	int err_num;
	int count_line_flag;
	char *filename;
	list_table *envi;
	list_table *historic;
	list_table *alia;
	char **environ;
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
typedef struct builtin
{
	char *type;
	int (*func)(info_table *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_table *, char **);
int find_builtin(info_table *);
void find_cmd(info_table *);
void fork_cmd(info_table *);

/* toem_parser.c */
int is_cmd(info_table *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_table *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* the function of _atoi.c */
int is_interact(info_table *);
int is_del(char, char *);
int _isalphanum(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_table *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_table *);
int _mycd(info_table *);
int _myhelp(info_table *);

/* toem_builtin1.c */
int _myhistory(info_table *);
int _myalias(info_table *);

/*toem_getline.c */
ssize_t get_input(info_table *);
int _getline(info_table *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_table *);
void set_info(info_table *, char **);
void free_info(info_table *, int);

/* toem_environ.c */
char *_getenv(info_table *, const char *);
int _myenv(info_table *);
int _mysetenv(info_table *);
int _myunsetenv(info_table *);
int populate_env_list(info_table *);

/* toem_getenv.c */
char **get_environ(info_table *);
int _unsetenv(info_table *, char *);
int _setenv(info_table *, char *, char *);

/* toem_history.c */
char *get_history_file(info_table *info);
int write_history(info_table *inf);
int read_history(info_table *inf);
int build_history_list(info_table *inf, char *buffer, int countline);
int renumber_history(info_table *inf);

/* toem_lists.c */
list_table *add_node(list_table **, const char *, int);
list_table *add_node_end(list_table **, const char *, int);
size_t print_list_str(const list_table *);
int delete_node_at_index(list_table **, unsigned int);
void free_list(list_table **);

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
