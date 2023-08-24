#include "main.h"

/****** Print Unsigned Number *******/

/**
 * print_unsigned - Prints an unsigned number
 * @types: List of Arguments
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print.
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/******* Print Unsigned Number in Octal  ***/

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}

/**** Print Unsigned Number in Hexadecimal ******/

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/*** Print Unsigned Number in Upper Hexadecimal ***/

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/*** Print Hexadecimal Number in Lower or Upper case ***/

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of argubnts
 * @map_to: Array of values to map the number to
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * @size: Size specification
 * Return: Number of Chars to Print
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
