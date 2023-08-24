#include "main.h"

/******** Print Char ********/

/**
 * print_char - Prints a char
 * @types: List of Arguments
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: Width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char cc = va_arg(types, int);

	return (handle_write_char(cc, buffer, flags, width, precision, size));
}
/********* Print A String *********/

/**
 * print_string - Prints a string
 * @types: List of Arguments
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width.
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/****** Print Percentage Sign *********/

/**
 * print_percent - Prints a percent sign
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width.
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/****** Print Integer ********/

/**
 * print_int - Print int
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width.
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int t = va_arg(types, long int);
	unsigned long int num;

	t = convert_size_number(t, size);

	if (t == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)t;

	if (t < 0)
	{
		num = (unsigned long int)((-1) * t);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/******** Print Binary ******/

/**
 * print_binary - Prints an unsigned number
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width.
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, b, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	a[0] = x / y;
	for (b = 1; b < 32; b++)
	{
		y /= 2;
		a[b] = (x / y) % 2;
	}
	for (b = 0, sum = 0, count = 0; b < 32; b++)
	{
		sum += a[b];
		if (sum || b == 31)
		{
			char z = '0' + a[b];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
