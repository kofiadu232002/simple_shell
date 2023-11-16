#include "shell.h"

/**
 * tokenize_usercommand - function to tokenize user command from the argument
 * @user_command: the string passed from the console
 * @args: the array of pointer to strings to store the tokenized arguments
 * Return: void
 */
void tokenize_usercommand(char *user_command, char **args)
{
	int index;
	char *copy = s_strdup(user_command);
	char *mytok = s_strtok(copy, " ");

	for (index = 0; mytok != NULL; index++)
	{
		args[index] = mytok;
		mytok = s_strtok(NULL, " ");
	}
	args[index] = NULL;
}

/**
 * exec_withpath - function to execute command without path specifield
 * @command: the user command
 * @args: the flag of the command
 * @env: parent environment
 * Return: 0 for success
 */
int exec_withpath(char *command, char *args[], char **env)
{
	int index;
	int outcome = -1;
	char *path_token;
	char *command_path, *duplicate;

	command_path = getenv("PATH");

	if (command_path == NULL)
		return (-1);

	duplicate = s_strdup(command_path);
	if (duplicate == NULL)
		return (-1);

	path_token = s_strtok(duplicate, ":");

	for (index = 0; path_token != NULL; index++)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, path_token);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, command);

		outcome = execve(abs_path, args, env);

		if (outcome == -1)
			path_token = s_strtok(NULL, ":");
	}
	free(duplicate);

	return (outcome);
}

/**
 * call_up - function to execute the command
 * @command: the command pass
 * @args: the flag of the command
 * @argv: the program name
 * @envp: the parent environment
 * Return: 0 if success
 */
int call_up(char *command, char *args[], char *argv, char **envp)
{
	int outcome;

	if (s_strchr(command, '/') != NULL)
	{
		outcome = execve(command, args, envp);
		return (outcome);
	}
	else
	{
		if (check_cmd(args[0]) == 0)
		{
			print_error(args[0], argv);
			exit(127);
		}
		outcome = exec_withpath(command, args, envp);

		if (outcome == -1)
		{
			print_error(args[0], argv);
			exit(127);
		}

		return (outcome);
	}
}
