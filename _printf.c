#include "main.h"

void print_buffer(char buffer[], int *buff_ind_var);

/**
 * _printf - This is a function for Printf
 * @format: This is variable called - format.
 * Return: Show all print_var chars.
 */
int _printf(const char *format, ...)
{
	int count_i, print_var = 0, printed_chars = 0;
	int flags_var, width_var, precision_var, size_var, buff_ind_var = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (count_i = 0; format && format[count_i] != '\0'; count_i++)
	{
		if (format[count_i] != '%')
		{
			buffer[buff_ind_var++] = format[count_i];
			if (buff_ind_var == BUFF_SIZE)
				print_buffer(buffer, &buff_ind_var);
			/* write(1, &format[count_i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind_var);
			flags_var = get_flags(format, &count_i);
			width_var = get_width(format, &count_i, list);
			precision_var = get_precision(format, &count_i, list);
			size_var = get_size(format, &count_i);
			++count_i;
			print_var = handle_print(format, &count_i, list, buffer,
				flags_var, width_var, precision_var, size_var);
			if (print_var == -1)
				return (-1);
			printed_chars += print_var;
		}
	}

	print_buffer(buffer, &buff_ind_var);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind_var: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind_var)
{
	if (*buff_ind_var > 0)
		write(1, &buffer[0], *buff_ind_var);

	*buff_ind_var = 0;
}
