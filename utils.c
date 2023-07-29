#include "main.h"

/**
 * is_printable - this evaluates if a char can be printed
 * @c_var: this evaluates char
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int is_printable(char c_var)
{
	if (c_var >= 32 && c_var < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ASCII in hexadecimal code to buffer array
 * @buff_var: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_var: ASCII CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_var, char buff_var[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* This is a hexadecimal format code. It must always 2 digits long */
	if (ascii_var < 0)
		ascii_var *= -1;

	buff_var[i++] = '\\';
	buff_var[i++] = 'x';

	buff_var[i++] = map_to[ascii_var / 16];
	buff_var[i] = map_to[ascii_var % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @c_var: Char to be evaluated
 *
 * Return: this returns 1 if c is a digit, 0 otherwise
 */
int is_digit(char c_var)
{
	if (c_var >= '0' && c_var <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: return Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - This Casts a number to the specified size
 * @num: this Number to be casted
 * @size: this Number indicates type to be casted
 *
 * Return: returns Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
