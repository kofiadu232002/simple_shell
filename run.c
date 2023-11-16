#include "shell.h"

/**
 * run_command - function for run_command
 * @user_command: the user input
 * @argv: the program name
 * @envp: parent environment
 * Return: status
 */
int run_command(char *user_command, char *argv, char *envp[])
{
	int i, status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *copy = strdup(user_command);
	char *token = s_strtok(user_command, ";\n");

	while (token != NULL)
	{
		if (!whitespace(token))
		{
			cmd_list[num_cmd] = token;
			num_cmd++;
		}
		token = s_strtok(NULL, ";\n");
	}

	for (i = 0; i < num_cmd; i++)
	{
		char *mycmd = cmd_list[i];
		char *args[ARG_SIZE];
		int check = tocen_command(mycmd, args);

		logical_commands(copy, args, check,
				&status, argv, envp);
	}
	free(copy);
	return (status);
}

/**
 * logical_operator - function to split logic operand
 * @input: user input
 * @delimiter: delimiter to sepperate user input
 * @result: where to store it
 * Return: the number of seperated command
 */
int logical_operator(char *input, const char *delimiter, char *result[])
{
	int num_parts = 0;
	char *token = s_strtok(input, delimiter);

	while (token != NULL)
	{
		result[num_parts] = token;
		num_parts++;
		token = s_strtok(NULL, delimiter);
	}
	return (num_parts);
}

/**
 * logical_commands - function to perform logical function
 * @copy: the command
 * @args: the argument
 * @check: to check the command for inbuilt
 * @last_status: the status code
 * @argv: the program name
 * @envp: parent environment
 * Return: void
 */
void logical_commands(char *copy, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	if (s_strstr(copy, "&&"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int parts = logical_operator(copy, "&&", cmd_parts);

		for (j = 0; j < parts; j++)
		{
			int part_check = tocen_command(cmd_parts[j], args);

			if (execute_command(args, part_check, last_status,
						argv, envp) != 0)
			{
				return;
			}
		}
	}
	else if (s_strstr(copy, "||"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int parts = logical_operator(copy, "||", cmd_parts);

		for (j = 0; j < parts; j++)
		{
			int part_check = tocen_command(cmd_parts[j], args);

			if (execute_command(args, part_check, last_status,
						argv, envp) == 0)
			{
				return;
			}
		}
	}
	else
	{
		execute_command(args, check, last_status, argv, envp);
	}
}

/**
 * whitespace - function to check for continuous whitespace
 * @str: the string to search for
 * Return: 0 if not all otherwise 1
 */
int whitespace(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isspace(str[i]))
			return (0);
	}
	return (1);
}
