#include "main.h"

/***** Print pointer ****/

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List of Arguments
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, pad = ' ';
	int ind = BUFF_SIZE - 2, length = 2, pad_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[a], BUFF_SIZE - a - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, pad, extra_c, pad_start));
}

/**** Print Non Printable ***/

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Number of Chars to Print
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = 0, OffSet = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + OffSet] = str[a];
		else
			OffSet += append_hexa_code(str[a], buffer, a + OffSet);

		a++;
	}

	buffer[a + OffSet] = '\0';

	return (write(1, buffer, a + OffSet));
}

/**** Print Reverse ***/

/**
 * print_reverse - Prints reverse string.
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int a, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (a = 0; str[a]; a++)
		;

	for (a = a - 1; a >= 0; a--)
	{
		char z = str[a];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**** Print a String in ROT13 ***/

/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of argubnts
 * @buffer: Buffer Array to Handle Print
 * @flags:  Calculates Flags that are Active
 * @width: get width
 * @precision: Precision Specification
 * @size: Size Specifier
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char me;
	char *str;
	unsigned int a, b;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				me = out[b];
				write(1, &me, 1);
				count++;
				break;
			}
		}
		if (!in[b])
		{
			me = str[a];
			write(1, &me, 1);
			count++;
		}
	}
	return (count);
}
