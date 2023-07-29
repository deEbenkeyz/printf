#include "main.h"

/**
 * get_size - this calculates the siz_var to cast the argument
 * @format: this Formats string in which to print the arguments
 * @i: this Lists all arguments to be printed.
 *
 * Return: this return Precision
 */
int get_size(const char *format, int *i)
{
	int count_i = *i + 1;
	int siz_var = 0;

	if (format[count_i] == 'l')
		siz_var = S_LONG;
	else if (format[count_i] == 'h')
		siz_var = S_SHORT;

	if (siz_var == 0)
		*i = count_i - 1;
	else
		*i = count_i;

	return (siz_var);
}
