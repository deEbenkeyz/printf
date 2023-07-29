#include "main.h"
/**
 * handle_print - this Prints an argument based on its type
 * @fmt: this is a Formatted string that prints the arguments.
 * @list: this is a List of arguments printed.
 * @ind: ind variable
 * @buff_var: this is Buffer array to handle print.
 * @flags_var: this Calculates active flags_var
 * @width_var: get width_var.
 * @prec_var: Specifies Precision
 * @siz_var: get Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buff_var[],
	int flags_var, int width_var, int prec_var, int siz_var)
{
	int i, unknow_len = 0, chars_printed = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buff_var, flags_var, width_var, prec_var, siz_var));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width_var)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (chars_printed);
}
