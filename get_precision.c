#include "main.h"

/**
 * get_precision - This function calculates the precision for displaying
 * @format: this is a formatted string variable that prints all arguments
 * @i: This is a List of all arguments that will be printed.
 * @list: this is a list of all arguments.
 *
 * Return: this returns precision_var.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int count_i = *i + 1;
	int precision_var = -1;

	if (format[count_i] != '.')
		return (precision_var);

	precision_var = 0;

	for (count_i += 1; format[count_i] != '\0'; count_i++)
	{
		if (is_digit(format[count_i]))
		{
			precision_var *= 10;
			precision_var += format[count_i] - '0';
		}
		else if (format[count_i] == '*')
		{
			count_i++;
			precision_var = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = count_i - 1;

	return (precision_var);
}
