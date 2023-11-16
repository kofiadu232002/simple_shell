#include "shell.h"

/**
 * main - main function Entry point
 * @argc: t keep count the number of argument
 * @argv: array to store the argument
 * @envp: the parent environment
 * Return: 0 for success 1 otherwise
 */
int main(int argc, char *argv[], char *envp[])
{
	char command[INPUT_SIZE];
	ssize_t input;
	char *cmd;
	int status;

	while (argc)
	{
		display("$ ", s_strlen("$ "));
		input = add_input(command);
		if (input == -1)
			continue;
		else if (input == 0)
		{
			display("\n", s_strlen("\n"));
			break;
		}

		disable_comment(command);
		cmd = handle_double_dollars(command, envp);
		status = run_command(cmd, argv[0], envp);

		free(cmd);
	}
	return (status);
}
