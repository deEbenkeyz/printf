#include "main.h"

/*** WRITE HANDLE ***/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buff_var: this is a buffer array for print
 * @flag_v:  this calculate all active flag_v .
 * @wid_var: get wid_var.
 * @prec_var: specifies prec_var
 * @siz_var:  specifies size
 *
 * Return: this returns number of all chars printed.
 */
int handle_write_char(char c, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{ /* char is stored at left and padding at buff_var's right */
	int i = 0;
	char padd = ' ';

	UNUSED(prec_var);
	UNUSED(siz_var);

	if (flag_v & F_ZERO)
		padd = '0';

	buff_var[i++] = c;
	buff_var[i] = '\0';

	if (wid_var > 1)
	{
		buff_var[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < wid_var - 1; i++)
			buff_var[BUFF_SIZE - i - 2] = padd;

		if (flag_v & F_MINUS)
			return (write(1, &buff_var[0], 1) +
					write(1, &buff_var[BUFF_SIZE - i - 1], wid_var - 1));
		else
			return (write(1, &buff_var[BUFF_SIZE - i - 1], wid_var - 1) +
					write(1, &buff_var[0], 1));
	}

	return (write(1, &buff_var[0], 1));
}

/** WRITE NUMBER **/
/**
 * write_number - Prints a string
 * @is_negative: List a of arguments
 * @ind: ind char types.
 * @buff_var: this is a buffer array for print
 * @flag_v:  this calculate all active flag_v
 * @wid_var: get wid_var.
 * @prec_var: specifies prec_var
 * @siz_var:  specifies size
 *
 * Return: this returns number of all chars printed.
 */
int write_number(int is_negative, int ind, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(siz_var);

	if ((flag_v & F_ZERO) && !(flag_v & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flag_v & F_PLUS)
		extra_ch = '+';
	else if (flag_v & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buff_var, flag_v, wid_var, prec_var,
		length, padd, extra_ch));
}

/**
 * write_num - this Writes a number using a buffer
 * @ind: Index at which the number starts on the buff_var
 * @buff_var: Buffer Variables
 * @flag_v: Flags Variable
 * @wid_var: wid_var variable
 * @prec: Precision specifier
 * @length: Specifies Number length
 * @padd: Padding char variable
 * @extra_c: Extra char variable
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buff_var[],
	int flag_v, int wid_var, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buff_var[ind] == '0' && wid_var == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buff_var[ind] == '0')
		buff_var[ind] = padd = ' '; /* wid_var is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buff_var[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (wid_var > length)
	{
		for (i = 1; i < wid_var - length + 1; i++)
			buff_var[i] = padd;
		buff_var[i] = '\0';
		if (flag_v & F_MINUS && padd == ' ')/* Assign extra char to left of buff */
		{
			if (extra_c)
				buff_var[--ind] = extra_c;
			return (write(1, &buff_var[ind], length) + write(1, &buff_var[1], i - 1));
		}
		else if (!(flag_v & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buff_var[--ind] = extra_c;
			return (write(1, &buff_var[1], i - 1) + write(1, &buff_var[ind], length));
		}
		else if (!(flag_v & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buff_var[--padd_start] = extra_c;
			return (write(1, &buff_var[padd_start], i - padd_start) +
				write(1, &buff_var[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buff_var[--ind] = extra_c;
	return (write(1, &buff_var[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buff_var
 * @buff_var: Array of chars variable
 * @flag_v: Flags specifiers variable
 * @wid_var: Width specifier variable
 * @prec_var: Precision specifier variable
 * @siz_var:  specifies size variable
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(siz_var);

	if (prec_var == 0 && ind == BUFF_SIZE - 2 && buff_var[ind] == '0')
		return (0); /* printf(".0d", 0)  no char must be printed */

	if (prec_var > 0 && prec_var < length)
		padd = ' ';

	while (prec_var > length)
	{
		buff_var[--ind] = '0';
		length++;
	}

	if ((flag_v & F_ZERO) && !(flag_v & F_MINUS))
		padd = '0';

	if (wid_var > length)
	{
		for (i = 0; i < wid_var - length; i++)
			buff_var[i] = padd;

		buff_var[i] = '\0';

		if (flag_v & F_MINUS) /* Assigning extra char to left of [buff_var>padd]*/
		{
			return (write(1, &buff_var[ind], length) + write(1, &buff_var[0], i));
		}
		else /* Assigning extra char to left of padding [padd>buff_var]*/
		{
			return (write(1, &buff_var[0], i) + write(1, &buff_var[ind], length));
		}
	}

	return (write(1, &buff_var[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buff_var: Arrays of chars
 * @ind: Index at which the number starts in the buff_var
 * @length: Length of number  variable
 * @wid_var: Width specifier variable
 * @flag_v: Flags specifier variable
 * @padd: Char representing the padding variable
 * @extra_c: Char representing extra char variable
 * @padd_start: Index at which padding should start variable
 *
 * Return: Number of written chars.
 */
int write_pointer(char buff_var[], int ind, int length,
	int wid_var, int flag_v, char padd, char extra_c, int padd_start)
{
	int i;

	if (wid_var > length)
	{
		for (i = 3; i < wid_var - length + 3; i++)
			buff_var[i] = padd;
		buff_var[i] = '\0';
		if (flag_v & F_MINUS && padd == ' ')/* Assigning extra char to buff_var */
		{
			buff_var[--ind] = 'x';
			buff_var[--ind] = '0';
			if (extra_c)
				buff_var[--ind] = extra_c;
			return (write(1, &buff_var[ind], length) + write(1, &buff_var[3], i - 3));
		}
		else if (!(flag_v & F_MINUS) && padd == ' ')/* extra char to buff_var all */
		{
			buff_var[--ind] = 'x';
			buff_var[--ind] = '0';
			if (extra_c)
				buff_var[--ind] = extra_c;
			return (write(1, &buff_var[3], i - 3) + write(1, &buff_var[ind], length));
		}
		else if (!(flag_v & F_MINUS) && padd == '0')/* extra char to padding all */
		{
			if (extra_c)
				buff_var[--padd_start] = extra_c;
			buff_var[1] = '0';
			buff_var[2] = 'x';
			return (write(1, &buff_var[padd_start], i - padd_start) +
				write(1, &buff_var[ind], length - (1 - padd_start) - 2));
		}
	}
	buff_var[--ind] = 'x';
	buff_var[--ind] = '0';
	if (extra_c)
		buff_var[--ind] = extra_c;
	return (write(1, &buff_var[ind], BUFF_SIZE - ind - 1));
}
