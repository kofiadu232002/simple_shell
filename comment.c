#include "shell.h"

/**
 * disable_comment - this function removes comment
 * @command: the user command
 * Return: void
 */
void disable_comment(char *command)
{
	int number = 0;
	int tou = 0;

	while (command[number] != '\0')
	{
		if (command[number] == '"')
		{
			tou = !tou;
		}
		else if (!tou && command[number] == '#' && is_word_start(command, number))
		{
			command[number] = '\0';
			break;
		}
		number++;
	}
}

/**
 * int_to_string - function to convert integer to string
 * @value: the integer
 * @str: the string where to store
 * @size: the length
 * Return: void
 */
void int_to_string(int value, char *str, int size)
{
	int index = size - 1;

	str[index] = '\0';
	do {
		index--;
		str[index] = '0' + (value % 10);
		value /= 10;
	} while (value != 0 && index > 0);
}

/**
 * s_strndup - function to copy string base on number of memory
 * @source: where to copy from
 * @n: number of memory
 * Return: the copy memory
 */
char *s_strndup(char *source, size_t n)
{
	char *destination = NULL;
	size_t length = 0;
	size_t i;

	while (source[length] != '\0' && length < n)
	{
		length++;
	}

	destination = (char *)malloc(length + 1);

	if (destination)
	{
		for (i = 0; i < length; i++)
		{
			destination[i] = source[i];
		}

		destination[length] = '\0';
	}

	return (destination);
}

/**
 * s_isalnum - function to check if character is alphanumeric
 * @c: the character
 * Return: the absolute int
 */
int s_isalnum(unsigned char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || (c == '_'));
}
