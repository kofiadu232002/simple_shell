#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#define TOK_DELIM " \t\r\n\a"

#define INPUT_SIZE 200

#define PATH_SIZE 1024

#define ARG_SIZE 200

/**
 * struct info - A struct type tracting the status of function
 * @status: variable to hold status code
 */
typedef struct info
{
	int status;
} test;

void set_executable_name(char *name);

void display(char *ch, int lent);

ssize_t add_input(char *input);

int run_commandfile(char *command, char *argv, char *envp[]);

void handle_command_exit(int status, const char *command);

void tokenize_command(char *command, char **args);

int call_up(char *command, char *args[], char *argv, char **env);

int exec_withpath(char *command, char *args[], char **env);

void exitShell(int status);

int chk_cmd_before_fork(char *command);

int tocen_command(char *command, char *args[]);

char *s_strdup(const char *string);

int s_strlen(const char *string);

int s_strcspn(const char *string, const char *chr);

char *s_strcpy(char *dest_string, const char *src_String);

char *s_strchr(const char *string, int chr);

char *s_strcat(char *dest, const char *src);

int s_strcmp(const char *str1, const char *str2);

char *s_strstr(const char *haystack, const char *needle);

int s_strncmp(const char *s1, const char *s2, size_t n);

char *s_strtok(char *str, const char *delim);

int is_delimiter(char ch, const char *delim);

char *s_getenv(const char *string, char *envp[]);

int sep_cmd(const char *command, char *outcome[], int num);

char *handle_double_dollar(const char *cmd, char *envp[]);

void disable_comment(char *cmd);

int get_status_code(int status);

void int_to_string(int value, char *str, int size);


int execute_command(char *args[], int check, int *status,
		char *argv, char *envp[]);

void replace_status_variable(char *args[], int count, int *status);


int logical_operator(char *input, const char *delimiter,
char *result[]);

void remove_quote(char *input, char *result);

void signal_handler(int signal);

int check_cmd(char *mycmd);

char *_itoa(int num);

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t s_getline(char **lineptr, size_t *n, FILE *stream);
void *s_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int is_whitespace(char ch);
int is_word_start(char *str, int number);

char *handle_double_dollars(char *cmd, char *envp[]);
void handle_environment_variable(char *cmd, char *result, int *i,
int *b, char *envp[]);
void handle_double_dollar_internal(char *cmd, char *result, int *i, int *j);
char *get_environment_variable_value(char *var_name, char *envp[]);
char *get_process_id_string();
int s_isalnum(unsigned char c);
char *s_strndup(char *source, size_t n);

void logical_commands(char *copy, char *args[], int check,
int *status, char *argv, char *envp[]);
int whitespace(char *str);
int run_command(char *command, char *argv, char *envp[]);

void intToString(int num, char *str, int str_size);
void print_error(const char *command, char *argv);

#endif
