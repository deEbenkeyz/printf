#include "main.h"

/**
 * get_width - This Calculates the width for print
 * @format: this Formats a string in which to print the arguments.
 * @i: This is a List of all arguments to be printed.
 * @list: this lists all arguments.
 *
 * Return: wid_var.
 */
int get_width(const char *format, int *i, va_list list)
{
	int count_i;
	int wid_var = 0;

	for (count_i = *i + 1; format[count_i] != '\0'; count_i++)
	{
		if (is_digit(format[count_i]))
		{
			wid_var *= 10;
			wid_var += format[count_i] - '0';
		}
		else if (format[count_i] == '*')
		{
			count_i++;
			wid_var = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = count_i - 1;

	return (wid_var);
}
