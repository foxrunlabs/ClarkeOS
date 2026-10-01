/*==============================================================================
  k_printf.c -> k_printf.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Kernel Printf Procedures
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  Includes
==============================================================================*/

#include <kernel/kernel.h>
#include <kernel/console.h>

#include <bool.h>
#include <varargs.h>

#include <system/types.h>


/*==============================================================================
  Constants
==============================================================================*/

#define ALTERNATE_FORM 0x01
#define SIGNED		   0x02


/*==============================================================================
  Static Function Prototypes (Internal Only)
==============================================================================*/

//static char *convert_number(char *, unsigned int, int);
static char *itoa(char *, unsigned int, int, uint8_t);


/*==============================================================================
  convert_number - convert a number to a specified base
--------------------------------------------------------------------------------
  Print the text equivalent of a <number> in the specified <base>. This is a
  recursive function.
==============================================================================*/
/*
static char *convert_number(char *buffer, unsigned int number, int base)
{
	int temp;
	static char hex_string[] = "0123456789abcdef";
			
	temp = number / base;
	
	if(temp > 0)
		buffer = convert_number(buffer, temp, base);
	
	*buffer++ = hex_string[number % base];
	
	return buffer;
}
*/

/*==============================================================================
  itoa - convert a number to a text string
--------------------------------------------------------------------------------
  Convert a <number>, of specified <base>, to a text string.
==============================================================================*/

static char *itoa(char *buffer, unsigned int number, int base, uint8_t flags)
{	
	char temp[11];
	char numbers[] = "0123456789abcdef";
	int i = 0;
	
	// Zero is just zero.
	if(number == 0)
	{
		*buffer++ = '0';
		return buffer;
	}
	
	// Check if the number is signed or not.
	if((flags & SIGNED) && ((signed)number < 0))
	{
		*buffer++ = '-';
		number *= -1;
	}
	
	// Check to see if we want the appropriate leading 0 or 0x for base 8 or 16.
	if(flags & ALTERNATE_FORM)
	{
		switch(base)
		{
			case 8:
				*buffer++ = '0';
				break;
			
			case 16:
				*buffer++ = '0';
				*buffer++ = 'x';
				break;
			
			default:
				break;
		}
	}
	
	// Convert the number to text from LSD to MSD.
	while(number)
	{
		temp[i++] = numbers[number % base];
		number /= base;
	}
	
	// Write the converted number to the text string in reverse order.
	while(i-- > 0)
	{
		*buffer++ = temp[i];
	}
	
	return buffer;
}


/*==============================================================================
  k_printf - output a formatted string to the screen
--------------------------------------------------------------------------------
  A basic form of the commonly used printf C standard library function.
==============================================================================*/

int k_printf(const char *format, ...)
{
	char buffer[1024];
	int i, count;
	va_list arglist;
	
	va_start(arglist, format);
	
	count = k_vsprintf(buffer, format, arglist);
	
	va_end(arglist);
	
	for(i = 0; i < count; i++)
		console_write(buffer[i]);
	
	return count;
}


/*==============================================================================
  k_vsprintf - output a formatted string to another string
--------------------------------------------------------------------------------
  A basic form of the vsprintf C standard library function.
==============================================================================*/

int k_vsprintf(char *buffer, const char *format, va_list arglist)
{
	uint8_t flags;
	bool process_flags;
	char *string;
	const char *temp_string;
	
	process_flags = true;
	flags = 0;
	string = buffer;
	
	while(*format)
	{
		if(*format == '%')
		{
			// Check if there are special flags
			while(process_flags)
			{
				switch(*(++format))
				{
					case '#':
						flags |= ALTERNATE_FORM;
						break;
					
					default:
						process_flags = false;
						break;
				}
			}
			
			switch(*format)
			{	
				// Character
				case 'c':
					*string = (char)va_arg(arglist, int);
					string++;
					break;
				
				// String
				case 's':
					temp_string = va_arg(arglist, const char *);
					
					while(*temp_string != 0)
					{
						*string = *temp_string;
						string++;
						temp_string++;
					}
					break;
				
				// Integers
				case 'd':
				case 'i':
					flags |= SIGNED;
				case 'u':
					string = itoa(string, va_arg(arglist, unsigned int), 10, flags);
					break;
										
				// Unsigned integer, hexadecimal
				case 'x':
					string = itoa(string, va_arg(arglist, unsigned int), 16, flags);
					break;
				
				case 'o':
					string = itoa(string, va_arg(arglist, unsigned int), 8, flags);
					break;
				
				// % character
				case '%':
					*string = '%';
					string++;
					break;
				
				default:
					break;
			}
		}
		else
		{
			*string = *format;
			string++;
		}

	process_flags = true;
	format++;
	}
	
	*string = 0;
	return (string - buffer);	// Calculate how many characters outputted.
}

