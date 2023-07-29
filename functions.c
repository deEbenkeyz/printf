#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - This prints a character
 * @types_var: this Lists a of all arguments
 * @buf_var: this is a Buffer array to handle printing
 * @flag_v:  this Calculates all active flag_v in the code
 * @wid_var: this is a Width function
 * @prec_var: This specifies Precision
 * @siz_var: This is a Size specifier
 * Return: This returns the Number of chars printed
 */
int print_char(va_list types_var, char buf_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	char c = va_arg(types_var, int);

	return (handle_write_char(c, buf_var, flag_v, wid_var, prec_var, siz_var));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - This Prints a string
 * @types_var: this is a List a of arguments
 * @buf_var: this is a Buffer array to handle print
 * @flag_v:  this Calculates all active flag_v
 * @wid_var: This gets wid_var.
 * @prec_var: this species Precision specification
 * @siz_var: this is a Size specifier
 * Return: THis returns Number of chars to be printed
 */
int print_string(va_list types_var, char buf_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	int length = 0, i;
	char *str = va_arg(types_var, char *);

	UNUSED(buf_var);
	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(prec_var);
	UNUSED(siz_var);
	if (str == NULL)
	{
		str = "(null)";
		if (prec_var >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prec_var >= 0 && prec_var < length)
		length = prec_var;

	if (wid_var > length)
	{
		if (flag_v & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = wid_var - length; i > 0; i--)
				write(1, " ", 1);
			return (wid_var);
		}
		else
		{
			for (i = wid_var - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wid_var);
		}
	}

	return (write(1, str, length));
}
/***PRINT PERCENT SIGN ****/
/**
 * print_percent - this Prints a percent sign
 * @types_var: This is List a of arguments
 * @buf_var: a Buffer array to handle prints
 * @flag_v: this Calculates active flag_v
 * @wid_var: this get wid_var
 * @prec_var: this specifies Precision
 * @siz_var: this is a Size specifier
 * Return: this returns Number of chars printed
 */
int print_percent(va_list types_var, char buf_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	UNUSED(types_var);
	UNUSED(buf_var);
	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(prec_var);
	UNUSED(siz_var);
	return (write(1, "%%", 1));
}

/**** PRINT INT ****/
/**
 * print_int - FUnction prints Print int
 * @types_var: List a of arguments
 * @buf_var: lists Buffer array to handle print
 * @flag_v:  this Calculates active flag_v
 * @wid_var: this gets wid_var.
 * @prec_var: specifies Precision specification
 * @siz_var: Specifies Size
 * Return: this returns Number of chars printed
 */
int print_int(va_list types_var, char buf_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	int i = BUFF_SIZE - 2;
	int is_neg = 0;
	long int n = va_arg(types_var, long int);
	unsigned long int num;

	n = convert_size_number(n, siz_var);

	if (n == 0)
		buf_var[i--] = '0';

	buf_var[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}

	while (num > 0)
	{
		buf_var[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_neg, i, buf_var, flag_v, wid_var, prec_var, siz_var));
}

/**** PRINT BINARY ****/
/**
 * print_binary - Prints an unsigned number
 * @types_var: this is a List of arguments
 * @buf_var: this Buffer array to handle print
 * @flag_v:  this Calculates active flag_v
 * @wid_var: this gets wid_var.
 * @prec_var: Specifies Precision
 * @siz_var: Specifies Size
 * Return: Numbers of char printed.
 */
int print_binary(va_list types_var, char buf_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buf_var);
	UNUSED(flag_v);
	UNUSED(wid_var);
	UNUSED(prec_var);
	UNUSED(siz_var);

	n = va_arg(types_var, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
