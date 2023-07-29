#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @type_var: This lists all arguments
 * @buff_var: THis is a buffer array that manages prints
 * @flag_v:  this calculates all active flag_v variables
 * @wid_var: this get width variable
 * @prec_var: Specifies precisions
 * @siz_var: Specifies size
 * Return: This prints Number of chars
 */
int print_unsigned(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type_var, unsigned long int);

	num = convert_size_unsgnd(num, siz_var);

	if (num == 0)
		buff_var[i--] = '0';

	buff_var[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff_var[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buff_var, flag_v, wid_var, prec_var, siz_var));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @type_var: This lists all arguments
 * @buff_var: THis is a buffer array that manages prints
 * @flag_v:  this calculates all active flag_v variables
 * @wid_var: this get width variable
 * @prec_var: Specifies precisions
 * @siz_var: Specifies size
 * Return: This prints Number of chars
 */
int print_octal(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type_var, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid_var);

	num = convert_size_unsgnd(num, siz_var);

	if (num == 0)
		buff_var[i--] = '0';

	buff_var[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff_var[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flag_v & F_HASH && init_num != 0)
		buff_var[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buff_var, flag_v, wid_var, prec_var, siz_var));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @type_var: This lists all arguments
 * @buff_var: THis is a buffer array that manages prints
 * @flag_v:  this calculates all active flag_v variables
 * @wid_var: this get width variable
 * @prec_var: Specifies precisions
 * @siz_var: Specifies size
 * Return: This prints Number of chars
 */
int print_hexadecimal(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	return (print_hexa(type_var, "0123456789abcdef", buff_var,
		flag_v, 'x', wid_var, prec_var, siz_var));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @type_var: This lists all arguments
 * @buff_var: THis is a buffer array that manages prints
 * @flag_v:  this calculates all active flag_v variables
 * @wid_var: this get width variable
 * @prec_var: Specifies precisions
 * @siz_var: Specifies size
 * Return: This prints Number of chars
 */
int print_hexa_upper(va_list type_var, char buff_var[],
	int flag_v, int wid_var, int prec_var, int siz_var)
{
	return (print_hexa(type_var, "0123456789ABCDEF", buff_var,
		flag_v, 'X', wid_var, prec_var, siz_var));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @type_var: This lists all arguments
 * @map_to: Array of values to map the number to
 * @buff_var: THis is a buffer array that manages prints
 * @flag_v:  this calculates all active flag_v variables
 * @flag_ch: this calculates all active flag_v variables
 * @wid_var: this get width variable
 * @prec_var: Specifies precisions
 * @siz_var: Specifies size
 * @siz_var: Size specification
 * Return: This prints Number of chars
 */
int print_hexa(va_list type_var, char map_to[], char buff_var[],
	int flag_v, char flag_ch, int wid_var, int prec_var, int siz_var)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(type_var, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid_var);

	num = convert_size_unsgnd(num, siz_var);

	if (num == 0)
		buff_var[i--] = '0';

	buff_var[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff_var[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flag_v & F_HASH && init_num != 0)
	{
		buff_var[i--] = flag_ch;
		buff_var[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buff_var, flag_v, wid_var, prec_var, siz_var));
}
