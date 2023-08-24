#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @x: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *x, va_list list)
{
	int curr_x;
	int width = 0;

	for (curr_x = *x + 1; format[curr_x] != '\0'; curr_x++)
	{
		if (is_digit(format[curr_x]))
		{
			width *= 10;
			width += format[curr_x] - '0';
		}
		else if (format[curr_x] == '*')
		{
			curr_x++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*x = curr_x - 1;

	return (width);
}
