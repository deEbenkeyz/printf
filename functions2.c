#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @type_var: This lists all arguments
 * @buff_var: this is a Buffer array that handles print
 * @flag_v:  this Calculates all active flag_v
 * @wid_var: this get width function
 * @prec_var: Specifies Precision
 * @siz_var: Specifies Size
 * Return: returns all printed chars.
 */
int print_pointer(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(type_var, void *);

	UNUSED(wid_var);
	UNUSED(siz_var);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff_var[BUFF_SIZE - 1] = '\0';
	UNUSED(prec_var);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buff_var[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flag_v & F_ZERO) && !(flag_v & F_MINUS))
		padd = '0';
	if (flag_v & F_PLUS)
		extra_c = '+', length++;
	else if (flag_v & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buff_var[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buff_var, ind, length,
		wid_var, flag_v, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @type_var: This lists all arguments
 * @buff_var: this is a Buffer array that handles print
 * @flag_v:  this Calculates all active flag_v
 * @wid_var: this get width function
 * @prec_var: Specifies Precision
 * @siz_var: Specifies Size
 * Return: returns all printed chars
 */
int print_non_printable(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	int i = 0, offset = 0;
	char *str = va_arg(type_var, char *);

	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(prec_var);
	UNUSED(siz_var);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buff_var[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buff_var, i + offset);

		i++;
	}

	buff_var[i + offset] = '\0';

	return (write(1, buff_var, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @type_var: This lists all arguments
 * @buff_var: this is a Buffer array that handles print
 * @flag_v:  this Calculates all active flag_v
 * @wid_var: this get width function
 * @prec_var: Specifies Precision
 * @siz_var: Specifies Size
 * Return: returns all printed chars
 */

int print_reverse(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	char *str;
	int i, count = 0;

	UNUSED(buff_var);
	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(siz_var);

	str = va_arg(type_var, char *);

	if (str == NULL)
	{
		UNUSED(prec_var);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @type_var: This lists all arguments
 * @buff_var: this is a Buffer array that handles print
 * @flag_v:  this Calculates all active flag_v
 * @wid_var: this get width function
 * @prec_var: Specifies Precision
 * @siz_var: Specifies Size
 * Return: returns all printed chars
 */
int print_rot13string(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(type_var, char *);
	UNUSED(buff_var);
	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(prec_var);
	UNUSED(siz_var);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
