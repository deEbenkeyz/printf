#include "main.h"

/**
 * get_flags - This Calculates all active flags in the code
 * @format: This is a Formatted string that is to print the arguments
 * @i: This takes a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int counter_j, current_val;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_val = *i + 1; format[current_val] != '\0'; current_val++)
	{
		for (j = 0; FLAGS_CH[counter_j] != '\0'; counter_j++)
			if (format[current_val] == FLAGS_CH[counter_j])
			{
				flags |= FLAGS_ARR[counter_j];
				break;
			}

		if (FLAGS_CH[counter_j] == 0)
			break;
	}

	*i = current_val - 1;

	return (flags);
}

